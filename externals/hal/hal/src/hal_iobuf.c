/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_iobuf.c
 Author:        Łukasz Krzak, Dominik Rzepka
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL IOBuf module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include <stdlib.h>
#include <string.h>

#include "hal.h"

#if defined HAL_USE_OWN_MEMCPY && (HAL_USE_OWN_MEMCPY == 1)
static size_t IOBUF_memcpy(void *dst, const void* src, size_t size);
#else
#define IOBUF_memcpy memcpy
#endif

// -----------------------------------------------------------------------------
//  IOBUF_Create
// -----------------------------------------------------------------------------
IOBuf IOBUF_Create(iobuf_size_t elem_size, iobuf_size_t max_elem_count)
{
    IOBuf iobuf;

    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem_size);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, max_elem_count);

    if ((!elem_size) || (!max_elem_count)) {
        return NULL;
    }

    // memory allocation for a descriptor
    iobuf = (IOBuf)HEAP_Alloc(sizeof(IOBufDesc));
    // allocation check
    if (iobuf == NULL) {
        return (IOBuf)NULL;
    }

    // memory allocation for a buffer pool
    iobuf->mem_ptr = (void*)HEAP_Alloc(elem_size * max_elem_count);
    // allocation check
    if (iobuf->mem_ptr == NULL) {
        // allocation failed, the descriptor is no longer needed
        HEAP_Free(iobuf);
        return (IOBuf)NULL;
    }
    // default buffer setup
    iobuf->read_ptr = iobuf->mem_ptr;
    iobuf->write_ptr = iobuf->mem_ptr;
    iobuf->elem_count = 0;
    iobuf->max_elem_count = max_elem_count;
    iobuf->elem_size = elem_size;
    
    // retrun a handle to a newly created buffer
    return iobuf;

} /* IOBUF_Create */


// -----------------------------------------------------------------------------
//  IOBUF_Destroy
// -----------------------------------------------------------------------------
IOBuf IOBUF_Destroy(IOBuf iobuf)
{
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf->mem_ptr);

    if (iobuf) {
        if (iobuf->mem_ptr) {
        	// free memory pool
        	HEAP_Free(iobuf->mem_ptr);
        }
    	// make sure there is no unwanted data retention
    	memset(iobuf, 0x00, sizeof(IOBufDesc));
        // free the descriptor
    	HEAP_Free(iobuf);
    }

	return NULL;
} /* IOBUF_Destroy */


// -----------------------------------------------------------------------------
//  IOBUF_GetCount
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_GetCount(IOBuf iobuf)
{
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);

    if (iobuf) {
        return iobuf->elem_count;
    }

    return 0;

} /* IOBUF_GetCount */


// -----------------------------------------------------------------------------
//  IOBUF_GetSpace
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_GetSpace(IOBuf iobuf)
{
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);

    if (iobuf) {
        return iobuf->max_elem_count - iobuf->elem_count;
    }

    return 0;
} /* IOBUF_GetSpace */


// -----------------------------------------------------------------------------
//  IOBUF_GetSpace
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_GetSize(IOBuf iobuf)
{
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);

    if (iobuf) {
        return iobuf->max_elem_count;
    }

    return 0;

} /* IOBUF_GetSize */


// -----------------------------------------------------------------------------
//  IOBUF_Init
// -----------------------------------------------------------------------------
IOBuf IOBUF_Init(void* buf_ptr, iobuf_size_t buf_size, iobuf_size_t elem_size)
{
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, buf_ptr);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem_size);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, buf_size >= sizeof(IOBufDesc)+elem_size);

    if ((buf_ptr) && (elem_size) && (buf_size >= sizeof(IOBufDesc)+elem_size)) {
        // fill the descriptor with default data
        ((IOBuf)(buf_ptr))->mem_ptr = (void*)((uint8_t*)buf_ptr + sizeof(IOBufDesc));
        ((IOBuf)(buf_ptr))->write_ptr = ((IOBuf)(buf_ptr))->mem_ptr;
        ((IOBuf)(buf_ptr))->read_ptr = ((IOBuf)(buf_ptr))->mem_ptr;
        ((IOBuf)(buf_ptr))->elem_count = 0;
        ((IOBuf)(buf_ptr))->elem_size = elem_size;
        ((IOBuf)(buf_ptr))->max_elem_count = (iobuf_size_t)((buf_size - sizeof(IOBufDesc))/elem_size);

        // return a pointer to the descriptor
        return (IOBuf)buf_ptr;
    }

	return  NULL;
} /* IOBUF_Init */


// -----------------------------------------------------------------------------
//  IOBUF_ReadNextFragment
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_ReadNextFragment(IOBuf iobuf, iobuf_size_t fragment_size, void** next_fragment_ptr, iobuf_size_t* next_fragment_size)
{	
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, next_fragment_ptr);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, next_fragment_size);

	if ((iobuf_size_t)0 == (iobuf_size_t)fragment_size) {
		return (iobuf_size_t)0;
	}
	
	CORE_EnterCritical();
	
	if (iobuf->elem_count){
		//buffer not empty

		*next_fragment_ptr = iobuf->read_ptr;

		if (fragment_size > iobuf->elem_count){
			// desired data size greater or equal than buffer content length
			// truncate
			fragment_size = iobuf->elem_count;
		}

		if ((uint8_t*)(iobuf->read_ptr) + (fragment_size*iobuf->elem_size) <= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) {
			// the fragment fits completely, before the buffer wraps around
			iobuf->read_ptr = (void*)(((uint8_t*)iobuf->read_ptr) + fragment_size*iobuf->elem_size);
		} else {
			//the fragment doesn't fit, before the buffer wraps around
			fragment_size = iobuf->max_elem_count - (((size_t)iobuf->read_ptr - (size_t)iobuf->mem_ptr) / iobuf->elem_size);
			iobuf->read_ptr = iobuf->mem_ptr;
		}	
		iobuf->elem_count -= fragment_size;
	} else {
		// buffer full
		fragment_size = 0;
	}

	*next_fragment_size = fragment_size;		
		
	CORE_ExitCritical();

	return *next_fragment_size;
} /* IOBUF_ReadNextFragment */


// -----------------------------------------------------------------------------
//  IOBUF_WriteNextFragment
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_WriteNextFragment(IOBuf iobuf, iobuf_size_t fragment_size, void** next_fragment_ptr, iobuf_size_t* next_fragment_size)
{
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, next_fragment_ptr);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, next_fragment_size);

	if ((iobuf_size_t)0 == (iobuf_size_t)fragment_size) {
		return (iobuf_size_t)0;
	}
	
	CORE_EnterCritical();
	
	if (iobuf->elem_count < iobuf->max_elem_count){
		//buffer not full
		
		*next_fragment_ptr = iobuf->write_ptr;
		
		if (fragment_size > iobuf->max_elem_count - iobuf->elem_count){
			// desired data size greater or equal than buffer content length
			// truncate
			fragment_size = iobuf->max_elem_count - iobuf->elem_count;
		}
		
	    if ((uint8_t*)(iobuf->write_ptr) + (fragment_size*iobuf->elem_size) <= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) {
	    	// the fragment fits completely, before the buffer wraps around
	    	iobuf->write_ptr = (void*)(((uint8_t*)iobuf->write_ptr) + fragment_size*iobuf->elem_size);
		} else {
			//the fragment doesn't fit, before the buffer wraps around
			fragment_size = iobuf->max_elem_count - (((size_t)iobuf->write_ptr - (size_t)iobuf->mem_ptr) / iobuf->elem_size);
			iobuf->write_ptr = iobuf->mem_ptr;
		}	
		iobuf->elem_count += fragment_size;
	} else {
		// buffer full
		fragment_size = 0;
	}

	*next_fragment_size = fragment_size;

	CORE_ExitCritical();

	return fragment_size;
} /* IOBUF_WriteNextFragment */ 


// -----------------------------------------------------------------------------
//  IOBUF_Read
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_Read(IOBuf iobuf, void* data, iobuf_size_t elem_count)
{
    iobuf_size_t i;
    
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, data);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem_count);

    if ((!iobuf) || (!data) || (!elem_count)) {
        return 0;
    }
    if ((!iobuf->mem_ptr) || (!iobuf->read_ptr) || (!iobuf->elem_size)) {
        return 0;
    }

    CORE_EnterCritical();

    // underrun check
    if (elem_count > iobuf->elem_count) {
    	// underrun, truncate
    	elem_count = iobuf->elem_count;
    }
    
    if ((uint8_t*)(iobuf->read_ptr) + (elem_count*iobuf->elem_size) <= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) { 
    	// the data reads completely before the buffer wraps around 
    	// just one copy operation needed
    	i = elem_count*iobuf->elem_size;
    	IOBUF_memcpy(data, iobuf->read_ptr, i);
    	iobuf->read_ptr = (void*)(((uint8_t*)iobuf->read_ptr) + i);
    } else {
    	// the data read will cause the buffer to wrap around
    	// two copy operations are needed
    	i = (iobuf_size_t)((uint8_t*)iobuf->mem_ptr + (iobuf->max_elem_count*iobuf->elem_size) - (uint8_t*)iobuf->read_ptr);
    	IOBUF_memcpy(data, iobuf->read_ptr, i);
    	IOBUF_memcpy((void*)((uint8_t*)data+i), iobuf->mem_ptr, (elem_count)*iobuf->elem_size - i);
    	iobuf->read_ptr = (void*)(((uint8_t*)iobuf->mem_ptr) + (elem_count)*iobuf->elem_size - i);
    }
    // update iobuf pointers
    iobuf->elem_count -= elem_count;
    
    if ((uint8_t*)iobuf->read_ptr == (uint8_t*)iobuf->mem_ptr + (iobuf->max_elem_count*iobuf->elem_size)) {
        iobuf->read_ptr = iobuf->mem_ptr;
    }

    CORE_ExitCritical();
    
    return elem_count;

} /* IOBUF_Read */


// -----------------------------------------------------------------------------
//  IOBUF_Write
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_Write(IOBuf iobuf, const void* data, iobuf_size_t elem_count)
{
    iobuf_size_t i;

    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, data);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem_count);

    if ((!iobuf) || (!data) || (!elem_count)) {
        return 0;
    }
    if ((!iobuf->mem_ptr) || (!iobuf->write_ptr) || (!iobuf->elem_size)) {
        return 0;
    }
        
    CORE_EnterCritical();

    // overflow check
    if (elem_count + iobuf->elem_count > iobuf->max_elem_count) {
    	// overflow, truncate
    	elem_count = iobuf->max_elem_count - iobuf->elem_count;
    }
        
    //if (iobuf->wrap_cnt >= elem_count) {
    if ((uint8_t*)(iobuf->write_ptr) + (elem_count*iobuf->elem_size) <= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) { 
    	// the data fits completely before the buffer wraps around 
    	// just one copy operation needed
    	i = elem_count*iobuf->elem_size;
    	IOBUF_memcpy(iobuf->write_ptr, data, i);
    	iobuf->write_ptr = (void*)(((uint8_t*)iobuf->write_ptr) + i);
    } else {
    	// the data will cause the buffer to wrap around
    	// two copy operations are needed
    	i = (iobuf_size_t)((uint8_t*)iobuf->mem_ptr + (iobuf->max_elem_count*iobuf->elem_size) - (uint8_t*)iobuf->write_ptr);
    	IOBUF_memcpy(iobuf->write_ptr, data, i);
    	IOBUF_memcpy(iobuf->mem_ptr, (void*)((uint8_t*)data+i), (elem_count)*iobuf->elem_size - i);
    	iobuf->write_ptr = (void*)(((uint8_t*)iobuf->mem_ptr) + (elem_count)*iobuf->elem_size - i);
    }
    
    // update iobuf pointers
    iobuf->elem_count += elem_count;

    if ((uint8_t*)iobuf->write_ptr == (uint8_t*)iobuf->mem_ptr + (iobuf->max_elem_count*iobuf->elem_size)) {
        iobuf->write_ptr = iobuf->mem_ptr;
    }

    CORE_ExitCritical();
    
    return elem_count;
    
} /* IOBUF_Write */ 


// -----------------------------------------------------------------------------
//  IOBUF_ReadFast
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_ReadFast(IOBuf iobuf, void* elem)
{    
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem);

    if (iobuf->elem_count) {
		// read one element
		IOBUF_memcpy(elem, iobuf->read_ptr, iobuf->elem_size);
		if ((uint8_t*)(iobuf->read_ptr) + iobuf->elem_size >= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) { 
			// buffer wraps around
			iobuf->read_ptr = iobuf->mem_ptr;
		} else {
			// no wrap yet, just forward the read pointer
			iobuf->read_ptr = (void*)(((uint8_t*)iobuf->read_ptr) + iobuf->elem_size);
		}
		iobuf->elem_count--;
		return 1;
    }
    
    return 0;
	
} /* IOBUF_ReadFast */


// -----------------------------------------------------------------------------
//  IOBUF_WriteFast
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_WriteFast(IOBuf iobuf, const void* elem)
{    
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem);

    if (iobuf->elem_count < iobuf->max_elem_count) {
		// write one element
    	IOBUF_memcpy(iobuf->write_ptr, elem, iobuf->elem_size);
		if ((uint8_t*)(iobuf->write_ptr) + iobuf->elem_size >= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) { 
			// buffer wraps around
			iobuf->write_ptr = iobuf->mem_ptr;
		} else {
			// no wrap yet, just forward the read pointer
			iobuf->write_ptr = (void*)(((uint8_t*)iobuf->write_ptr) + iobuf->elem_size);
		}
		iobuf->elem_count++;
		return 1;
    }
    
    return 0;
	
} /* IOBUF_WriteFast */


// -----------------------------------------------------------------------------
//  IOBUF_Clear
// -----------------------------------------------------------------------------
void IOBUF_Clear(IOBuf iobuf)
{
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);

    if (!iobuf) {
        return;
    }
    
    CORE_EnterCritical();
    
    iobuf->elem_count = 0;
    iobuf->read_ptr = iobuf->mem_ptr;
    iobuf->write_ptr = iobuf->mem_ptr;
    
    CORE_ExitCritical();
	
} /* IOBUF_Clear */


// -----------------------------------------------------------------------------
//  IOBUF_Peek
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_Peek(IOBuf iobuf, void* data, iobuf_size_t elem_count)
{
    iobuf_size_t i;
    
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, data);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem_count);

    if ((!iobuf) || (!data) || (!elem_count)) {
        return 0;
    }
    if ((!iobuf->mem_ptr) || (!iobuf->read_ptr) || (!iobuf->elem_size)) {
        return 0;
    }

    CORE_EnterCritical();

    // underrun chceck
    if (elem_count > iobuf->elem_count) {
    	// underrun, truncate
    	elem_count = iobuf->elem_count;
    }
    
    if ((uint8_t*)(iobuf->read_ptr) + (elem_count*iobuf->elem_size) <= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) { 
    	// the data reads completely before the buffer wraps around 
    	// just one copy operation needed
    	i = elem_count*iobuf->elem_size;
    	IOBUF_memcpy(data, iobuf->read_ptr, i);
    } else {
    	// the data read will cause the buffer to wrap around
    	// two copy operations are needed
    	i = (iobuf_size_t)((uint8_t*)iobuf->mem_ptr + (iobuf->max_elem_count*iobuf->elem_size) - (uint8_t*)iobuf->read_ptr);
    	IOBUF_memcpy(data, iobuf->read_ptr, i);
    	IOBUF_memcpy((void*)((uint8_t*)data+i), iobuf->mem_ptr, (elem_count)*iobuf->elem_size - i);
    }

    CORE_ExitCritical();
    
    return elem_count;

} /* IOBUF_Peek */


// -----------------------------------------------------------------------------
//  IOBUF_Move
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_Move(IOBuf dst_iobuf, IOBuf src_iobuf, iobuf_size_t elem_count)
{
    iobuf_size_t d;
    void* dst_space;

    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, dst_iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, src_iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem_count);

    if ((!dst_iobuf) || (!src_iobuf) || (!elem_count)) {
        return 0;
    }
    if ((!src_iobuf->mem_ptr) || (!src_iobuf->write_ptr) || (!src_iobuf->elem_size)) {
        return 0;
    }
    if ((!dst_iobuf->mem_ptr) || (!dst_iobuf->write_ptr) || (!dst_iobuf->elem_size)) {
        return 0;
    }
        
    CORE_EnterCritical();
    
    // truncate elem_count if needed
    if (elem_count > dst_iobuf->max_elem_count - dst_iobuf->elem_count) {
    	// destination buffer doesn't have enough space
    	elem_count = dst_iobuf->max_elem_count - dst_iobuf->elem_count;
    }
    if (elem_count > src_iobuf->elem_count) {
    	// source buffer doesn't have enough data
    	elem_count = src_iobuf->elem_count;
    }

    dst_space = NULL;
    // allocate space in the destination buffer
   	IOBUF_WriteNextFragment(dst_iobuf, elem_count, &dst_space, &d);
   	if (dst_space) {
   		// move source data into the allocated buffer
   		IOBUF_Read(src_iobuf, dst_space, d);
   	
   		if (d < elem_count) {
   			// the write buffer wrapped around
   			// allocate additional space in the destination buffer
   			IOBUF_WriteNextFragment(dst_iobuf, elem_count-d, &dst_space, &d);
   			// move source data into the allocated buffer
   			if (dst_space) {
   				IOBUF_Read(src_iobuf, dst_space, elem_count-d);
   			}
   		}
   	} else {
   		elem_count = 0;
   	}

    CORE_ExitCritical();

    return elem_count;

} /* IOBUF_Move */ 


// -----------------------------------------------------------------------------
//  IOBUF_Remove
// -----------------------------------------------------------------------------
iobuf_size_t IOBUF_Remove(IOBuf iobuf, iobuf_size_t elem_count)
{
    iobuf_size_t i;

    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, iobuf);
    DIAG7_ASSERT(DIAG_DEFAULT_CHANNEL, elem_count);

    if ((!iobuf) || (!elem_count)) {
        return 0;
    }
    if ((!iobuf->mem_ptr) || (!iobuf->read_ptr) || (!iobuf->elem_size)) {
        return 0;
    }

    CORE_EnterCritical();

    // underrun check
    if (elem_count > iobuf->elem_count) {
    	// underrun, truncate
    	elem_count = iobuf->elem_count;
    }

    if ((uint8_t*)(iobuf->read_ptr) + (elem_count*iobuf->elem_size) <= ((uint8_t*)iobuf->mem_ptr) + (iobuf->max_elem_count*iobuf->elem_size)) {
    	// the data reads completely before the buffer wraps around
    	i = elem_count*iobuf->elem_size;
    	iobuf->read_ptr = (void*)(((uint8_t*)iobuf->read_ptr) + i);
    } else {
    	// the data read will cause the buffer to wrap around
    	i = (iobuf_size_t)((uint8_t*)iobuf->mem_ptr + (iobuf->max_elem_count*iobuf->elem_size) - (uint8_t*)iobuf->read_ptr);
    	iobuf->read_ptr = (void*)(((uint8_t*)iobuf->mem_ptr) + (elem_count)*iobuf->elem_size - i);
    }
    // update iobuf pointers
    iobuf->elem_count -= elem_count;

    if ((uint8_t*)iobuf->read_ptr == (uint8_t*)iobuf->mem_ptr + (iobuf->max_elem_count*iobuf->elem_size)) {
        iobuf->read_ptr = iobuf->mem_ptr;
    }

    CORE_ExitCritical();

    return elem_count;

} /* IOBUF_Remove */


#if defined HAL_USE_OWN_MEMCPY && (HAL_USE_OWN_MEMCPY == 1)

// We're using own implementation of memcpy

static size_t IOBUF_memcpy(void *dst, const void* src, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++) {
		((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
	}

	return i;
}
#endif


/*! \file hal_iobuf.c
    \brief General purpose ring buffer

 */


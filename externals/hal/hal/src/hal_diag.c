/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_diag.c
 Author:        Lukasz Krzak, Dominik Rzepka, Piotr Wojtowicz
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL diagnostic module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


#include <string.h>
#include <stdarg.h>
#include "hal.h"

#ifndef HAL_DIAG_MAX_CHANNELS
// default maximum number of diagnostic channels
#define HAL_DIAG_MAX_CHANNELS 									4
#endif

#ifndef HAL_DIAG_USE_ERROR_BUFFERING
/// Enable error buffering by default. 0 disables error buffering capabilities od the DIAG module
#define HAL_DIAG_USE_ERROR_BUFFERING						1
#endif

#ifndef HAL_DIAG_ERROR_BUFFER_SIZE
/// This definition controls how may error descriptions can fit into error buffer, when error buffering is enabled. Must be greater than 0
#define HAL_DIAG_ERROR_BUFFER_SIZE							30
#endif

#ifndef HAL_DIAG_USE_ERROR_DESCRIPTIONS
/// Enables (1) or disables (0) error descriptions
#define HAL_DIAG_USE_ERROR_DESCRIPTIONS						1
#endif

#ifndef HAL_DIAG_USE_ERROR_TIME_STAMPS
/// Enables (1) or disables (0) error time stamps
#define HAL_DIAG_USE_ERROR_TIME_STAMPS						1
#endif


#ifndef HAL_DIAG_LOCK_TIMEOUT
/// Set to default 1s timeout
#define HAL_DIAG_LOCK_TIMEOUT								1000
#endif

#ifndef HAL_DIAG_NL_MODE
#define HAL_DIAG_NL_MODE									0
#endif

/** Diagnostic channel description structure. */
typedef struct {
	/// determines if the channel is active (1) or not (0)
	sig_atomic_t active;
	/// diagnostic detail level (0 means lowest detail)
	uint8_t level;
	/// IODevice used by this channel
	IODevice iodev;
	/// Clock source for this channel
	uint32_t (*time)(void);
} DIAG_ChannelDesc;

/** error descriptor structure. */
typedef struct 
{
	/// diagnostic channel
	int channel;
	/// error number
	uint16_t error_no;
	/// line of code from which the notification was called
	uint32_t code_line;
	/// user supplied data attached to the error
	void* user_data;
	/// pointer to the error description string
	const char* description;
#if(HAL_DIAG_USE_ERROR_TIME_STAMPS)
	/// time at which the condition ocured
	uint64_t time;
#endif
} DIAG_ErrorDesc;

/** 
 *  User-defined error handler function.
 *
 *  \param channel
 *  \param error_no
 *  \param code_line
 *  \param user_data
 *  \param description 
*/
static int (*DIAG_error_handler)(int channel, uint16_t error_no, uint16_t code_line, void* user_data, const char* description) = NULL;

// list of diagnostic channels
static DIAG_ChannelDesc DIAG_channel[HAL_DIAG_MAX_CHANNELS];


#if defined HAL_DIAG_USE_ERROR_BUFFERING && (HAL_DIAG_USE_ERROR_BUFFERING == 1)
// stuff used only when error buffering is enabled

// error buffer
IOBUF_DECLARE(DIAG_error_buf, HAL_DIAG_ERROR_BUFFER_SIZE + 1, sizeof(DIAG_ErrorDesc));

#endif // HAL_DIAG_USE_ERROR_BUFFERING


#define DIAG_IS_CHANNEL_ACTIVE(channel)			(((channel) >= 0) && ((channel) < HAL_DIAG_MAX_CHANNELS) && (DIAG_channel[channel].active))

// -----------------------------------------------------------------------------
//  DIAG_Init
// -----------------------------------------------------------------------------
void DIAG_Init(void)
{
	int i;

	// initialize all local variables to default state
	DIAG_error_handler = NULL;

	for (i = 0; i < HAL_DIAG_MAX_CHANNELS; i++) {
		DIAG_channel[i].active = 0;
		DIAG_channel[i].iodev = NULL;
		DIAG_channel[i].time = NULL;
	}

#if defined HAL_DIAG_USE_ERROR_BUFFERING && (HAL_DIAG_USE_ERROR_BUFFERING == 1)
	// clear error buffer
	IOBUF_Clear(&DIAG_error_buf);
#endif
} /* DIAG_Init */


// -----------------------------------------------------------------------------
//  DIAG_Deinit
// -----------------------------------------------------------------------------
void DIAG_Deinit(void)
{
	// actually do the same job as with init
	DIAG_Init();

} /* DIAG_Deinit */


// -----------------------------------------------------------------------------
//  DIAG_SetOutputDevice
// -----------------------------------------------------------------------------
HALRESULT DIAG_SetOutputDevice(int channel, IODevice iodevice)
{
	if ((channel >= 0) && (channel < HAL_DIAG_MAX_CHANNELS)) {
		// channel number within bounds
		DIAG_channel[channel].iodev = iodevice;
		// all OK
		return HALRESULT_OK;
	}

	return HALRESULT_INVALID_DIAG_CHANNEL_NUMBER;

} /* DIAG_SetOutputDevice */ 


// -----------------------------------------------------------------------------
//  DIAG_GetOutputDevice
// -----------------------------------------------------------------------------
IODevice DIAG_GetOutputDevice(int channel)
{
	if ((channel >= 0) && (channel < HAL_DIAG_MAX_CHANNELS)) {
		// channel number within bounds
		return DIAG_channel[channel].iodev;
	}

	return NULL;

} /* DIAG_GetOutputDevice */


// -----------------------------------------------------------------------------
//  DIAG_ActivateChannel
// -----------------------------------------------------------------------------
HALRESULT DIAG_ActivateChannel(int channel)
{
	if ((channel >= 0) && (channel < HAL_DIAG_MAX_CHANNELS)) {
		// channel number within bounds
		DIAG_channel[channel].active = 1;
		// all OK
		return HALRESULT_OK;
	}

	return HALRESULT_INVALID_DIAG_CHANNEL_NUMBER;

} /* DIAG_ActivateChannel */


// -----------------------------------------------------------------------------
//  DIAG_DeactivateChannel
// -----------------------------------------------------------------------------
HALRESULT DIAG_DeactivateChannel(int channel)
{
	if ((channel >= 0) && (channel < HAL_DIAG_MAX_CHANNELS)) {
		// channel number within bounds
		DIAG_channel[channel].active = 0;
		// all OK
		return HALRESULT_OK;
	}

	return HALRESULT_INVALID_DIAG_CHANNEL_NUMBER;

} /* DIAG_DeactivateChannel */


// -----------------------------------------------------------------------------
//  DIAG_SetClockSource
// -----------------------------------------------------------------------------
HALRESULT DIAG_SetClockSource(int channel, uint32_t (*clk_src)(void))
{
	if ((channel >= 0) && (channel < HAL_DIAG_MAX_CHANNELS)) {
		// channel number within bounds
		DIAG_channel[channel].time = clk_src;
		// all OK
		return HALRESULT_OK;
	}

	return HALRESULT_INVALID_DIAG_CHANNEL_NUMBER;

} /* DIAG_SetClockSource */


// -----------------------------------------------------------------------------
//  DIAG_Log
// -----------------------------------------------------------------------------
void DIAG_Log(int channel, const char * str, ...)
{
    va_list vl;
    size_t s,i;
    union printable_t {
        int     	 	i;
		unsigned int 	u;
        float   		f;
        char    		c;
        char   			*s;
    } printable;
    IODevice iodev;

    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active

		// get output IODevice associated with the specified diagnostic channel
		iodev = DIAG_channel[channel].iodev;
	
		if (iodev) {
			// channel has an associated IODevice

			// init variable argument list, starting after 'str' parameter
			va_start( vl, str );
	
			// go through the string, until 0x00 is found
			s = 0;
			for (i = 0; str[i] != 0x00; i++ ) {
				if (str[i] == '%') {
					// '%' character was found - print all characters parsed until now
					IODEV_Write(iodev, str+s, i-s, 0);
					s = i;
					// check argument
					switch (str[i+1]) {
						case 'd':
							printable.i = va_arg(vl, int);
							DIAG_LogINT(channel, printable.i, 10);
							// skip "%d"
							i++;
							s+=2;
							break;
						case 'u':
							printable.i = va_arg(vl, int);
							DIAG_LogUINT(channel, printable.i, 10);
							// skip "%u"
							i++;
							s+=2;
							break;
						case 'f':
							//printable.f = va_arg(vl, float);
							//DIAG_LogFLOAT(printable.f, 8);
							// skip "%f"
							i++;
							s+=2;
							break;
						case 'c':
							printable.c = va_arg(vl, int);
							DIAG_LogINT(channel, printable.i, 10);
							// skip "%c"
							i++;
							s+=2;
							break;
						case 's':
							printable.s = va_arg(vl, char*);
							DIAG_LogMsg(channel, printable.s);
							// skip "%s"
							i++;
							s+=2;
							break;
						case '%':
							IODEV_Write(iodev, str+i, 1, 0);
							// skip "%%"
							i++;
							s+=2;
							break;
						default:
							break;
					} // switch
				} // if '%'
			} // for

			if (i-s > 0) {
				// print remaining characters
				IODEV_Write(iodev, str+s, i-s, 0);
			}

			va_end(vl);

		} // if (iodev)

    } // if channel is active

} /* DIAG_Log */


// -----------------------------------------------------------------------------
//  DIAG_LogChar
//------------------------------------------------------------------------------
void DIAG_LogChar(int channel, char character)
{
    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active
    	if (DIAG_channel[channel].iodev) {
    		// channel has an associated IODevice
    		IODEV_Write(DIAG_channel[channel].iodev, (void*)&character, 1, 0);
    	}
    }
} /* DIAG_LogChar */


// -----------------------------------------------------------------------------
//  DIAG_LogINT
// -----------------------------------------------------------------------------
void DIAG_LogINT(int channel, int32_t value, uint8_t base)
{
	int32_t i, size;
	int32_t x, digit; // digit value
	int neg = 0;
	// handy buffer
	char buf[32];
    IODevice iodev;

    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active

		// get output IODevice associated with the specified diagnostic channel
		iodev = DIAG_channel[channel].iodev;

		if (iodev) {
			// channel has an associated IODevice

			//check sign
			if (value < 0){
				buf[0] = '-';
				value = -value;
				size = 2;
				neg = 1;
			} else {
				size = 1;
			}

			//compute number of digits
			digit = base;
			for (; value >= digit; size++)
			{
				x = digit * base;
				if (digit > x){
					//overflow - 0xFFFFFFFF reached
					size++;
					break;
				} else
					digit = x;
			}

			//convert
			x = 1;
			for (i = 1; size - i >= neg; i++) {
				digit = (value / x) % base;
				buf[size - i] = '0' + (char)digit + (digit > 9) * ('A' - 10 - '0');
				x *= base;
			}

			IODEV_Write(iodev, buf, size, 0);
		}
    }
} /* DIAG_LogINT */


// -----------------------------------------------------------------------------
//  DIAG_LogUINT
// -----------------------------------------------------------------------------
void DIAG_LogUINT(int channel, uint32_t value, uint8_t base)
{
	int32_t i, size;
	uint32_t x, digit;
	// handy buffer
	char buf[32];
    IODevice iodev;
		
    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active

		// get output IODevice associated with the specified diagnostic channel
		iodev = DIAG_channel[channel].iodev;

		if (iodev) {
			// channel has an associated IODevice
			//compute number of digits
			digit = base;
			for (size = 1; value >= digit; size++)
			{
				x = digit * base;
				if (digit > x){
					//overflow - 0xFFFFFFFF reached
					size++;
					break;
				} else
					digit = x;
			}

			//convert
			x = 1;
			for (i = 1; size - i >= 0; i++) {
				digit = (value / x) % base;
				buf[size - i] = '0' + (char)digit + (digit > 9) * ('A' - 10 - '0');
				x *= base;
			}

			buf[size] = 0x00;

			IODEV_Write(iodev, buf, size, 0);
		}
    }
} /* DIAG_LogUINT */


// -----------------------------------------------------------------------------
//  DIAG_LogMsg
// -----------------------------------------------------------------------------
void DIAG_LogMsg(int channel, const char* msg)
{
    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active
    	if (DIAG_channel[channel].iodev) {
    		// channel has an associated IODevice
        	IODEV_Write(DIAG_channel[channel].iodev, (void*)msg, strlen(msg), 0);
    	}
    }
} /* DIAG_LogMsg */


// -----------------------------------------------------------------------------
//  DIAG_LogNL
// -----------------------------------------------------------------------------
void DIAG_LogNL(int channel)
{
    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active
    	if (DIAG_channel[channel].iodev) {
#if (HAL_DIAG_NL_MODE == 0)
    		IODEV_Write(DIAG_channel[channel].iodev, "\n", 1, 0);
#endif
#if (HAL_DIAG_NL_MODE == 1)
    		IODEV_Write(DIAG_channel[channel].iodev, "\n\r", 2, 0);
#endif
    	}
    }
} /* DIAG_LogNL */


// -----------------------------------------------------------------------------
//  DIAG_LogHeader
// -----------------------------------------------------------------------------
void DIAG_LogHeader(int channel, const char* module)
{
	if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
		// channel is active
		if (DIAG_channel[channel].iodev) {
			// channel has an associated IODevice
			if (DIAG_channel[channel].time) {
				// channel has an associated clock source
				TXTDEV_WriteUINT(DIAG_channel[channel].iodev, DIAG_channel[channel].time(), 10);
				IODEV_Write(DIAG_channel[channel].iodev, " ", 1, 0);
			}
			IODEV_Write(DIAG_channel[channel].iodev, (void*)module, strlen(module), 0);
			IODEV_Write(DIAG_channel[channel].iodev, ": ", 2, 0);
		}
	}
} /* DIAG_LogHeader */


// -----------------------------------------------------------------------------
//  DIAG_LogFLOAT
// -----------------------------------------------------------------------------
void DIAG_LogFLOAT(int channel, float value, int precision)
{
	IODevice iodev;

    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active
    	iodev = DIAG_channel[channel].iodev;
    	if (iodev) {
    		// channel has an associated IODevice
			DIAG_LogINT(channel, (int32_t)value, 10);
			value = value - (int32_t)value;
			if (precision > 0) {
				while (precision--) {
					value *= 10;
				}
			}
			if ((int32_t)value) {
				DIAG_LogChar(channel, '.');
				DIAG_LogINT(channel, (int32_t)value, 10);
			}
    	}
	}
} /* DIAG_LogFLOAT */


// -----------------------------------------------------------------------------
//  DIAG_LogData
// -----------------------------------------------------------------------------
void DIAG_LogData(int channel, uint8_t* data, size_t size, int base, int spacing, const char* space)
{
	IODevice iodev;
	size_t i;

    if (DIAG_IS_CHANNEL_ACTIVE(channel)) {
    	// channel is active
    	iodev = DIAG_channel[channel].iodev;
    	if (iodev) {
    		// channel has an associated IODevice
			if (data) {
				// data is not-NULL
				for (i = 0; i < size; ) {
					if ((base == 16) && (data[i] < 16)) {
						IODEV_Write(iodev, "0", 1, 0);
					}
					TXTDEV_WriteUINT(iodev, data[i], base);
					i++;

					if (((i % spacing) == 0) && (space)) {
						TXTDEV_WriteString(iodev, space);
					}
				}
			} else {
				// NULL data
				TXTDEV_WriteString(iodev, "NULL");
			}
    	}
    }
} /* DIAG_LogData */


// -----------------------------------------------------------------------------
//  DIAG_LogIOBuf
// -----------------------------------------------------------------------------
void DIAG_LogIOBuf(int channel, IOBuf iobuf, int indent)
{
	int i;

	for (i=0; i < indent; i++) {
		DIAG_LogChar(channel, ' ');
	}
	DIAG_LogMsg(channel, "elem_size = ");
	DIAG_LogINT(channel, iobuf->elem_size, 10);
	DIAG_LogMsg(channel, ", max_elem_count = ");
	DIAG_LogINT(channel, iobuf->max_elem_count, 10);
	DIAG_LogMsg(channel, ", elem_count = ");
	DIAG_LogINT(channel, iobuf->elem_count, 10);
	DIAG_LogNL(channel);
	for (i=0; i < indent; i++) {
		DIAG_LogChar(channel, ' ');
	}
	DIAG_LogMsg(channel, "mem_ptr = 0x");
	DIAG_LogUINT(channel, (size_t)iobuf->mem_ptr, 16);
	DIAG_LogMsg(channel, ", read_ptr = 0x");
	DIAG_LogUINT(channel, (size_t)iobuf->read_ptr, 16);
	DIAG_LogMsg(channel, ", write_ptr = 0x");
	DIAG_LogUINT(channel, (size_t)iobuf->write_ptr, 16);
	DIAG_LogNL(channel);

} /* DIAG_LogIOBuf */


// -----------------------------------------------------------------------------
//  DIAG_ProcError
// -----------------------------------------------------------------------------
static void DIAG_ProcError(DIAG_ErrorDesc* error)
{
	IODevice iodev;

    // process error
    if ((DIAG_error_handler) && (0 == DIAG_error_handler(error->channel, error->error_no, error->code_line, error->user_data, error->description))) {
        return;
    }
    if (DIAG_IS_CHANNEL_ACTIVE(error->channel)) {
    	// channel at wich the error was reported is active
    	iodev = DIAG_channel[error->channel].iodev;
    	if (iodev) {
    		// channel has an associated IODevice
    		DIAG7_ASSERT_AND_EXECUTE(DIAG_DEFAULT_CHANNEL, 0 == IODEV_Lock(iodev, HAL_DIAG_LOCK_TIMEOUT)) {
    			// lock successful
				TXTDEV_WriteString(iodev, "ERROR: ");
				if (error->description) {
					// there is an error description
					TXTDEV_WriteString(iodev, error->description);
					TXTDEV_WriteNL(iodev);
				}
				TXTDEV_WriteString(iodev, " ErrorNo: ");
				TXTDEV_WriteUINT(iodev, error->error_no, 10);
				TXTDEV_WriteString(iodev, " Channel: ");
				TXTDEV_WriteUINT(iodev, error->channel, 10);
				TXTDEV_WriteString(iodev, " Line: ");
				TXTDEV_WriteUINT(iodev, error->code_line, 10);
#if(HAL_DIAG_USE_ERROR_TIME_STAMPS)
				TXTDEV_WriteString(iodev, " Time: <TODO>");
#endif
				TXTDEV_WriteNL(iodev);
				IODEV_Unlock(iodev);
    		} // if (IODEV_Lock)
		} // if (iodev)
    } // if (channel active)
} /* DIAG_ProcError */


// -----------------------------------------------------------------------------
//  DIAG_ReportError
// -----------------------------------------------------------------------------
void DIAG_ReportError(int channel, uint16_t error_no, uint32_t code_line, void* user_data, const char* description)
{
#if (HAL_DIAG_USE_ERROR_BUFFERING)
	size_t buf_space;
#endif
    DIAG_ErrorDesc error;
    
#if (HAL_DIAG_USE_ERROR_BUFFERING)
    // buffered mode
    buf_space = IOBUF_GetSpace(&DIAG_error_buf);
	if (buf_space > 1) {
		error.channel = channel;
		error.error_no = error_no;
		error.code_line = code_line;
		error.user_data = user_data;
		error.description = description;
#if(HAL_DIAG_USE_ERROR_TIME_STAMPS)
		error.time = CORE_GetSystemTime();
#endif
		IOBUF_Write(&DIAG_error_buf, &error, 1);
    } else {
        // no free space in the buffer, warn the user
	    if (buf_space) {
		    error.channel = DIAG_DEFAULT_CHANNEL;
		    error.error_no = 0;
		    error.code_line = (uint16_t)__LINE__;
		    error.user_data = 0;
		    error.description = "DIAG error buffer overrun!";
#if(HAL_DIAG_USE_ERROR_TIME_STAMPS)
		    error.time = CORE_GetSystemTime();
#endif
		    IOBUF_Write(&DIAG_error_buf, &error, 1);
        }
    }
#else 
    // non-buffered mode
    error.channel = channel;
    error.error_no = error_no;
    error.code_line = code_line;
    error.user_data = user_data;
    error.description = description;
#if(HAL_DIAG_USE_ERROR_TIME_STAMPS)
    error.time = CORE_GetSystemTime();
#endif
    DIAG_ProcError(&error);
#endif
} /* DIAG_ReportError */


// -----------------------------------------------------------------------------
//  DIAG_ProcessErrors
// -----------------------------------------------------------------------------
uint32_t DIAG_ProcessErrors(uint32_t max_error_count)
{
#if defined HAL_DIAG_USE_ERROR_BUFFERING && (HAL_DIAG_USE_ERROR_BUFFERING == 1)
	size_t count;
	DIAG_ErrorDesc error;
	
	count = IOBUF_GetCount(&DIAG_error_buf);
	
	while ((count) && (max_error_count)) {
		IOBUF_Read(&DIAG_error_buf, &error, 1);
        DIAG_ProcError(&error);
		count--;
		max_error_count--;
	}
	return (uint32_t)IOBUF_GetCount(&DIAG_error_buf);

#endif // HAL_DIAG_USE_ERROR_BUFFERING

	return 0;

} /* DIAG_ProcessErrors */


// -----------------------------------------------------------------------------
//  DIAG_SetErrorHandler
// -----------------------------------------------------------------------------
void DIAG_SetErrorHandler(int (*error_handler)(int, uint16_t, uint16_t, void*, const char*))
{
	DIAG_error_handler = error_handler;
} /* DIAG_SetErrorHandler */





/*! \file hal_diag.c
    \brief HAL diagnostic tools

 */


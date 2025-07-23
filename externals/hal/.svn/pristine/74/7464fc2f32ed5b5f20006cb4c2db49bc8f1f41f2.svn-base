/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_defs.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       additional HAL definitions
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_DEFS
#define HAL_DEFS

/**
 * HAL result type (common for all HAL modules)
 */
typedef enum
{
	HALRESULT_OK = 0,
    HALRESULT_ERROR,
	HALRESULT_NO_EFFECT,
	HALRESULT_INVALID_BUFFER_HANDLE,
	HALRESULT_INVALID_USART_PORT, 
	HALRESULT_OSMUTEX_CREATION_FAILED,
	HALRESULT_OSSEM_CREATION_FAILED,
	HALRESULT_INVALID_DIAG_CHANNEL_NUMBER
} HALRESULT;


/**
 * Macro for testing operation result (returns true if operation succeeded)
 */
#define HAL_SUCCESS(x) ((x) == HALRESULT_OK) 

/**
 * Macro for testing operation result (returns true if operation failed)
 */
#define HAL_FAILED(x) (!HAL_SUCCESS(x)) 


/*! \file hal_defs.h
    \brief Additional HAL definitions
*/

#endif // HAL_DEFS

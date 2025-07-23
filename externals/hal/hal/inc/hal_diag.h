/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_diag.h
 Author:        Lukasz Krzak, Dominik Rzepka, Piotr Wojtowicz
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL diagnostic module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_DIAG_H
#define HAL_DIAG_H

#include <stdint.h>
#include "hal_iodevice.h"
#include "hal_iobuf.h"
#include "hal_config.h"
#if defined HAL_ENABLE_OS && (HAL_ENABLE_OS > 0)
#include "hal_os.h"
#endif

/** \defgroup hal_diag DIAG module
 * 
 * <b>Introduction.</b>
 * 
 * The diagnostics module in HAL (called DIAG) provides a standard way for user 
 * modules and applications to report their condition. The DIAG module supports:
 *
 *   - multiple diagnostic channels, providing controllable output from different
 *     software components
 *   - 8 levels of diagnostic detail
 *   - creating log output with simple text formatting tools
 *   - standarized way to signal and manage errors, that are reported from multiple 
 *     points in an application
 *   - assertions
 *
 * The DIAG module is also used internally by other HAL modules, to report their 
 * errors and log status.
 * 
 * <b>Module architecture.</b>
 *
 * The DIAG module is build around a concept, that a single software project is built
 * using separated software components. Such components are reusable and redistributable.
 * One of such components is HAL itself.
 * Another key thing is that each of the components can have different level of detail
 * of debugging information it provides.
 * The DIAG module captures these ideas in a concept of diagnostic channels and diagnostic
 * level.
 *
 * <b>Diagnostic channels.</b>
 *
 * All status logging is done through diagnostic channels. Each channel can be seen as
 * a data pipe, which can be activated or deactivated and which has an associated
 * output \ref IODevice. Obviously, if the application uses distinct software components, each
 * of such components may be associated with different debugging channel. This actually
 * allows the developer to enable, disable and adjust diagnostic output form different
 * software components independently.
 *
 * The number of channels that can be used is controlled by the \ref DIAG_MAX_CHANNELS definition
 * in \ref hal_config.
 *
 * <b>Diagnostic level.</b>
 *
 * Each software component may have different level of detail as far as diagnostic output
 * is concerned. The DIAG module provides status logging tools that allow for controllable
 * level of detail. One of key aspects here, is that using DIAG tools it is possible not
 * only to control whether or not the diagnostic messages are displayed, but also whether
 * the functionality of displaying then is built into the object code or not.
 *
 * DIAG provides 8 standard levels of detail for diagnostic information called simply DIAG levels.
 * These levels range from 0 to 7, where 0 means the least detail and 7 means the most detail.
 * It's up to the developer to assign diagnostic messages to an appropriate level.
 *
 * Let's look at the following example: Assume we have a component that handles some sort
 * of serial port communication protocol. The lowest level status reporting messages would include
 * things like "I'm ready to receive new data", or "An error occurred". Such messages may be
 * assigned to level 0. Perhaps level 1 would be something like "Packet received" or "Retransmission
 * needed" etc. The most detailed status logging such as information about a single processed
 * character could be level 7. Let's follow this example and assume that our component provided
 * diagnostic output at levels 0, 1 and 7. In order to control what diagnostic output will be
 * built into the object code the \ref HAL_DIAG_LEVEL definition is used. The \ref HAL_DIAG_LEVEL
 * definition denotes the highest diagnostic level of detail that will be built into the object code.
 * In our example:
 * if \ref HAL_DIAG_LEVEL is set to 0, only level 0 diagnostic messages will be built into the object code.
 * if \ref HAL_DIAG_LEVEL is set to 1, level 0 and 1 diagnostic messages will be built into the object code.
 * The same happens when \ref HAL_DIAG_LEVEL is set from 2 to 6. The level 7 diagnostic output will be
 * compiled in when \ref HAL_DIAG_LEVEL is set to 7.
 *
 * <b>Level-aware status logging.</b>
 * 
 * The status logging is particularly useful during development stage, but many times
 * it is also left inactive in the final product, making the servicing easier. The DIAG
 * module API provides several functions to make the log output formating and control easier.
 * These functions are: DIAGx_LogChar, DIAGx_LogMsg, DIAGx_LogINT, DIAGx_LogUINT
 * and DIAGx_LogNL where x is the diagnostic level.
 * The log output is directed to the IODevice, associated with the
 * DIAG module, with a prior call to DIAG_SetOutputDevice.This IODevice must be 
 * properly configured and operational.
 * 
 * <b>Level-aware assertions.</b>
 * 
 * The diagnostics module provides macros for making assertions in the
 * program flow. Assertions are simply true-false test statements used to express, that
 * some conditions during code execution should be met. If they're not then something
 * is wrong. The DIAG module provides two types of macros for handling assertions:
 * DIAGx_ASSERT() and DIAGx_ASSERT_AND_EXECUTE() where x is the diagnostic level (0..7)
 * 
 * 
 * \code
 * int divide(int x, int y)
 * {
 *     DIAG0_ASSERT(3, y != 0);
 *     DIAG1_ASSERT(3, x > y);
 *     return x/y;
 * }
 * \endcode
 * 
 * When channel 3 diagnostic level is set to 1 or higher, the following function will
 * report violations when y is equal to zero and when x is less or equal to y. If level
 * 1 diagnostic messages are not enabled, only the first violation is checked.
 * However, even though the violation is reported, the division in the example above
 * is still executed, which can lead to unwanted behavior.
 * To protect execution of a code block, under assertion condition use 
 * DIAGx_ASSERT_AND_EXECUTE(). Let's modify the example above:
 * 
 * \code
 * int divide(int x, int y)
 * {
 *     DIAG0_ASSERT_AND_EXECUTE(3, y != 0) {
 *         DIAG1_ASSERT(3, x > y) {
 *             return x/y;
 *         }
 *     }
 *     return 0;
 * }
 * \endcode
 * 
 * Now, the division is only executed when y is not equal to 0. If y is 0, an error is reported
 * and the following code block is not executed. The division is never executed also, when x <= y
 * whether the diagnostic level 1 is enabled or not. The only difference is that when it is
 * enabled, an error is reported, when x <= y.
 * 
 * <b>Managing errors.</b>
 * 
 * The error handling capability of the DIAG module can be configured and tuned to 
 * cover a wide range of applications, from simple to quite complex ones.The whole 
 * error management idea is built around one function: DIAG_ReportError that is called 
 * in the error signaling module, and provides the one and only method for reporting
 * an error. A single error report consists of several items:
 * 
 *   - diagnostic channel through which the error was reported,
 *   - error code (error number),
 *   - line of code from which the error notification was called
 * 
 * Optionally, the report can be extended with:
 * 
 *   - the time of notification
 *   - error description string
 *   - additional user supplied data
 * 
 * The error report can be processed right away - in the context of the signaling
 * module, or it can be buffered and processed later by a call to DIAG_ProcessErrors. 
 * The specification of this behavior is configured at compile-time through definitions. 
 * See module configuration section below for more details.
 * 
 * <b>Processing a single error.</b>
 * 
 * No matter whether the error buffering feature is enabled or not, processing an 
 * error consists of several steps. First, the DIAG module tries to call the 
 * application's error handler, set with a prior call to \ref DIAG_SetErrorHandler.
 * If this handler is present, it is called and it's return value decides, if the 
 * error should be logged to the output device (return !0) or not (return 0). 
 * If the error is to be logged the information about an error is written to the
 * output IODevice associated with the diagnostic channel. If buffering
 * is enabled, then the processed error is removed from the queue.
 * 
 * <b>Using DIAG module in multi-task software.</b>
 * 
 * When \ref HAL_ENABLE_OS is set to 1 in hal_config, the DIAG module integrates with the OS module
 * providing access control to output IODevice. This guard relies on IODevice lock/unlock mechanisms.
 * The following example illustrates how to use this feature:
 *
 * \code
 * if (0 == DIAG_Lock(DIAG_DEFAULT_CHANNEL, 100)) {
 *     DIAG_LogMsg(DIAG_DEFAULT_CHANNEL, "This is a diagnostic message.");
 *     DIAG_LogMsg(DIAG_DEFAULT_CHANNEL, "Hopefully it won't get split in half.");
 *     DIAG_Unlock(DIAG_DEFAULT_CHANNEL);
 * }
 * \endcode 
 *
 * In the example above, the diagnostic message won't be displayed if the lock is not successful.
 * We can use ASSERT statement to reveal such cases:
 *
 * \code
 * DIAG0_ASSERT_AND_EXECUTE(DIAG_DEFAULT_CHANNEL, 0 == DIAG_Lock(DIAG_DEFAULT_CHANNEL, 100)) {
 *     DIAG_LogMsg(DIAG_DEFAULT_CHANNEL, "This is a diagnostic message.");
 *     DIAG_LogMsg(DIAG_DEFAULT_CHANNEL, "Hopefully it won't get split in half.");
 *     DIAG_Unlock(DIAG_DEFAULT_CHANNEL);
 * }
 * \endcode 
 *
 * It is advised to use this strategy in multi-tasking (OS-based) software for all DIAG-based
 * output, to prevent undesired output conflicts. Please note, that the error reporting feature
 * already uses this mechanism. In this case additional definition: \ref HAL_DIAG_LOCK_TIMEOUT
 * is required to configure the timeout, when waiting for IODevice lock. The default timeout 
 * value is 1 second.
 *
 * <b>Module configuration.</b>
 * 
 * To enable the DIAG module, \ref HAL_ENABLE_DIAG definition must be set to 1,
 * in \ref hal_config.
 * 
 * To enable error buffering, the \ref HAL_DIAG_USE_ERROR_BUFFERING must be set to 1.
 * The \ref HAL_DIAG_ERROR_BUFFER_SIZE defines how many errors can fit into error buffer.
 * To enable buffering, it must be set to a non-zero value. 
 * 
 * To extend error report with a timestamp, set \ref HAL_DIAG_USE_ERROR_TIME_STAMPS to 1.
 * 
 */
/*@{*/


// -----------------------------------------------------------------------------
//  GLOBAL MACROS
// -----------------------------------------------------------------------------

/** Default diagnostic channel used internally by HAL. */
#define DIAG_DEFAULT_CHANNEL										0


#ifndef HAL_DIAG_LEVEL
/** Controls the detail level of the diagnostic messages. Zero means the least detail. */
#define HAL_DIAG_LEVEL												0
#endif

#ifndef HAL_DIAG_LOCK_TIMEOUT
/** Sets the timeout when trying to lock diagnostic output device */
#define HAL_DIAG_LOCK_TIMEOUT										1000
#endif



// -----------------------------------------------------------------------------
//  Level-independent API
// -----------------------------------------------------------------------------


/** Tests the assertion condition.
 *
 * \param channel diagnostic channel number
 * \param condition expression to evaluate. This must be true to pass the assertion test. 
 */
#define DIAG_ASSERT(channel, condition) 					if (!(condition)) do { \
																if (0 == DIAG_Lock((channel), HAL_DIAG_LOCK_TIMEOUT)) {  \
																	DIAG0_LogMsg((channel), "Assertion failed in "); \
																	DIAG0_LogMsg((channel), __FILE__); \
																	DIAG0_LogMsg((channel), " at line "); \
																	DIAG0_LogUINT((channel), __LINE__, 10); \
																	DIAG0_LogNL(channel); \
																	DIAG_Unlock((channel)); \
																} \
															} while (0)

/** Tests the assertion condition and executes the following code block, if the 
 * condition is true.
 *
 * \param condition expression to evaluate. This must be true to pass the assertion test. 
 */
#define DIAG_ASSERT_AND_EXECUTE(channel, condition) 		if (!(condition)) { \
																if (0 == DIAG_Lock((channel), HAL_DIAG_LOCK_TIMEOUT)) {  \
																	DIAG0_LogMsg((channel), "Assertion failed in "); \
																	DIAG0_LogMsg((channel), __FILE__); \
																	DIAG0_LogMsg((channel), " at line "); \
																	DIAG0_LogUINT((channel), __LINE__, 10); \
																	DIAG0_LogNL(channel); \
																	DIAG_Unlock((channel)); \
																} \
															} else

#if defined HAL_ENABLE_DIAG && (HAL_ENABLE_DIAG == 1)
#define DIAG_Lock(channel, timeout)							IODEV_Lock(DIAG_GetOutputDevice(channel), timeout)
#else
#define DIAG_Lock(channel, timeout)							(0)
#endif

#if defined HAL_ENABLE_DIAG && (HAL_ENABLE_DIAG == 1)
#define DIAG_Unlock(channel)								IODEV_Unlock(DIAG_GetOutputDevice(channel));
#else
#define DIAG_Unlock(channel)
#endif


/** 
 * Initializes the diagnostics module
 */
void DIAG_Init(void);

/** 
 * Deinitializes the diagnostics module.
 */
void DIAG_Deinit(void);

/** 
 *  Sets the output device for all diagnostic messages and error logs. Setting this
 *  to NULL disables all output, but not the error processing itself.
 *  
 *  \param channel diagnostic channel number
 *  \param iodevice iodevice used for diagnostic output 
 *  \return HALRESULT_OK if the iodevice was set or HALRESULT_INVALID_DIAG_CHANNEL_NUMBER if the provided channel
 *                       number was out of bounds (see \ref DIAG_MAX_CHANNELS definition)
*/
HALRESULT DIAG_SetOutputDevice(int channel, IODevice iodevice);

/** 
 *  Gets the currently set output device.
 *  
 *  \param channel diagnostic channel number
 *  \return IODevice currently used for diagnostic output 
*/
IODevice DIAG_GetOutputDevice(int channel);

/**
 *  Activates log output from a given diagnostic channel.
 *
 *  \param channel diagnostic channel number
 *  \return HALRESULT_OK if channel was activated or HALRESULT_INVALID_DIAG_CHANNEL_NUMBER if the provided channel
 *                       number was out of bounds (see \ref DIAG_MAX_CHANNELS definition)
 */
HALRESULT DIAG_ActivateChannel(int channel);

/**
 *  Deactivates log output from a given diagnostic channel.
 *
 *  \param channel diagnostic channel number
 *  \return HALRESULT_OK if channel was deactivated or HALRESULT_INVALID_DIAG_CHANNEL_NUMBER if the provided channel
 *                       number was out of bounds (see \ref DIAG_MAX_CHANNELS definition)
 */
HALRESULT DIAG_DeactivateChannel(int channel);

/**
 *  Sets up a clock source for a given channel. The clock information will be used by
 *  \ref DIAG_LogHeader function.
 *
 *  \param channel diagnostic channel number
 *  \param clk_src a function that will supply the clock information
 *  \return HALRESULT_OK if the clock source was successfully assigned to a channel
 *                       or HALRESULT_INVALID_DIAG_CHANNEL_NUMBER if the provided channel
 *                       number was out of bounds (see \ref DIAG_MAX_CHANNELS definition)
 */
HALRESULT DIAG_SetClockSource(int channel, uint32_t (*clk_src)(void));


/**
 *  Logs formatted string.
 *
 *  \param channel diagnostic channel number
 *  \param str string that contains text to be logged including embedded format tags
 */
void DIAG_Log(int channel, const char * str, ...);

/** 
 *  Logs a single character.
 *  
 *  \param channel diagnostic channel number
 *  \param character character that will be written to the output device 
*/
void DIAG_LogChar(int channel, char character);

/** 
 *  Logs a string message.
 *  
 *  \param channel diagnostic channel number
 *  \param msg string message that will be written to the output device 
*/
void DIAG_LogMsg(int channel, const char* msg);

/** 
 *  Logs a signed integer value.
 *  
 *  \param channel diagnostic channel number
 *  \param value signed value that will be written to the output device
 *  \param base a base for integer to string conversion 
*/
void DIAG_LogINT(int channel, int32_t value, uint8_t base);

/** 
 *  Logs an unsigned integer value.
 *  
 *  \param channel diagnostic channel number
 *  \param value unsigned value that will be written to the output device
 *  \param base a base for integer to string conversion 
*/
void DIAG_LogUINT(int channel, uint32_t value, uint8_t base);

/** 
 *  Logs a floating point value.
 *
 *  \param channel diagnostic channel number
 *  \param value floating point value that will be written to the output device
 *  \param precision number of fractional digits to print
 *
 */
void DIAG_LogFLOAT(int channel, float value, int precision);

/** 
 *  Logs an end-of-line character.
 *
 *  \param channel diagnostic channel number
 */
void DIAG_LogNL(int channel);

/**
 *  Logs a message header.
 *
 *  \param channel diagnostic channel number
 *  \param module module name
 */
void DIAG_LogHeader(int channel, const char* module);

/**
 *  Logs contents of a data buffer.
 *
 *  \param channel diagnostic channel number
 *  \param data data buffer
 *  \param size size of the data buffer
 *  \param base a base for integer to string conversion
 *  \param spacing number of bytes after which a space string should be inserted
 *  \param space space string or NULL
 */
void DIAG_LogData(int channel, uint8_t* data, size_t size, int base, int spacing, const char* space);

/**
 *  Prints out some basic information about an IOBuf in human readable form.
 *  \param iobuf IOBuf to print
 *  \param indent indentation of log (number of spaces)
 */
void DIAG_LogIOBuf(int channel, IOBuf iobuf, int indent);

/** 
 *  Reports an error
 *  
 *  \param channel diagnostic channel number
 *  \param error_no error number
 *  \param code_line line of code from which the notification was called
 *  \param user_data user supplied data attached to the error
 *  \param description pointer to the error description string 
*/
void DIAG_ReportError(int channel, uint16_t error_no, uint32_t code_line, void* user_data, const char* description);

/** 
 *  A parser function that handles the buffered errors. Used when error buffering
 *  for DIAG is enabled. This function should be called periodically by the
 *  application to ensure proper error handling.
 *  \return number of errors still left to parse
 *  
 *  \param max_error_count specifies the maximum number of errors that can be processed 
 *                         in one run of this function
*/
uint32_t DIAG_ProcessErrors(uint32_t max_error_count);

/** 
 *  Sets an error handler callback function, that will be called when an error is
 *  signaled.
*/
void DIAG_SetErrorHandler(int (*error_handler)(int, uint16_t, uint16_t, void*, const char*));



// -----------------------------------------------------------------------------
//  Level-dependent API
// -----------------------------------------------------------------------------

#if defined HAL_ENABLE_DIAG && (HAL_ENABLE_DIAG != 0)

#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 0)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)   if (condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)
#define DIAG2_Unlock(channel)
#define DIAG3_Unlock(channel)
#define DIAG4_Unlock(channel)
#define DIAG5_Unlock(channel)
#define DIAG6_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)

#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)
#define DIAG2_LogNL(channel)
#define DIAG3_LogNL(channel)
#define DIAG4_LogNL(channel)
#define DIAG5_LogNL(channel)
#define DIAG6_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)

#endif // HAL_DIAG_LEVEL == 0)


#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 1)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)				

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)   if (condition)   
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)   if (condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG2_Unlock(channel)
#define DIAG3_Unlock(channel)
#define DIAG4_Unlock(channel)
#define DIAG5_Unlock(channel)
#define DIAG6_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)

#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG2_LogNL(channel)
#define DIAG3_LogNL(channel)
#define DIAG4_LogNL(channel)
#define DIAG5_LogNL(channel)
#define DIAG6_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)

#endif // HAL_DIAG_LEVEL == 1)


#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 2)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)   if (condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG2_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG3_Unlock(channel)
#define DIAG4_Unlock(channel)
#define DIAG5_Unlock(channel)
#define DIAG6_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)

#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG2_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG3_LogNL(channel)
#define DIAG4_LogNL(channel)
#define DIAG5_LogNL(channel)
#define DIAG6_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)

#endif // HAL_DIAG_LEVEL == 2)


#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 3)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)   if (condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG2_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG3_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG4_Unlock(channel)
#define DIAG5_Unlock(channel)
#define DIAG6_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)


#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG2_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG3_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG4_LogNL(channel)
#define DIAG5_LogNL(channel)
#define DIAG6_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)

#endif // HAL_DIAG_LEVEL == 3)


#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 4)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)   if (condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG2_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG3_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG4_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG5_Unlock(channel)
#define DIAG6_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)


#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG2_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG3_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG4_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG5_LogNL(channel)
#define DIAG6_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)

#endif // HAL_DIAG_LEVEL == 4)


#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 5)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)   if (condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)   if (condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG2_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG3_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG4_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG5_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG6_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)


#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG2_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG3_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG4_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG5_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG6_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)

#endif // HAL_DIAG_LEVEL == 5)


#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 6)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)   if (condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG2_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG3_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG4_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG5_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG6_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)


#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG2_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG3_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG4_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG5_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG6_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)


#endif // HAL_DIAG_LEVEL == 6)


#if defined HAL_DIAG_LEVEL && (HAL_DIAG_LEVEL == 7)

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)				DIAG_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)

#define DIAG0_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)					DIAG_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)					DIAG_Lock(channel, timeout)

#define DIAG0_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG1_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG2_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG3_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG4_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG5_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG6_Unlock(channel)							DIAG_Unlock(channel)
#define DIAG7_Unlock(channel)							DIAG_Unlock(channel)

#define DIAG0_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)				DIAG_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)				DIAG_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)						DIAG_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)				DIAG_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)				DIAG_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)		DIAG_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)	DIAG_LogData(channel, data, size, base, spacing, space)

#define DIAG0_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG1_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG2_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG3_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG4_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG5_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG6_LogNL(channel)							DIAG_LogNL(channel)
#define DIAG7_LogNL(channel)							DIAG_LogNL(channel)

#define DIAG0_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)				DIAG_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)				DIAG_LogHeader(channel, module)

#endif // HAL_DIAG_LEVEL == 7)

#else

// no DIAG

#define DIAG0_ASSERT(channel, condition) 				DIAG_ASSERT(channel, condition)
#define DIAG1_ASSERT(channel, condition)
#define DIAG2_ASSERT(channel, condition)
#define DIAG3_ASSERT(channel, condition)
#define DIAG4_ASSERT(channel, condition)
#define DIAG5_ASSERT(channel, condition)
#define DIAG6_ASSERT(channel, condition)
#define DIAG7_ASSERT(channel, condition)

#define DIAG0_ASSERT_AND_EXECUTE(channel, condition)	DIAG_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG1_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG2_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG3_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG4_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG5_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG6_ASSERT_AND_EXECUTE(channel, condition)
#define DIAG7_ASSERT_AND_EXECUTE(channel, condition)

#define DIAG0_Lock(channel, timeout)
#define DIAG1_Lock(channel, timeout)
#define DIAG2_Lock(channel, timeout)
#define DIAG3_Lock(channel, timeout)
#define DIAG4_Lock(channel, timeout)
#define DIAG5_Lock(channel, timeout)
#define DIAG6_Lock(channel, timeout)
#define DIAG7_Lock(channel, timeout)

#define DIAG0_Unlock(channel)
#define DIAG1_Unlock(channel)
#define DIAG2_Unlock(channel)
#define DIAG3_Unlock(channel)
#define DIAG4_Unlock(channel)
#define DIAG5_Unlock(channel)
#define DIAG6_Unlock(channel)
#define DIAG7_Unlock(channel)

#define DIAG0_LogChar(channel, character)
#define DIAG1_LogChar(channel, character)
#define DIAG2_LogChar(channel, character)
#define DIAG3_LogChar(channel, character)
#define DIAG4_LogChar(channel, character)
#define DIAG5_LogChar(channel, character)
#define DIAG6_LogChar(channel, character)
#define DIAG7_LogChar(channel, character)

#define DIAG0_LogMsg(channel, msg)
#define DIAG1_LogMsg(channel, msg)
#define DIAG2_LogMsg(channel, msg)
#define DIAG3_LogMsg(channel, msg)
#define DIAG4_LogMsg(channel, msg)
#define DIAG5_LogMsg(channel, msg)
#define DIAG6_LogMsg(channel, msg)
#define DIAG7_LogMsg(channel, msg)

#define DIAG0_LogINT(channel, value, base)
#define DIAG1_LogINT(channel, value, base)
#define DIAG2_LogINT(channel, value, base)
#define DIAG3_LogINT(channel, value, base)
#define DIAG4_LogINT(channel, value, base)
#define DIAG5_LogINT(channel, value, base)
#define DIAG6_LogINT(channel, value, base)
#define DIAG7_LogINT(channel, value, base)

#define DIAG0_LogUINT(channel, value, base)
#define DIAG1_LogUINT(channel, value, base)
#define DIAG2_LogUINT(channel, value, base)
#define DIAG3_LogUINT(channel, value, base)
#define DIAG4_LogUINT(channel, value, base)
#define DIAG5_LogUINT(channel, value, base)
#define DIAG6_LogUINT(channel, value, base)
#define DIAG7_LogUINT(channel, value, base)

#define DIAG0_LogFLOAT(channel, value, precision)
#define DIAG1_LogFLOAT(channel, value, precision)
#define DIAG2_LogFLOAT(channel, value, precision)
#define DIAG3_LogFLOAT(channel, value, precision)
#define DIAG4_LogFLOAT(channel, value, precision)
#define DIAG5_LogFLOAT(channel, value, precision)
#define DIAG6_LogFLOAT(channel, value, precision)
#define DIAG7_LogFLOAT(channel, value, precision)

#define DIAG0_LogData(channel, data, size, base, spacing, space)
#define DIAG1_LogData(channel, data, size, base, spacing, space)
#define DIAG2_LogData(channel, data, size, base, spacing, space)
#define DIAG3_LogData(channel, data, size, base, spacing, space)
#define DIAG4_LogData(channel, data, size, base, spacing, space)
#define DIAG5_LogData(channel, data, size, base, spacing, space)
#define DIAG6_LogData(channel, data, size, base, spacing, space)
#define DIAG7_LogData(channel, data, size, base, spacing, space)

#define DIAG0_LogNL(channel)
#define DIAG1_LogNL(channel)
#define DIAG2_LogNL(channel)
#define DIAG3_LogNL(channel)
#define DIAG4_LogNL(channel)
#define DIAG5_LogNL(channel)
#define DIAG6_LogNL(channel)
#define DIAG7_LogNL(channel)

#define DIAG0_LogHeader(channel, module)
#define DIAG1_LogHeader(channel, module)
#define DIAG2_LogHeader(channel, module)
#define DIAG3_LogHeader(channel, module)
#define DIAG4_LogHeader(channel, module)
#define DIAG5_LogHeader(channel, module)
#define DIAG6_LogHeader(channel, module)
#define DIAG7_LogHeader(channel, module)


#endif // no DIAG

/*@}*/

/*! \file hal_diag.h
    \brief HAL diagnostic tools

 */

#endif /* HAL_DIAG_H */

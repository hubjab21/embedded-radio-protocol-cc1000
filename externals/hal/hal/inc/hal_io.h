/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_io.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL IO module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_IO_H
#define HAL_IO_H

/** \defgroup hal_io IO module
 * 
 * <b>Introduction.</b>
 * 
 * The IO module is responsible for handling communication through several common
 * peripherals, such as UART or SPI. It provides a unified high-level application 
 * interface for different devices and is capable of working in several modes, 
 * taking advantage of additional microcontroler's mechanisms, such as interrupts
 * or DMA channels. The IO module interface is flexible enough to handle most of
 * the common data transmission tasks, but may be also used and abused in different 
 * areas of application.
 * 
 * <b>IO Interfaces.</b>
 * 
 * The main IO interface that the application interacts with is the \ref hal_iodevice.
 * This interface encapsulates all the functionality provided by the IO module.
 * 
 * The \ref hal_txtdevice sits on top of the IODevice interface. It provides functions
 * for easier handling of textual information sent and received through IODevices.
 *
 * <b>Porting HAL IO.</b>
 * 
 * TBD
 * 
 * <b>Module configuration.</b>
 * 
 * To enable the IO module, HAL_ENABLE_IO definition must be set to 1, 
 * in hal_config.h. Additional definitions may be required to enable specific modes
 * of operation for specific ports, or other options. Refer to the port documentation.
 *  
 */
/*@{*/


/*@}*/

/*! \file hal_io.h
    \brief HAL IO module
*/


#endif /* HAL_IO_H */


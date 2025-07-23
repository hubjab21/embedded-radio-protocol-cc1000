/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HALFRED's main header file
--------------------------------------------------------------------------------
 Comments:      This is the ONLY file you need to include in application
                in order to use HALFRED.
================================================================================
*/

#ifndef HAL_H
#define HAL_H

/**
 * \if halfred_blend_doc
 * \page halfred HALFRED Hardware Abstraction Layer
 * \else
 * \mainpage HALFRED Hardware Abstraction Layer
 * \endif
 *
 * <b>Welcome to HALFRED!</b>
 *
 * This is the documentation section. If you're new here, we invite you to read
 * \ref HALFRED_intro "the introduction to HALFRED".
 *
 * HALFRED is modular - you can read documentation for each module here:
 * - \ref hal_core "CORE module (CPU core functionality)"
 * - \ref hal_clk "CLK module (clock handling)"
 * - \ref hal_pwr "PWR module (power modes handling)"
 * - \ref hal_gpio "GPIO module (general purpose I/O handling)"
 * - \ref hal_iobuf "IOBUF module (ring buffers)"
 * - \ref hal_io "IO module (communication)"
 * 		- \ref hal_iodevice
 * 		- \ref hal_txtdevice
 * 		- \ref hal_iocomposite
 * - \ref hal_tim "TIM module (timers)"
 * - \ref hal_diag "DIAG module (diagnostics)"
 * - \ref hal_cli "CLI module (command line interface)"
 * - \ref hal_os "OS module (operating system support)"
 * 		- \ref hal_os_task
 * 		- \ref hal_os_sem
 * 		- \ref hal_os_cntsem
 * 		- \ref hal_os_mutex
 * - \ref hal_nv "NV module (non-volatile memory handling)"
 * - \ref hal_bp "BP module (universal buffer pools)"
 * - \ref hal_heap "HEAP module (dynamic memory management)"
 * - \ref hal_delay "DELAY module (delay loops)"
 *
 * HALFRED is also highly configurable. See \ref hal_config on how to adjust HALFRED for your application.
 *
 *
 * NOTE: The contents here are generated automatically from source code.
 */

/**
 * \page HALFRED_intro Introduction to HALFRED
 * 
 * <b>Getting the main idea.</b>
 * 
 * HALFRED is a short from Hardware Abstraction Layer For Real-time Embedded Designs.
 * It is indeed a piece of software - a software layer. The main purpose of creating
 * HALFRED was to provide better portability to the embedded applications, that are
 * based on popular, low-cost microcontrollers. Nowadays we're facing a situation,
 * where a designer has a wide variety of such hardware to choose from. Not all of the
 * decisions taken will last long. The market changes along with user demands, silicon
 * chips capabilities and pricing. On the other hand you always want to have a reusable
 * software. A reusable piece of code is something you can trust and base upon, because
 * it has proved correctness in more than one application. It is probably well tested
 * too. You don't  want to throw that away just because your microcontroller changes.
 * 
 * To allow your software to adapt to a new hardware you need a way of translating it 
 * to a new microcontroller. HALFRED is such a way. It translates the demands from your
 * application to the hardware it works on. In other terms, it actually mimics the 
 * microcontroler in a standard way, so your software can always use the same virtual 
 * hardware interfaces, while HALFRED translates it to execute on a particular silicon chip.
 * This way your software doesn't change, while microcontroller changes. It is portable.
 *
 * By using HALFRED, your application draws a clear line between the hardware-independent
 * and hardware-dependent parts of the code. This line is actually set inside the HALFRED,
 * meaning that HALFRED itself is divided into portable code and the "port" itself. This
 * "port" can be viewed as a driver, for a particular microcontroller.
 *
 * <b>More benefits.</b>
 *
 * If you're not interested in writing portable code, there is still an issue that might 
 * convince you to consider using HALFRED. Developing an embedded application is generally
 * considered to be more difficult and demanding than "standard" PC software. The main 
 * reason is the usual unfriendliness of embedded debuggers and tools, when compared to
 * will-do-it-all-for-you integrated development environments on PC. It is then attractive
 * to develop, debug and test code with a more capable tools. on the PC platform HALFRED gives
 * you this opportunity by providing ports for PC, that emulate virtual hardware peripherals. 
 * These modules are especially suited for developing an testing pieces of code, that are 
 * hardware-independent, but eventually must run on some hardware (in this case - virtual 
 * hardware). What you can do is for example: develop and test a protocol that uses UART 
 * communication as a physical layer before your actual hardware arrives. This also boosts 
 * unit-test and debugging capabilities. With some effort you can even simulate your whole 
 * application and it's interaction with the environment on a single PC.
 *
 * <b>Digging deeper into abstraction.</b>
 *
 * Abstraction usually means that some details are hidden, and more general properties are 
 * exposed. In case of the HALFRED there are several interfaces exposed, that allow you to use
 * the most common abilities of modern microcontrollers. What is hidden is the actual 
 * microcontroller implementation.
 * 
 * <b>The glitch.</b>
 *
 * All this value comes with no disadvantages, right? Well... no. We won't lie to you.
 * The price for abstraction is less detail, and the price for portability is less performance.
 * We did our best to provide as much functionality as possible, based on current state of art
 * microcontrollers, but there are always exotic peripheral capabilities that didn't fit
 * into the interfaces. While these can still be used, by modifying/extending ports, it 
 * would  probably break seriously the portability advantage. We also did our best to minimize 
 * the performance penalty, but it's fair to say that a 100% target-specific implementation 
 * has a good chance to outperform the HALFRED-based one. But we still think that the HALFRED engine
 * is an excellent compromise between total portability (such as JAVA) and pure hardware-specific
 * assembly.
 *  
 */

/**
 * \defgroup ports Available ports
 * 
 * Here is a list of available HALFRED ports:
 * 
 */

#if defined __cplusplus
extern "C" {
#endif


#include "hal_config.h"
#include "hal_core.h"
#include "hal_heap.h"
#include "hal_delay.h"
#include "hal_diag.h"
#include "hal_port_core.h"

#if (HAL_ENABLE_CLK)
#include "hal_clk.h"
#include "hal_port_clk.h"
#endif
#if (HAL_ENABLE_GPIO)
#include "hal_gpio.h"
#include "hal_port_gpio.h"
#endif
#if (HAL_ENABLE_IO)
#include "hal_io.h"
#include "hal_iobuf.h"
#include "hal_iodevice.h"
#include "hal_iobus.h"
#include "hal_txtdevice.h"
#include "hal_iocomposite.h"
#include "hal_port_io.h"
#endif
#if (HAL_ENABLE_TIM)
#include "hal_tim.h"
#include "hal_port_tim.h"
#endif
#if (HAL_ENABLE_OS)
#include "hal_os.h"
#endif
#if (HAL_ENABLE_BP)
#include "hal_bp.h"
#endif
#if (HAL_ENABLE_NV)
#include "hal_nv.h"
#endif
#if (HAL_ENABLE_CLI)
#include "hal_cli.h"
#endif

#if defined __cplusplus
} // extern "C"
#endif

// include port
//#include "hal_port.h"


/*! \file hal.h
    \brief HALFRED's main header file.

 */


#endif /* HAL_H */


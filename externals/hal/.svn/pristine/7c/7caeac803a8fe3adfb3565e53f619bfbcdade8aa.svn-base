/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_gpio.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL GPIO module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef GPIO_H
#define GPIO_H


/** \defgroup hal_gpio GPIO module
 * 
 * <b>Introduction.</b>
 * 
 * This module provides an interface for handling general purpose input/output pins.
 * It provides an interface for changing pin direction settings, reading pin state and 
 * controlling the output state.
 * 
 * <b>Pin identification.</b>
 * 
 * On the application level, every pin is identified only by it's name. Typical name examples
 * would be: MEM_CS, LCD_RESET, PWR_SHUTDOWN etc. The pin is assumed to belong to an i/o port
 * (i/o bank), as this is the most common case in general purpose microcontrollers.\n
 * The actual pin identifier is created by adding "_PIN" suffix to the pin name. For the above
 * examples, the actual pin identifiers would be MEM_CS_PIN, LCD_RESET_PIN, PWR_SHUTDOWN_PIN etc.
 * Similarly, port identifiers comes form pin name and "_PORT" suffix, for example: MEM_CS_PORT,
 * LCD_RESET_PORT, PWR_SUTDOWN_PORT etc.
 * HAL does not typecast the pin and port identifiers, as all the GPIO handling is done by macros.
 * This means that for example MEM_CS_PIN and MEM_CS_PORT can represent any type of data. Most
 * often pins would be represented as integers (either pin number or bitmask) but ports may be
 * represented as integers or pointers to internal register banks in the address space of the
 * microcontroller. 
 * 
 * <b>Pin configuration.</b>
 * 
 * Any pin can be configured to serve several purposes. It may be configured as input,
 * then as push-pull output or open drain etc. Pin reconfiguration can be done dynamically 
 * at runtime, so the GPIO module must provide a way to identify the configurations.
 * In the context of GPIO module, pin configurations also have names. Typical would be:
 * OUTPUT_PP, OUTPUT_OD, INPUT_PU, but the name can also be strongly coupled with the application.
 * TODO: decide whether or not define standard configuration names
 * The actual configuration identifier is created by adding name of configuration as a suffix to the
 * pin name, for example MEM_CS_OUTPUT_PP, MEM_CS_OUTPUT_OD etc. These identifier are not type-casted
 * by HAL, so they may represent any type of data.
 * 
 * <b>Application definitions.</b>
 * 
 * On the application level, pin handling comes down to using GPIO API with pin names and pin
 * configuration names. These (along with port identifiers) must be visible during compile time.
 * HAL expects to find them in a file called gpio_config.h. This file in most cases sits in the
 * application folder. As discussed above, for every pin there are 3 definitions needed: pin, port
 * and at least one configuration. Let's look at the following example of a hypothetical pin
 * being a half-duplex serial communication line on the first pin of imaginary port A.
 * \code
 * #define SERIAL_DATA_PIN          1
 * #define SERIAL_DATA_PORT         PORTA
 * #define SERIAL_DATA_OUTPUT       1
 * #define SERIAL_DATA_INPUT        0
 * #define SERIAL_DATA_DEFAULT      SERIAL_DATA_INPUT
 * \endcode
 * Such code placed in the GPIO section of hal_config.h enables the application to use pin named "SERIAL_DATA"
 * in two configurations named "OUTPUT" and "INPUT". Additionally, a default configuration has been distinguished.
 * The following code initializes the GPIO module, configures the pin as output and sets it to a high state.
 * \code
 * GPIO_Init();
 * GPIO_ConfigurePin(SERIAL_DATA, SERIAL_DATA_OUTPUT);
 * GPIO_SetPinHigh(SERIAL_DATA);
 * \endcode
 * 
 * <b>GPIO events.</b>
 * 
 * The GPIO events mechanism provides a way to handle external interrupts triggered on GPIO pins. The pins
 * are identified using the same pin name as described above. Additional API for events consists of the 
 * following items: \ref GPIO_EnableEvent, \ref GPIO_DisableEvent, \ref GPIO_SetEventHandler
 * and \ref GPIO_IsEventEnabled. At least one additional application definition is required to configure
 * the source of an event.
 * 
 * For example, if an interrupt is needed on a SERIAL_DATA line, when it transits from high to low state
 * the application must provide at least 3 definitions:
 * \code
 * #define SERIAL_DATA_PIN          1
 * #define SERIAL_DATA_PORT         PORTA
 * #define SERIAL_DATA_TRIGGER      falling_edge_trigger
 * \endcode
 * 
 * Such code placed in the GPIO section of hal_config.h enables the application to use pin named "SERIAL_DATA"
 * with an event which source is set as "falling_edge_trigger" (note that this is purely port-specific
 * definition). 
 * The following code initializes the GPIO module, configures the pin event and sets its handler.
 * \code
 * GPIO_Init();
 * GPIO_SetEventHandler(SERIAL_DATA, MyHandler);
 * GPIO_EnableEvent(SERIAL_DATA, SERIAL_DATA_TRIGGER);
 * \endcode
 * where the handler is defined as:
 * \code
 * void MyHandler(void)
 * {
 *     do_something();
 * }
 * \endcode
 * Please note, that it's usually a good idea to setup the handler BEFORE the event is actually enabled. 
 * 
 * <b>Module configuration.</b>
 * 
 * To enable the GPIO module, HAL_ENABLE_GPIO definition must be set to 1, 
 * in hal_config.h.  
 */ 
/*@{*/

// -----------------------------------------------------------------------------
//  LOCAL MACROS 
//  don't call these on application level, as they are subject to change!
// -----------------------------------------------------------------------------
/**@cond DEV*/

/** 
 * A local helper macro to resolve full port identifier from the pin name.
 * Don't call it on the application level, as it's subject to change.
 * \param name pin name 
 */
#define GPIO_GET_PORT_NAME(name) 			name##_##PORT

/** 
 * A local helper macro to resolve full port mask identifier from the pin name.
 * Don't call it on the application level, as it's subject to change. 
 * \param name pins group name
 */
#define GPIO_GET_PORT_MASK_NAME(name) 			name##_##PORT_MASK

/**
 * A local helper macro to resolve full pin identifier from the pin name.
 * Don't call it on the application level, as it's subject to change.
 * \param name pin name
 */
#define GPIO_GET_PIN_NAME(name) 			name##_##PIN

/** 
 * A local helper macro to resolve full configuration identifier from the pin name
 * and configuration name. Don't call it on the application level, as it's subject 
 * to change. 
 * \param name pin name 
 * \param name name of configuration, for example: "OUTPUT", "INPUT_PULL_UP" etc. 
 */
#define GPIO_GET_CONFIG_NAME(name, config)  name##_##config

/**@endcond*/


// -----------------------------------------------------------------------------
//  PUBLIC MACROS
// -----------------------------------------------------------------------------

/** 
 * Initializes the GPIO module. Must be called before any other GPIO functions.
 * The functionality of this procedure is system dependent. This API call is provided
 * to satisfy special requirements, such as initial state configuration of all pins etc.
 */
#define GPIO_Init() 						GPIO_PORT_Init()

/**
 * Deinitializes the GPIO module. The functionality of this procedure is system dependent.
 */
#define GPIO_Deinit() 						GPIO_PORT_Deinit()

/**
 * Sets up pin to the specified configuration.
 * \param name name of the pin
 * \param config name of the configuration 
 */
#define GPIO_ConfigurePin(name, config) 	GPIO_PORT_ConfigurePin(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name), GPIO_GET_CONFIG_NAME(name, config))

/**
 * Sets up group of pins associated with specified port
 * to the specified configuration.
 * \param name name of the pins group
 * \param config name of the configuration
 */
#define GPIO_ConfigurePort(name, config) 	GPIO_PORT_ConfigurePort(GPIO_GET_PORT_NAME(name), GPIO_GET_PORT_MASK_NAME(name), GPIO_GET_CONFIG_NAME(name, config))

/**
 * Returns the current pin configuration.
 * \param name name of the pin
 */
#define GPIO_GetConfig(name)				GPIO_PORT_GetConfig(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name))

/**
 * Reads pin state, if the pin is configured as input or the hardware allows to read the state of 
 * an output pin. Otherwise the result of this macro is undefined.
 * \param name name of the pin
 * \return 0 if the pin is in zero logic state (low voltage)
 *         1 if the pin is in one logic state (high voltage)
 *         undefined if pin can not be read due to it's current configuration
 */
#define GPIO_ReadPin(name) 					GPIO_PORT_ReadPin(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name))

/**
 * Set the state of the output pin to high voltage state (logic 1). If the pin is not configured as output
 * this function does nothing. 
 * \param name name of the output pin
 */
#define GPIO_SetPinHigh(name) 				GPIO_PORT_SetPinHigh(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name))

/**
 * Set the state of the output pin to low voltage state (logic 0). If the pin is not configured as output
 * this function does nothing. 
 * \param name name of the output pin
 */
#define GPIO_SetPinLow(name) 				GPIO_PORT_SetPinLow(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name))

/**
 * Changes the state of the output pin to the oposite one. If the pin is not configured as output
 * this function does nothing. 
 * \param name name of the output pin
 */
#define GPIO_TogglePin(name)				GPIO_PORT_TogglePin(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name))

/**
 * Reads port state, if the port is configured as input or the hardware allows to read the state of
 * an output port. Otherwise the result of this macro is undefined.
 * This macro reads whole port data (each bit), so if some bits are not used or configured
 * as outputs it is recommended to use some mask to clear unused bits cause their values may be undefined.
 * \param name name of the port
 * \return uint32_t type data read from port
 *         undefined if port can not be read due to it's current configuration
 */
#define GPIO_ReadPort(name)					GPIO_PORT_ReadPort(GPIO_GET_PORT_NAME(name))

/**
 * Writes data to the output port. If the port is not configured as output
 * this function does nothing.
 * This macro writes data to whole port (each bit), so if some bits of port are used as other group
 * of pins it is necessary to read port, modify requested bits and then write new value to the port
 * \param name name of the output port
 * \param data uint32_t type data to be written to port
 */
#define GPIO_WritePort(name, data)			GPIO_PORT_WritePort(GPIO_GET_PORT_NAME(name), data)

/**
 * Set the state of the group of pins of port to high voltage state (logic 1). If the pins are not configured as output
 * this function does nothing.
 * \param name name of the output pins group
 * \param data mask with bits to be set high
 */
#define GPIO_SetPortHigh(name, data) 		GPIO_PORT_SetPortHigh(GPIO_GET_PORT_NAME(name), (data))

/**
 * Set the state of the group of pins of port to low voltage state (logic 0). If the pins are not configured as output
 * this function does nothing.
 * \param name name of the output pins group
 * \param data mask with bits to be set low
 */
#define GPIO_SetPortLow(name, data) 		GPIO_PORT_SetPortLow(GPIO_GET_PORT_NAME(name), (data))

/**
 * Configures and enables an event on the specified pin. Pin have to be configured before
 * calling GPIO_EnableEvent
 * \param name name of the pin
 * \param source of the event
 */
#define GPIO_EnableEvent(name, source)		GPIO_PORT_EnableEvent(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name), (source))

/**
 * Disables an event on the specified pin. 
 * \param name name of the pin
 */
#define GPIO_DisableEvent(name)				GPIO_PORT_DisableEvent(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name))

/**
 * Associates an event handler func to be called when an event is triggered on the specified pin. 
 * \param name name of the pin
 * \param handler event handler function. This function does not have any parameters and returns nothing, in ex.: void MyHandler(void) 
 */
#define GPIO_SetEventHandler(name, handler)	GPIO_PORT_SetEventHandler(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name), (handler))

/**
 * Checks, if an event on the specified pin is enabled.
 * \param name name of the pin
 * \return !0 if an event on the specified pin is enabled, or 0 if it's not
 */
#define GPIO_IsEventEnabled(name)			GPIO_PORT_IsEventEnabled(GPIO_GET_PORT_NAME(name), GPIO_GET_PIN_NAME(name))


/*@}*/

/*! \file hal_gpio.h
    \brief HAL GPIO module definition

 */

#endif /* GPIO_H */


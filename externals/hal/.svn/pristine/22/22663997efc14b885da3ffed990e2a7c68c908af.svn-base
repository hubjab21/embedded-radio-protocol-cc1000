/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_cli.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       Command Line Interface (CLI) module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_CLI_H
#define HAL_CLI_H

#include <stdint.h>
#include <stddef.h>

/** \defgroup hal_cli CLI module
 *
 * <b>Introduction.</b>
 *
 * This module provides simple yet powerful implementation of a Command Line Interface.
 * A command line interface is represented by the \ref CLIConsole object. CLIConsole
 * object should be associated with an IODevice, through which it communicates with the
 * user.
 *
 * CLI module provides two types of input:
 * - in key press mode, the console reacts on every single key
 * - in command line mode, the console buffers the incoming characters until end-of-line
 *   character (ENTER) is received, and then it reacts
 * The user can switch between both operating modes by pressing the '~' character.
 *
 * <b>Configuration</b>
 *
 * To enable CLI module the \ref HAL_ENABLE_CLI declaration should be set to 1 in \ref hal_config.
 *
 * <b>Declaring CLIConsole objects.</b>
 *
 * Usually, an application requires only one command line interface - thus only one
 * \ref ClIConsole object is needed. To declare it, use convenient macro \ref CLI_DECLARE
 * like this:
 *
 * \code
 * CLI_DECLARE(mycli, USART1, mycommandprocessor, static);
 * \endcode
 *
 * This declares \ref CLIConsole object with name 'mycli', working on \ref IODevice named
 * USART1, with a command handler function named commandProcessor. Additionally, the 'mycli'
 * object will be declared as static (you can leave the last parameter blank for no additional
 * attributes).
 *
 * <b>Running the console.</b>
 *
 * To run the console, the \ref CLI_ProcessConsole function should be executed periodically, with
 * an interval short enough to provide good user experience (responsiveness). Usually, before running
 * the main console screen is displayed:
 *
 * \code
 * // Clear console screen and display main menu
 * CLI_DisplayMainScreen(mycli);
 *
 * while (1) {
 *     // Process the console
 *     CLI_ProcessConsole(cli);
 * }
 * \endcode
 *
 * <b>Parsing the commands.</b>
 *
 * When run in command line mode, the console buffers all incomming characters until end-of-line (ENTER)
 * character is received. After that the console executes a special user-defined command line processing
 * function, that handles the command. The \ref hal_cli defines the format and behaviour of that function
 * as well as provides tools for making the job of command processing easier.
 *
 * The command processor function should have the following declaration:
 * \code
 * void mycommandprocessor(CLIConsole cli);
 * \endcode
 *
 * The function takes the cli console handle as a parameter. Let's look at a simplest implementation of
 * a command processor function.
 *
 * \code
 * void mycommandprocessor(CLIConsole cli)
 * {
 *     IODevice iodevice;
 *     char item[32];
 *
 *     // first, get the IODevice associated with console
 *     iodevice = CLI_GetIODevice(cli);
 *
 *     // get command from command line (returns only the first word of a command)
 *     CLI_GetCommand(cli, item);
 *
 *     // compare the command string against predefined commands
 *     if (0 == strcmp((char*)item,"help")) {
 *         // 'help' command
 *         TXTDEV_WriteString(iodevice,"This is HELP.");
 *         TXTDEV_WriteString(iodevice,"Use the ~ character to change CLI mode.");
 *         TXTDEV_WriteNL(iodevice);
 *         return;
 *     }
 *
 *     TXTDEV_WriteString(iodevice,"Unknown command.");
 *
 *     return;
 *
 * }
 * \endcode
 *
 */
/*@{*/

#ifndef CLI_COMMAND_BUF_SIZE

/// Default size of the command line buffer
#define CLI_COMMAND_BUF_SIZE 	127

#endif

/** Handle of the CLIConsole object (pointer to \ref CLIConsoleDesc structure) */
typedef struct CLIConsoleDesc* CLIConsole;

/// Type denoting action taken by the \ref CLI_ProcessConsole function
typedef enum {
	/// No action was taken
	CLI_NO_ACTION,
	/// A default action was taken (could not resolve which option call)
	CLI_DEFAULT_ACTION,
	/// User supplied function was called
	CLI_USER_ACTION,
	/// Console is busy
	CLI_BUSY,
} CLIConsoleAction;

/// Command Line Interface Console descriptor
struct CLIConsoleDesc {
    /// IODevice object associated with console
    IODevice iodevice;
    /// console state and work mode
   	struct {
    	/// bit indicating that the console is busy and unable to receive new charaters
   		uint8_t busy : 1;
   		/// bit indicating command line mode (1) or key press mode (0: default)
   		uint8_t multichar : 1;
   		uint8_t doublechar : 1;
    } state;
    /// external command processor handle
    void (*command_processor) (CLIConsole clic);
    /// command buffer
    char buf[CLI_COMMAND_BUF_SIZE];
    /// command buffer counter
    size_t cnt;
    /// command analyzer progress offset
    size_t offset;
};

/** \brief Macro that declares a \ref CLIConsole object
 *
 *  Declares a CLIConsole object in a convenient manner.
 *  \param name name of the new CLIConsole
 *  \param iodevice \ref an IODevice that will be associated with the console
 *  \param command_processor a function that will act as a command handler for CLIConsole
 *  \param attribute additional attributes for the CLIConsole variable such as 'static' or 'volatile' etc.
 */
#define CLI_DECLARE(name, iodevice, command_processor, attribute) \
	static struct CLIConsoleDesc name##_desc = {iodevice, {0,0,0}, command_processor, {0x00}, 0, 0 }; \
	attribute CLIConsole name = &name##_desc


/**
 * Creates the console object and associates it with a given IODevice object. Uses \ref hal_heap for memory
 * allocation. To delete the object created use \ref CLI_Destroy.
 *
 * \param iodevice IODevice on top of which the console operates
 * \return handle of the console, which in fact is a pointer to console's description structure
*/
CLIConsole CLI_Create(IODevice iodevice);

/**
 * Deletes the previously created console object. Uses \ref hal_heap to free the memory allocated by
 * a call to complementary \ref CLI_Create.
 *
 * \param cli console handle
*/
void CLI_Destroy(CLIConsole cli);

/**
 * Displays main screen on the console.
 *
 * \param cli console handle
*/
void CLI_DisplayMainScreen(CLIConsole cli);

/**
 *  CLI core processor function. It reads data from the IODevice object associated with console
 *  and processes it. If necessary, it calls the user supplied functions according to the recognized
 *  commands. It handles both hot-key and command line modes. In command line mode, external,
 *  user supplied command processor function is called (see \ref CLI_SetCommandProcessor).
 *
 *  \param cli console handle
*/
CLIConsoleAction CLI_ProcessConsole(CLIConsole cli);

/**
 * Sets the command processor function for command-line mode of operation.
 *
 * \param cli console handle
 * \param cmd_proc command processor function
*/
void CLI_SetCommandProcessor(CLIConsole cli, void (*cmd_proc) (CLIConsole cli));

/**
 * Forces the console to go into command mode.
 *
 * \param cli console handle
*/
void CLI_ForceCommandMode(CLIConsole cli);

/**
 *  Extracts and copies first item from the source command line to a destination
 *  buffer. This function initializes further processing of arguments on the
 *  provided command line. To sequentially get additional command line arguments
 *  use \ref CLI_GetNextArg or \ref CLI_GetNextArgInt32.
 *
 *  \param cli console handle
 *  \param dst destination buffer
 */
void CLI_GetCommand(CLIConsole cli, char* dst);

/**
 *  Checks if there is another argument on the command line.
 *
 *  \param cli console handle
 *  \return 0 if there are no more arguments or !0 if there are some more
 */
int CLI_IsNextArg(CLIConsole cli);

/**
 *  Extracts next argument from the command line as a string.
 *
 *  \param cli console handle
 *  \param arg destination buffer
 */
void CLI_GetNextArg(CLIConsole cli, char* arg);

/**
 *  Extracts next argument from the command line as a 32bit signed integer.
 *
 *  \param cli console handle
 *  \param arg pointer to destination variable where the argument will be stored
 *  \returns 0 if operation succeeded, !0 if failed
 *
 */
int CLI_GetNextArgInt32(CLIConsole cli, int32_t *arg);

/**
 *  Moves back argc arguments in the command line.
 *
 *  \param cli console handle
 *	\param argc number of arguments
 */
void CLI_GetBack(CLIConsole cli, int argc);


/**
 * \brief Disables input grabbing.
 *
 * Disables input grabbing. No data will be read from IODevice object.
 *
 * \param cli console handle
*/
#define CLI_HaltConsoleInput(cli)			do { cli->state.busy = 1; } while (0)

/**
 * \brief Enables input grabbing.
 *
 * Re-enables input grabbing (see also \ref CLI_HaltConsoleInput)
 * \param cli console handle
*/
#define CLI_EnableConsoleInput(cli)			do { cli->state.busy = 0; } while (0)

/**
 * \brief Gets IODevice associated with console.
 *
 * Returns the currently associated IODevice object on top of which the console operates.
 *
 * \param cli console handle
 * \return IODevice object associated with console.
*/
#define CLI_GetIODevice(cli)				(cli->iodevice)

/*@}*/

#endif /* HAL_CLI_H */

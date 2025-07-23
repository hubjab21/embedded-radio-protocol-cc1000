/*
================================================================================
 File:          hal_port_cli.c
--------------------------------------------------------------------------------
 Author:        Lukasz Krzak
 Purpose:       HAL CLI VT100 protocol handling
 Compiler:      GCC
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Includes:      
--------------------------------------------------------------------------------
 Comments:      
================================================================================
*/

#include "hal.h"
#include <string.h>
//#include "crt_itoa.h"

// VT100 cache buffer for local string operations
static char VT100_Cache[16] = {'\033','[','\0','\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };

extern char* itoa(int value, char* buf, int base);

// -----------------------------------------------------------------------------
//  CLI_PORT_CursorPosition
// -----------------------------------------------------------------------------
void CLI_PORT_CursorPosition (IODevice iodevice, int x, int y)
{
    itoa(y, VT100_Cache+3, 10);
    strcat(VT100_Cache+3, ";");
    itoa(x, VT100_Cache+3+strlen(VT100_Cache+3), 10);
    strcat(VT100_Cache+3, "H");
    IODEV_Write(iodevice, VT100_Cache, strlen(VT100_Cache+3)+3, 0);
    
} /* CLI_PORT_CursorPosition */


// -----------------------------------------------------------------------------
//  CLI_PORT_SaveCursor
// -----------------------------------------------------------------------------
void CLI_PORT_SaveCursor (IODevice iodevice)
{
	VT100_Cache[3] = '\033';
	VT100_Cache[4] = '\067';
	IODEV_Write(iodevice, VT100_Cache+3, 2, 0);
	
} /* CLI_PORT_SaveCursor */


// -----------------------------------------------------------------------------
//  CLI_PORT_RestoreCursor
// -----------------------------------------------------------------------------
void CLI_PORT_RestoreCursor (IODevice iodevice)
{
	VT100_Cache[3] = '\033';
	VT100_Cache[4] = '\070';
	IODEV_Write(iodevice, VT100_Cache+3, 2, 0);
	
} /* CLI_PORT_RestoreCursor */


// -----------------------------------------------------------------------------
//  CLI_PORT_CursorForward
// -----------------------------------------------------------------------------
void CLI_PORT_CursorForward (IODevice iodevice, int count)
{
	itoa(count, VT100_Cache+3, 10);
    strcat(VT100_Cache+3, "C");		
    IODEV_Write(iodevice, VT100_Cache, strlen(VT100_Cache+3)+3, 0);
    
} /* CLI_PORT_CursorForward */


// -----------------------------------------------------------------------------
//  CLI_PORT_CursorBackward
// -----------------------------------------------------------------------------
void CLI_PORT_CursorBackward (IODevice iodevice, int count)
{                                          
	itoa(count, VT100_Cache+3, 10);
    strcat(VT100_Cache+3, "D");		
    IODEV_Write(iodevice, VT100_Cache, strlen(VT100_Cache+3)+3, 0);
    
} /* CLI_PORT_CursorBackward */


// -----------------------------------------------------------------------------
//  CLI_PORT_CursorDown
// -----------------------------------------------------------------------------
void CLI_PORT_CursorDown (IODevice iodevice, int count)
{                                     
	itoa(count, VT100_Cache+3, 10);
    strcat(VT100_Cache+3, "B");		
    IODEV_Write(iodevice, VT100_Cache, strlen(VT100_Cache+3)+3, 0);
 
} /* CLI_PORT_CursorDown */

                                    
// -----------------------------------------------------------------------------
//  CLI_PORT_CursorUp
// -----------------------------------------------------------------------------
void CLI_PORT_CursorUp (IODevice iodevice, int count)
{
	itoa(count, VT100_Cache+3, 10);
    strcat(VT100_Cache+3, "A");		
    IODEV_Write(iodevice, VT100_Cache, strlen(VT100_Cache+3)+3, 0);
 
} /* CLI_PORT_CursorUp */


// -----------------------------------------------------------------------------
//  CLI_PORT_EraseDisplay
// -----------------------------------------------------------------------------
void CLI_PORT_EraseDisplay (IODevice iodevice)
{
	VT100_Cache[3] = (uint8_t)2+48;
	VT100_Cache[4] = 'J';
    IODEV_Write(iodevice, VT100_Cache, 5, 0);
} /* CLI_PORT_EraseInDisplay */


// -----------------------------------------------------------------------------
//  CLI_PORT_SetTopAndBottomMarg
// -----------------------------------------------------------------------------
void CLI_PORT_SetTopAndBottomMarg (IODevice iodevice, int top, int bottom)
{
    itoa(top, VT100_Cache+3, 10);
    strcat(VT100_Cache+3, ";");
    itoa(bottom, VT100_Cache+3+strlen(VT100_Cache+3), 10);
    strcat(VT100_Cache+3, "r");    
    IODEV_Write(iodevice, VT100_Cache, strlen(VT100_Cache+3)+3, 0);

} /* CLI_PORT_SetTopAndBottomMarg */

/*! \file vt100.c
    \brief VT100 protocol library

    Library for the VT100 protocol.
 */

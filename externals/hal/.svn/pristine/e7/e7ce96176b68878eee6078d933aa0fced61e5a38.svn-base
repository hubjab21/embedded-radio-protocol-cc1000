/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_usart_poll.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's AVR port
 Compiler:      %COMPILER%
 Hardware:      AVR
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for AVR (USART)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

// TODO: remove that!
#ifndef F_CPU
#define F_CPU 8000000
#endif

#include "hal_iodevice.h"

#include <avr/io.h>
#include "hal_port_io_usart.h"

#if (HAL_IO_OS_INTEGRATION)
#include "hal_os.h"
#endif

// function prototypes
HALRESULT HAL_PORT_USART_POLL_Init(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_Deinit(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_EnableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_DisableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_EnableRead(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_DisableRead(USART_IODevice dev);
size_t HAL_PORT_USART_POLL_GetReadCount(USART_IODevice dev);
size_t HAL_PORT_USART_POLL_GetWriteSpace(USART_IODevice dev);
size_t HAL_PORT_USART_POLL_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_USART_POLL_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout);

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
struct USART_IODeviceDesc io_usart0_poll = {
    // base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_POLL_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_POLL_Read
#if defined HAL_IO_USE_EVENTS && (HAL_IO_USE_EVENTS != 0)
        ,
        .EventHandler = NULL
#endif // HAL_IO_USE_EVENTS
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
        ,
        .lock = NULL,
        .rx_notifier = { NULL, 0 },
        .tx_notifier = { NULL, 0 }
#endif // HAL_IO_OS_INTEGRATION
    },
    // port extensions:
    NULL,
    NULL
};
#endif // HALPORT_USE_USART0


#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
struct USART_IODeviceDesc io_usart1_poll = {
    // base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_POLL_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_POLL_Read
#if defined HAL_IO_USE_EVENTS && (HAL_IO_USE_EVENTS != 0)
        ,
        .EventHandler = NULL
#endif // HAL_IO_USE_EVENTS
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
        ,
        .lock = NULL,
        .rx_notifier = { NULL, 0 },
        .tx_notifier = { NULL, 0 }
#endif // HAL_IO_OS_INTEGRATION
    },
    // port extensions:
    NULL,
    NULL
};
#endif // HALPORT_USE_USART1



// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_Init(USART_IODevice dev)
{

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_poll) {
		// 8N1, double transmission speed = 0, multi-processor mode = 0
#if defined PRUSART0
		PRR0 &= ~PRUSART0;
#endif
		
		// RXCn TXCn UDREn FEn DORn UPEn U2Xn MPCMn
		//  0    0    0     0   0    0    0    0
		UCSR0A = 0x00;
		// RXCIEn TXCIEn UDRIEn RXENn TXENn UCSZn2 RXB8n TXB8n
		//  0      0      0      0     0     0      0     0
		UCSR0B = 0x00;
		// –  UMSELn UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
		// 0   0      0     0     0     1      1      0
		//     |      |     |     |     |      |
		//     |      |     |     |     ---------> 8-bit
		//     |      |     |     --> one stop bit
		//     |      ---------> no parity
		//     --> asynchronous operation
		UCSR0C = 0x06;
		#define USART0_BAUD_RATE_PRESC  (((F_CPU/16)/HALPORT_USART0_DEFAULT_BAUDRATE)-1)
		UBRR0H = (uint8_t)(USART0_BAUD_RATE_PRESC >> 8);
        UBRR0L = (uint8_t)(USART0_BAUD_RATE_PRESC);
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	
#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

#if defined PRUSART1
		PRR1 &= ~PRUSART1;
#endif
		// 8N1, double transmission speed = 0, multi-processor mode = 0
		
		// RXCn TXCn UDREn FEn DORn UPEn U2Xn MPCMn
		//  0    0    0     0   0    0    0    0
		UCSR1A = 0x00;
		// RXCIEn TXCIEn UDRIEn RXENn TXENn UCSZn2 RXB8n TXB8n
		//  0      0      0      0     0     0      0     0
		UCSR1B = 0x00;
		// –  UMSELn UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
		// 0   0      0     0     0     1      1      0
		//     |      |     |     |     |      |
		//     |      |     |     |     ---------> 8-bit
		//     |      |     |     --> one stop bit
		//     |      ---------> no parity
		//     --> asynchronous operation
		UCSR1C = 0x06;
		#define USART1_BAUD_RATE_PRESC  (((F_CPU/16)/HALPORT_USART1_DEFAULT_BAUDRATE)-1)
		UBRR1H = (uint8_t)(USART1_BAUD_RATE_PRESC >> 8);
        UBRR1L = (uint8_t)(USART1_BAUD_RATE_PRESC);
		#undef USART1_BAUD_RATE_PRESC
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_Deinit(USART_IODevice dev)
{
    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_EnableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_poll) {
	    // set TXEN to 1
		UCSR0B |= (1<<TXEN0);
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {
	    // set TXEN to 1
		UCSR1B |= (1<<TXEN1);
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_DisableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_poll) {
	    // set TXEN to 0
		UCSR0B &= ~(1<<TXEN0);
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {
	    // set TXEN to 0
		UCSR1B &= ~(1<<TXEN1);
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_EnableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_poll) {
	    // set RXEN to 0
		UCSR0B &= ~(1<<RXEN0);
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {
	    // set RXEN to 1
		UCSR1B |= (1<<RXEN1);
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_DisableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {
	    // set RXEN to 0
		UCSR0B &= ~(1<<RXEN0);
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {
	    // set RXEN to 0
		UCSR1B &= ~(1<<RXEN1);
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_GetReadCount(USART_IODevice dev)
{

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {
		if (UCSR0A & (1<<RXC0)) {
			// RXC bit set, there are unread data in the receive buffer
			return 1;
		}
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {
		if (UCSR1A & (1<<RXC1)) {
			// RXC bit set, there are unread data in the receive buffer
			return 1;
		}
	}
#endif

    return 0;

} /* HAL_PORT_USART_POLL_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_GetWriteSpace(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {
		if (UCSR0A & (1<<UDRE0)) {
			// UDRE bit set, UDR is ready to receive data
			return 1;
		}
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {
		if (UCSR1A & (1<<UDRE1)) {
			// UDRE bit set, UDR is ready to receive data
			return 1;
		}
	}
#endif

    return 0;

} /* HAL_PORT_USART_POLL_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout)
{
    size_t i = size;

    if (data) {

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
		if (dev == &io_usart0_poll) {
			while (i--) {
				// wait for data, until RXC bit is set
				while (0 == (UCSR0A & (1<<RXC0))) {
					;
				}
				*((uint8_t*)(data)) = (uint8_t)(UDR0);
#if(HAL_IO_USE_EVENTS)
				// if declared - call EventHandler
				if (dev->iodev.EventHandler) {
					dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_RECEPTION, (void*)data, 1);
				}

#endif
				data = (void*)((size_t)data + 1);
			}
			return size;
		}
#endif // HALPORT_USE_USART0
		
#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
		if (dev == &io_usart1_poll) {
			while (i--) {
				// wait for data, until RXC bit is set
				while (0 == (UCSR1A & (1<<RXC1))) {
					;
				}
				*((uint8_t*)(data)) = (uint8_t)(UDR1);
#if(HAL_IO_USE_EVENTS)
				// if declared - call EventHandler
				if (dev->iodev.EventHandler) {
					dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_RECEPTION, (void*)data, 1);
				}

#endif
				data = (void*)((size_t)data + 1);

			}		
			return size;
		}
#endif // HALPORT_USE_USART1		
		
    } // if (data)

    return 0;

} /* HAL_PORT_USART_POLL_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout)
{

    uint8_t* ptr;
    size_t i;

    ptr = (uint8_t*)data;
    i = size;

    if (data) {
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
		if (dev == &io_usart0_poll) {
			while (i--) {			
				// wait until UDR register is ready
				while (0 == (UCSR0A & (1<<UDRE0))) {
					;
				}
				UDR0 = *ptr;
	#if(HAL_IO_USE_EVENTS)

				// if declared - call EventHandler
				if (dev->iodev.EventHandler) {
					dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_TRANSMISSION, (void*)ptr, 1);
				}

	#endif
				ptr++;
			}

			return  size;
		}
#endif // HALPORT_USE_USART0

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)	
		if (dev == &io_usart1_poll) {
			while (i--) {			
				// wait until UDR register is ready
				while (0 == (UCSR1A & (1<<UDRE1))) {
					;
				}
				UDR1 = *ptr;
	#if(HAL_IO_USE_EVENTS)

				// if declared - call EventHandler
				if (dev->iodev.EventHandler) {
					dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_TRANSMISSION, (void*)ptr, 1);
				}

	#endif
				ptr++;
			}

			return  size;
		}
#endif // HALPORT_USE_USART1
    } // if (data)

    return 0;

} /* HAL_PORT_USART_POLL_Write */


/*! \file hal_port_usart_poll.c
    \brief AVR USART port in polling mode
*/

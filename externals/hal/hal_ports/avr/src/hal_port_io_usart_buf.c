/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_usart_buf.c
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

#include "hal_iodevice.h"

#include <avr/io.h>
#include "hal_port_io_usart.h"

#if (HAL_IO_OS_INTEGRATION)
#include "hal_os.h"
#endif

// function prototypes
HALRESULT HAL_PORT_USART_BUF_Init(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_Deinit(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_EnableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_DisableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_EnableRead(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_DisableRead(USART_IODevice dev);
size_t HAL_PORT_USART_BUF_GetReadCount(USART_IODevice dev);
size_t HAL_PORT_USART_BUF_GetWriteSpace(USART_IODevice dev);
size_t HAL_PORT_USART_BUF_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_USART_BUF_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout);

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

IOBUF_DECLARE(io_usart0_txbuf, HALPORT_USART0_TXBUF_SIZE, 1);
IOBUF_DECLARE(io_usart0_rxbuf, HALPORT_USART0_RXBUF_SIZE, 1);

struct USART_IODeviceDesc io_usart0_buf = {
    // base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_BUF_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_BUF_Read
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
    .tx_buf = &io_usart0_txbuf,
    .rx_buf = &io_usart0_rxbuf
};
#endif // HALPORT_USE_USART0


#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

IOBUF_DECLARE(io_usart1_txbuf, HALPORT_USART1_TXBUF_SIZE, 1);
IOBUF_DECLARE(io_usart1_rxbuf, HALPORT_USART1_RXBUF_SIZE, 1);

struct USART_IODeviceDesc io_usart1_buf = {
    // base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_BUF_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_BUF_Read
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
    .tx_buf = &io_usart1_txbuf,
    .rx_buf = &io_usart1_rxbuf
};
#endif // HALPORT_USE_USART1



// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_Init(USART_IODevice dev)
{

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_buf) {
		// 8N1, double transmission speed = 0, multi-processor mode = 0
		
		// RXCn TXCn UDREn FEn DORn UPEn U2Xn MPCMn
		//  0    0    0     0   0    0    0    0
		UCSR0A = 0x00;
		// RXCIEn TXCIEn UDRIEn RXENn TXENn UCSZn2 RXB8n TXB8n
		//  0      0      0      0     0     0      0     0
		UCSR0B = 0x00;
		// â€“  UMSELn UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
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
	if (dev == &io_usart1_buf) {
		// 8N1, double transmission speed = 0, multi-processor mode = 0
		
		// RXCn TXCn UDREn FEn DORn UPEn U2Xn MPCMn
		//  0    0    0     0   0    0    0    0
		UCSR1A = 0x00;
		// RXCIEn TXCIEn UDRIEn RXENn TXENn UCSZn2 RXB8n TXB8n
		//  0      0      0      0     0     0      0     0
		UCSR1B = 0x00;
		// â€“  UMSELn UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
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
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_Deinit(USART_IODevice dev)
{
    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_EnableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_buf) {
	    // set TXEN and UDRIE to 1
		CORE_PORT_EnterCritical();
		UCSR0B |= (1<<TXEN0) | (1<<UDRIE0);
		CORE_PORT_ExitCritical();
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {
	    // set TXEN and UDRIE to 1
		CORE_PORT_EnterCritical();
		UCSR1B |= (1<<TXEN1) | (1<<UDRIE1);
		CORE_PORT_ExitCritical();
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_DisableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_buf) {
	    // set TXEN and UDRIE to 0
		CORE_PORT_EnterCritical();
		UCSR0B &= ~((1<<TXEN0) | (1<<UDRIE0));
		CORE_PORT_ExitCritical();
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {
	    // set TXEN and UDRIE to 0
		CORE_PORT_EnterCritical();
		UCSR1B &= ~((1<<TXEN1) | (1<<UDRIE1));
		CORE_PORT_ExitCritical();
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_EnableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_buf) {
	    // set RXEN and RXCIE to 1
		CORE_PORT_EnterCritical();
		UCSR0B |= (1<<RXEN0) | (1<<RXCIE0);
		CORE_PORT_ExitCritical();
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {
	    // set RXEN and RXCIE to 1
		CORE_PORT_EnterCritical();
		UCSR1B |= (1<<RXEN1) | (1<<RXCIE1);
		CORE_PORT_ExitCritical();
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_DisableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {
	    // set RXEN and RXCIE to 0
		CORE_PORT_EnterCritical();
		UCSR0B &= ~((1<<RXEN0) | (1<<RXCIE0));
		CORE_PORT_ExitCritical();
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {
	    // set RXEN and RXCIE to 0
		CORE_PORT_EnterCritical();
		UCSR1B &= ~((1<<RXEN1) | (1<<RXCIE1));
		CORE_PORT_ExitCritical();
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_GetReadCount(USART_IODevice dev)
{
	return IOBUF_GetCount(dev->rx_buf);

} /* HAL_PORT_USART_BUF_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_GetWriteSpace(USART_IODevice dev)
{
	return IOBUF_GetSpace(dev->tx_buf);

} /* HAL_PORT_USART_BUF_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout)
{
    return IOBUF_Read(dev->rx_buf, data, size);
	
} /* HAL_PORT_USART_BUF_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout)
{
	
	size = IOBUF_Write(dev->tx_buf, data, size);

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)	
	if (dev == &io_usart0_buf) {
	    // set UDRIE to 1
		CORE_PORT_EnterCritical();
		UCSR0B |= (1<<UDRIE0);
		CORE_PORT_ExitCritical();
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {
	    // set UDRIE to 1
		CORE_PORT_EnterCritical();
		UCSR1B |= (1<<UDRIE1);
		CORE_PORT_ExitCritical();
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	
    return size;

} /* HAL_PORT_USART_BUF_Write */


#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

// -----------------------------------------------------------------------------
//  USART0 data received interrupt handler
// -----------------------------------------------------------------------------
ISR(USART0_RX_vect)
{
	volatile uint8_t data;
	
	// get data from USART register
	data = UDR0;
	// insert it into IOBuffer
	IOBUF_WriteFast(&io_usart0_rxbuf, (const void*)&data);
	
} // ISR(USART0_RX_vect)


// -----------------------------------------------------------------------------
//  USART0 data register empty interrupt handler
// -----------------------------------------------------------------------------
ISR(USART0_UDRE_vect)
{
	volatile uint8_t data;
	
	// This has to be present so that CORE_ExitCritical() wouldn't reenable interrupts to soon
	// in a call to IOBUF_Read
	//HAL_PORT_InterruptState++;
		
	// try to read byte from buffer
	if (IOBUF_ReadFast(&io_usart0_txbuf, (void*)&data)) {
		// put in into USART data register
		UDR0 = data;
	} else {
	    // no more data to send, disable UDR interrupt
		UCSR0B &= ~(1<<UDRIE0);
	}
	
	// roll-back interrupt state
	//HAL_PORT_InterruptState--;
	
} // ISR(USART0_UDRE_vect)


// -----------------------------------------------------------------------------
//  USART0 transmission complete interrupt handler
// -----------------------------------------------------------------------------
ISR(USART0_TX_vect)
{

} // ISR(USART0_TX_vect)

#endif // HALPORT_USE_USART0


#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

// -----------------------------------------------------------------------------
//  USART1 data received interrupt handler
// -----------------------------------------------------------------------------
ISR(USART1_RX_vect)
{
	volatile uint8_t data;

	// get data from USART register
	data = UDR1;
	// insert it into IOBuffer
	IOBUF_WriteFast(&io_usart1_rxbuf, (const void*)&data);

} // ISR(USART1_RX_vect)


// -----------------------------------------------------------------------------
//  USART1 data register empty interrupt handler
// -----------------------------------------------------------------------------
ISR(USART1_UDRE_vect)
{
	volatile uint8_t data;
	
	// This has to be present so that CORE_ExitCritical() wouldn't reenable interrupts to soon
	// in a call to IOBUF_Read
//	HAL_PORT_InterruptState++;
		
	// try to read byte from buffer
	if (IOBUF_ReadFast(&io_usart1_txbuf, (void*)&data)) {
		// put in into USART data register
		UDR1 = data;
	} else {
	    // no more data to send, disable UDR interrupt
		UCSR1B &= ~(1<<UDRIE1);
	}
	
	// roll-back interrupt state
//	HAL_PORT_InterruptState--;
	
} // ISR(USART1_UDRE_vect)


// -----------------------------------------------------------------------------
//  USART1 transmission complete interrupt handler
// -----------------------------------------------------------------------------
ISR(USART1_TX_vect)
{

} // ISR(USART1_TX_vect)

#endif // HALPORT_USE_USART1


/*! \file hal_port_usart_buf.c
    \brief AVR USART port in buffered mode
*/

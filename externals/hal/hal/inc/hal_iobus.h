/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_iobus.h
 Author:        Lukasz Duda
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL IOBus API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_IOBUS_H_
#define HAL_IOBUS_H_

// -----------------------------------------------------------------------------
//  IOBus structure
// -----------------------------------------------------------------------------

typedef enum{
	IOBUS_Ready = 0,
	IOBUS_Busy
} IOBUS_TransactionState;

// type of IO Bus Address
typedef uint64_t IOBusAddr;

typedef struct IOBusDesc* IOBus;
struct IOBusDesc {
	// variables
	IOBUS_TransactionState state;
	// methods
    HALRESULT (*Init)(IOBus);
    HALRESULT (*Deinit)(IOBus);
    HALRESULT (*EnableWrite)(IOBus);
    HALRESULT (*DisableWrite)(IOBus);
    HALRESULT (*EnableRead)(IOBus);
    HALRESULT (*DisableRead)(IOBus);
    size_t (*GetReadCount)(IOBus);
    size_t (*GetWriteSpace)(IOBus);
    size_t (*Read)(IOBus, IOBusAddr, void*, size_t, IOTime);
    size_t (*Write)(IOBus, IOBusAddr, const void*, size_t, IOTime);
    HALRESULT (*StartTransaction)(IOBus);
    HALRESULT (*EndTransaction)(IOBus);
    size_t (*RawWrite)(IOBus, const void*, size_t, IOTime);
    size_t (*SearchDevices)(IOBus, IOBusAddr*, IOTime);
};

// -----------------------------------------------------------------------------
//  PUBLIC API
// -----------------------------------------------------------------------------

#define IOBUS_Init(iobus)                     		   	 (iobus)->Init((iobus))

#define IOBUS_Deinit(iobus)                    		 	 (iobus)->Deinit((iobus))

#define IOBUS_EnableWrite(iobus)                     	 (iobus)->EnableWrite((iobus))

#define IOBUS_DisableWrite(iobus)                     	 (iobus)->DisableWrite((iobus))

#define IOBUS_EnableRead(iobus)                       	 (iobus)->EnableRead((iobus))

#define IOBUS_DisableRead(iobus)                      	 (iobus)->DisableRead((iobus))

#define IOBUS_GetReadCount(iobus)                     	 (iobus)->GetReadCount((iobus))

#define IOBUS_GetWriteSpace(iobus)                    	 (iobus)->GetWriteSpace((iobus))

#define IOBUS_Read(iobus, addr, data, size, timeout)  	 (iobus)->Read((iobus), (addr), (data), (size), (timeout))

#define IOBUS_Write(iobus, addr, data, size, timeout) 	 (iobus)->Write((iobus), (addr), (data), (size), (timeout))

#define IOBUS_StartTransaction(iobus)					 (iobus)->StartTransaction((iobus))

#define IOBUS_EndTransaction(iobus)						 (iobus)->EndTransaction((iobus))

#define IOBUS_RawWrite(iobus, data, size, timeout)		 (iobus)->RawWrite((iobus), (data), (size), (timeout))

#define IOBUS_SearchDevices(iobus, data, timeout)	     (iobus)->SearchDevices((iobus), (data), (timeout))

// -----------------------------------------------------------------------------
//  IOBusDevice Structure
// -----------------------------------------------------------------------------

struct IOBusDeviceDesc{
	IOBus bus;
	IOBusAddr address;
	void* param;
};

typedef struct IOBusDeviceDesc* IOBusDevice;

// -----------------------------------------------------------------------------
//  Declaration of new IOBus Device (obviously, name must be different)
// -----------------------------------------------------------------------------

#define IOBUS_DEVICE_DECLARE(name, IOBus, addr, parameters)					\
		struct IOBusDeviceDesc name ## _desc = {							\
			.bus = (IOBus),													\
			.address = (addr),												\
			.param = (parameters)											\
		};																	\
		IOBusDevice name = &name ## _desc;


#endif /* HAL_IOBUS_H_ */

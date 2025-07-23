/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_os.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED's OS port
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       OS module port for non-OS implementation
--------------------------------------------------------------------------------
 Comments:		a lot of stubs, counting semaphore not functional!
================================================================================
*/

// -----------------------------------------------------------------------------
//  OS CORE PORT
// -----------------------------------------------------------------------------

typedef int OSTime;

#define OS_PORT_Start()							do { ;  } while (0)

#define OS_PORT_Stop()							do { ;  } while (0)

#define OS_PORT_Sleep(ticks)   					do { ;  } while (0)

#define OS_PORT_SleepUntil(time)				do { ;  } while (0)

#define OS_PORT_GetSystemTime()					(0)

// -----------------------------------------------------------------------------
//  OS TASK PORT
// -----------------------------------------------------------------------------

typedef int OSTask;

#define OSTASK_PORT_Create(task_impl, priority, stack_size, arg)		(0)

#define OSTASK_PORT_Destroy(task)				do { ;  } while (0)

#define OSTASK_PORT_Suspend(task)				do { ;  } while (0)

#define OSTASK_PORT_Resume(task)				do { ;  } while (0)

#define OSTASK_PORT_Yield()						do { ;  } while (0)

#define OSTASK_PORT_SetPriority(task, priority) do { ;  } while (0)

#define OSTASK_PORT_GetPriority(task)			(0)

#define OSTASK_PORT_GetCurrentTask()			(0)

// -----------------------------------------------------------------------------
//  OS SEM PORT
// -----------------------------------------------------------------------------

typedef int* OSSem;

OSSem OSSEM_PORT_Create(void);

void OSSEM_PORT_Destroy(OSSem sem);


void OSSEM_PORT_Give(OSSem sem);

int OSSEM_PORT_Take(OSSem sem, int timeout); 

// -----------------------------------------------------------------------------
//  OS CNTSEM PORT
// -----------------------------------------------------------------------------

typedef int* OSCntSem;

OSSem OSCNTSEM_PORT_Create(int init, int max);

void OSCNTSEM_PORT_Destroy(OSSem sem);



// -----------------------------------------------------------------------------
//  OS MUTEX PORT
// -----------------------------------------------------------------------------

typedef int* OSMutex;

#define OSMUTEX_PORT_Create()					OSSEM_PORT_Create()

#define OSMUTEX_PORT_Destroy(mutex) 			OSSEM_PORT_Destroy((mutex))

#define OSMUTEX_PORT_Give(mutex) 				OSSEM_PORT_Give((mutex))

#define OSMUTEX_PORT_Take(mutex, timeout) 		OSSEM_PORT_Take((mutex), (timeout))



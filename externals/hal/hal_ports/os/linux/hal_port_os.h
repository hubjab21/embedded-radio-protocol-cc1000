/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_os.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED's OS port for pthreads
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       OS module port for pthreads
--------------------------------------------------------------------------------
 Comments:		uses pthread_mutex_timedlock_np (non-portable) for
                OSMUTEX_PORT_Take implementation
================================================================================
*/

#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

// -----------------------------------------------------------------------------
//  OS CORE PORT
// -----------------------------------------------------------------------------

typedef unsigned int OSTime;

void OS_PORT_Start(void);

void OS_PORT_Stop(void);

#define OS_PORT_Sleep(ticks)					usleep(((ticks)*1000))

#define OS_PORT_GetSystemTime()					times(0)

// -----------------------------------------------------------------------------
//  OS TASK PORT
// -----------------------------------------------------------------------------


typedef pthread_t OSTask;

#define OSTASK(name)							void* name (void* arg)

OSTask OSTASK_PORT_Create(void (*task_impl)(void*), int priority, size_t stack_size, void* arg);

#define OSTASK_PORT_Destroy(task)

#define OSTASK_PORT_Suspend(task)

#define OSTASK_PORT_Resume(task)

#define OSTASK_PORT_Yield()						pthread_yield()

#define OSTASK_PORT_SetPriority(task, priority)

#define OSTASK_PORT_GetPriority(task)

#define OSTASK_PORT_GetCurrentTask()			pthread_self()


// -----------------------------------------------------------------------------
//  OS SEM PORT
// -----------------------------------------------------------------------------

typedef pthread_mutex_t* OSSem;

OSSem OSSEM_PORT_Create(void);

void OSSEM_PORT_Destroy(OSSem sem);

#define OSSEM_PORT_Give(sem) 					pthread_mutex_unlock(sem)

int OSSEM_PORT_Take(OSSem sem, uint32_t timeout);

// -----------------------------------------------------------------------------
//  OS CNTSEM PORT
// -----------------------------------------------------------------------------

typedef sem_t* OSCntSem;

OSCntSem OSCNTSEM_PORT_Create(int init, int max);

void OSCNTSEM_PORT_Destroy(OSCntSem sem);

#define OSCNTSEM_PORT_Give(sem)					sem_post((sem))

int OSCNTSEM_PORT_Take(OSCntSem sem, uint32_t timeout);

// -----------------------------------------------------------------------------
//  OS MUTEX PORT
// -----------------------------------------------------------------------------

typedef pthread_mutex_t* OSMutex;

OSMutex OSMUTEX_PORT_Create(void);

void OSMUTEX_PORT_Destroy(OSMutex mutex);

#define OSMUTEX_PORT_Give(mutex)				pthread_mutex_unlock(mutex)

int OSMUTEX_PORT_Take(OSMutex mutex, uint32_t timeout);



/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_os.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's OS port for pthreads
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       OS module port for pthreads
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


#include <pthread.h>
#include <semaphore.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include "hal_port_os.h"

typedef struct {
	void (*task_impl)(void*);
	void *arg;
} ostask_pthread_desc;

static int os_started = 0;
static pthread_mutex_t ostask_suspend_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t ostask_suspend_cond = PTHREAD_COND_INITIALIZER;

static int os_stopped = 0;
static pthread_mutex_t ostask_stop_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t ostask_stop_cond = PTHREAD_COND_INITIALIZER;


// -----------------------------------------------------------------------------
//  OSTASK_pthread_wrapper
// -----------------------------------------------------------------------------
void* OSTASK_pthread_wrapper(void* arg)
{
	// wait until OS starts
/*	pthread_mutex_lock(&ostask_suspend_mutex);
	while (os_started == 0) {
		pthread_cond_wait(&ostask_suspend_cond, &ostask_suspend_mutex);
	}
	pthread_mutex_unlock(&ostask_suspend_mutex);
*/
	// run the task
	((ostask_pthread_desc*)arg)->task_impl(((ostask_pthread_desc*)arg)->arg);
	// free task descriptor
	free(arg);
	// exit pthread
	pthread_exit(NULL);
} /* OSTASK_pthread_wrapper */


// -----------------------------------------------------------------------------
//  OSTASK_PORT_Create
// -----------------------------------------------------------------------------
OSTask OSTASK_PORT_Create(void (*task_impl)(void*), int priority, size_t stack_size, void* arg)
{
	OSTask task;
	pthread_attr_t attr;
	ostask_pthread_desc *thread_desc;
	int result;

	thread_desc = (ostask_pthread_desc*)malloc(sizeof(ostask_pthread_desc));
	if (thread_desc) {
		thread_desc->task_impl = task_impl;
		thread_desc->arg = arg;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		result = pthread_create(&task, NULL, OSTASK_pthread_wrapper, (void*)thread_desc);
		pthread_attr_destroy(&attr);
		if (result) {
			return 0;
		}
	}
	return task;

} /* OSTASK_PORT_Create */


// -----------------------------------------------------------------------------
//  OSSEM_PORT_Create
// -----------------------------------------------------------------------------
OSSem OSSEM_PORT_Create(void)
{
	pthread_mutex_t* mutex;

	// create mutex without priority inversion mechanism as a binary semaphore
	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	if (mutex) {
		// initialize mutex
		if (0 != pthread_mutex_init(mutex, NULL)) {
			// error!
			free(mutex);
			return NULL;
		} else {
			// take the mutex
			pthread_mutex_lock(mutex);
		}
	}

	return mutex;
} /* OSSEM_PORT_Create */


// -----------------------------------------------------------------------------
//  OSSEM_PORT_Destroy
// -----------------------------------------------------------------------------
void OSSEM_PORT_Destroy(OSSem sem)
{
	if (sem) {
		pthread_mutex_destroy(sem);
		free(sem);
	}
} /* OSSEM_PORT_Destroy */


// -----------------------------------------------------------------------------
//  OSSEM_PORT_Take
// -----------------------------------------------------------------------------
int OSSEM_PORT_Take(OSSem sem, uint32_t timeout)
{
	struct timespec abstime;
	uint32_t secs, nsecs;

	clock_gettime(CLOCK_REALTIME, &abstime);

	secs = timeout/1000;
	abstime.tv_sec += secs;
	abstime.tv_nsec += timeout - (secs*1000);

	if (abstime.tv_nsec > 1000000000) {
		abstime.tv_nsec -= 	1000000000;
		abstime.tv_sec++;
	}

	return pthread_mutex_timedlock(sem, &abstime);

} /* OSSEM_PORT_Take */

// -----------------------------------------------------------------------------
//  OSCNTSEM_PORT_Create
// -----------------------------------------------------------------------------
OSCntSem OSCNTSEM_PORT_Create(int init, int max)
{
	sem_t* sem;

	// create semaphore
	sem = (sem_t*)malloc(sizeof(sem_t));
	if (sem) {
		// initialize semaphore
		if (0 != sem_init(sem, 0, 0)) {
			// error!
			free(sem);
			return NULL;
		}
	}

	return sem;
} /* OSCNTSEM_PORT_Create */


// -----------------------------------------------------------------------------
//  OSCNTSEM_PORT_Destroy
// -----------------------------------------------------------------------------
void OSCNTSEM_PORT_Destroy(OSCntSem sem)
{
	if (sem) {
		sem_destroy(sem);
		free(sem);
	}
} /* OSCNTSEM_PORT_Destroy */


// -----------------------------------------------------------------------------
//  OSCNTSEM_PORT_Take
// -----------------------------------------------------------------------------
int OSCNTSEM_PORT_Take(OSCntSem sem, uint32_t timeout)
{
	struct timespec abstime;
	uint32_t secs, nsecs;
	int val;

	clock_gettime(CLOCK_REALTIME, &abstime);

	secs = timeout/1000;
	abstime.tv_sec += secs;
	abstime.tv_nsec += timeout - (secs*1000);

	if (abstime.tv_nsec > 1000000000) {
		abstime.tv_nsec -= 	1000000000;
		abstime.tv_sec++;
	}

	return sem_timedwait(sem, &abstime);

} /* OSCNTSEM_PORT_Take */


// -----------------------------------------------------------------------------
//  OSMUTEX_PORT_Create
// -----------------------------------------------------------------------------
OSMutex OSMUTEX_PORT_Create(void)
{
	pthread_mutex_t* mutex;

	// create mutex
	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	if (mutex) {
		// initialize mutex
		if (0 != pthread_mutex_init(mutex, NULL)) {
			// error!
			free(mutex);
			return NULL;
		}
	}

	return mutex;

} /* OSMUTEX_PORT_Create */


// -----------------------------------------------------------------------------
//  OSMUTEX_PORT_Destroy
// -----------------------------------------------------------------------------
void OSMUTEX_PORT_Destroy(OSMutex mutex)
{
	if (mutex) {
		 pthread_mutex_destroy(mutex);
		 free(mutex);
	}
} /* OSMUTEX_PORT_Destroy */


// -----------------------------------------------------------------------------
//  OSMUTEX_PORT_Take
// -----------------------------------------------------------------------------
int OSMUTEX_PORT_Take(OSMutex mutex, uint32_t timeout)
{
	struct timespec abstime;
	uint32_t secs, nsecs;

	clock_gettime(CLOCK_REALTIME, &abstime);

	secs = timeout/1000;
	abstime.tv_sec += secs;
	abstime.tv_nsec += timeout - (secs*1000);

	if (abstime.tv_nsec > 1000000000) {
		abstime.tv_nsec -= 	1000000000;
		abstime.tv_sec++;
	}

	return pthread_mutex_timedlock(mutex, &abstime);

} /* OSMUTEX_PORT_Take */


// -----------------------------------------------------------------------------
//  OS_PORT_Start
// -----------------------------------------------------------------------------
void OS_PORT_Start(void)
{
	// start all suspended threads
	pthread_mutex_lock(&ostask_suspend_mutex);
	os_started = 1;
	pthread_mutex_unlock(&ostask_suspend_mutex);
	pthread_cond_broadcast(&ostask_suspend_cond);

	// wait until OS stops
	pthread_mutex_lock(&ostask_stop_mutex);
	while (os_stopped == 0) {
		pthread_cond_wait(&ostask_stop_cond, &ostask_stop_mutex);
	}
	pthread_mutex_unlock(&ostask_stop_mutex);


} /* OS_PORT_Start */


// -----------------------------------------------------------------------------
//  OS_PORT_Stop
// -----------------------------------------------------------------------------
void OS_PORT_Stop(void)
{
	pthread_mutex_lock(&ostask_stop_mutex);
	os_stopped = 1;
	pthread_mutex_unlock(&ostask_stop_mutex);
	pthread_cond_broadcast(&ostask_stop_cond);

} /* OS_PORT_Stop */

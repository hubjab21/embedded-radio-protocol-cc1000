/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			mortal_thread.hpp
 Author:        Lukasz Krzak
 Purpose:       HALFRED's C++ wrappers
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       MortalThread class
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef MORTAL_THREAD_HPP
#define MORTAL_THREAD_HPP

#include "hal.h"

namespace halfred {

class MortalThread
{
private:
	OSTask task;
	OSMutex runMux;
	OSMutex termMux;
	sig_atomic_t sigterm;
	bool isTerminated();
public:
	MortalThread(void (*threadFunc)(void*), int priority, void* arg = 0, size_t stackSize = 0);
	bool run(unsigned int timeout);
	bool terminate(unsigned int timeout = 0);
	bool waitForTermination(unsigned int timeout);
};

} // namespace halfred


#endif // MORTAL_THREAD_HPP

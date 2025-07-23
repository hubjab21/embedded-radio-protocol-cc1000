/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			diag_channel.cpp
 Author:        Lukasz Krzak
 Purpose:       HALFRED's C++ wrappers
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       DiagChannel class
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "diag_channel.hpp"

using namespace halfred;

// Utility class for the 'header' manipulator
class halfred::DiagChannelHeaderSetter
{
friend class DiagChannel;
private:
	const char* headerName;
public:
	void setHeader(const char* hn)	{
		headerName = hn;
	}
};

// Utility object for the 'header' manipulator
static DiagChannelHeaderSetter headerSetter;


// -----------------------------------------------------------------------------
//  DiagChannel::DiagChannel
// -----------------------------------------------------------------------------
DiagChannel::DiagChannel(int channelNo, IODevice outputDevice, uint32_t (*clockSource)(void), int lockTimeout)
{
	channel = channelNo;
	calcBase = 10;
	precision = 8;
	timeout = lockTimeout;

	// by default the DiagChannel is locked, meaning it will provide output
	locked = true;

	// if provided, set output device
	if (outputDevice) {
		DIAG_SetOutputDevice(channel, outputDevice);
	}

	// if provided, set clock source function
	if (clockSource) {
		DIAG_SetClockSource(channel, clockSource);
	}

} /* DiagChannel::DiagChannel */


// -----------------------------------------------------------------------------
//  DiagChannel::activate
// -----------------------------------------------------------------------------
void DiagChannel::activate()
{
	(void)DIAG_ActivateChannel(channel);

} /* DiagChannel::DiagChannel */


// -----------------------------------------------------------------------------
//  DiagChannel::setOutputDevice
// -----------------------------------------------------------------------------
void DiagChannel::setOutputDevice(IODevice outputDevice)
{
	(void)DIAG_SetOutputDevice(channel, outputDevice);

} /* DiagChannel::setOutputDevice */


// -----------------------------------------------------------------------------
//  DiagChannel::setClockSource
// -----------------------------------------------------------------------------
void DiagChannel::setClockSource(uint32_t (*clockSource)(void))
{
	(void)DIAG_SetClockSource(channel, clockSource);

} /* DiagChannel::setOutputDevice */


// -----------------------------------------------------------------------------
//  DiagChannel::deactivate
// -----------------------------------------------------------------------------
void DiagChannel::deactivate()
{
	(void)DIAG_DeactivateChannel(channel);

} /* DiagChannel::deactivate */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<< (const char* msg)
{
	// print out string message
	DIAG_LogMsg(channel, msg);
	// return self reference
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<< (int val)
{
	// print out string message
	DIAG_LogINT(channel, val, calcBase);
	// return self reference
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<< (unsigned int val)
{
	// print out string message
	DIAG_LogUINT(channel, val, calcBase);
	// return self reference
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<< (long val)
{
	// print out string message
	DIAG_LogINT(channel, val, calcBase);
	// return self reference
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<< (unsigned long val)
{
	// print out string message
	DIAG_LogUINT(channel, val, calcBase);
	// return self reference
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<< (float val)
{
	// print out string message
	DIAG_LogFLOAT(channel, val, precision);
	// return self reference
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<<(DiagChannel& (*pfn)(DiagChannel&))
{
	// call manipulator function
	(*pfn)(*this);
	// return self reference
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  DiagChannel::operator<<
// -----------------------------------------------------------------------------
DiagChannel& DiagChannel::operator<< (DiagChannelHeaderSetter& hs)
{
	DIAG_LogHeader(channel, hs.headerName);
	return *this;

} /* DiagChannel::operator<< */


// -----------------------------------------------------------------------------
//  halfred::endl
// -----------------------------------------------------------------------------
DiagChannel& halfred::endl(DiagChannel& channel)
{
	// log new line
	DIAG_LogNL(channel.channel);
	// return self reference
	return channel;

} /* halfred::endl */


// -----------------------------------------------------------------------------
//  halfred::hex
// -----------------------------------------------------------------------------
DiagChannel& halfred::hex(DiagChannel& channel)
{
	// change calculation base
	channel.calcBase = 16;
	// return self reference
	return channel;

} /* halfred::hex */


// -----------------------------------------------------------------------------
//  halfred::dec
// -----------------------------------------------------------------------------
DiagChannel& halfred::dec(DiagChannel& channel)
{
	// change calculation base
	channel.calcBase = 10;
	// return self reference
	return channel;

} /* halfred::dec */


// -----------------------------------------------------------------------------
//  halfred::lock
// -----------------------------------------------------------------------------
DiagChannel& halfred::lock(DiagChannel& channel)
{
	if (DIAG_Lock(channel.channel, channel.timeout)) {
		channel.locked = true;
	} else {
		channel.locked = false;
	}

	return channel;

} /* halfred::lock */


// -----------------------------------------------------------------------------
//  halfred::unlock
// -----------------------------------------------------------------------------
DiagChannel& halfred::unlock(DiagChannel& channel)
{
	DIAG_Unlock(channel.channel);

	// by default the DiagChannel is locked, meaning it will provide output
	channel.locked = true;

	return channel;

} /* halfred::unlock */


// -----------------------------------------------------------------------------
//  halfred::header
// -----------------------------------------------------------------------------
DiagChannelHeaderSetter& halfred::header(const char* header)
{
	// when header manipulator is called we change the state of the headerSetter
	// object to remember the current header name
	headerSetter.setHeader(header);

	// then we return the object, which is later processed by the DiagChannel's << operator
	return headerSetter;

} /* halfred::header */


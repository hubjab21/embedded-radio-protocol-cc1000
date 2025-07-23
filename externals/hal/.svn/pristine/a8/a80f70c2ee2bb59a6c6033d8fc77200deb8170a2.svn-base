/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			diag_channel.hpp
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

#ifndef HAL_DIAG_HPP
#define HAL_DIAG_HPP

#include "hal.h"

namespace halfred {

/** Forward declaration of the utility class used for handling the 'header' manipulator. */
class DiagChannelHeaderSetter;

/**
 * \brief Diagnostics (DIAG module) done the C++ way.
 */
class DiagChannel
{
private:

	/// channel number
	int channel;
	/// integer to string calculation base
	int calcBase;
	/// float to string conversion precision
	int precision;
	/// max time that can be spent on locking the output device
	int timeout;
	/// holds true if channel was successfully locked, false otherwise
	bool locked;

public:

	/**
	 * The one and only constructor.
	 *
	 * \param channelNo channel number (channel 0 reserved for internal HALFRED usage)
	 * \param outputDevice output IODevice
	 * \param clockSource pointer to a function that will provide time base for logging (can be NULL if
	 *        timestamps are not needed)
	 *
	 */
	DiagChannel(int channelNo, IODevice outputDevice = NULL, uint32_t (*clockSource)(void) = NULL, int lockTimeout = 1000);

	/**
	 * Activates the DIAG channel.
	 */
	void activate();

	/**
	 * Deactivates the DIAG channel.
	 */
	void deactivate();

	/**
	 * Sets an output device.
	 * \param outputDevice output IODevice
	 */
	void setOutputDevice(IODevice outputDevice);

	/**
	 * Sets clock source funtion.
	 * \param clockSource clock source function
	 */
	void setClockSource(uint32_t (*clockSource)(void));

	/**
	 * Operator that shifts (outputs) a C string into the DIAG channel.
	 */
	DiagChannel& operator<< (const char* msg);

	/**
	 * Operator that shifts (outputs) a signed integer into the DIAG channel.
	 */
	DiagChannel& operator<< (int val);

	/**
	 * Operator that shifts (outputs) an unsigned integer into the DIAG channel.
	 */
	DiagChannel& operator<< (unsigned int val);

	/**
	 * Operator that shifts (outputs) a signed long integer into the DIAG channel.
	 */
	DiagChannel& operator<< (long val);

	/**
	 * Operator that shifts (outputs) an unsigned long integer into the DIAG channel.
	 */
	DiagChannel& operator<< (unsigned long val);

	/**
	 * Operator that shifts (outputs) a float into the DIAG channel.
	 */
	DiagChannel& operator<< (float val);

	/**
	 * Operator handling simple argument-less manipulators.
	 */
	DiagChannel& operator<< (DiagChannel& (*pfn)(DiagChannel&));

	/**
	 * Operator designed especially to handle the 'header' manipulator.
	 */
	DiagChannel& operator<< (DiagChannelHeaderSetter& hs);

	// list of friendly manipulators
	friend DiagChannel& endl(DiagChannel& channel);
	friend DiagChannel& hex(DiagChannel& channel);
	friend DiagChannel& dec(DiagChannel& channel);
	friend DiagChannel& lock(DiagChannel& channel);
	friend DiagChannel& unlock(DiagChannel& channel);
};


/**
 * End-of-line manipulator for the \ref DiagChannel.
 */
DiagChannel& endl(DiagChannel& channel);

/**
 * Hexadecimal manipulator for the \ref DiagChannel. It causes all subsequent numbers
 * to be output as hex strings.
 */
DiagChannel& hex(DiagChannel& channel);

/**
 * Decimal manipulator for the \ref DiagChannel. It causes all subsequent numbers
 * to be output as decimal strings.
 */
DiagChannel& dec(DiagChannel& channel);

/**
 * Locks the channel for exclusive access.
 */
DiagChannel& lock(DiagChannel& channel);

/**
 * Unlocks the channel.
 */
DiagChannel& unlock(DiagChannel& channel);


/**
 * Header manipulator for the \ref DiagChannel.
 */
DiagChannelHeaderSetter& header(const char* header);



}; // namespace halfred

#endif /* HAL_DIAG_HPP */

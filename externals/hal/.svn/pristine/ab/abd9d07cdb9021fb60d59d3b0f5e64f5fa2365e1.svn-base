/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          diag_logger.hpp
 Author:        Lukasz Krzak
 Purpose:       HALFRED's C++ wrappers
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       DiagLogger class
--------------------------------------------------------------------------------
 Comments:      Subclassing from the DiagLogger class is the preferred way
                to add diagnostic capabilities to other classes.
================================================================================
*/

#ifndef DIAG_LOGGER_H
#define DIAG_LOGGER_H

namespace halfred {

/**
 * \brief Preferred base class for classes that use \ref DiagChannel as log output.
 *
 * <b>Usage.</b>
 *
 * Deriving from the \ref DiagLogger gives the derived class access to a
 * \ref DiagChannel object called "log".
 *
 * The following example shows the basic idea, however please read further as this example
 * does not produce any output yet.
 * The derived class is called myClass and by having the DiagLogger parent we can easily
 * use the log object inside the method body.
 *
 * \code
 * #include "hal.hpp"
 *
 * using namespace halfred;
 *
 * class myClass : public DiagLogger
 * {
 *     void doSomething()  {  log << "doing something" << endl; }
 * };
 * \endcode
 *
 * By default the DiagLogger will direct all output to a NULL diagnostic channel. In order
 * to see the output we need to set up a valid diagnostic channel. A convenient way of doing
 * so is to arm our class with an extended constructor to pass the reference to \ref DiagChannel
 * object to be used.
 *
 * <i>myClass.h:</i>
 * \code
 * #include "hal.hpp"
 *
 * using namespace halfred;
 *
 * class myClass : public DiagLogger
 * {
 *     myClass(DiagChannel& diagChannel) : DiagLogger(diagChannel) { ; }
 *     void doSomething()  {  log << "doing something" << endl; }
 * };
 * \endcode
 *
 * Then we can easily use the class.
 *
 * \code
 * #include "hal.hpp"
 * #include "myClass.h"
 *
 * using namespace halfred;
 *
 * DiagChannel myDiagChannel(1, IO_STD);
 * myClass myObject(myDiagChannel);
 *
 * int main()
 * {
 *     myObject.doSomething();
 * }
 * \endcode
 *
 * In the example above, diagnostic channel 1 is used (see \ref hal_diag) with IO_STD as an \ref IODevice.
 *
 */
class DiagLogger
{

protected:

    /// Actual diagnostic channel
    DiagChannel log;

public:

    /** Default constructor initializing the log object to NULL output */
    DiagLogger() : log(0) { ; }

    /** Parameterized constructor allowing to initialize the log object using \ref DiagChannel
     *  object.
     *  \param diagChannel diagnostic channel object that will be used for log output
     */
    DiagLogger(DiagChannel& diagChannel) : log(diagChannel) { ; }

    /**
     * Sets the diagnostic channel for output.
     * \param diagChannel diagnostic channel
     */
    void setDiagChannel(DiagChannel& diagChannel) { log = diagChannel; }

    /**
     * Gets the currently set diagnostic channel.
     * \return currently set diagnostic channel
     */
    DiagChannel& getDiagChannel() { return log; }
};


} // namespace halfred

#endif /* DIAG_LOGGER_H */

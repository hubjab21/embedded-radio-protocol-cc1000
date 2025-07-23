/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_iocomposite.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED's universal components
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IODevice that reads and writes to multiple other IODevices
--------------------------------------------------------------------------------
 Comments:      
================================================================================
*/

#ifndef HAL_IOCOMPOSITE_H
#define HAL_IOCOMPOSITE_H


/** \defgroup hal_iocomposite IOComposite device
 *
 * <b>Overview.</b>
 *
 * The IOComposite device is a special kind of IODevice. It is used to simultaneously
 * read and write to multiple other IODevices.
 *
 * <b>Creating and destroying composite IODevices.</b>
 *
 * In order to use IOComposite device it must be first created through a call to \ref IOCOMPOSITE_Create.
 * In the end the device should be destroyed by a complementary call to \ref IOCOMPOSITE_Destroy. Both these
 * functions use \ref hal_heap for dynamic memory allocation.
 *
 * <b>Using composite IODevices.</b>
 *
 * The IOComposite device groups (associates) one ore more other IODevices. To associate an IODevice with
 * the IOComposite device the \ref IOCOMPOSITE_SetAssociation function is used. Here's an example.
 *
 * \code
 * IODevice composite;
 *
 * // first we create the IOComposite device
 * composite = IOCOMPOSITE_Create(2);
 * if (composite) {
 *     // next we associate other IODevices (USART1, USART2) with the created IOComposite device
 *     IOCOMPOSITE_SetAssociation(composite, 0, USART1);
 *     IOCOMPOSITE_SetAssociation(composite, 1, USART2);
 *
 *     // now we can use the IOComposite device just like any other IODevice
 *     IODEV_Init(composite);
 *     IODEV_EnableWrite(composite);
 *
 *     // this will write to both USART1 and USART2
 *     IODEV_Write(composite, "hello", 5, 0);
 *
 *     // etc..
 *
 *     // on exit, we must destroy the IOComposite device
 *     IOCOMPOSITE_Destroy(composite);
 * } else {
 *     // create failed - do some error handling here
 * }
 * \endcode
 *
 *
 *
 *//*@{*/

/**
 * Creates a new IODevice, that reads and writes to multiple other IODevices.
 * \param max_associates maximum number of associated IODevices
 * \return new composite IODevice handle or NULL if creation failed
 */
IODevice IOCOMPOSITE_Create(unsigned int max_associates);

/**
 * Destroys a composite IODevice and frees all memory allocated for it.
 * This call does NOT destroy nor deinitialize associated IODevices.
 * Note, that this function should NOT be used to free other types of IODevices.
 * \param iocomposite IODevice handle of the IOComposite device
 */
void IOCOMPOSITE_Destroy(IODevice iocomposite);

/**
 * Associates an IODevice to the IOComposite device under given index.
 * \param iocomposite IODevice handle of the IOComposite device
 * \param index association index
 * \param iodevice IODevice handle to associate
 * \return HALRESULT_OK on success, otherwise HALRESULT_ERROR
 */
HALRESULT IOCOMPOSITE_SetAssociation(IODevice iocomposite, unsigned int index, IODevice iodevice);

/**
 * Clears association of an IODevice with the IOComposite device under given index.
 * \param iocomposite IODevice handle of the IOComposite device
 * \param index association index
 * \return HALRESULT_OK on success, otherwise HALRESULT_ERROR
 */
HALRESULT IOCOMPOSITE_ClearAssociation(IODevice iocomposite, unsigned int index);

/**
 * Gets the IODevice associated with the IOComposite device under given index.
 * \param iocomposite IODevice handle of the IOComposite device
 * \param index association index
 * \return IODevice handle or NULL if there is no IODevice associated under given index
 */
IODevice IOCOMPOSITE_GetAssociation(IODevice iocomposite, unsigned int index);

/*@}*/

#endif /* HAL_IOCOMPOSITE_H */

/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_os.hc
 Author:        Łukasz Krzak
 Purpose:       HALFRED's OS port
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       OS module port for non-OS implementation
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include <stdlib.h>
#include "hal_port_os.h"

// -----------------------------------------------------------------------------
//  OSSEM_PORT_Create
// -----------------------------------------------------------------------------
OSSem OSSEM_PORT_Create(void)
{
	OSSem result;
	
	result = (OSSem)malloc(sizeof(int));
	*result = 1;
	
	return result;
	
} /* OSSEM_PORT_Create */

// -----------------------------------------------------------------------------
//  OSSEM_PORT_Destroy
// -----------------------------------------------------------------------------
void OSSEM_PORT_Destroy(OSSem sem)
{
	if (sem) {
		free(sem);
	}
	
} /* OSSEM_PORT_Destroy */


// -----------------------------------------------------------------------------
//  OSSEM_PORT_Give
// -----------------------------------------------------------------------------
void OSSEM_PORT_Give(OSSem sem)
{
	if (sem) {
		*sem = 1;
	}
} /* OSSEM_PORT_Give */


// -----------------------------------------------------------------------------
//  OSSEM_PORT_Take
// -----------------------------------------------------------------------------
int OSSEM_PORT_Take(OSSem sem, int timeout)
{
	if (sem) {
		if (*sem) {
			*sem = 0;
			return 0;
		}
	}
	return 1;
} /* OSSEM_PORT_Take */


// -----------------------------------------------------------------------------
//  OSCNTSEM_PORT_Create
// -----------------------------------------------------------------------------
OSSem OSCNTSEM_PORT_Create(int init, int max)
{
	OSSem result;

	result = (OSSem)malloc(sizeof(int));
	*result = init;

	max=max;

	return result;

} /* OSCNTSEM_PORT_Create */


// -----------------------------------------------------------------------------
//  OSCNTSEM_PORT_Destroy
// -----------------------------------------------------------------------------
void OSCNTSEM_PORT_Destroy(OSSem sem)
{
	if (sem) {
		free(sem);
	}

} /* OSCNTSEM_PORT_Destroy */


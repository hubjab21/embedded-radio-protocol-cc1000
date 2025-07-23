/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_config.h"

#include "src/hal_heap1.c"
#include "src/hal_heap2.c"

#if (HAL_ENABLE_IO)
#include "src/hal_iodevice.c"
#include "src/hal_txtdevice.c"
#include "src/hal_iocomposite.c"
#endif

#if ((HAL_ENABLE_IOBUF) || (HAL_ENABLE_IO))
#include "src/hal_iobuf.c"
#endif

#if (HAL_ENABLE_DIAG)
#include "src/hal_diag.c"
#endif

#if (HAL_ENABLE_TIM)
#include "src/hal_tim.c"
#endif

#if (HAL_IO_OS_INTEGRATION)
#include "src/hal_osnotifier.c"
#endif

#if (HAL_ENABLE_BP)
#include "src/hal_bp.c"
#endif

#if (HAL_ENABLE_NV)
#include "src/hal_nv.c"
#endif

#if (HAL_ENABLE_CLI)
#include "src/hal_cli.c"
#endif

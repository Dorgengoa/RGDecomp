/* Force-included ahead of every game/ translation unit
 * (`-include port/prelude.h`, see docs/PORT-HEADERS.md).  Keep it tiny: only
 * what an ingest stage's rewritten spelling depends on. */
#ifndef RG_PORT_PRELUDE_H
#define RG_PORT_PRELUDE_H

#include "port/u128.h"   /* stage int128: rg_u128 / rg_s128 */
#include "port/vu0.h"    /* stage vu0asm: rg_vu0_* calls */
#include "port/vcall.h"  /* stage devirt: VC_VPTR_MEMBER / VCM* slot thunks */
#include "port/hwaccess.h" /* stage hwaccess: HW_R32 etc., PS2_SPR, RG_OVL_DATA */

#endif

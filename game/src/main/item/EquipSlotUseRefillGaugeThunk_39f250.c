/* rgp:protos */
#define RGP_SELF_EquipSlotUseRefillGaugeThunk_39f250 1
#include "port/game_protos.h"
#line 1
/* EquipSlotUseRefillGaugeThunk_39f250 -- shape-identical to merged KernelExitThunk_120d18 (1 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 0 immediate(s) substituted:
     KernelExit_120d18 -> EquipSlotUseRefillGauge_3a0070
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EquipSlotUseRefillGaugeThunk_39f250(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    EquipSlotUseRefillGauge_3a0070(p0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
}

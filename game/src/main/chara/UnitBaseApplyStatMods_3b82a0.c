/* rgp:protos */
#define RGP_SELF_UnitBaseApplyStatMods_3b82a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048381C;

s32 UnitBaseApplyStatMods_3b82a0(void)
{
    s32 r0;
    s32 rv1;
    s32 t0;

    r0 = UnitApplyStatModsGate_3b8a10();
    rv1 = (t0 != 0);
    if ((r0 & 0xFF) == 0) {
        rv1 = 0;
    } else {
        t0 = D_0048381C;
        rv1 = (t0 != 0);
    }
    return rv1;
}

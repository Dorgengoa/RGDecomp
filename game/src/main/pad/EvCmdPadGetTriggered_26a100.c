/* rgp:protos */
#define RGP_SELF_EvCmdPadGetTriggered_26a100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B2570[];

s32 EvCmdPadGetTriggered_26a100(s32 p0, s32 p1)
{
    s32 rv2;
    s32 r0;
    s32 r1;

    rv2 = 1;
    if (p1 <= 0) {
        rv2 = 0;
    } else {
        r0 = PadGetTriggeredMask_183d00(D_004B2570);
        r1 = (ScriptSetRefInt_26a1e0(p0, r0), (s32)0);
        rv2 = 1;
    }
    return rv2;
}

/* rgp:protos */
#define RGP_SELF_EvCmdSubCastSlotValid_262d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSubCastSlotValid_262d20(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = ((s32)EvtGetSubMachine_26abb0(r0));
    rv3 = 1;
    if (r1 == 0) {
        rv3 = 0;
    } else {
        r2 = ((s32)EventSubNodeAddCastSlotValid_251220(r1));
        rv3 = 1;
    }
    return rv3;
}

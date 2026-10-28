/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectNodeIsNull_32ebd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826E0;

s32 ScriptCmdEffectNodeIsNull_32ebd0(s32 p0)
{
    s32 t0;
    s32 rv0;
    s32 rv1;

    t0 = D_004826E0;
    rv0 = 0;
    rv1 = 1;
    if (t0 != 0) {
        rv0 = t0;
        rv1 = 0;
    }
    ScriptSlotStoreIntRef_3347f0(p0, rv1);
    return 1;
}

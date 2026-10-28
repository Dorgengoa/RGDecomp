/* rgp:protos */
#define RGP_SELF_AiCmdCharaActionCanCancelMaybe_2cb4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004DB92C;

s32 AiCmdCharaActionCanCancelMaybe_2cb4e0(s32 p0, s32 p1)
{
    s32 rv3;
    s32 t0;
    s32 rv2;
    s32 r0;
    s32 r1;

    rv3 = rv2;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        t0 = D_004DB92C;
        rv2 = 1;
        if (t0 == 0) {
            rv2 = 0;
        } else {
            r0 = ((unsigned char)CharaActionCanCancelMaybe_210b30(t0));
            r1 = (ScriptSlotStoreIntRef_2cc900(p0, (r0 & 0xFF)), (s32)0);
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}

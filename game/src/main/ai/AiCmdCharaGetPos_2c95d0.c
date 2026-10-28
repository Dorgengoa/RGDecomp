/* rgp:protos */
#define RGP_SELF_AiCmdCharaGetPos_2c95d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004DB92C;

s32 AiCmdCharaGetPos_2c95d0(s32 p0)
{
    u128 v20;
    s32 t0;
    s32 rv2;
    s32 r1;

    t0 = D_004DB92C;
    rv2 = 1;
    if (t0 == 0) {
        rv2 = 0;
    } else {
        CharaGetPos_2388a0(t0, &v20);
        r1 = (ScriptSlotStoreVec3_2cc8a0(p0, &v20), (s32)0);
        rv2 = 1;
    }
    return rv2;
}

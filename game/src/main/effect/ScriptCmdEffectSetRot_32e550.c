/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetRot_32e550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826E0;

s32 ScriptCmdEffectSetRot_32e550(s32 p0, s32 p1)
{
    u128 v40;
    u128 v20[2];
    s32 t0;
    s32 rv6;
    s32 r2;
    s32 rv5;
    s32 t1;
    E8W *q;

    q = (E8W *)p0;
    if (p1 != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)q++);
    ScriptSlotsToVec4_334810(&v40, (s32)q);
    t0 = D_004826E0;
    if (t0 == 0) {
        rv6 = 0;
    } else {
        r2 = ((s32)GetEffectMgr_2d9040());
        rv5 = 1;
        if (r2 == 0) {
            rv5 = 0;
        } else {
            t1 = D_004826E0;
            EffectCopyHandle_2dd3b0(v20, t1);
            EffectSetRot_2e09f0(r2, v20, &v40);
            rv5 = 1;
        }
        rv6 = rv5;
    }
    return rv6;
}

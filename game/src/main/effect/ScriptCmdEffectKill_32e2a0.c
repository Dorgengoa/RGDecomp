/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectKill_32e2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826E0;

s32 ScriptCmdEffectKill_32e2a0(void)
{
    u128 v20[2];
    s32 t0;
    s32 rv4;
    s32 r0;
    s32 rv3;
    s32 t1;
    s32 r2;

    t0 = D_004826E0;
    if (t0 == 0) {
        rv4 = 0;
    } else {
        r0 = ((s32)GetEffectMgr_2d9040());
        rv3 = 1;
        if (r0 == 0) {
            rv3 = 0;
        } else {
            t1 = D_004826E0;
            EffectCopyHandle_2dd3b0(v20, t1);
            r2 = EffectKill_2e06c0(r0, v20, 0, 0);
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}

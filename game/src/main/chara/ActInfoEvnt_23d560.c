/* rgp:protos */
#define RGP_SELF_ActInfoEvnt_23d560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481E78;
extern s32 D_00481E7C;

s32 ActInfoEvnt_23d560(s32 p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 r0;

    if (p1 <= 0) {
        return 0;
    }
    t0 = D_00481E78;
    if (t0 != 0) {
        t1 = D_00481E7C;
        if (t1 < 0x200) {
            goto ok;
        }
    }
    return 1;
ok:
    r0 = ScriptCallBuildCharaCmd_23f980((t0 + (t1 * 12)), p0, p1);
    if (r0 != 0) {
        D_00481E7C = D_00481E7C + 1;
    }
    return 1;
}

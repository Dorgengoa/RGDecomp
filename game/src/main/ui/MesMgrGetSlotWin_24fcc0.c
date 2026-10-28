/* rgp:protos */
#define RGP_SELF_MesMgrGetSlotWin_24fcc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 MesMgrGetSlotWin_24fcc0(s32 p0)
{
    s32 r0;
    s32 rv3;
    struct Obj0 *r1;
    s32 rv2;
    s32 t0;

    r0 = ((s32)GetMesMgr_277e90());
    if (r0 == 0) {
        rv3 = 0;
    } else {
        r1 = MesMgrGetSlot_277a20(r0, p0);
        if (r1 == 0) {
            rv2 = 0;
        } else {
            t0 = r1->m04;
            rv2 = t0;
        }
        rv3 = rv2;
    }
    return rv3;
}

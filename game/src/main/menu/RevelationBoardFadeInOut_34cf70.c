/* rgp:protos */
#define RGP_SELF_RevelationBoardFadeInOut_34cf70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D628;
extern f32 D_0047D634;

struct Obj0;

struct Obj0 {
    s32 m00;
};

void RevelationBoardFadeInOut_34cf70(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    f32 t1;
    f32 t2;

    t0 = p0->m00;
    if (t0 != 0) {
        if (p1 != 0) {
            t1 = D_0047D634;
            UiFadeWidgetAlpha_290690(t0, 0x47, 1.0f, t1, -1.0f);
        } else {
            t2 = D_0047D628;
            UiFadeWidgetAlpha_290690(t0, 0x47, 0.0f, t2, -1.0f);
        }
    }
}

/* rgp:protos */
#define RGP_SELF_UiGetWidgetTargetPos_290d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x60];
    f32 m60;
    f32 m64;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    s32 m00;
};

s32 UiGetWidgetTargetPos_290d90(s32 p0, s32 p1, struct Obj1 *p2, struct Obj2 *p3)
{
    struct Obj0 *r0;
    f32 t0;
    f32 t1;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 != 0) {
        t0 = r0->m60;
        p2->m00 = ((s32)t0);
        t1 = r0->m64;
        p3->m00 = ((s32)t1);
        return 1;
    }
    return 0;
}

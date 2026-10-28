/* rgp:protos */
#define RGP_SELF_UiFadeWidgetColor_2904e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x40];
    f32 m40;
    f32 m44;
    f32 m48;
    f32 m4C;
    f32 m50;
    f32 m54;
    f32 m58;
    f32 m5C;
};

void UiFadeWidgetColor_2904e0(s32 p0, s32 p1, f32 fa0, f32 fa1, f32 fa2, f32 fa3, f32 fa4)
{
    struct Obj0 *r0;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 != 0) {
        if (fa0 >= 0.0f) {
            r0->m40 = fa0;
            r0->m50 = fa4;
        }
        if (fa1 >= 0.0f) {
            r0->m44 = fa1;
            r0->m54 = fa4;
        }
        if (fa2 >= 0.0f) {
            r0->m48 = fa2;
            r0->m58 = fa4;
        }
        if (fa3 >= 0.0f) {
            r0->m4C = fa3;
            r0->m5C = fa4;
        }
        return;
    }
}

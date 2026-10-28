/* rgp:protos */
#define RGP_SELF_UiSetWidgetColor_2905b0 1
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
    u8 pad000[0x30];
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
};

void UiSetWidgetColor_2905b0(s32 p0, s32 p1, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    struct Obj0 *r0;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 != 0) {
        if (fa0 >= 0.0f) {
            r0->m30 = fa0;
        }
        if (fa1 >= 0.0f) {
            r0->m34 = fa1;
        }
        if (fa2 >= 0.0f) {
            r0->m38 = fa2;
        }
        if (fa3 >= 0.0f) {
            r0->m3C = fa3;
        }
        return;
    }
}

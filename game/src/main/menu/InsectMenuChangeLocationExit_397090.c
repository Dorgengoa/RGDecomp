/* rgp:protos */
#define RGP_SELF_InsectMenuChangeLocationExit_397090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s16 D_00483500;
extern u8 D_00483514;
extern u8 D_004E95C0[];

struct Obj0;

struct Obj0 {
    f32 m00;
};

s32 InsectMenuChangeLocationExit_397090(void)
{
    struct Obj0 *r0;
    f32 t0;

    r0 = UiGetWidgetColor_2904b0(D_004E95C0, 0x7532);
    t0 = r0->m00;
    if (t0 <= 1.0f) {
        D_00483514 = 0;
        D_00483500 = 2;
    }
    return 1;
}

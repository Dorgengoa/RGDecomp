/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2b1790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004823CC;
extern u8 D_004DB430[];

s32 MenuGridCursorBobCb_2b1790(s32 p0, s32 p1)
{
    s32 r1;
    u8 t0;

    MenuCursorBobToCell_2b3260(p0, p1, -0xE, 0x1C);
    r1 = (UiSelFrameAnimStep_28d820(D_004DB430, 0x78), (s32)0);
    t0 = D_004823CC;
    if (t0 != 0) {
        MenuWidgetPulseColor_2b3200();
    }
    return 1;
}

/* rgp:protos */
#define RGP_SELF_GoTitleMenuPromptClose_39bc60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00483624;
extern u8 D_0048363C;
extern s32 D_00483640;
extern u8 D_00483644;
extern u8 D_004E9660[];

s32 GoTitleMenuPromptClose_39bc60(void)
{
    f32 r0;
    u8 t0;
    s32 rv1;

    r0 = UiGetWidgetAlpha_290770(D_004E9660, 0xA);
    if (r0 <= 0.0f) {
        t0 = D_00483644;
        rv1 = 2;
        if (t0 != 0) {
            D_00483640 = 1;
            rv1 = 1;
        } else {
            D_00483640 = 2;
            rv1 = 2;
        }
        D_00483624 = 0;
        D_0048363C = 0;
    }
    return 1;
}

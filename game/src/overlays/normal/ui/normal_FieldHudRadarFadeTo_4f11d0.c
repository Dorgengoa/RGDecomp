/* rgp:protos */
#define RGP_SELF_normal_FieldHudRadarFadeTo_4f11d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F11D0 -- the 0x25 widget's RE-TARGET step: f(Obj *, f32, f32).
 * Both float parameters are copied into callee-saved $f20/$f21 (hence the
 * -0x30 frame with two `swc1` below the `sq $16`), because both survive the
 * func_290770 call.  The new rate is `(a - func_290770(p, 0x25)) / b`, fed
 * straight into func_290690's second float slot; -1.0f is inline.
 * `blezl $3` on the s16 at 0x386 is `> 0` with the shared `ld $31` tail in
 * the delay slot.  Returns void.
 */

typedef struct Obj {
    u8   pad000[0x378];
    s16  f378;
    u8   pad37A[0x386 - 0x37A];
    s16  f386;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudRadarFadeTo_4f11d0(Obj *p, f32 a, f32 b)
{
    if (p->f378 != 0) {
        UiFadeWidgetAlpha_290690(p, 0x25, a, (a - UiGetWidgetAlpha_290770(p, 0x25)) / b, -1.0f);
        if (p->f386 > 0) {
            UiSetWidgetAlpha_2907a0(p, 0x55, a);
        }
    }
}

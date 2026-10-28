/* rgp:protos */
#define RGP_SELF_normal_FieldHudMissionBannerHideMaybe_4f2350 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F2350 -- the 0x4F widget's stage-2 fade.  Two nested guards
 * (retail falls THROUGH into the body on both, so both are written
 * positively), the phase word is bumped to 2 BEFORE the fade is started, and
 * the settle test `c.lt.s $f0,$f1` against an inline 0.0f is `< 0.0f` with
 * the block on the fall-through side.  `sh $0,0x37A($16)` sits in the
 * func_291110 delay slot, so that clear precedes its call in source.
 * Returns void -- $2 is never written.
 *
 * ** The middle float is a LITERAL, not `extern f32 D_0047DCF8`. **
 * With the extern spelling mwcc will not move the `lwc1` above the
 * `sh 0x37A` (the load-across-store rule) and lands it four slots late;
 * naming it in a local hoists the load but then loses the `addiu $5,0x4F`
 * delay slot and flips the two `mtc1`s -- 5 and 4 wrong words respectively.
 * A .lit4 entry is a known constant with no alias hazard, so it hoists to the
 * top of the block and the rest of the schedule falls out.  Twenty-two other
 * spellings (argument temporaries in every order, s16 store temp, id
 * signedness, u16 field, `&&` guard, early return, volatile store cast,
 * const/volatile extern, load hoisted to the outer block) were measured; 14
 * of them are the SAME object as the extern baseline.
 */

typedef struct Obj {
    u8   pad000[0x378];
    s16  f378;
    s16  f37A;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudMissionBannerHideMaybe_4f2350(Obj *p)
{
    if (p->f378 != 0) {
        if (p->f37A != 0) {
            p->f37A = 2;
            UiFadeWidgetAlpha_290690(p, 0x4F, 0.0f, -0.3f, -1.0f);
            if (UiGetWidgetAlpha_290770(p, 0x4F) < 0.0f) {
                p->f37A = 0;
                UiSetWidgetsVisibleById_291110(p, 0x4F, 0, 1);
            }
        }
    }
}

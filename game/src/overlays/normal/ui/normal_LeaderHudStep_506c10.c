/* rgp:protos */
#define RGP_SELF_normal_LeaderHudStep_506c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506C10 -- the horizontal slide step for the shop cursor.
 * `fB8` is the per-frame delta; the clamp window is fB4 +/- |delta|, and
 * landing inside it snaps fB0 to fB4 and kills the delta.  Both func_290690
 * posts push the same x with y = 1.0f, z = -1.0f. */

typedef struct Obj {
    u8  pad000[0x5C];
    s8  f05C;
    u8  pad05D[0xB0 - 0x5D];
    f32 f0B0;
    f32 f0B4;
    f32 f0B8;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_LeaderHudStep_506c10(Obj *p)
{
    void *a;
    void *b;
    f32   d;

    if (p->f05C == 0) {
        return 0;
    }
    a = UiPageGetStateMachine_289b40((int)p);
    b = UiPageGetLayout_289b60(p);
    if (b == 0) {
        return 0;
    }
    if (a == 0) {
        return 0;
    }
    if (p->f0B8 != 0.0f) {
        p->f0B0 = p->f0B0 + p->f0B8;
        d = (p->f0B8 < 0.0f) ? -p->f0B8 : p->f0B8;
        if (!(p->f0B0 < p->f0B4 - d)) {
            if (p->f0B0 <= p->f0B4 + d) {
                p->f0B0 = p->f0B4;
                p->f0B8 = 0.0f;
            }
        }
        UiFadeWidgetAlpha_290690(b, 1, p->f0B0, 1.0f, -1.0f);
        UiFadeWidgetAlpha_290690(b, 0xE, p->f0B0, 1.0f, -1.0f);
    }
    UiUpdateWidgets_2913a0(b);
    StateMachineUpdate_28ed70(a);
    return 1;
}

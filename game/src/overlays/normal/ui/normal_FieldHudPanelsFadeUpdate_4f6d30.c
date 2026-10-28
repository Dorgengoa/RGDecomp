/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelsFadeUpdate_4f6d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F6D30 -- scroll driver: advance 0x36C by the 0x364 step, snap it
 * to the 0x368 target when it lands inside +/-|step|, then push the (clamped)
 * value out to every row widget. */

typedef struct Obj {
    u8  pad000[0x364];
    f32 f364;
    f32 f368;
    f32 f36C;
    s32 f370;
    u8  pad374[0x378 - 0x374];
    s16 f378;
} Obj;

extern f32 D_0047D248;          /* gp - 0x7F28 */
extern f32 D_0047D288;          /* gp - 0x7EE8 */

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudPanelsFadeUpdate_4f6d30(Obj *p)
{
    s32 i;
    s32 n;
    f32 t;
    f32 d;

    if (p->f378 == 0) {
        return;
    }
    if (p->f364 != 0.0f) {
        p->f36C = p->f36C + p->f364;
        d = p->f364;
        d = d < 0.0f ? -d : d;
        if (p->f36C >= p->f368 - d && p->f36C <= p->f368 + d) {
            p->f36C = p->f368;
        }
    }
    if (p->f370 != 0) {
        return;
    }
    if (((s32)GetGameData_1fede0()) == 0) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50();
    for (i = 0; i < n; i++) {
        t = p->f36C;
        if (t >= D_0047D248) {
            t = D_0047D248;
        }
        UiSetWidgetAlpha_2907a0(p, (u16)((i + 1) * 7), t);
        t = p->f36C;
        if (t >= D_0047D288) {
            t = D_0047D288;
        }
        UiSetWidgetAlpha_2907a0(p, (u16)(i * 7 + 8), t);
        UiSetWidgetAlpha_2907a0(p, (u16)(i * 7 + 9), p->f36C);
        UiSetWidgetAlpha_2907a0(p, (u16)(i + 3), p->f36C);
    }
    t = p->f36C;
    UiSetWidgetAlpha_2907a0(p, 2, t);
    t = p->f36C;
    if (t >= D_0047D248) {
        t = D_0047D248;
    }
    UiSetWidgetAlpha_2907a0(p, 0x24, t);
}

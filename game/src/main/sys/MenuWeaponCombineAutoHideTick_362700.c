/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineAutoHideTick_362700 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
typedef struct {
    u8 pad0[0x5C];
    s32 cnt;
    u8 pad60[0x84 - 0x60];
    s32 h;
    u8 pad88[0x95 - 0x88];
    u8 state;
} O362700;

/*rgp*/
/*rgp*/
extern f32 D_0047D4E8;

void MenuWeaponCombineAutoHideTick_362700(O362700 *o) {
    s32 n;
    u8 st;

    st = o->state;
    if (st == 6 || st == 7) return;
    if (o->cnt <= 0) return;
    if (UiGetWidgetAlpha_290770(o->h, 0x1E7) < D_0047D4E8) return;
    n = o->cnt - 1;
    o->cnt = n;
    if (n <= 0) {
        o->cnt = 0;
        UiFadeWidgetAlpha_290690(o->h, 0x1E7, 0.0f, -0.0625f, -1.0f);
    }
}

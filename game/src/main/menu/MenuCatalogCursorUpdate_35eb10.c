/* rgp:protos */
#define RGP_SELF_MenuCatalogCursorUpdate_35eb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0047D458;

void MenuCatalogCursorUpdate_35eb10(u8 *arg0, s32 arg1)
{
    f32 t;
    s16 *p;
    s32 g;
    f32 f;
    s32 x;
    s32 y;
    s32 c;

    *(f32 *)(arg0 + 0x1D4) = t = *(f32 *)(arg0 + 0x1D4) + D_0047D3B8;
    if (!(t <= 0.0f)) {
        *(f32 *)(arg0 + 0x1D4) = D_0047D458;
    }
    p = (s16 *)(((s32)UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 0x278), 0x24)) + 4);
    g = (s32)GetGameData_1fede0();
    switch (*(s32 *)(arg0 + 0x284)) {
    case 0:
        f = 6.0f * Sinf_128fd0(*(f32 *)(arg0 + 0x1D4));
        x = (s32)(f + (f32)(p[0] + p[8] * p[2]));
        y = (s32)(f + (f32)(p[1] + p[9] * p[3]));
        if (arg1 != 0) {
            UiSetWidgetPos_290f60(*(s32 *)(arg0 + 0x274), 0x20D, x, y);
        } else {
            UiMoveWidgetUniform_290f50(*(s32 *)(arg0 + 0x274), 0x20D, x, y, 0.25f, 0);
        }
        UiSelFrameSetPos_28daa0(arg0 + 0x1D8, 0x1F6, p[8] * p[2] + 0x1E, p[9] * p[3] + 0x22);
        UiSelFrameAnimStep_28d820(arg0 + 0x1D8, 0x1F6);
        c = ((s32)InvFindByCategoryIndex_3c86e0(*(s32 *)(g + 0x18), 6, 0, p[8], p[9] + p[11], 0));
        if (c == 0) {
            UiSetWidgetsVisibleById_291110(*(s32 *)(arg0 + 0x274), 0x1FC, 0, 1);
        } else {
            UiSetWidgetsVisibleById_291110(*(s32 *)(arg0 + 0x274), 0x1FC, 1, 1);
            UiSetTextString_28f510(*(s32 *)(arg0 + 0x274), 0x207, *(s32 *)(*(s32 *)(c + 0x10) + 0xC), 0);
        }
        break;
    case 1:
    case 2:
        f = 12.0f * Sinf_128fd0(*(f32 *)(arg0 + 0x1D4));
        x = (s32)((f32)p[0] + f);
        y = p[1] + p[9] * p[3];
        if (arg1 != 0) {
            UiSetWidgetPos_290f60(*(s32 *)(arg0 + 0x274), 0x20E, x, y);
        } else {
            UiMoveWidgetUniform_290f50(*(s32 *)(arg0 + 0x274), 0x20E, x, y, 0.25f, 0);
        }
        break;
    }
}

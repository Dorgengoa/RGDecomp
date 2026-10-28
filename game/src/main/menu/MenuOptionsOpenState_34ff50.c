/* rgp:protos */
#define RGP_SELF_MenuOptionsOpenState_34ff50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
} Rect;

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    s16 x10;
    s16 x12;
    s16 x14;
    s16 x16;
} Menu;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D35C;
extern f32 D_0047D5EC;
extern f32 D_0047D638;
extern f32 D_0047D648;
extern s32 D_0047F6E4;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s16 D_00482E84;
extern s16 D_00482E86;
extern s32 D_00482EA0;
extern f32 D_00482EA4;
extern s16 D_00482EA8;

s32 MenuOptionsOpenState_34ff50(s32 arg0, s32 arg1) {
    Rect *r;
    Menu *m;
    s32 obj;
    s32 i;

    if (arg1 != 0) {
        UiSetWidgetVisible_290010(D_00482360, 0x1B3, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x1B3, 0x200, 0x3C);
        UiMoveWidgetUniform_290f50(D_00482360, 0x1B3, 0x4D, 0x3C, D_0047D638, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1B3, 1.0f, 0.0625f, 0.0f);
        r = ((Rect *)UiGetWidgetSprite_28fe10(D_00482360, 0x25, 0));
        if (r == NULL) {
            return 0;
        }
        r->x0 = -10;
        r->x8 = 0xAC;
        r->xA = 0x54;
        r->xC = 0x54;
        r->x4 = 0x54;
        UiSlideInWidgetPair_28d010(0x1D, 0x14, D_00482360);
        UiFadeWidgetAlpha_290690(D_00482360, 0x41, 1.0f, D_0047D648, -1.0f);
        for (i = 0; i < 10; i++) {
            UiSetTextString_28f510(D_00482360, 0x1B4, ((char *)MsgTableLookup_28aa30(D_00481BBC, i + 0x3C)), i);
        }
        m = ((Menu *)UiEntryListFindByTag_28ea40(D_00482364, 0x1D));
        MenuOptionsRefresh_34f8e0();
        obj = ((s32)GetGameData_1fede0());
        D_00482EA8 = 0;
        if (*(s16 *)(*(s32 *)(obj + 0xC) + 0x26) == 1) {
            D_00482EA8 = PartyMenuCursorGet_3c0760(*(s32 *)(obj + 0x18), 0x13);
        }
        m->x14 = 0;
        m->x16 = D_00482EA8;
        UiSetWidgetPos_290f60(D_00482360, 0x1B5, 0, m->x16 * 30);
        MenuOptionLoadValue_350240(&m->x4);
        D_00482E84 = 0;
        D_00482E86 = 0;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x1CB, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1CB, 1.0f, D_0047D648, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x1CB, m->x4 + m->x14 * m->x8, m->x6 + m->x16 * m->xA);
        D_00482EA0 = 0;
        D_0047F6E4 = -1;
        D_00482EA4 = 0.0f;
    }
    if (D_00482EA0 == 0) {
        D_00482EA4 += D_0047D5EC;
        if (D_00482EA4 >= D_0047D35C) {
            D_00482EA4 = D_0047D35C;
            D_00482EA0 = 1;
        }
    } else if (D_00482EA0 == 1) {
        D_00482EA4 -= D_0047D5EC;
    }
    UiSetWidgetColor_2905b0(D_00482360, 0x41, D_00482EA4, D_00482EA4, D_00482EA4, 1.0f);
    if (D_00482EA4 <= 1.0f && D_00482EA0 == 1) {
        D_00482EA4 = 1.0f;
        UiSetWidgetColor_2905b0(D_00482360, 0x41, 1.0f, 1.0f, 1.0f, 1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x80, 0);
    }
    return 1;
}

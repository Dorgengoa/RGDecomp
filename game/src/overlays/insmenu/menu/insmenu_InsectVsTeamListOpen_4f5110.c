/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamListOpen_4f5110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F5110 (748 bytes, 188 instructions, 36 calls, 2 branches) --
 * the page teardown/rebuild: a long straight-line reconfiguration of the panel
 * guarded by the second parameter, then a widget fix-up if func_28EA40 finds
 * the 0x88BD entry.
 *
 * The sub-object at +4 is reached as a CAST, not as a struct member, and that
 * is deliberate: the cast form is what CSEs the ADDRESS into the callee-saved
 * register (`addiu $16, $2, 0x4`), which is what retail has here.  A real
 * member would cache the BASE (`daddu $16, $2, $0`) and fold +4 into every
 * offset.  The two stores that DO go through the widget's own base are written
 * on the widget for the same reason.
 *
 * The first parameter is never read; only $5 is used.  There is no caller
 * inside the overlay, so its type is unconstrained.
 */

typedef struct Obj Obj;
struct Obj {                /* the +4 sub-object, same shape as 004F5050's */
    u8  pad00[0x12];
    s16 f12;
    s16 f14;
    s16 f16;
};

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0xE];
    s16 f0E;
    s16 pad10;
    s16 f12;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004842E8;       /* gp - 0xE88, passed by address */
extern f32 D_0047D460;
extern f32 D_0047D488;

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
/*rgp*/

s32 insmenu_InsectVsTeamListOpen_4f5110(s32 arg0, s32 run)
{
    Widget *w;
    Obj *o;

    if (run != 0) {
        insmenu_InsectVsSaveProgressWindowShow_4f6b90(2, 0);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C2, 1, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88BA, 1, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C6, 1, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C8, 0, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C7, 0, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CAA, 1, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88CC, 1, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88E0, 1, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88F4, 1, 1);
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x890D, 0, 1);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88BA, 0xC8, 0);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88CC, 0x38, 0x49);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88E0, 0x38, 0xC0);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88F4, 0x38, 0x137);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x890B, 0x1E5, 0x4A);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x890C, 0x1E9, 0x4C);
        insmenu_InsectVsSavePortSelectDraw_4f6bf0(-1);
        insmenu_InsectVsSaveHighlightOption_4f6bb0(-1);
        InsectVsTeamListRefreshMaybe_37a2b0(0);
        insmenu_InsectVsTeamListTitleUpdate_4f5400();
        SaveUiScrollBarLayoutMaybe_377830(0x890C, 0x15B, 3, 0x14, 0);
        insmenu_InsectVsLoadWidgetsFade_4f6ac0(0);
        insmenu_InsectVsLoadWidgetsFade_4f6ac0(1);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BA, 1.0f, D_0047D460, 0.0f);
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88BA, -0x17, 0, D_0047D488, 0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CAA, 1.0f, D_0047D460, 0.0f);
        w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88BD));
        if (w != 0) {
            o = (Obj *)((u8 *)w + 4);
            w->f12 = 0x13;
            w->f0E = 2;
            SaveUiWidgetFadeIn_37b490(0x890D);
            insmenu_InsectVsLoadSlotCursorBob_4f6810(o, insmenu_D_004FA180, 1);
            insmenu_InsectVsSaveHighlightOption_4f6bb0(o->f12);
            SaveUiScrollBarThumbPlace_3777a0(o, 0x890C, 0);
            InsectVsTeamListRefreshMaybe_37a2b0(o->f16);
            insmenu_InsectVsTeamListTitleUpdate_4f5400();
        }
        UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BD, 0);
        StateMachineSetState_28ede0(&D_004842E8, 0x88C2, 0);
    }
    return 1;
}

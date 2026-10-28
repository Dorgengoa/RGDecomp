/* rgp:protos */
#define RGP_SELF_InsectVsTeamPanelSetupMaybe_379000 1
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
extern s32 func_4F3320(void);
extern s32 D_004831D4;

s32 InsectVsTeamPanelSetupMaybe_379000(u8 *arg0, s16 arg1) {
    s32 w;
    s32 m;
    s32 id;
    u16 win;
    s32 i;
    s32 msg;
    s32 h;

    w = D_004831D4;
    m = func_4F3320();
    id = *(s32 *)(*(u8 **)(*(u8 **)(((u8 *)GetGameData_1fede0()) + 0x24) + 0x1188) + 8);
    if (arg1 == 2) {
        win = 0x9CA7;
        UiSetTextString_28f510(w, 0x9CA7, MsgTableLookup_28aa30(m, 0x5E1), 0);
    } else if (id == 0x25C || id == 0x267 || id == 0x26F || id == 0x25D || arg1 == 1) {
        win = 0x9CA7;
        UiSetTextString_28f510(w, 0x9CA7, 0, 0);
    } else {
        win = 0x9CA7;
        UiSetTextString_28f510(w, 0x9CA7, MsgTableLookup_28aa30(m, 0x5DF), 0);
    }
    UiSetTextString_28f510(w, win, MsgTableLookup_28aa30(m, 0x5E0), 1);
    if (arg0 == NULL) {
        return -1;
    }
    if (arg0 + 0x18 == NULL) {
        return -1;
    }
    UiSetSpriteX_28fcd0(w, 0x9CA8, 0x13C, 0x28);
    for (i = 0; i < 0xF; i++) {
        UiSetSubItemGlyphUvW_28f0c0(w, 0x9CA8, 0, i);
    }
    for (i = 0; i < 0x14; i++) {
        UiSetTextString_28f510(w, 0x9CA8, 0, i);
    }
    for (i = 0; i < 5; i++) {
        UiSetSpriteW_28fbf0(w, 0x9CA9, 0, i);
        UiSetSpriteUvW_28f850(w, 0x9CA9, 0, i);
    }
    UiSetSubItemX_28f1c0(w, 0x9CA8, 0x35, 0xF);
    UiSetSpriteX_28fcd0(w, 0x9CA8, 0x24, 0x25);
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, 0x460), 0x12);
    msg = 0x514;
    if (id == 0x12F || id == 0x192 || id == 0x1F6) {
        msg = 0x514;
    } else if (id == 0x130 || id == 0x193 || id == 0x1F7) {
        msg = 0x515;
    } else if (id == 0x25C || id == 0x267 || id == 0x26F || id == 0x25D) {
        msg = 0x17;
    }
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, msg), 0);
    h = UiGetWidgetTextWidth_28f400(w, 0x9CA8, 0);
    UiSetTextX_28f590(w, 0x9CA8, 0x100 - h / 2, 0);
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, 0x3E9), 2);
    UiSetTextX_28f590(w, 0x9CA8, 0x140, 2);
    UiSetTextString_28f510(w, 0x9CA8, MsgTableLookup_28aa30(m, 0x44C), 1);
    UiSetTextString_28f510(w, 0x9CA8, (s32)arg0, 0x13);
    for (i = 0; i < 3; i++) {
        UiSetSpriteW_28fbf0(w, 0x9CA8, 0, i + 0xF);
        UiSetSpriteUvW_28f850(w, 0x9CA8, 0, i + 0xF);
        UiSetSpriteW_28fbf0(w, 0x9CA8, 0, i + 0x21);
        UiSetSpriteUvW_28f850(w, 0x9CA8, 0, i + 0x21);
    }
    return 5;
}

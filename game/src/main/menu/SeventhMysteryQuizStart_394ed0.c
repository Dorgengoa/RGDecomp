/* rgp:protos */
#define RGP_SELF_SeventhMysteryQuizStart_394ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct X394ed0 {
    u8 pad00[0x20];
    void *m20;
} X394ed0;

extern u8 D_004E9550[];
extern u8 D_004E9570[];
extern u8 D_004E95A0[];
extern s32 D_00483494;
extern s16 D_0048349C;
extern u8 D_00483498;
extern s32 D_004834A0;
extern s32 D_00483470;
extern void *D_0048347C;
extern f32 D_0047D5D0;

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
extern void *memset(void *d, s32 c, s32 n);
/*rgp*/
/*rgp*/

s32 SeventhMysteryQuizStart_394ed0(s32 unused, s32 en)
{
    void *w;
    s16 *r;
    X394ed0 *x;
    void *y;

    if (en != 0) {
        GetGameData_1fede0();
        D_00483494 = 0;
        D_0048349C = 0;
        UiSetWidgetsVisibleById_291110(D_004E9550, 2, 1, 1);
        UiSetWidgetPos_290f60(D_004E9550, 2, 0, 0x14);
        UiFadeWidgetAlpha_290690(D_004E9550, 2, 1.0f, D_0047D5D0, 0.0f);
        r = ((s16 *)UiEntryListFindByTag_28ea40(D_004E9570, 0x7531));
        UiSetWidgetPos_290f60(D_004E9550, 0xB, r[2], r[3]);
        w = UiGetWidgetSprite_28fe10(D_004E9550, 6, 0);
        if (w == 0) {
            return 0;
        }
        UiLayoutFrameRectsMaybe_28bbb0(w, 0x1A8, 0x28);
        UiSetWidgetPos_290f60(D_004E9550, 6, 0x2C, 0xF8);
        x = ((X394ed0 *)UiFindWidget_290460(D_004E9550, 7));
        if (x == 0) {
            return 0;
        }
        y = x->m20;
        if (y == 0) {
            return 0;
        }
        UiLayoutWindowFrame_28b8e0(y, 0x2A, 0x76, 4);
        UiSetWidgetPos_290f60(D_004E9550, 7, 0x2C, 0x120);
        x = ((X394ed0 *)UiFindWidget_290460(D_004E9550, 8));
        if (x == 0) {
            return 0;
        }
        y = x->m20;
        if (y == 0) {
            return 0;
        }
        UiLayoutWindowFrame_28b8e0(y, 0x182, 0x76, 4);
        UiSetWidgetPos_290f60(D_004E9550, 8, 0x52, 0x120);
        RandUniqueFill_3950e0(D_004E95A0, 7, atoi(((char *)MsgTableLookup_28aa30(D_0048347C, 0))));
        D_00483498 = 1;
        memset(&D_004834A0, 0, 0x10);
    }
    if (UiGetWidgetAlpha_290770(D_004E9550, 4) >= 1.0f) {
        StateMachineSetState_28ede0(&D_00483470, 0x7532, 1);
    }
    return 1;
}

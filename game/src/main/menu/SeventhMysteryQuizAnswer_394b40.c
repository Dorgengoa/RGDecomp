/* rgp:protos */
#define RGP_SELF_SeventhMysteryQuizAnswer_394b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x0;
    u8 pad[0xAC];
} Buf;

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
/*rgp*/
/*rgp*/

extern s8 D_00464278[];
extern f32 D_0047D5D0;
extern s32 D_00483470;
extern s32 D_0048347C;
extern s32 D_00483494;
extern s16 D_0048349C;
extern s32 D_004834A0;
extern s32 D_004834B0;
extern u8 D_004B2570[];
extern u8 D_004E9550[];
extern u8 D_004E9570[];
extern s32 D_004E95A0[];

s32 SeventhMysteryQuizAnswer_394b40(s32 arg0, s32 arg1) {
    Buf buf __attribute__((aligned(16)));
    s32 i;
    s32 j;
    u16 k;
    s32 res;
    u8 *obj;
    s32 n;
    s8 *str;
    s8 *p;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004E9570, 30001, 1);
        UiSetWidgetsVisibleById_291110(D_004E9550, 4, 1, 1);
        UiSetWidgetPos_290f60(D_004E9550, 4, 0x2C, 100);
        UiFadeWidgetAlpha_290690(D_004E9550, 4, 1.0f, D_0047D5D0, 0.0f);
        MsgFormatParamsCtor_28aa00(&buf);
        buf.x0 = D_0048349C + 1;
        MsgFormat_28a9a0(&D_004834A0, MsgTableLookup_28aa30(D_0048347C, 900), &buf, 1);
        UiSetTextString_28f510(D_004E9550, 4, &D_004834A0, 0);
        UiSetTextString_28f510(D_004E9550, 6, (void *)MsgTableLookup_28aa30(D_0048347C, 905), 0);
        UiSetTextCenteredX_28f300(D_004E9550, 6, 0xD4, 0);
        for (i = 0; i < 4; i++) {
            UiSetTextString_28f510(D_004E9550, 7, (void *)MsgTableLookup_28aa30(D_0048347C, i + 901), i);
        }
        SeventhMysteryShowQuestion_3947c0(D_0048349C);
        UiSetWidgetsVisibleById_291110(D_004E9550, 5, 1, 1);
        UiSetWidgetAlpha_2907a0(D_004E9550, 5, 1.0f);
        for (j = 0; j < 4; j++) {
            k = j + 6;
            UiSetWidgetsVisibleById_291110(D_004E9550, k, 1, 1);
            UiFadeWidgetAlpha_290690(D_004E9550, k, 1.0f, D_0047D5D0, 0.0f);
        }
        UiSetWidgetsVisibleById_291110(D_004E9550, 11, 1, 1);
        UiFadeWidgetAlpha_290690(D_004E9550, 11, 1.0f, D_0047D5D0, 0.0f);
        SeventhMysteryCursorPlace_3948a0(((s32)UiEntryListFindByTag_28ea40(D_004E9570, 30001)) + 4);
    }
    res = MenuGridCursorInput_28e170(D_004E9570, D_004B2570, 1, 0);
    obj = (u8 *)UiEntryListGetCurrentData_28ec60(D_004E9570);
    if (ReturnZero_207fe0() != 0 && PadIsTriggered_1839f0(D_004B2570, 8) != 0) {
        for (i = 0; i < 4; i++) {
            MsgTableLookup_28aa30(D_0048347C, (&D_004834B0)[i] + 2 + D_004E95A0[D_0048349C] * 5);
        }
    }
    if (res == 1) {
        PlayMenuSe_289ef0(3);
        n = *(s16 *)(obj + 0x12);
        str = D_00464278;
        for (i = 0; i < 4; i++) {
            p = (s8 *)MsgTableLookup_28aa30(D_0048347C, (&D_004834B0)[i] + 2 + D_004E95A0[D_0048349C] * 5);
            if (*p == *str && i == n) {
                D_00483494++;
            }
        }
        StateMachineSetState_28ede0(&D_00483470, 30004, 0);
    }
    return 1;
}

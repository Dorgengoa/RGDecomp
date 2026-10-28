/* rgp:protos */
#define RGP_SELF_InsectMenuEmptyCageChoiceOpen_397370 1
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
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004834F0;
extern s32 D_00483530;
extern u8 D_004E95C0[0x400];
extern u8 D_004E95E0[0x400];

typedef struct {
    u8 pad0[0xC];
    s32 n;
    u8 pad10[0xA0];
} Buf;

s32 InsectMenuEmptyCageChoiceOpen_397370(s32 arg0, s32 arg1)
{
    Buf buf __attribute__((aligned(16)));
    s32 *c;
    u8 *e;

    if (arg1 != 0) {
        UiSetWidgetVisible_290010(D_004E95C0, 0x7532, 1, -1);
        UiSetWidgetVisible_290010(D_004E95C0, 0x7533, 1, -1);
        UiSetWidgetPos_290f60(D_004E95C0, 0x7533, 0xF5, 0xA6);
        InsectMenuChoiceWindowLayout_396fc0(UiEntryListFindDataByTag_28ec30(D_004E95E0, 0x7532));
        e = UiGetWidgetText_28f620(D_004E95C0, 0x7533, 0);
        if (e != NULL) {
            *(s32 *)(e + 0x4) = InsectMenuMsgLookup_398200(2);
            *(s32 *)(e + 0x14) = InsectMenuMsgLookup_398200(3);
        }
    }
    c = ((s32 *)GetSelectedInsectEntryMaybe_206ad0());
    if (*c > 0) {
        MsgFormatParamsCtor_28aa00(&buf);
        buf.n = *c;
        MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(0), &buf, 1);
        UiSetTextString_28f510(D_004E95C0, 0x7531, D_00483530, 0);
        UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
        UiSetTextCenteredX_28f300(D_004E95C0, 0x7531, 0x100, 0);
    }
    UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7531, 1, 1);
    UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
    StateMachineSetState_28ede0(&D_004834F0, 0x7536, 0);
    return 1;
}

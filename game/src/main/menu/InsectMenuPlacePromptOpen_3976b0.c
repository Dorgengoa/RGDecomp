/* rgp:protos */
#define RGP_SELF_InsectMenuPlacePromptOpen_3976b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xC];
    s32 xC;
    u8 pad10[0xA0];
} Buf3976;

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
extern void *memset(void *, s32, u32);
extern s32 D_004834F0;
extern void *D_00483530;
extern void *D_00483534;
extern u8 D_004E95C0[0x400];

s32 InsectMenuPlacePromptOpen_3976b0(s32 pad0, s32 arg1)
{
    Buf3976 buf __attribute__((aligned(16)));
    s32 *p;

    if (arg1 != 0) {
        memset(D_00483530, 0, 0x80);
        memset(D_00483534, 0, 0x80);
        if (((s32)GetGameData_1fede0()) == 0) {
            return 0;
        }
    }
    p = ((s32 *)GetSelectedInsectEntryMaybe_206ad0());
    if (*p > 0) {
        MsgFormatParamsCtor_28aa00(&buf);
        buf.xC = *p;
        MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(0), &buf, 1);
        UiSetTextString_28f510(D_004E95C0, 0x7531, D_00483530, 0);
        UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
        UiSetTextCenteredX_28f300(D_004E95C0, 0x7531, 0x100, 0);
    }
    UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7531, 1, 1);
    UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
    StateMachineSetState_28ede0(&D_004834F0, 0x7533, 0);
    return 1;
}

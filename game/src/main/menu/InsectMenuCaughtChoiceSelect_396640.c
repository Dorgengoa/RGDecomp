/* rgp:protos */
#define RGP_SELF_InsectMenuCaughtChoiceSelect_396640 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_004504F0[][2];
extern f32 D_004504F4[][2];
extern f32 D_0047DD44;
extern s32 D_0047FF48;
extern u8 D_004834F0;
extern u8 D_0048350C;
extern f32 D_00483520;
extern f32 D_00483524;
extern s32 D_00483530;
extern s32 D_00483534;
extern s32 D_00483560;
extern u8 D_00483568;
extern u8 D_004B2570[];
extern u8 D_004E95C0[];
extern u8 D_004E95E0[];

s32 InsectMenuCaughtChoiceSelect_396640(s32 pad0, s32 arg1) {
    s32 b[0x2C] __attribute__((aligned(16)));
    s32 a[0x10] __attribute__((aligned(16)));
    u8 *p;
    u8 *d;
    u8 *q;
    s32 r;
    s32 k;
    s32 j;
    s16 cnt;
    s16 sum;
    s32 i;
    u8 *e;

    if (arg1 != 0) {
        D_0048350C = 1;
        p = ((u8 *)GetSelectedInsectEntryMaybe_206ad0());
        if (p != NULL) {
            MsgFormatParamsCtor_28aa00(b);
            b[3] = *(s32 *)(p + 0x0);
            MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(0xC), b, 1);
            UiSetTextString_28f510(D_004E95C0, 0x7531, D_00483530, 0);
            UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
            UiSetTextCenteredX_28f300(D_004E95C0, 0x7531, 0x100, 0);
            D_0047FF48 = b[3] = *(s16 *)(*(u8 **)(*(u8 **)(p + 0x4) + 0x18) + 0x4);
            MsgFormat_28a9a0(D_00483534, InsectMenuMsgLookup_398200(0xD), b, 1);
            UiSetTextString_28f510(D_004E95C0, 0x7534, D_00483534, 0);
        }
        UiWindowFitInit_398170(a, 0x7534);
        a[5] = 0xC;
        a[6] = 0x58;
        a[7] = 8;
        a[10] = 0x200;
        a[11] = 0x104;
        a[4] = 0xEE;
        a[8] = 0xA;
        *(u16 *)&a[12] |= 8;
        UiWindowFitToText_28d0c0(a, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7534, 1, 1);
        k = 0x7C7;
        j = 0x7B2;
        D_00483520 = (f32)k + D_004504F0[D_00483560][0];
        D_00483524 = (f32)j + D_004504F4[D_00483560][0];
        UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7535, 0);
    }
    if (D_00483568 == 1) {
        d = ((u8 *)GetGameData_1fede0());
        if (WorldDataMgrNoRequestPending_3eef10(((s32)GetWorldDataMgr_1fedf0())) != 0) {
            q = ((u8 *)GetSelectedInsectEntryMaybe_206ad0());
            if (*(s32 *)(q + 4) != 0) {
                CageRecRollCatchesMaybe_3e8510(d, *(s32 *)(q + 4));
            }
            D_00483568 = 2;
        }
    }
    if (D_00483568 == 2) {
        D_00483568 = 3;
        UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7533, 0);
        StateMachineSetState_28ede0(&D_004834F0, 0x753D, 0);
        return 1;
    }
    k = 0x7C7;
    j = 0x7B2;
    D_00483520 = (f32)k + D_004504F0[D_00483560][0];
    D_00483524 = (f32)j + D_004504F4[D_00483560][0];
    r = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
    p = ((u8 *)UiEntryListGetCurrentData_28ec60(D_004E95E0));
    if (r == 1) {
        if (*(s16 *)(p + 0x12) == 0) {
            cnt = 0;
            sum = 0;
            d = ((u8 *)GetGameData_1fede0());
            if (d == NULL) {
                return 0;
            }
            for (i = 0; i < 3; i++) {
                e = ((u8 *)InvGetCageItem_3c8040(*(s32 *)(d + 0x18), i));
                if (e != NULL) {
                    cnt++;
                    if (InsectRecSlotCountItems_3cfb80(e) != 0) {
                        sum += (s16)InsectRecSlotCountItems_3cfb80(e);
                    }
                }
            }
            if (cnt == 0) {
                StateMachineSetState_28ede0(&D_004834F0, 0x7537, 0);
            } else if (sum / cnt == 5) {
                StateMachineSetState_28ede0(&D_004834F0, 0x7540, 0);
            } else {
                UiSetWidgetVisible_290010(D_004E95C0, 0x7533, 0, -1);
                UiSetWidgetVisible_290010(D_004E95C0, 0x7532, 0, -1);
                UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7534, 0);
                UiFadeWidgetAlpha_290690(D_004E95C0, 0x7531, 0.0f, D_0047DD44, -1.0f);
                if (D_00483568 == 0 || D_00483568 == 3) {
                    if (D_00483568 == 0) {
                        WorldDataRequestKind_3f0960(((s32)GetWorldDataMgr_1fedf0()), 4);
                    }
                    D_00483568 = 1;
                }
            }
        } else {
            UiSetWidgetVisible_290010(D_004E95C0, 0x7533, 0, -1);
            UiSetWidgetVisible_290010(D_004E95C0, 0x7532, 0, -1);
            UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7531, 0);
            StateMachineSetState_28ede0(&D_004834F0, 0x753C, 0);
        }
    } else if (r == 2) {
        StateMachineSetState_28ede0(&D_004834F0, 0x7537, 0);
    }
    return 1;
}

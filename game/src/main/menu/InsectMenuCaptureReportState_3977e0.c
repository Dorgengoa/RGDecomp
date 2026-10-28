/* rgp:protos */
#define RGP_SELF_InsectMenuCaptureReportState_3977e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_lifetimes off

extern s32 Sprintf_1343b8(s8 *, s8 *, ...);
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
extern s8 D_004544F0[];
extern s8 D_004642E8[];
extern s32 D_004834F0;
extern s8 *D_00483530;
extern s8 **D_0048356C;
extern s8 D_004B2570[];
extern s8 D_004E95C0[];
extern s8 D_004E95E0[];

s32 InsectMenuCaptureReportState_3977e0(s32 arg0, s32 arg1) {
    s32 a;
    s8 *s;
    s32 j;
    s8 *p;
    s8 *e;
    s32 buf[44] __attribute__((aligned(16)));
    s32 r;
    s32 n;
    s32 i;

    if (arg1 != 0) {
        PlayMenuSe_289ef0(5);
        p = ((s8 *)GetSelectedInsectEntryMaybe_206ad0());
        if (p != 0) {
            MsgFormatParamsCtor_28aa00(buf);
            buf[3] = *(s32 *)p;
            MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(0xF), buf, 1);
            UiSetTextString_28f510(D_004E95C0, 0x7536, D_00483530, 0);
            n = *(s16 *)(*(s8 **)(*(s8 **)(p + 4) + 0x18) + 0xA);
            if (n > 6) {
                n = 6;
            }
            j = 0;
            do {
                UiSetTextString_28f510(D_004E95C0, 0x7537, 0, j);
                j++;
            } while (j < 6);
            for (i = 0; i < n; i++) {
                e = ((s8 *)CageRecGetEntry_3d0880(*(s8 **)(p + 4), i));
                if (*(u8 *)(e + 0xE) & 1) {
                    if (*(s16 *)(e + 4) == 1) {
                        a = InsectMenuMsgLookup_398200(0x10);
                        Sprintf_1343b8(D_0048356C[i], D_004642E8, a, &D_004544F0[*(s16 *)(e + 8) * 3], InsectMenuMsgLookup_398200(0x11));
                    } else if (*(s16 *)(e + 4) == 2) {
                        a = InsectMenuMsgLookup_398200(0x10);
                        Sprintf_1343b8(D_0048356C[i], D_004642E8, a, &D_004544F0[*(s16 *)(e + 8) * 3], InsectMenuMsgLookup_398200(0x12));
                    } else if (*(s16 *)(e + 4) == 3) {
                        a = InsectMenuMsgLookup_398200(0x10);
                        Sprintf_1343b8(D_0048356C[i], D_004642E8, a, &D_004544F0[*(s16 *)(e + 8) * 3], InsectMenuMsgLookup_398200(0x14));
                    }
                    s = *(s8 **)((s32)D_0048356C + (i << 2));
                    if (*s != 0) {
                        UiSetTextString_28f510(D_004E95C0, 0x7537, s, i);
                    }
                }
            }
        }
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7536, 1, 1);
    }
    r = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004E95E0);
    if ((u32)(r - 1) < 2) {
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7536, 0, 1);
        p = ((s8 *)GetSelectedInsectEntryMaybe_206ad0());
        if (p == 0) {
            return 0;
        }
        if (*(s16 *)(*(s8 **)(*(s8 **)(p + 4) + 0x18) + 4) > 0) {
            StateMachineSetState_28ede0(&D_004834F0, 0x7539, 0);
        } else {
            StateMachineSetState_28ede0(&D_004834F0, 0x7535, 0);
        }
    }
    return 1;
}

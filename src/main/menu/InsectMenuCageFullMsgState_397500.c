#include "types.h"

typedef struct Desc {
    s32 x0[4];
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30[4];
} Desc;

extern void UiWindowFitToText_28d0c0(Desc *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 MenuGridCursorInput_28e170(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void UiEntryListSelectByTag_28ea90(void *arg0, s32 arg1, s32 arg2);
extern void UiEntryListGetCurrentData_28ec60(void *arg0);
extern void StateMachineSetState_28ede0(void *arg0, s32 arg1, s32 arg2);
extern void UiSetTextString_28f510(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void UiSetWidgetsVisibleById_291110(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void UiWindowFitInit_398170(Desc *arg0, s32 arg1);
extern s32 InsectMenuMsgLookup_398200(s32 arg0);
extern u8 D_004834F0[] __attribute__((section(".sdata")));
extern u8 D_004B2570[0x40];
extern u8 D_004E95C0[0x20];
extern u8 D_004E95E0[0x40];

s32 InsectMenuCageFullMsgState_397500(s32 arg0, s32 arg1)
{
    Desc d;
    s32 r;

    if (arg1 != 0) {
        UiSetTextString_28f510(D_004E95C0, 0x7535, InsectMenuMsgLookup_398200(0xE), 0);
        UiWindowFitInit_398170(&d, 0x7535);
        d.x10 = 0x3C;
        d.x14 = 0xC;
        d.x18 = 0x1C;
        d.x1C = 8;
        d.x28 = 0x200;
        d.x2C = 0x200;
        UiWindowFitToText_28d0c0(&d, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7535, 1, 1);
        UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7534, 0);
    }
    r = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004E95E0);
    if ((u32)(r - 1) < 2) {
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7535, 0, 1);
        StateMachineSetState_28ede0(D_004834F0, 0x753B, 0);
    }
    return 1;
}

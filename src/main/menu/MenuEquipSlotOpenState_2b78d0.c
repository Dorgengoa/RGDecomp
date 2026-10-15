#include "types.h"

typedef struct B2b78d0 {
    s8 m00;
    s8 m01;
} B2b78d0;

extern void *D_00482360;
extern void *D_00482364;
extern void *D_00482370;
extern void *D_0048235C;
extern u16 D_004614C0[];
extern u8 D_004DB790[];

extern B2b78d0 *MenuGetCursorPos_29fae0(void *o);
extern void UiSetWidgetPos_290f60(void *o, s32 id, s32 x, s32 y);
extern void UiSelFrameInit_28da30(void *w, void *o, s32 id);
extern void UiGetWidgetPos_2910a0(void *o, s32 id, s32 *a, s32 *b);
extern void UiSelFrameSetRect_28db40(void *w, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e,
                         s32 f);
extern void UiSelFrameCalcTileCounts_28d9d0(void *w);
extern void UiSetWidgetAlpha_2907a0(void *o, s32 id, f32 t);
extern void UiEntryListSelectByTag_28ea90(void *o, s32 a, s32 b);
extern s16 *UiEntryListGetCurrentData_28ec60(void *o);
extern void UiSetWidgetsVisibleById_291110(void *o, s32 id, s32 a, s32 b);
extern u8 MenuPartyFadeSequenceStep_2b9240(s32 a, s32 b, s32 c);
extern void StateMachineSetState_28ede0(void *o, s32 a, s32 b);

s32 MenuEquipSlotOpenState_2b78d0(s32 unused, s32 en)
{
    s32 a;
    s32 b;
    B2b78d0 *y;
    s16 *r;
    s32 v;

    y = MenuGetCursorPos_29fae0(D_00482370);
    v = D_004614C0[y->m01];
    if (en != 0) {
        UiSetWidgetPos_290f60(D_00482360, 0x185, 0x4E, 0xB0);
        UiSelFrameInit_28da30(D_004DB790, D_00482360, 0x14D);
        UiGetWidgetPos_2910a0(D_00482360, 0xB6, &a, &b);
        UiSelFrameSetRect_28db40(D_004DB790, 0x14D, 0x2E, 0x8E, 0x2A, 0x30, a, b);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB790);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x14D, 0.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x13, 0);
        r = UiEntryListGetCurrentData_28ec60(D_00482364);
        r[8] = 0;
        r[9] = 0;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x1A9, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x1A9, 0x104, 0x15E);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x1A9, 0.0f);
    }
    if (MenuPartyFadeSequenceStep_2b9240(0x183, 0x11C, v) != 0) {
        StateMachineSetState_28ede0(D_0048235C, 0x58, 0);
    }
    return 1;
}

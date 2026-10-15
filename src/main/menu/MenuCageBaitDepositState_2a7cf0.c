#include "types.h"

typedef struct { u8 pad[0x11]; s8 m11; u8 pad12[0x5A]; s32 m6C; } G374;
typedef struct { u8 pad[0x18]; s32 m18; } Scn;
typedef struct { u8 pad[4]; s16 m4; s16 m6; u8 pad8[8]; s16 m10; s16 m12; } Pos;
typedef struct { s16 m0; u8 pad[0x2A]; s16 m2C; } Inf;
typedef struct { u8 pad[0x10]; Inf *m10; } Chr;

extern f32 D_0047D580;
extern f32 D_0047D5A8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern G374 *D_00482374;
extern s16 D_00482510;

void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
Scn *GetGameData_1fede0(void);
Pos *UiEntryListGetCurrentData_28ec60(s32);
Chr *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetItemIconUv_288e50(s32, s32, s32, s32);
void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
void PlayMenuSe_289ef0(s32);
s32 InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
s32 InvObjCastToItem4B0_3d3cd0(s32);
void CageRecSetBait_3d0c30(s32, Chr *);
void MenuSetItemSlotValueById_2a4e50(G374 *, s32, s32);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
f32 UiGetWidgetAlpha_290770(s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void StateMachineSetState_28ede0(s32, s32, s32);

s32 MenuCageBaitDepositState_2a7cf0(s32 pad0, s32 arg1)
{
    s32 sp4C;
    s32 sp48;
    Scn *scn;
    Pos *pos;
    Chr *chr;
    s32 h;
    s32 id;

    if (arg1 != 0) {
        D_00482510 = 0;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x141, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x141, 1.0f);
        scn = GetGameData_1fede0();
        if (scn == 0) {
            return 0;
        }
        pos = UiEntryListGetCurrentData_28ec60(D_00482364);
        if (pos == 0) {
            return 0;
        }
        chr = InvFindByCategoryIndex_3c86e0(scn->m18, 0, D_00482374->m11, pos->m10, pos->m12, 0);
        if (chr == 0) {
            return 0;
        }
        UiSetWidgetPos_290f60(D_00482360, 0x141, (s32)(98.0f + (f32)(pos->m10 * pos->m4)), (s32)(73.0f + (f32)(pos->m12 * pos->m6)));
        h = UiGetWidgetSprite_28fe10(D_00482360, 0x141, 0);
        if (h == 0) {
            return 0;
        }
        UiSetItemIconUv_288e50(h, chr->m10->m2C, 0x28, 0x2D);
        UiMoveWidget_290e00(D_00482360, 0x141, 0x2B, 0x168, 3, D_0047D5A8, 0.0f);
        PlayMenuSe_289ef0(7);
        h = UiGetWidgetSprite_28fe10(D_00482360, 0x142, 0);
        if (h == 0) {
            return 0;
        }
        UiSetItemIconUv_288e50(h, chr->m10->m2C, 0x28, 0x2D);
        UiSetWidgetPos_290f60(D_00482360, 0x142, 0xD, -0x27);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x142, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x142, 0.0f);
        id = D_00482374->m6C;
        h = InvFindInCategoryRange_3c8370(scn->m18, id, 0, -1, 0, 0);
        if (h != 0) {
            h = InvObjCastToItem4B0_3d3cd0(h);
            if (h != 0) {
                CageRecSetBait_3d0c30(h, chr);
                MenuSetItemSlotValueById_2a4e50(D_00482374, id, chr->m10->m0);
            }
        }
    }
    UiGetWidgetPos_2910a0(D_00482360, 0x141, &sp4C, &sp48);
    if (sp4C == 0x2B && sp48 == 0x168) {
        UiSetWidgetAlpha_2907a0(D_00482360, 0x141, 0.0f);
        if (UiGetWidgetAlpha_290770(D_00482360, 0x142) == 0.0f) {
            PlayMenuSe_289ef0(8);
        }
        UiFadeWidgetAlpha_290690(D_00482360, 0x142, 1.0f, D_0047D580, -1.0f);
    }
    if (!(UiGetWidgetAlpha_290770(D_00482360, 0x142) < 1.0f)) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x141, 0, 1);
        D_00482510++;
    }
    if (D_00482510 > 30) {
        StateMachineSetState_28ede0(D_0048235C, 0xB1, 0);
    }
    return 1;
}

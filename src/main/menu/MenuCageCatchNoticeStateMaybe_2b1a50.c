#include "types.h"

typedef struct Desc {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s16 f30;
} Desc;

typedef struct Msg {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    u8 pad[0xA0];
} Msg;

typedef struct Ctx { u8 pad[0x18]; s32 ctx; } Ctx;
typedef struct Unit { u8 pad[0x10]; s16 *id; } Unit;

extern Ctx *GetGameData_1fede0(void);
extern void MsgFormatParamsCtor_28aa00(void *);
extern Unit *InvGetItem4B0_3c80c0(s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void MsgFormat_28a9a0(void *, s32, void *, s32);
extern void UiSetTextString_28f510(s32, s32, void *, s32);
extern void UiWindowFitToText_28d0c0(Desc *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 MenuGridCursorInput_28e170(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern void UiEntryListSelectByTag_28ea90(s32 arg0, s32 arg1, s32 arg2);
extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern s32 UiGetWidgetText_28f620(s32 arg0, s32 arg1, s32 arg2);
extern s32 UiGetWidgetSprite_28fe10(s32 arg0, s32 arg1, s32 arg2);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetsVisibleById_291110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void PlayMenuSe_289ef0(s32);
extern s32 UiEntryListGetCurrentData_28ec60(s32);
extern s32 CageRecIsPlaced_3d0d20(Unit *);
extern s32 CageRecCountTriggered_3d08c0(Unit *);
extern void MenuItemSectionEnter_2b3400(void);
extern void memset(void *arg0, s32 arg1, s32 arg2);
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_004823D8;
extern u8 D_004B2570[];
extern u8 D_004DB460[];
extern s8 D_0047EC50;
extern s16 D_004824B0[3];

s32 MenuCageCatchNoticeStateMaybe_2b1a50(s32 pad0, s32 arg1)
{
    Msg m;
    Desc d;
    Ctx *c;
    s32 r;
    s32 i;
    Unit *u;
    s16 *q;
    s16 v;

    c = GetGameData_1fede0();
    if (c == 0) {
        return 0;
    }
    if (arg1 != 0) {
        MsgFormatParamsCtor_28aa00(&m);
        u = InvGetItem4B0_3c80c0(c->ctx, D_0047EC50);
        D_0047EC50++;
        m.xC = *u->id;
        MsgFormat_28a9a0(D_004DB460, MsgTableLookup_28aa30(D_004823D8, 0x3EE), &m, 1);
        UiSetTextString_28f510(D_00482360, 0x21E, D_004DB460, 0);
        memset(&d, 0, 0x34);
        d.f0 = UiGetWidgetSprite_28fe10(D_00482360, 0x21E, 0);
        d.f4 = UiGetWidgetText_28f620(D_00482360, 0x21E, 0);
        d.f10 = 0x3C;
        d.f14 = 0xC;
        d.f18 = 0x1C;
        d.f1c = 8;
        d.f20 = 0x62;
        d.f24 = 0x49;
        d.f28 = 0x186;
        d.f2c = 0x12C;
        d.f30 = 4;
        UiWindowFitToText_28d0c0(&d, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x21E, 1.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        PlayMenuSe_289ef0(0x2D);
        goto end;
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_00482364);
    if ((u32)(r - 1) < 2U) {
        for (i = D_0047EC50; i < 3; i++) {
            u = InvGetItem4B0_3c80c0(c->ctx, i);
            if (u == 0) continue;
            if (CageRecIsPlaced_3d0d20(u) == 0) continue;
            if (CageRecCountTriggered_3d08c0(u) <= 0) continue;
            q = &D_004824B0[i];
            v = *q;
            if (v == CageRecCountTriggered_3d08c0(u)) continue;
            *q = CageRecCountTriggered_3d08c0(u);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 0, 1);
            D_0047EC50 = i;
            StateMachineSetState_28ede0(D_0048235C, 0xB, 0);
            return 1;
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 0, 1);
        MenuItemSectionEnter_2b3400();
    }
end:
    return 1;
}

#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[4];
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
} Cur;

typedef struct {
    u8 pad0[0x11];
    s8 b11;
} Win;

typedef struct {
    u8 pad0[0x18];
    s32 x18;
} Ctx;

typedef struct {
    u8 pad0[4];
    s16 h4;
} Ent;

typedef struct {
    s16 v[9];
} A9;

typedef struct {
    s16 v[5];
} A5;

extern Ctx *GetGameData_1fede0(void);
extern void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern Cur *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Cur *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiGetWidgetText_28f620(u32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(u32, s32, s32);
extern void UiFadeWidgetAlpha_290690(u32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(u32, s32);
extern void UiMoveWidgetUniform_290f50(u32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(u32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(u32, s32, s32, s32);
extern void MenuItemInfoPopupShow_2a33e0(Win *, Ent *, s32, s32, s32 *, s32, s32, s32, f32);
extern void MenuFillItemCounts_2a3d90(Win *, s32);
extern void MenuPlaceWidgetAtCurEntry_2a4a10(Win *, s32, f32);
extern void MenuFillItemGrid_2a4b40(Win *, s32);
extern void MenuDrawItemTabs_2a4ee0(Win *, s32, s32);
extern void RevelationBoardBeginPlace_3498d0(u8 *, s32);
extern void RevelationBoardSetPlaceCell_34cdf0(u8 *, s32);
extern Ent *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern s32 RevelationBoardPlaceItemMaybe_3e9b40(Ctx *, s32, s32, s32, u8 *);
extern s32 RevelationBoardGetCells_3eb510(Ctx *, s32);
extern void *memset(void *, s32, u32);
extern u8 D_004539B0[];
extern f32 D_0047D470;
extern const f32 D_0047D5D0 __attribute__((section(".sdata")));
extern s32 D_0047F6C4;
extern s16 D_0047F6C8;
extern s32 D_0048235C;
extern u32 D_00482360;
extern s32 D_00482364;
extern Win *D_00482374;
extern u8 *D_0048238C;
extern s16 D_00482E20;
extern s16 D_00482E2C;
extern u8 D_004B2570[];
extern u8 D_004DB430[];

s32 RevelationItemSelect_346af0(s32 arg0, s32 arg1) {
    s16 tb[5];
    s16 ta[9];
    s32 sp40[4];
    Ctx *ctx;
    Cur *cur;
    s16 *src;
    s16 *dst;
    s32 n;
    Ent *ent;
    s32 k;
    s32 r;
    s32 p;
    s16 *q;

    ctx = GetGameData_1fede0();
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x1C, 0);
        cur = UiEntryListFindByTag_28ea40(D_00482364, 0x1C);
        src = (s16 *)D_004539B0;
        dst = ta;
        n = 9;
        do {
            n--;
            *dst = *src;
            src++;
            dst++;
        } while (n > 0);
        src = &D_0047F6C8;
        dst = tb;
        n = 5;
        do {
            n--;
            *dst = *src;
            src++;
            dst++;
        } while (n > 0);
        UiSelFrameSetRect_28db40(D_004DB430, 0x78, ta[cur->h14], tb[cur->h16], 0x2A, 0x30, 0x62, 0x49);
        MenuPlaceWidgetAtCurEntry_2a4a10(D_00482374, 0x227, 0.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x227, cur->h4 + cur->h14 * cur->h8 - 18, cur->h6 + cur->h16 * cur->hA + 24);
        ent = InvFindByCategoryIndex_3c86e0(ctx->x18, 0, D_00482374->b11, cur->h14, cur->h16, 0);
        k = cur->h14 + cur->h16 * 8;
        memset(sp40, 0, 0x10);
        sp40[0] = UiGetWidgetSprite_28fe10(D_00482360, 0x231, 0);
        sp40[1] = UiGetWidgetSprite_28fe10(D_00482360, 0x230, 0);
        sp40[2] = UiGetWidgetText_28f620(D_00482360, 0x230, 0);
        sp40[3] = UiGetWidgetSprite_28fe10(D_00482360, 0x232, 0);
        MenuItemInfoPopupShow_2a33e0(D_00482374, ent, 0x1AA, 0x1A9, sp40, 0x68, 0x15E, k, 2.0f);
        MenuDrawItemTabs_2a4ee0(D_00482374, 0x67, 0);
        MenuFillItemGrid_2a4b40(D_00482374, 0x76);
        MenuFillItemCounts_2a3d90(D_00482374, 0x77);
    } else if (!(UiGetWidgetAlpha_290770(D_00482360, 0x65) <= D_0047D470)) {
        r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 6, 0);
        cur = UiEntryListGetCurrentData_28ec60(D_00482364);
        if (r == 1) {
            ent = InvFindByCategoryIndex_3c86e0(ctx->x18, 0, D_00482374->b11, cur->h10, cur->h12, 0);
            if (ent != 0) {
            q = (s16 *)(D_0048238C + 0x10);
            p = RevelationBoardGetCells_3eb510(ctx, D_0047F6C4);
            p += (q[0] + q[1] * 26) * 4;
            if (p != 0) {
            r = RevelationBoardPlaceItemMaybe_3e9b40(ctx, D_0047F6C4, p, ent->h4, D_0048238C + 0x1C);
            if (r == -2 || (u32)(r - 3) < 2) {
                *(s16 *)(D_0048238C + 0x7A4) = r;
                *(s32 *)(D_0048238C + 0x7A8) = p;
                UiMoveWidgetUniform_290f50(D_00482360, 0x65, 0x200, 0x49, 0, D_0047D5D0);
                UiFadeWidgetAlpha_290690(D_00482360, 0x65, 0.0f, -2.0f, -1.0f);
                UiFadeWidgetAlpha_290690(D_00482360, 0x1A9, 0.0f, -2.0f, -1.0f);
                UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, -2.0f, -1.0f);
                StateMachineSetState_28ede0(D_0048235C, 0x79, 0);
            } else {
                RevelationBoardBeginPlace_3498d0(D_0048238C, r);
                if ((u32)(r - 1) < 2) {
                    RevelationBoardSetPlaceCell_34cdf0(D_0048238C, p);
                    D_00482E20 = 1;
                    if (r == 2) {
                        D_00482E20 = 2;
                    }
                    D_00482E2C = 0;
                    StateMachineSetState_28ede0(D_0048235C, 0x8E, 0);
                }
            }
            }
            }
        } else if (r == 2) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0xB5, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x8E, 0);
        }
    }
    return 1;
}

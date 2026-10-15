#include "types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 ox;
    s16 oy;
    f32 t;
    s16 cnt;
    u8 padE[0x2];
    s32 active;
} Grid;

extern f32 Sinf_128fd0(f32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 GetGameData_1fede0(void);
extern void UiSetSpritePosSizeUv_28f710(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void UiSetSpritePos_28fd10(void *, s32, s32, s32, s32);
extern void DebugItemIconGridSetScrollThumbs_29a7e0(Grid *);
extern s16 *DebugItemIconGridFindItem_29aa10(s32, s32);
extern void MenuFillItemGrid_2a4b40(s32, s32);
extern void MenuDrawItemTabs_2a4ee0(s32, s32, s32);
extern void IterInit_370170(void *, s32);
extern void InvAddItemCoreMaybe_3c6540(s32, s16, s32, s32, s32, s32, s32);
extern void RevelationBoardRefreshMaybe_3eaec0(s32, s32, s32);
extern f32 D_0047D1FC;
extern f32 D_0047D3F8;
extern s32 D_0047F6C4;
extern s32 D_00482374;
extern u8 D_004B2570[];
extern u8 D_004DB1B0[];

void DebugItemIconGridUpdate_29a2f0(Grid *g) {
    s32 obj;
    s32 p;
    s16 *cell;
    s32 cx;
    s32 cy;
    s32 bx;
    s32 by;
    s32 tmp[2];
    f32 f;
    f32 lim;

    if (g->active == 0) {
        return;
    }
    obj = GetGameData_1fede0();
    if (obj == 0) {
        return;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x8000)) {
        if (g->ox == 0) {
            if (g->x != 0) {
                g->x--;
            }
        } else {
            g->ox--;
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x2000)) {
        if (g->ox == 9) {
            if (g->x < 0x16) {
                g->x++;
            }
        } else {
            g->ox++;
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x1000)) {
        if (g->oy == 0) {
            if (g->y != 0) {
                g->y--;
            }
        } else {
            g->oy--;
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x4000)) {
        if (g->oy == 7) {
            if (g->y < 0x16) {
                g->y++;
            }
        } else {
            g->oy++;
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x40)) {
        p = *(s32 *)(*(s32 *)(*(s32 *)(obj + 8) + 0x40) + 8);
        if (p != 0) {
            p += 0x88;
        }
        IterInit_370170(tmp, p);
        cell = DebugItemIconGridFindItem_29aa10(g->x + g->ox, g->y + g->oy);
        if (cell != 0) {
            InvAddItemCoreMaybe_3c6540(*(s32 *)(obj + 0x18), *cell, 0xA, 1, -1, 0, 0);
            MenuDrawItemTabs_2a4ee0(D_00482374, 0x67, 1);
            MenuFillItemGrid_2a4b40(D_00482374, 0x76);
            RevelationBoardRefreshMaybe_3eaec0(obj, D_0047F6C4, 0);
            g->cnt = 3;
        }
    }
    cx = (g->ox << 5) + 0x10;
    cy = (g->oy << 5) + 0x10;
    bx = g->x << 5;
    by = g->y << 5;
    if (g->cnt > 0) {
        UiSetSpritePosSizeUv_28f710(D_004DB1B0, 0x1CC, 0, 0, 0, 0, 0, 0, 0, 0, 1);
    } else {
        UiSetSpritePosSizeUv_28f710(D_004DB1B0, 0x1CC, cx, cy, 0x20, 0x20, 0xD, 0x63, 0xC, 6, 1);
    }
    UiSetSpritePosSizeUv_28f710(D_004DB1B0, 0x1CD, 0x10, 0x10, 0x140, 0x100, bx, by, 0x13F, 0xFF, 0);
    UiSetSpritePos_28fd10(D_004DB1B0, 0x1CE, (cx - 8) - (s32)(8.0f * Sinf_128fd0(g->t)), cy + 8, 0);
    DebugItemIconGridSetScrollThumbs_29a7e0(g);
    f = g->t + D_0047D3F8;
    lim = D_0047D1FC;
    g->t = f;
    if (f > lim) {
        g->t = f - lim;
    }
    if (g->cnt > 0) {
        g->cnt--;
    }
}

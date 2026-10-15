#include "types.h"

extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetVisible_290010(void *, s32, s32, s32);
extern u8 *UiEntryListFindByTag_28ea40(void *, s32);
extern void UiSelFrameReset_28db70(void *);
extern void UiSelFrameInit_28da30(void *, void *, s32);
extern void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
extern void UiSelFrameCalcTileCounts_28d9d0(void *);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern u8 *GetGameData_1fede0(void);
extern s16 PartyMenuCursorGet_3c0760(s32, s32);
extern void UiSetWidgetSubItemValue_291250(void *, s32, s32, s32);
extern const f32 D_0047D5E0 __attribute__((section(".sdata")));
extern const f32 D_0047D5E8 __attribute__((section(".sdata")));
extern f32 D_0047F830;
extern s32 D_0047F834;
extern s16 D_0047F838;
extern u8 D_004DB1D0[0x400];

typedef struct Rect {
    u8 pad0[4];
    s16 x, y, w, h;
    s16 c, d, e, f;
    s16 g, h2, i, j;
} Rect;

void MenuCatalogPageReset_360980(u8 *arg0) {
    Rect *r;
    u8 *g;
    s32 i;
    s16 x;
    s16 m;
    s16 d;
    s16 e;
    s16 a;
    s16 b;

    *(s32 *)(arg0 + 0x1D0) = 0;
    *(s32 *)(arg0 + 0x284) = 0;
    *(f32 *)(arg0 + 0x1D4) = D_0047D5E8;
    UiSetWidgetPos_290f60(*(void **)(arg0 + 0x274), 0x1F4, 0x1F, 0x21);
    UiSetWidgetPos_290f60(*(void **)(arg0 + 0x274), 0x1F5, 0x1F, 0x21);
    r = (Rect *)UiEntryListFindByTag_28ea40(*(void **)(arg0 + 0x278), 0x24);
    r->x = 0;
    r->y = 0;
    r->w = 0;
    r->h = 0;
    r->g = 0;
    r->h2 = 0;
    r->i = 0;
    r->j = 0;
    UiSetWidgetVisible_290010(*(void **)(arg0 + 0x274), 0x20D, 1, -1);
    r->x = 0x6E;
    r->y = 0x77;
    r->w = 0x54;
    r->h = 0x59;
    r->c = 3;
    r->d = 2;
    r->e = 4;
    r->f = 3;
    UiSetWidgetPos_290f60(*(void **)(arg0 + 0x274), 0x20D, r->x, r->y);
    UiSetWidgetVisible_290010(D_004DB1D0, 5, 0, -1);
    UiSetWidgetVisible_290010(D_004DB1D0, 6, 0, -1);
    UiSetWidgetPos_290f60(D_004DB1D0, 5, 0x52, 0x4C);
    UiSetWidgetPos_290f60(D_004DB1D0, 6, 0x52, 0x4C);
    UiSelFrameReset_28db70(arg0 + 0x1D8);
    UiSelFrameInit_28da30(arg0 + 0x1D8, *(void **)(arg0 + 0x274), 0x1F6);
    UiSelFrameSetRect_28db40(arg0 + 0x1D8, 0x1F6, 0x1E, 0x22, 0x50, 0x58, 0, 0);
    UiSelFrameCalcTileCounts_28d9d0(arg0 + 0x1D8);
    UiSelFrameAnimStep_28d820(arg0 + 0x1D8, 0x1F6);
    g = GetGameData_1fede0();
    *(s32 *)(arg0 + 0x204) = 0;
    for (i = 0; i < 3; i++) {
        *(s32 *)(arg0 + i * 8 + 0x208) = 0;
        *(s32 *)(arg0 + i * 8 + 0x20C) = 0;
        *(s32 *)(arg0 + i * 8 + 0x220) = 0;
        *(s32 *)(arg0 + i * 8 + 0x224) = 0;
    }
    if (*(s16 *)(*(u8 **)(g + 0xC) + 0x26) == 1) {
        x = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x1B);
        *(s32 *)(arg0 + 0x204) = x;
        if (x < 0) {
            *(s32 *)(arg0 + 0x204) = 0;
        } else if (x > 2) {
            *(s32 *)(arg0 + 0x204) = 2;
        }
        *(s32 *)(arg0 + 0x284) = *(s32 *)(arg0 + 0x204);
        x = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x11);
        m = x % 4;
        d = x / 4;
        e = 0;
        if (d >= 3) {
            e = d - 2;
            d = 2;
        }
        *(s32 *)(arg0 + 0x208) = m;
        *(s32 *)(arg0 + 0x20C) = d;
        *(s32 *)(arg0 + 0x220) = 0;
        *(s32 *)(arg0 + 0x224) = e;
        x = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x12);
        if (x >= 5) {
            a = 5;
        } else {
            a = x;
        }
        b = x - 5;
        if (b < 0) {
            b = 0;
        }
        *(s32 *)(arg0 + 0x210) = 0;
        *(s32 *)(arg0 + 0x214) = a;
        *(s32 *)(arg0 + 0x228) = 0;
        *(s32 *)(arg0 + 0x22C) = b;
    }
    *(u8 *)(arg0 + 0x200) = 1;
    *(s32 *)(arg0 + 0x288) = 0;
    *(s32 *)(arg0 + 0x28C) = 0;
    D_0047F830 = D_0047D5E0;
    D_0047F834 = 0x3F800000;
    D_0047F838 = -1;
    *(s32 *)(arg0 + 0x238) = -1;
    *(s32 *)(arg0 + 0x23C) = 0;
    *(s32 *)(arg0 + 0x240) = -1;
    *(u8 *)(arg0 + 0x244) = 0;
    *(s32 *)(arg0 + 0x250) = 0;
    *(u8 *)(arg0 + 0x270) = 0;
    *(s16 *)(arg0 + 0x246) = -1;
    *(s16 *)(arg0 + 0x248) = 0;
    UiSetWidgetSubItemValue_291250(*(void **)(arg0 + 0x274), 0x2C, 0, *(s32 *)(*(u8 **)(GetGameData_1fede0() + 0x18) + 0x180));
}

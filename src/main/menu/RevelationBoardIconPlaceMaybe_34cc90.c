#include "types.h"

#pragma divbyzerocheck on

typedef struct Obj {
    s32 x0;
    u32 x4;
    s32 pad8;
    s32 xC;
    u8 pad10[0x772 - 0x10];
    s16 x772;
} Obj;

extern s32 GetGameData_1fede0(void);
extern void UiSetItemIconUv_288e50(s32, s16, s32, s32);
extern void *UiFindWidget_290460(s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void *RevelationBoardCellGetItemRec_3ead00(s32, s32, u32);
extern u32 RevelationBoardGetCells_3eb510(s32, s32);

void RevelationBoardIconPlaceMaybe_34cc90(Obj *arg0)
{
    s32 g;
    void *it;
    s32 w;
    void *r;
    s32 idx;
    u32 t;
    s64 d;
    u64 x4;
    s32 x;
    s32 y;

    g = GetGameData_1fede0();
    if (g == 0) {
        return;
    }
    arg0->x772 = 1;
    if (arg0->x0 == 0) {
        return;
    }
    it = UiFindWidget_290460(arg0->x0, 0xB5);
    if (it == NULL) {
        return;
    }
    w = *(s32 *)((u8 *)it + 0x20);
    if (w == 0) {
        return;
    }
    if (arg0->x4 == 0) {
        return;
    }
    r = RevelationBoardCellGetItemRec_3ead00(g, arg0->xC, arg0->x4);
    if (r == NULL) {
        return;
    }
    UiSetItemIconUv_288e50(w, *(s16 *)((u8 *)r + 0x2C), 0x20, 0x24);
    t = RevelationBoardGetCells_3eb510(g, arg0->xC);
    idx = (s64)((u64)arg0->x4 - (u64)t) / 4;
    x = idx % 26 * 42 + 25;
    y = idx / 26 * 46 + 23;
    UiSetWidgetsVisibleById_291110(arg0->x0, 0xB5, 1, 1);
    UiSetWidgetPos_290f60(arg0->x0, 0xB5, x, y);
    UiSetWidgetPos_290f60(arg0->x0, 0x59, x, y);
}

/* rgp:protos */
#define RGP_SELF_MenuItemIconSwapAnim_29b880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 pad8[0xC - 0x8];
    s16 unkC;
    s16 unkE;
} Rec;

typedef struct {
    u8 pad0[0x20];
    Rec *unk20;
} Slot;

typedef struct {
    u8 pad0[0x4C4];
    s32 unk4C4;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D68C;

s32 MenuItemIconSwapAnim_29b880(Obj *o, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 a;
    s32 b;
    Slot *sl;
    Rec *r1;
    Rec *r2;
    s32 row;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    s32 dx;
    s32 dy;

    sl = ((Slot *)UiFindWidget_290460(o->unk4C4, 0x17E));
    if (sl == 0) {
        return 1;
    }
    r1 = sl->unk20;
    if (r1 == 0) {
        return 2;
    }
    r1->unkE = 0;
    r1->unkC = 0;
    r1->unk6 = 0;
    r1->unk4 = 0;
    UiPlaceItemIconInQuadrant_29f720(o, sl, arg1, arg3);
    if (arg1 != -1) {
        UiSetWidgetsVisibleById_291110(o->unk4C4, 0x17E, 1, 1);
    }
    sl = ((Slot *)UiFindWidget_290460(o->unk4C4, 0x17F));
    if (sl == 0) {
        return 1;
    }
    r2 = sl->unk20;
    if (r2 == 0) {
        return 2;
    }
    r2->unkE = 0;
    r2->unkC = 0;
    r2->unk6 = 0;
    r2->unk4 = 0;
    if (arg4 < 8) {
        row = 0;
    } else {
        arg4 -= 8;
        row = 1;
    }
    r2->unk0 = arg4 * 0x2C + 0x1D;
    r2->unk2 = row * 0x32 + 0x1C;
    UiSetItemIconSprite_288490((u8 *)o + 0x5C, sl, arg2, 0x28, 0x2D, 1);
    UiGetWidgetPos_2910a0(o->unk4C4, 0xD6, &a, &b);
    x1 = a;
    y1 = b;
    UiGetWidgetPos_2910a0(o->unk4C4, 0xB6, &a, &b);
    x1 += a;
    y1 += b;
    x1 += r1->unk0;
    y1 += r1->unk2;
    x2 = 0;
    y2 = 0;
    UiGetWidgetPos_2910a0(o->unk4C4, 0xB6, &a, &b);
    x2 += a;
    y2 += b;
    x2 += r2->unk0;
    y2 += r2->unk2;
    dx = x1 - x2;
    dy = y1 - y2;

    if (arg1 != -1) {
        UiMoveWidget_290e00(o->unk4C4, 0x17E, -dx, -dy, 3, D_0047D68C, 0.0f);
    }
    UiSetWidgetsVisibleById_291110(o->unk4C4, 0x17F, 1, 1);
    UiMoveWidget_290e00(o->unk4C4, 0x17F, dx, dy, 3, D_0047D68C, 0.0f);
    MenuSetMoveTarget_29f9d0(o, dx, dy);
    return 0;
}

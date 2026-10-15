#pragma opt_dead_assignments off
#include "types.h"

class Unit003619d0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual s32 f();
};

struct Obj003619d0 {
    u8 pad0[0x84];
    s32 unk84;
};

extern "C" {
u8 *GetGameData_1fede0();
void UiSetSubItemFlags_28ef30(s32, s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiSetSpriteFlags_290bd0(s32, s32, s32, s32, s32, s32);
Unit003619d0 *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
s32 ItemRecKindIs6_3d4510(Unit003619d0 *);
s32 ItemIsWeapon_3d46c0(Unit003619d0 *);
extern s32 D_004659F0[];
extern s32 D_004659F8[];
extern f32 D_0047D40C;
extern f32 D_0047D488;
extern u8 *D_00482374;
}

extern "C" void MenuWeaponCombineGridRefreshMaybe_3619d0(Obj003619d0 *arg0, s32 arg1)
{
    u8 *w;
    s32 y;
    s32 x;
    s32 idx;
    s32 i;
    s32 n;
    f32 f;
    Unit003619d0 *u;

    w = GetGameData_1fede0();
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 8; x++) {
            idx = x + y * 8;
            UiSetSpriteFlags_290bd0(arg0->unk84, 0x76, 0x238, -1, idx, 0);
            UiSetSpriteFlags_290bd0(arg0->unk84, 0x74, 8, -1, idx, 0);
            UiSetSubItemFlags_28ef30(arg0->unk84, 0x77, 0x20, -1, idx);
            if (arg1 == 0) {
                continue;
            }
            u = InvFindByCategoryIndex_3c86e0(*(s32 *)(w + 0x18), 0, *(s8 *)(D_00482374 + 0x11), x, y, 0);
            if (u == 0) {
                continue;
            }
            if (ItemRecKindIs6_3d4510(u) != 0) {
                UiSetSpriteFlags_290bd0(arg0->unk84, 0x76, 0x208, 1, idx, 0);
            } else if (ItemIsWeapon_3d46c0(u) != 0) {
                if (u->f() == 0) {
                    UiSetSpriteFlags_290bd0(arg0->unk84, 0x76, 0x10, 1, idx, 0);
                } else {
                    UiSetSpriteFlags_290bd0(arg0->unk84, 0x76, 8, 1, idx, 0);
                }
                UiSetSpriteFlags_290bd0(arg0->unk84, 0x74, 8, 1, idx, 0);
            } else {
                UiSetSpriteFlags_290bd0(arg0->unk84, 0x76, 0x20, 1, idx, 0);
            }
        }
    }
    if (arg1 != 0) {
        UiSetWidgetColor_2905b0(arg0->unk84, 0x77, D_0047D40C, D_0047D40C, D_0047D40C, 1.0f);
        UiSetWidgetColor_2905b0(arg0->unk84, 0x75, D_0047D40C, D_0047D40C, D_0047D40C, 1.0f);
        { f32 o = 1.0f; UiSetWidgetColor_2905b0(arg0->unk84, 0x74, D_0047D488, D_0047D488, D_0047D488, o); }
        return;
    }
    UiSetWidgetColor_2905b0(arg0->unk84, 0x77, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetColor_2905b0(arg0->unk84, 0x75, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetColor_2905b0(arg0->unk84, 0x74, 1.0f, 1.0f, 1.0f, 1.0f);
    i = 0;
    n = D_004659F0[0] * D_004659F8[0];
    for (; i < n; i++) {
        UiSetSpriteFlags_290bd0(arg0->unk84, 0x76, 0x20, 1, i, 0);
    }
}

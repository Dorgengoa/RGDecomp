#pragma opt_dead_assignments off
#include "types.h"


class VO {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual s32 v16();
};

struct G374 {
    u8 pad0[0x11];
    s8 b11;
    u8 pad12[0x1A];
    s32 w2C;
    s32 w30;
};

extern "C" {
u8 *GetGameData_1fede0(void);
void UiSetSubItemFlags_28ef30(s32, s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiSetSpriteFlags_290bd0(s32, s32, s32, s32, s32, s32);
VO *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
s32 ItemRecKindIs6_3d4510(VO *);
extern s32 D_004659F0[4];
extern s32 D_004659F8[4];
extern f32 D_0047D40C;
extern f32 D_0047D488;
extern G374 *D_00482374;
}

extern "C" void MenuWeaponCombineGridHighlightMatchingMaybe_361640(u8 *arg0, s32 arg1)
{
    u8 *g;
    s32 y;
    s32 x;
    s32 n;
    VO *o;
    u8 *q;
    s32 k;
    s32 e4;
    s32 e8;
    bool same;
    s32 cnt;
    s32 ww;
    s32 i;

    g = GetGameData_1fede0();
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 8; x++) {
            n = x + y * 8;
            UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x76, 0x238, -1, n, 0);
            UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x74, 8, -1, n, 0);
            UiSetSubItemFlags_28ef30(*(s32 *)(arg0 + 0x84), 0x77, 0x20, -1, n);
            if (arg1 == 0) {
                continue;
            }
            o = InvFindByCategoryIndex_3c86e0(*(s32 *)(g + 0x18), 0, D_00482374->b11, x, y, 0);
            if (o == 0) {
                continue;
            }
            q = *(u8 **)((u8 *)o + 0x10);
            k = *(s8 *)(q + 2);
            e4 = *(s16 *)(q + 4);
            e8 = *(s16 *)(q + 8);
            if (((ww = ((volatile G374 *)D_00482374)->w2C, D_00482374->b11 == ww) && n == D_00482374->w30) || ItemRecKindIs6_3d4510(o) != 0) {
                UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x76, 0x208, 1, n, 0);
            } else {
                if (*(s32 *)(arg0 + 0x64) == k && *(s32 *)(arg0 + 0x68) == e4 && *(s32 *)(arg0 + 0x6C) == e8) {
                    same = 1;
                } else {
                    same = 0;
                }
                if (same || k == 7) {
                    if (o->v16() == 0) {
                        UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x76, 0x10, 1, n, 0);
                        UiSetSubItemFlags_28ef30(*(s32 *)(arg0 + 0x84), 0x77, 0x20, 1, n);
                    } else {
                        UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x76, 8, 1, n, 0);
                    }
                    UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x74, 8, 1, n, 0);
                } else {
                    UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x76, 0x20, 1, n, 0);
                }
            }
        }
    }
    if (arg1 != 0) {
        UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x84), 0x77, D_0047D40C, D_0047D40C, D_0047D40C, 1.0f);
        UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x84), 0x75, D_0047D40C, D_0047D40C, D_0047D40C, 1.0f);
        { f32 o = 1.0f; UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x84), 0x74, D_0047D488, D_0047D488, D_0047D488, o); }
    } else {
        UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x84), 0x77, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x84), 0x75, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetColor_2905b0(*(s32 *)(arg0 + 0x84), 0x74, 1.0f, 1.0f, 1.0f, 1.0f);
        i = 0;
        cnt = D_004659F0[0] * D_004659F8[0];
        for (; i < cnt; i++) {
            UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x84), 0x76, 0x20, 1, i, 0);
        }
    }
}

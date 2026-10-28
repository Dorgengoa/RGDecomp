/* rgp:protos */
#line 1
#include "types.h"

typedef struct Desc { s16 m0; s8 m2; s8 m3; s16 m4; } Desc;
typedef struct Pos { s16 a; s16 b; } Pos;
typedef struct Win {
    u8 pad0[4];
    s16 m4;
    u8 pad6[0x3E];
    s16 m44;
    u8 pad46[0x1A];
    s16 m60;
    u8 pad62[0x3E];
    s16 mA0;
    u8 padA2[0x42];
    s16 mE4;
    u8 padE6[0x1A];
    s16 m100;
} Win;
typedef struct Wld { u8 pad0[0x18]; s32 m18; } Wld;
typedef struct Self { s32 m0; } Self;

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v050() { return VCM0(s32, 0x50); }
    u8 pad4[0xC];
    Desc *desc;
};

extern "C" {
extern Wld *GetGameData_1fede0(void);
extern Win *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetSubItemValue_291250(s32, s32, s32, s64);
extern s32 InvGetCageItem_3c8040(s32, s32);
extern s32 InsectRecSlotCountItems_3cfb80(s32);
extern s32 ItemGetStackLimit_3d4480(Chr *);
extern s32 ItemDefIsKindCId4B1_40e2e0(Desc *);
extern Pos D_00450DD2[];
extern f32 D_0047D76C;
}

extern "C" s32 MenuItemCountPanelSetupMaybe_2a53f0(Self *self, Chr *obj, s32 id2, s32 id3, s32 id4, s32 id5, s32 flag)
{
    s32 ret;
    bool ok;
    s32 offs;
    s16 idx;
    Desc *d;
    s32 v;
    Win *p;
    Pos *e;
    s32 b;
    s32 k2;
    s32 k4;
    s32 k0;

    ok = false;
    d = obj->desc;
    k2 = d->m2;
    k4 = d->m4;
    k0 = d->m0;
    offs = 0;
    ret = 0;
    if (flag != 0) {
        if (k2 == 4 || k4 == 0x1F4 || k0 == 0x40D9) {
            UiFadeWidgetAlpha_290690(self->m0, id2, 1.0f, D_0047D76C, 0.0f);
            UiFadeWidgetAlpha_290690(self->m0, id3, 1.0f, D_0047D76C, 0.0f);
            UiFadeWidgetAlpha_290690(self->m0, id5, 1.0f, D_0047D76C, 0.0f);
            UiSetWidgetAlpha_2907a0(self->m0, id4, 0.0f);
            UiSetWidgetSubItemValue_291250(self->m0, id3, 0, obj->v050());
            UiSetWidgetSubItemValue_291250(self->m0, id3, 1, ItemGetStackLimit_3d4480(obj));
            ret = 0x1C;
            offs = 0xA7;
            idx = 0;
            ok = true;
        } else if (ItemDefIsKindCId4B1_40e2e0(d) != 0) {
            UiFadeWidgetAlpha_290690(self->m0, id2, 1.0f, D_0047D76C, 0.0f);
            UiFadeWidgetAlpha_290690(self->m0, id3, 1.0f, D_0047D76C, 0.0f);
            UiFadeWidgetAlpha_290690(self->m0, id4, 1.0f, D_0047D76C, 0.0f);
            UiSetWidgetAlpha_2907a0(self->m0, id5, 0.0f);
            v = InvGetCageItem_3c8040(GetGameData_1fede0()->m18, obj->desc->m3);
            if (v != 0) {
                UiSetWidgetSubItemValue_291250(self->m0, id3, 0, InsectRecSlotCountItems_3cfb80(v));
                UiSetWidgetSubItemValue_291250(self->m0, id3, 1, 5);
            }
            offs = -0x1C;
            idx = 5;
            ok = true;
        }
    }
    if (!ok) {
        UiSetWidgetAlpha_2907a0(self->m0, id2, 0.0f);
        UiSetWidgetAlpha_2907a0(self->m0, id3, 0.0f);
        UiSetWidgetAlpha_2907a0(self->m0, id4, 0.0f);
        UiSetWidgetAlpha_2907a0(self->m0, id5, 0.0f);
        return 0;
    }
    p = UiGetWidgetSprite_28fe10(self->m0, id2, 0);
    e = &D_00450DD2[idx];
    v = e->a - 0xE;
    p->m4 = v + 0xE;
    p->mE4 = v;
    p->m44 = v;
    p->m100 = v + 0xC;
    p->m60 = v + 0xC;
    p->mA0 = v + 0x11;
    b = e->a / 2 - 0x21;
    UiSetWidgetPos_290f60(self->m0, id2, 0, offs);
    UiSetWidgetPos_290f60(self->m0, id3, b + 0x29, offs);
    UiSetWidgetPos_290f60(self->m0, id4, b, offs);
    UiSetWidgetPos_290f60(self->m0, id5, b, offs);
    return ret;
}

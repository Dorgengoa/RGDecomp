/* rgp:protos */
#line 1
#include "types.h"

struct R002A7370 {
    u8 pad0[0x2C];
    s16 unk2C;
};

class V002A7370 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void x10() { VCM0(void, 0x30); }
    
    
    
    
    
    
    
    void x18() { VCM0(void, 0x50); }
    
    
    
    
    
    
    
    struct R002A7370 * f26(s16 a0) { return VCM(struct R002A7370 *, (void *, s16), 0x70, a0); }
};
struct C002A7370 {
    u8 pad0[8];
    V002A7370 *unk8;
};

struct B002A7370 {
    u8 pad0[0x40];
    C002A7370 *unk40;
};

struct A002A7370 {
    u8 pad0[8];
    B002A7370 *unk8;
};

struct P002A7370 {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
};

struct Q002A7370 {
    u8 pad0[2];
    s16 unk2;
};

struct S002A7370 {
    u8 pad0[0x18];
    Q002A7370 *unk18;
};

struct T002A7370 {
    u8 pad0[4];
    u16 unk4;
    u8 pad6[0xC - 6];
    u16 unkC;
};

struct O002A7370 {
    u8 pad0[0x10];
    s32 unk10;
};

extern "C" {
extern A002A7370 *GetGameData_1fede0(void);
extern void UiSetItemIconUv_288e50(T002A7370 *, s16, s32, s32);
extern P002A7370 *UiEntryListGetCurrentData_28ec60(s32);
extern T002A7370 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern S002A7370 * InvObjCastToItem4B0_3d3cd0(O002A7370 *, int, int, int);
extern s32 ItemDefIsKindCId4B0_40e310(s32);
extern f32 D_0047D34C;
extern f32 D_0047D3C8;
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 D_004823CC;
extern s16 D_00482488;
}

extern "C" void MenuCageBaitIconUpdate_2a7370(O002A7370 *arg0, s32 arg1)
{
    S002A7370 *s;
    P002A7370 *p;
    s32 n;
    R002A7370 *r;
    T002A7370 *t;

    if (D_00482488 != 0) {
        return;
    }
    if (D_004823CC != 0) {
        UiSetWidgetAlpha_2907a0(D_00482360, 0x140, 0.0f);
        return;
    }
    if (arg1 != 0) {
        if (arg0 == NULL) {
            UiFadeWidgetAlpha_290690(D_00482360, 0x140, 0.0f, D_0047D3C8, -1.0f);
        } else if (arg0->unk10 != 0) {
            if (ItemDefIsKindCId4B0_40e310(arg0->unk10) != 0) {
                s = InvObjCastToItem4B0_3d3cd0(arg0, 0, 0, 0);
                if (s == NULL) {
                    return;
                }
                p = UiEntryListGetCurrentData_28ec60(D_00482364);
                UiSetWidgetPos_290f60(D_00482360, 0x140, p->unk10 * 0x2A + 0x10, p->unk12 * 0x32);
                UiSetWidgetPos_290f60(D_00482360, 0x142, 0xD, -0x27);
                UiFadeWidgetAlpha_290690(D_00482360, 0x140, 1.0f, D_0047D34C, -1.0f);
                n = s->unk18->unk2;
                if (n > 0) {
                    r = GetGameData_1fede0()->unk8->unk40->unk8->f26(n);
                    if (r == NULL) {
                        return;
                    }
                    t = UiGetWidgetSprite_28fe10(D_00482360, 0x142, 0);
                    if (t == NULL) {
                        return;
                    }
                    UiSetItemIconUv_288e50(t, r->unk2C, 0x28, 0x2D);
                } else {
                    t = UiGetWidgetSprite_28fe10(D_00482360, 0x142, 0);
                    if (t == NULL) {
                        return;
                    }
                    t->unkC = 0;
                    t->unk4 = 0;
                }
            } else {
                UiFadeWidgetAlpha_290690(D_00482360, 0x140, 0.0f, D_0047D3C8, -1.0f);
            }
        }
    } else {
        UiFadeWidgetAlpha_290690(D_00482360, 0x140, 0.0f, D_0047D3C8, -1.0f);
    }
}

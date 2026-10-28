#include "types.h"
#pragma opt_propagation off

class Obj003d3ef0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vB4() { return VCM0(s32, 0xB4); }
    u8 pad4[0xC];
    s32 unk10;
};

typedef struct {
    u8 pad0[0x6];
    u16 unk6;
} Obj0040e110;

typedef struct {
    u8 pad0[0x94];
    f32 unk94;
    f32 unk98;
} Obj3d3ef0_b;

extern "C" Obj0040e110 *ItemDefGetWeaponData_40e110(s32);
extern "C" s32 D_00465BF8[];
extern "C" u8 *D_004838EC;
extern "C" f32 D_0047D258;

extern "C" s32 ItemWeaponGetPowerMaybe_3d3ef0(Obj003d3ef0 *arg0)
{
    s32 v;
    Obj0040e110 *t;
    Obj3d3ef0_b *b;
    f32 fv;
    f32 x;
    f32 y;
    f32 k;

    t = ItemDefGetWeaponData_40e110(arg0->unk10);
    if (t == NULL) {
        return 0;
    }
    v = t->unk6 & 0x3FF;
    if (arg0->vB4() != 0) {
        b = *(Obj3d3ef0_b **)(*(u8 **)(D_004838EC + 0x40) + 0x8);
        x = b->unk94; y = b->unk98; fv = (f32)v;
        v = (s32)(D_0047D258 + (y + fv * x));
    }
    if (D_00465BF8[0] < v) {
        v = D_00465BF8[0];
    }
    return v;
}

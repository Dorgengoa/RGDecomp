#include "types.h"
#undef NULL
#define NULL 0
#pragma opt_propagation off
extern "C" {

typedef struct VTb4 {
    u8 pad[0xB4];
    s32 (*unkB4)(void *);
} VTb4;

s32 ItemDefGetWeaponData_40e110(s32);
extern s32 D_004659B0[4];
extern f32 D_0047D258;
extern u8 *D_004838EC;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xB4); }
};
s32 ItemWeaponGetAttrMax_3d3470(u8 *arg0, s32 arg1) {
    s32 temp_2;
    s32 var_16;
    u8 *p3;
    f32 fv;
    f32 fb;
    f32 fm;

    if ((arg1 < 0) || (arg1 >= 5)) return 0;
    temp_2 = ItemDefGetWeaponData_40e110(*(s32 *)(arg0 + 0x10));
    if (temp_2 == 0) {
        return 0;
    }
    var_16 = *(u8 *)((u8 *)(arg1 * 2) + temp_2 + 0x19);
    if (((VC_0 *)(arg0))->f() != 0) {
        p3 = *(u8 **)(*(u8 **)(D_004838EC + 0x40) + 8);
        fm = *(f32 *)(p3 + 0x94);
        fb = *(f32 *)(p3 + 0x98);
        fv = (f32) var_16;
        var_16 = (s32) (D_0047D258 + (fb + fv * fm));
    }
    if (D_004659B0[0] < var_16) {
        var_16 = D_004659B0[0];
    }
    return var_16;
}

}

#include "types.h"
extern "C" {

extern void *ItemDefGetSpecialWeaponData_40e0e0(s32 arg0);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    f32 f() { return VCM0(f32, 0xE0); }
};
f32 ItemSpecialWeaponGetChargePercent_3d2db0(void *arg0)
{
    f32 var_f1;
    f32 temp_f5;
    f32 temp_f0;
    f32 temp_f4;
    f32 add;
    f32 var_f2;
    void *temp_2;

    temp_2 = ItemDefGetSpecialWeaponData_40e0e0(*(s32 *)((u8 *)arg0 + 0x10));
    if (temp_2 == NULL) {
        return 0.0f;
    }
    temp_f0 = ((VC_0 *)(arg0))->f();
    temp_f5 = (f32) *(s8 *)((u8 *)temp_2 + 0x2E);
    temp_f4 = (f32) *(s16 *)((u8 *)temp_2 + 0x30);
    add = (f32) *(s16 *)((u8 *)arg0 + 0x26) / 25.0f;
    var_f2 = temp_f4 * ((f32)(*(s8 *)((u8 *)temp_2 + 0x2C)) / temp_f5);
    if (var_f2 <= 0.0f) {
        var_f2 = 1.0f;
    }
    var_f1 = temp_f4 * (*(f32 *)((u8 *)arg0 + 0x20) / temp_f5);
    if (*(s16 *)((u8 *)arg0 + 0x24) & 4) {
        var_f1 += add;
    }
    if (!(var_f1 <= var_f2)) {
        var_f1 = var_f2;
    }
    return temp_f0 * (var_f1 / var_f2);
}

}

/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

extern "C" {
extern s32 EquipSlotGetGaugeMax_3a02d0(void *);
extern void *D_0048374C;
}
class VA_3a07b0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x28); }
};
class VB_3a07b0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s16 x) { return VCM(s32, (void *, s16), 0x70, x); }
};

extern "C" s32 EquipSlotSetAbility_3a07b0(void *arg0, s16 arg1, s64 arg2)
{
    f32 var_f21;
    f32 var_f20;
    f32 temp_f0;
    s16 var_16;
    VB_3a07b0 *temp_4;

    if (D_0048374C == NULL) {
        return 0;
    }
    var_f21 = 0.0f;
    var_16 = 0;
    var_f20 = var_f21;
    if (*(s32 *)((u8 *)arg0 + 0x4) != 0) {
        temp_f0 = (f32)EquipSlotGetGaugeMax_3a02d0((void *)arg0);
        var_16 = *(s16 *)((u8 *)arg0 + 0xC);
        var_f21 = *(f32 *)((u8 *)arg0 + 0x10);
        var_f20 = temp_f0 - var_f21;
    }
    ((VA_3a07b0 *)arg0)->f();
    *(s16 *)((u8 *)arg0 + 0xA) = arg1;
    *(s16 *)((u8 *)arg0 + 0x8) = (s16)arg2;
    temp_4 = *(VB_3a07b0 **)((u8 *)(*(void **)((u8 *)D_0048374C + 0x44)) + 0x8);
    *(s32 *)((u8 *)arg0 + 0x4) = temp_4->f((s16)arg2);
    if ((*(s16 *)((u8 *)arg0 + 0xA) < 0) || (*(s32 *)((u8 *)arg0 + 0x4) == 0)) {
        {
            s16 m = -1;
            *(s16 *)((u8 *)arg0 + 0xA) = m;
            *(s16 *)((u8 *)arg0 + 0x8) = m;
        }
        *(s32 *)((u8 *)arg0 + 0x4) = 0;
        return 0;
    }
    if (!(var_f21 <= 0.0f)) {
        temp_f0 = (f32)EquipSlotGetGaugeMax_3a02d0((void *)(arg0));
        var_f21 = temp_f0 - var_f20;
        if (!(var_f21 <= temp_f0)) {
            var_f21 = temp_f0;
        }
    }
    *(f32 *)((u8 *)arg0 + 0x10) = var_f21;
    *(s16 *)((u8 *)arg0 + 0xC) = var_16;
    return 1;
}

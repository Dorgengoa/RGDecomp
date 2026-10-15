#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

extern "C" {
extern s32 EquipSlotGetGaugeMax_3a02d0(...);
extern void *D_0048374C;
}
class VA_3a07b0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void f();
};
class VB_3a07b0 {
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
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual s32 f(s16 x);
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
        temp_f0 = (f32)EquipSlotGetGaugeMax_3a02d0();
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
        temp_f0 = (f32)EquipSlotGetGaugeMax_3a02d0(arg0);
        var_f21 = temp_f0 - var_f20;
        if (!(var_f21 <= temp_f0)) {
            var_f21 = temp_f0;
        }
    }
    *(f32 *)((u8 *)arg0 + 0x10) = var_f21;
    *(s16 *)((u8 *)arg0 + 0xC) = var_16;
    return 1;
}

#include "types.h"
extern "C" {

extern void *ItemDefGetSpecialWeaponData_40e0e0(s32 arg0);

class VC_0 {
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
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual f32 f();
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

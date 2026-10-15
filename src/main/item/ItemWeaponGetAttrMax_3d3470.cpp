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
    virtual s32 f();
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

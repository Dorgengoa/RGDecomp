#include "types.h"

extern "C" {

class C {
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
    virtual s32 f94(s32);
    virtual s32 f98();
};
static inline bool lt5(s32 i)
{
    return i < 5;
}
static inline bool valid(s32 i)
{
    return i >= 0 && i < 5;
}

#pragma opt_propagation off
void ItemWeaponSetAttr_3d32e0(C *arg0, s32 arg1, s32 arg2) {
    s32 v;
    s32 lo;
    s32 hi;
    u8 *q;

    if (arg1 < 0 || arg1 >= 5) {
        return;
    }
    {
    s32 w = arg2;
    lo = arg0->f98();
    v = w;
    }
    hi = arg0->f94(arg1);
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    *(u8 *)(arg1 + (s32)arg0 + 0x17) = v;
}

}

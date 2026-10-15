#pragma opt_propagation off
#include "types.h"
#pragma divbyzerocheck on

class B39f030 {
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
    virtual s32 f();
};

class A39f030 {
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
    virtual B39f030 *f();
};

struct P39f030 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
};

struct O39f030 : public A39f030 {
    P39f030 *p4;
};

extern "C" void *memset(void *, s32, s32);
extern s8 D_00483780[16] __attribute__((section(".sdata")));

extern "C" s8 *EquipSlotBuildUnitAbilityResNameMaybe_39f030(O39f030 *arg0)
{
    B39f030 *b;
    s8 *r;
    s32 id;
    s32 n;
    s32 c0;
    s32 c1;
    s32 c2;

    if (arg0->p4 == 0) {
        return 0;
    }
    memset(D_00483780, 0, 16);
    c0 = 0;
    c1 = 0;
    c2 = 0;
    id = -1;
    b = arg0->f();
    if (b != 0) {
        id = b->f();
    }
    id = id % 1000;
    switch (arg0->p4->b2) {
    case 0:
        switch (arg0->p4->b3) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            c0 = 'a';
            c1 = 'b';
            c2 = 'i';
            break;
        default:
            c0 = 0;
            c1 = 0;
            c2 = 0;
            break;
        }
        break;
    }
    n = arg0->p4->b4;
    r = 0;
    if (id >= 0 && (s8)c0 != 0 && (s8)c1 != 0 && (s8)c2 != 0 && n >= 0) {
        s8 *p;
        D_00483780[0] = 'e';
        p = D_00483780;
        p[1] = id / 100 % 10 + '0';
        p[2] = id / 10 % 10 + '0';
        p[3] = id % 10 + '0';
        p[4] = '_';
        p[5] = c0;
        p[6] = c1;
        p[7] = c2;
        p[8] = n / 10 % 10 + '0';
        p[9] = n % 10 + '0';
        p[10] = 0;
        r = D_00483780;
    }
    return r;
}

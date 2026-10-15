#include "types.h"

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
    virtual s32 f(s16 x0);
};

extern "C" {
extern s32 Fprintf_12f9a0(s32, void *);
extern void Abort_12de80(void);
extern s16 *AbilityListFindByCompositeId_3f5670(s32, s32, s32);
extern u8 *D_00449858[0x100];
extern u8 D_00465ED0[];
extern u8 *D_0048381C;
}

class Bit3AD940 {
public:
    s64 *p;
    u32 n;
    Bit3AD940(s64 *pp, u32 nn) : p(pp), n(nn) {}
    s64 Get()
    {
        u32 k = n;
        if (k >= 0x40) {
            Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00465ED0);
            Abort_12de80();
        }
        return *p & (1LL << k);
    }
};

extern "C" s32 CharaFindLearnedAbility_3ad940(u8 *arg0, s32 arg1, s32 arg2)
{
    s32 result;
    s16 *p3;
    s32 i;
    s32 t2;
    s16 *node;

    if (D_0048381C == 0 || (p3 = *(s16 **)(arg0 + 0x230)) == 0) {
        return 0;
    }
    if ((t2 = (*(VC_0 **)(*(u8 **)(D_0048381C + 0x44) + 0xC))->f(*p3)) == 0) {
        return 0;
    }
    result = 0;
    i = 0;
    for (;;) {
        node = AbilityListFindByCompositeId_3f5670(t2, arg1, i);
        if (node == 0) {
            if (i == 0) {
            } else {
                break;
            }
        } else {
            if (Bit3AD940((s64 *)(arg0 + (arg2 & 0xFF) * 8 + 0x2E0), *node - 1).Get()) {
                result = *(s32 *)(node + 2);
                break;
            }
        }
        i++;
    }
    return result;
}

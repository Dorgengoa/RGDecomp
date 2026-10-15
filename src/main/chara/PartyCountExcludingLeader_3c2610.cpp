#include "types.h"
#pragma opt_propagation off
#undef NULL
#define NULL 0

class VC_1 {
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
    virtual s32 fBC();
    virtual s32 fC0();
};

extern "C" {
extern VC_1 *CharaMgrPoolFindById_3a8c60(s32, s16);
extern s32 PartyCountMembers_3c2010(void *, s32, s32);
extern void *D_00483890;

s32 PartyCountExcludingLeader_3c2610(void *arg0, s32 arg1, s32 arg2)
{
    s32 n;
    VC_1 *o;
    s16 k;

    if ((arg1 == 0) && (arg2 == 0)) {
        return 0;
    }
    n = PartyCountMembers_3c2010(arg0, arg1, arg2);
    if (D_00483890 == NULL) {
        o = NULL;
    } else {
        k = *(s16 *)((u8 *)arg0 + 0x18E);
        o = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), k);
    }
    if (o != NULL) {
        if (arg1 != 0 && o->fBC() != 0) {
            n -= 1;
        }
        if (arg2 != 0 && o->fC0() != 0) {
            n -= 1;
        }
    }
    if (n < 0) {
        n = 0;
    }
    return n;
}
}

#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

class VC_40b490 {
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
    virtual s32 f(s16);
};

extern "C" {

extern void *IterNext_370040(void *arg0);
extern void IterInit_370170(void *arg0, s32 arg1);
static inline void *Nx(void *s) { return IterNext_370040(s); }

s32 WorldSubsysLinkIds_40b490(s32 arg0, void *arg1)
{
    u8 sp78[8];
    u8 *q;
    s32 j;
    u8 *p;
    s32 i;
    u8 *e;
    s32 a;

    if (arg1 == NULL) {
        return 0;
    }
    a = arg0;
    if (arg0 != 0) {
        a += 0x88;
    }
    IterInit_370170(sp78, a);
    while ((e = (u8 *)Nx(sp78)) != NULL) {
        q = *(u8 **)(e + 0x10);
        for (j = 0; j < *(s16 *)(e + 0xE); j++, q += 0x18) {
            *(s32 *)(q + 0xC) = (*(VC_40b490 **)(*(u8 **)((u8 *)arg1 + 0x6C) + 8))->f(*(s32 *)(q + 0xC));
            p = *(u8 **)(q + 0x14);
            for (i = 0; i < *(s16 *)(q + 0x12); i++) {
                *(s32 *)(p + 8) = (*(VC_40b490 **)(*(u8 **)((u8 *)arg1 + 0x40) + 8))->f(*(s32 *)(p + 8));
                p += 0x28;
            }
        }
    }
    return 1;
}

}

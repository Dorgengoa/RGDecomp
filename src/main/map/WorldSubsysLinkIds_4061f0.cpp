#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
class VC_4061f0 {
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

s32 WorldSubsysLinkIds_4061f0(s32 arg0, void *arg1)
{
    u8 sp58[0x8];
    u8 *e;
    u8 *p;
    s32 n;
    s32 i;
    s32 a;

    if (arg1 == NULL) {
        return 0;
    }
    a = arg0;
    if (arg0 != 0) {
        a += 0x88;
    }
    IterInit_370170(sp58, a);
    while ((e = (u8 *)IterNext_370040(sp58)) != NULL) {
        *(s32 *)(e + 4) = (*(VC_4061f0 **)(*(u8 **)((u8 *)arg1 + 0x40) + 8))->f(*(s32 *)(e + 4));
        p = *(u8 **)(e + 0xC);
        n = *(s16 *)(e + 8);
        if (p != NULL && n > 0) {
            for (i = 0; i < n; i++) {
                *(s32 *)p = (*(VC_4061f0 **)(*(u8 **)((u8 *)arg1 + 0x40) + 8))->f(*(s32 *)p);
                p += 0x10;
            }
        }
    }
    return 1;
}

}

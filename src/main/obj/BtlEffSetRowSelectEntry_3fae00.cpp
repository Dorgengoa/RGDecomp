#include "types.h"

struct R3FAE00 { u8 pad000[0x10]; s32 f10; };
struct Base3FAE00 { u8 pad000[0x10]; };
struct C3FAE00 : Base3FAE00 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual struct R3FAE00 *v7(void *b, void *c, void *d);
};

extern "C" s32 BtlEffSetRowSelectEntry_3fae00(void *self, struct C3FAE00 *a, void *b, void *c, void *d)
{
    struct R3FAE00 *r;

    if (a == 0) return 0;
    r = a->v7(b, c, d);
    if (r == 0) return 0;
    if (r != 0) {
        return r->f10;
    }
    return 0;
}

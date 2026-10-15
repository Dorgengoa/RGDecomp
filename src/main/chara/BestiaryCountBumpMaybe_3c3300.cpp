#pragma opt_propagation off
#include "types.h"

struct Ent003C3300 {
    s16 key;
    s16 cnt;
};

class V003C3300 {
public:
    virtual void x0();
    virtual void x1();
    virtual void x2();
    virtual void x3();
    virtual void x4();
    virtual void x5();
    virtual void x6();
    virtual void x7();
    virtual void x8();
    virtual void x9();
    virtual void x10();
    virtual void x11();
    virtual void x12();
    virtual void x13();
    virtual void x14();
    virtual void x15();
    virtual void x16();
    virtual void x17();
    virtual void x18();
    virtual void x19();
    virtual void x20();
    virtual void x21();
    virtual void x22();
    virtual void x23();
    virtual void x24();
    virtual void x25();
    virtual void f26(s16);
};
struct B003C3300 {
    u8 pad0[0xC];
    V003C3300 *unkC;
};

struct A003C3300 {
    u8 pad0[0x64];
    B003C3300 *unk64;
};

struct O003C3300 {
    u8 pad0[0x17C];
    Ent003C3300 *unk17C;
};

extern "C" {
extern s32 D_00465B70[];
extern s32 D_00465B78[];
extern A003C3300 *D_00483894;
}

static inline Ent003C3300 *find003C3300(Ent003C3300 *t, s32 key)
{
    Ent003C3300 *p;
    s32 i;

    if (t != 0) {
        goto scan;
    }
    return 0;
scan:
    p = t;
    for (i = 0; i < D_00465B70[0]; i++, p++) {
        if (p->key == key) {
            return p;
        }
    }
    return 0;
}

extern "C" Ent003C3300 *BestiaryCountBumpMaybe_3c3300(O003C3300 *arg0, s32 arg1)
{
    Ent003C3300 *t;
    Ent003C3300 *e;
    s32 i;
    s16 n;

    if (D_00483894 == 0) {
        return 0;
    }
    t = arg0->unk17C;
    if (t == 0) {
        return 0;
    }
    if (arg1 < 0) {
        return 0;
    }
    e = find003C3300(t, arg1);
    if (e == 0) {
        for (i = 0; i < D_00465B70[0]; i++, t++) {
            if (t->key == -1) {
                t->key = -1;
                e = t;
                t->cnt = 0;
                t->key = arg1;
                break;
            }
        }
    }
    if (e != 0) {
        D_00483894->unk64->unkC->f26(arg1);
        {
            s16 c = e->cnt;
            s32 m = D_00465B78[0];
            n = c + 1;
            e->cnt = n;
            if (m < n) {
                e->cnt = m;
            }
        }
    }
    return e;
}

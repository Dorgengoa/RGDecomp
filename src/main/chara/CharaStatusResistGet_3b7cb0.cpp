#include "types.h"

struct R_003b7cb0 {
    u8 pad0[3];
    s8 f3;
};

struct O_003b7cb0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual R_003b7cb0 *v26(s32);
};

struct P_003b7cb0 {
    u8 pad0[8];
    O_003b7cb0 *f8;
};

struct G_003b7cb0 {
    u8 pad0[0x58];
    P_003b7cb0 *f58;
};

struct Row_003b7cb0 {
    s16 e[2];
};

struct S_003b7cb0 {
    u8 pad0[0x68];
    Row_003b7cb0 tbl[1];
};

extern "C" G_003b7cb0 *D_0048381C;

extern "C" s32 CharaStatusResistGet_3b7cb0(S_003b7cb0 *self, s32 b, s32 c)
{
    G_003b7cb0 *g;
    O_003b7cb0 *o;
    R_003b7cb0 *r;
    s32 k;
    g = D_0048381C;
    if (g != 0) goto g1;
    return 0;
g1:
    if (c < 0) goto zero;
    if (c < 2) goto ok;
zero:
    return 0;
ok:
    o = g->f58->f8;
    if (o != 0) {
        r = o->v26((s16)b);
    } else {
        r = 0;
    }
    if (r == 0) return 0;
    k = r->f3;
    if (k < 0) return 0;
    return self->tbl[k].e[c];
}

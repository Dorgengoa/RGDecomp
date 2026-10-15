#include "types.h"

struct E_003eae10 { u8 b[28]; };

struct R_003eae10 {
    u8 pad0[4];
    s16 f4;
    u8 pad6[2];
    E_003eae10 *f8;
};

struct O_003eae10 {
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
    virtual R_003eae10 *v26(s32);
};

struct P_003eae10 {
    u8 pad0[0xC];
    O_003eae10 *fC;
};

struct Q_003eae10 {
    u8 pad0[0x8C];
    P_003eae10 *f8C;
};

struct S_003eae10 {
    u8 pad0[8];
    Q_003eae10 *f8;
};

struct C_003eae10 {
    u8 f0_lo : 6;
    u8 f0_hi : 2;
    u8 f1_lo : 1;
    u8 f1_mid : 4;
    u8 f1_hi : 3;
};

extern "C" E_003eae10 *RevelationBoardCellGetEntry_3eae10(S_003eae10 *self, s32 b, C_003eae10 *c)
{
    R_003eae10 *r;
    s32 f;
    s32 i;
    if (c != 0) goto g1;
    return 0;
g1:
    r = self->f8->f8C->fC->v26((s16)b);
    if (r == 0) return 0;
    f = c->f1_mid;
    if (f <= 9) return 0;
    i = c->f0_lo;
    if (i < 0) goto zero;
    if (i < r->f4) goto ok;
zero:
    return 0;
ok:
    return &r->f8[i];
}

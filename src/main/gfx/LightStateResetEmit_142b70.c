#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;
typedef struct F4 { f32 v[4]; } F4;
typedef struct I16 { s32 v[16]; } I16;
typedef struct F16 { F4 r0; F4 r1; F4 r2; F4 r3; } F16;
typedef struct Q12 { u128 v[12]; } Q12;

typedef struct Big {
    s32 m0;
    s32 m4;
    s32 pad8[2];
    F4 m10;
    I16 m20;
    I16 m60;
    F16 mA0;
    Q12 mE0;
} Big;

typedef struct Res {
    u8 pad0[0x28];
    u8 *m28;
    s32 m2C;
} Res;

typedef struct Mgr {
    s32 m0;
    u8 pad4[4];
    u8 *m8[0x3C6];
    s32 mF20;
    u8 padF24[0x2790];
    Big *m36B4;
    u8 pad36B8[4];
    s32 m36BC;
    s32 m36C0;
} Mgr;

extern s32 LightStateWritePacket_1484a0(Mgr *, u8 *);
extern void MemStackAllocQw_14d950(Res *, s32);

void LightStateResetEmit_142b70(Mgr *arg0)
{
    Big *p;
    Big *q;
    u8 *d;
    Res *r;
    s32 n;
    u8 *e;

    if (arg0->mF20 == 0) {
        return;
    }
    arg0->m36C0 = 1;
    p = arg0->m36B4;
    if (p != NULL && arg0->mF20 != 0) {
        n = arg0->m36C0;
        arg0->m36C0 = n + 1;
        p->m0 = n;
        arg0->m36BC = n;
        q = p;
        p->m0 = q->m0;
        p->m4 = q->m4;
        p->m10 = q->m10;
        p->m20 = q->m20;
        p->m60 = q->m60;
        p->mA0.r0 = q->mA0.r0;
        p->mA0.r1 = q->mA0.r1;
        p->mA0.r2 = q->mA0.r2;
        p->mA0.r3 = q->mA0.r3;
        p->mE0 = q->mE0;
        p->m4 = 0;
        arg0->m36B4 = p;
    }
    p = arg0->m36B4;
    if (p->m4 != 0) {
        return;
    }
    e = arg0->m8[arg0->m0];
    if (e != NULL) {
        r = (Res *)(e + 8);
    } else {
        r = NULL;
    }
    d = NULL;
    if (r != NULL) {
        d = r->m28 + r->m2C * 16;
    }
    if (d == NULL) {
        return;
    }
    n = LightStateWritePacket_1484a0(arg0, d);
    if (n <= 0) {
        return;
    }
    MemStackAllocQw_14d950(r, n);
    p->m4 = (s32)d;
}

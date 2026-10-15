#include "types.h"

typedef struct E1_0040ed50 { u8 b[992]; } E1_0040ed50;
typedef struct E2_0040ed50 { u8 b[152]; } E2_0040ed50;
typedef struct E3_0040ed50 { u8 b[88]; } E3_0040ed50;

typedef struct T_0040ed50 {
    u8 pad0[8];
    s16 f8;
} T_0040ed50;

typedef struct P_0040ed50 {
    u8 pad0[8];
    E3_0040ed50 *f8;
} P_0040ed50;

typedef struct S_0040ed50 {
    s32 f0;
    P_0040ed50 *f4;
    u8 pad8[4];
    E1_0040ed50 *fC;
    u8 pad10[4];
    E2_0040ed50 *f14;
} S_0040ed50;

extern struct { s32 v; s32 pad[3]; } D_00465828;
extern struct { s32 v; s32 pad[3]; } D_00465830;
extern void DataTableInitWithCount_368b00(void *, E3_0040ed50 *);
extern void WorldSubsysPlanetEntryBind_40fda0(E1_0040ed50 *, T_0040ed50 *, s32);
extern void WorldSubsysPlanetEntryBind_40f5d0(E2_0040ed50 *, T_0040ed50 *, s32);

s32 WorldSubsysPlanetEntryAttach_40ed50(S_0040ed50 *self, T_0040ed50 *t)
{
    E1_0040ed50 *e1;
    E2_0040ed50 *e2;
    E1_0040ed50 *b1;
    E2_0040ed50 *b2;
    P_0040ed50 *p;
    E3_0040ed50 *m;
    s32 n;
    if (t == 0) return 0;
    n = t->f8;
    if (n < 0) goto zero;
    if (n < 2) goto g1;
zero:
    return 0;
g1:
    if (self->f0 != 0) goto g2;
    return 0;
g2:
    b1 = self->fC;
    e1 = 0;
    if (b1 != 0) {
        e1 = &b1[n];
    }
    b2 = self->f14;
    e2 = 0;
    if (b2 != 0) {
        e2 = &b2[n];
    }
    p = self->f4;
    if (p == 0) goto skip;
    m = &p->f8[n];
    if (m == 0) goto skip;
    if (e1 == 0) goto s2l;
    if (D_00465828.v != 0) goto s2l;
    DataTableInitWithCount_368b00(e1, m);
s2l:
    if (e2 == 0) goto skip;
    if (D_00465830.v != 0) goto skip;
    DataTableInitWithCount_368b00(e2, m);
skip:
    if (e1 == 0) goto s3l;
    WorldSubsysPlanetEntryBind_40fda0(e1, t, D_00465828.v != 0);
s3l:
    if (e2 == 0) goto one;
    WorldSubsysPlanetEntryBind_40f5d0(e2, t, D_00465830.v != 0);
one:
    return 1;
}

#include "types.h"

typedef struct E1_00411a40 { u8 b[164]; } E1_00411a40;
typedef struct E2_00411a40 { u8 b[156]; } E2_00411a40;
typedef struct E3_00411a40 { u8 b[152]; } E3_00411a40;
typedef struct E4_00411a40 { u8 b[180]; } E4_00411a40;
typedef struct E5_00411a40 { u8 b[760]; } E5_00411a40;
typedef struct M_00411a40 { u8 b[88]; } M_00411a40;

typedef struct T_00411a40 {
    u8 pad0[8];
    s16 f8;
} T_00411a40;

typedef struct P_00411a40 {
    u8 pad0[8];
    M_00411a40 *f8;
} P_00411a40;

typedef struct S_00411a40 {
    s32 f0;
    P_00411a40 *f4;
    u8 pad8[0x3C - 8];
    E1_00411a40 *f3C;
    E2_00411a40 *f40;
    u8 pad44[4];
    E3_00411a40 *f48;
    E4_00411a40 *f4C;
    E5_00411a40 *f50;
} S_00411a40;

extern struct { s32 v; s32 pad[3]; } D_004656C0;
extern struct { s32 v; s32 pad[3]; } D_004656C8;
extern struct { s32 v; s32 pad[3]; } D_004656D0;
extern struct { s32 v; s32 pad[3]; } D_004656D8;
extern struct { s32 v; s32 pad[3]; } D_004656E0;
extern void DataTableInitWithCount_368b00(void *, M_00411a40 *);
extern void WorldSubsysPlanetEntryBind_414060(E1_00411a40 *, T_00411a40 *, s32);
extern void WorldSubsysPlanetEntryBind_413930(E2_00411a40 *, T_00411a40 *, s32);
extern void WorldSubsysPlanetEntryBind_413550(E3_00411a40 *, T_00411a40 *, s32);
extern void WorldSubsysPlanetEntryBind_413110(E4_00411a40 *, T_00411a40 *, s32);
extern void WorldSubsysPlanetEntryBind_412a80(E5_00411a40 *, T_00411a40 *, s32);

s32 WorldSubsysPlanetEntryAttach_411a40(S_00411a40 *self, T_00411a40 *t)
{
    E1_00411a40 *e1;
    E2_00411a40 *e2;
    E3_00411a40 *e3;
    E4_00411a40 *e4;
    E5_00411a40 *e5;
    E1_00411a40 *b1;
    E2_00411a40 *b2;
    E3_00411a40 *b3;
    E4_00411a40 *b4;
    E5_00411a40 *b5;
    P_00411a40 *p;
    M_00411a40 *m;
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
    b1 = self->f3C;
    e1 = 0;
    if (b1 != 0) {
        e1 = &b1[n];
    }
    b2 = self->f40;
    e2 = 0;
    if (b2 != 0) {
        e2 = &b2[n];
    }
    b3 = self->f48;
    e3 = 0;
    if (b3 != 0) {
        e3 = &b3[n];
    }
    b4 = self->f4C;
    e4 = 0;
    if (b4 != 0) {
        e4 = &b4[n];
    }
    b5 = self->f50;
    e5 = 0;
    if (b5 != 0) {
        e5 = &b5[n];
    }
    p = self->f4;
    if (p == 0) goto skip;
    m = &p->f8[n];
    if (m == 0) goto skip;
    if (e1 == 0) goto s2l;
    if (D_004656C0.v != 0) goto s2l;
    DataTableInitWithCount_368b00(e1, m);
s2l:
    if (e2 == 0) goto s3l;
    if (D_004656C8.v != 0) goto s3l;
    DataTableInitWithCount_368b00(e2, m);
s3l:
    if (e3 == 0) goto s4l;
    if (D_004656D0.v != 0) goto s4l;
    DataTableInitWithCount_368b00(e3, m);
s4l:
    if (e4 == 0) goto s5l;
    if (D_004656D8.v != 0) goto s5l;
    DataTableInitWithCount_368b00(e4, m);
s5l:
    if (e5 == 0) goto skip;
    if (D_004656E0.v != 0) goto skip;
    DataTableInitWithCount_368b00(e5, m);
skip:
    if (e1 == 0) goto t2l;
    WorldSubsysPlanetEntryBind_414060(e1, t, D_004656C0.v != 0);
t2l:
    if (e2 == 0) goto t3l;
    WorldSubsysPlanetEntryBind_413930(e2, t, D_004656C8.v != 0);
t3l:
    if (e3 == 0) goto t4l;
    WorldSubsysPlanetEntryBind_413550(e3, t, D_004656D0.v != 0);
t4l:
    if (e4 == 0) goto t5l;
    WorldSubsysPlanetEntryBind_413110(e4, t, D_004656D8.v != 0);
t5l:
    if (e5 == 0) goto one;
    WorldSubsysPlanetEntryBind_412a80(e5, t, D_004656E0.v != 0);
one:
    return 1;
}

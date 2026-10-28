/* rgp:protos */
#define RGP_SELF_WorldSubsysPlanetEntryAttach_41fdb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E1_0041fdb0 { u8 b[192]; } E1_0041fdb0;
typedef struct E2_0041fdb0 { u8 b[152]; } E2_0041fdb0;
typedef struct E3_0041fdb0 { u8 b[88]; } E3_0041fdb0;

typedef struct T_0041fdb0 {
    u8 pad0[8];
    s16 f8;
} T_0041fdb0;

typedef struct P_0041fdb0 {
    u8 pad0[8];
    E3_0041fdb0 *f8;
} P_0041fdb0;

typedef struct S_0041fdb0 {
    s32 f0;
    P_0041fdb0 *f4;
    E1_0041fdb0 *f8;
    E2_0041fdb0 *fC;
} S_0041fdb0;

extern struct { s32 v; s32 pad[3]; } D_00465808;
extern struct { s32 v; s32 pad[3]; } D_00465810;
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysPlanetEntryAttach_41fdb0(S_0041fdb0 *self, T_0041fdb0 *t)
{
    E1_0041fdb0 *e1;
    E2_0041fdb0 *e2;
    E1_0041fdb0 *b1;
    E2_0041fdb0 *b2;
    P_0041fdb0 *p;
    E3_0041fdb0 *m;
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
    b1 = self->f8;
    e1 = 0;
    if (b1 != 0) {
        e1 = &b1[n];
    }
    b2 = self->fC;
    e2 = 0;
    if (b2 != 0) {
        e2 = &b2[n];
    }
    p = self->f4;
    if (p == 0) goto skip;
    m = &p->f8[n];
    if (m == 0) goto skip;
    if (e1 == 0) goto s2l;
    if (D_00465808.v != 0) goto s2l;
    DataTableInitWithCount_368b00(e1, m);
s2l:
    if (e2 == 0) goto skip;
    if (D_00465810.v != 0) goto skip;
    DataTableInitWithCount_368b00(e2, m);
skip:
    if (e1 == 0) goto s3l;
    WorldSubsysPlanetEntryBind_420730(e1, t, D_00465808.v != 0);
s3l:
    if (e2 == 0) goto one;
    WorldSubsysPlanetEntryBind_420170(e2, t, D_00465810.v != 0);
one:
    return 1;
}

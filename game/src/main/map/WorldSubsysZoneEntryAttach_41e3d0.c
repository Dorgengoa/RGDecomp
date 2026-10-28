/* rgp:protos */
#define RGP_SELF_WorldSubsysZoneEntryAttach_41e3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_0041e3d0 { u8 b[152]; } E_0041e3d0;

typedef struct T_0041e3d0 {
    u8 pad0[0x10];
    s16 f10;
} T_0041e3d0;

typedef struct S_0041e3d0 {
    s32 f0;
    void *f4;
    E_0041e3d0 *f8;
    E_0041e3d0 *fC;
} S_0041e3d0;

extern struct { s32 v; s32 pad[3]; } D_004644A8;
extern struct { s32 v; s32 pad[3]; } D_004657C0;
extern struct { s32 v; s32 pad[3]; } D_004657C8;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysZoneEntryAttach_41e3d0(S_0041e3d0 *self, T_0041e3d0 *t)
{
    E_0041e3d0 *e1;
    E_0041e3d0 *e2;
    E_0041e3d0 *b1;
    E_0041e3d0 *b2;
    void *p;
    s32 m;
    s32 n;
    if (t == 0) return 0;
    n = t->f10;
    if (n < 0) goto zero;
    if (n < D_004644A8.v) goto g1;
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
    m = ((s32)MemStackArrayGet_3f23f0(p, (int)(n)));
    if (m == 0) goto skip;
    if (e1 == 0) goto s2l;
    if (D_004657C0.v != 0) goto s2l;
    DataTableInitWithCount_368b00(e1, m);
s2l:
    if (e2 == 0) goto skip;
    if (D_004657C8.v != 0) goto skip;
    DataTableInitWithCount_368b00(e2, m);
skip:
    if (e1 == 0) goto s3l;
    WorldSubsysZoneEntryBind_41ecb0(e1, t, D_004657C0.v != 0);
s3l:
    if (e2 == 0) goto one;
    WorldSubsysZoneEntryBind_41e7e0(e2, t, D_004657C8.v != 0);
one:
    return 1;
}

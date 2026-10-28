/* rgp:protos */
#define RGP_SELF_SoundResolveKey_1b9970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct C_001b9970 { u8 b[12]; } C_001b9970;

typedef struct B_001b9970 {
    u8 pad0[0x18];
    s32 f18;
    C_001b9970 *f1C;
    u8 pad20[56 - 0x20];
} B_001b9970;

typedef struct A_001b9970 {
    u8 pad0[0x18];
    B_001b9970 arr18[1];
    u8 pad[480 - 0x18 - 56];
} A_001b9970;

typedef struct O_001b9970 {
    A_001b9970 *f0;
    B_001b9970 *f4;
    C_001b9970 *f8;
    s32 fC;
} O_001b9970;

extern A_001b9970 D_0049EB10[];

void SoundResolveKey_1b9970(O_001b9970 *out, u32 key, s32 i3)
{
    A_001b9970 *p1;
    B_001b9970 *p2;
    C_001b9970 *p3;
    s32 i1;
    s32 i2;
    i1 = (key >> 24) & 0xFF;
    out->f4 = 0;
    out->f8 = 0;
    i2 = (key >> 16) & 0xFF;
    out->fC = -1;
    if (i1 < 0) goto z1;
    if (i1 <= 0x10) goto g1;
z1:
    p1 = 0;
    goto s1;
g1:
    p1 = &D_0049EB10[i1];
s1:
    out->f0 = p1;
    if (p1 == 0) return;
    if (i2 < 0) goto z2;
    if (i2 < 5) goto g2;
z2:
    p2 = 0;
    goto s2;
g2:
    p2 = &p1->arr18[i2];
s2:
    out->f4 = p2;
    if (p2 == 0) return;
    if (i3 < 0) goto z3;
    if (i3 < p2->f18) goto g3;
z3:
    p3 = 0;
    goto s3;
g3:
    p3 = &p2->f1C[i3];
s3:
    out->f8 = p3;
    if (p3 == 0) return;
    out->fC = i3;
}

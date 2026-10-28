/* rgp:protos */
#define RGP_SELF_CameraScreenPointVisible_15d520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B_0015d520 {
    u8 pad0[0xC];
    f32 fC;
    f32 f10;
} B_0015d520;

typedef struct G_0015d520 {
    u8 pad0[0xF20];
    u8 *fF20;
} G_0015d520;

extern G_0015d520 *D_004810A4;

s32 CameraScreenPointVisible_15d520(f32 *p)
{
    G_0015d520 *g;
    B_0015d520 *b;
    u8 *q;
    f32 x;
    f32 y;
    f32 z;
    g = D_004810A4;
    q = (g == 0) ? 0 : g->fF20;
    b = (B_0015d520 *)(q + 0x14);
    x = p[0];
    if (x < 0.0f) goto zeroA;
    if (x <= (f32)0xFFF) goto n1;
zeroA:
    return 0;
n1:
    y = p[1];
    if (y < 0.0f) goto zeroB;
    if (y <= (f32)0xFFF) goto n2;
zeroB:
    return 0;
n2:
    z = p[3];
    if (z < b->fC) goto zeroC;
    if (z <= b->f10) goto one;
zeroC:
    return 0;
one:
    return 1;
}

/* rgp:protos */
#define RGP_SELF_FogSet_15cc60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct D15C {
    f32 f00;
    f32 f04;
    s8  f08;
    s8  f09;
    s8  f0A;
    u8  pad0B[0x9];
    f32 f14;
    f32 f18;
} D15C;

typedef struct C15C {
    u8    pad000[0x36B8];
    D15C *f36B8;
} C15C;

extern C15C *D_004810A4;

void FogSet_15cc60(s32 a, s32 b, s32 c, f32 x, f32 y, f32 u, f32 v)
{
    D15C *q;

    q = D_004810A4->f36B8;
    if (q != 0) {
        q->f00 = x;
        q->f04 = y;
        q->f08 = a;
        q->f09 = b;
        q->f0A = c;
        q->f14 = u;
        q->f18 = v;
    }
}

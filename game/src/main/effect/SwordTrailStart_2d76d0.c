/* rgp:protos */
#define RGP_SELF_SwordTrailStart_2d76d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D5D0 __attribute__((section(".sdata")));

typedef struct S2D7 {
    s16 f00;
    u8  pad002[0xA];
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
} S2D7;



void SwordTrailStart_2d76d0(S2D7 *p, f32 v)
{
    p->f0C = v;
    p->f00 = 1;
    p->f18 = 1.0f;
    p->f14 = 1.0f;
    p->f10 = 0.0f;
    p->f1C = 0.0f;
    p->f2C = 1.0f;
    p->f20 = 1.0f;
    p->f24 = D_0047D5D0;
    p->f28 = 5.0f;
}

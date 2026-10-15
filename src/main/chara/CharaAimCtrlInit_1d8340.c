#include "types.h"

extern const f32 D_0047D244 __attribute__((section(".sdata")));

typedef unsigned __int128 u128;

typedef struct S1D8 {
    u128 f00;
    s16  f10;
    s16  f12;
    f32  f14;
    s32  f18;
    s32  f1C;
    s32  f20;
} S1D8;



void CharaAimCtrlInit_1d8340(S1D8 *p)
{
    p->f18 = 0;
    p->f1C = 0;
    p->f10 = 0;
    p->f12 = 2;
    p->f14 = D_0047D244;
    p->f00 = 0;
    p->f20 = 0;
}

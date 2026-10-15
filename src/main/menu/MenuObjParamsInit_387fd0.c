#include "types.h"

extern const f32 D_0047D2CC __attribute__((section(".sdata")));
extern const f32 D_0047D2BC __attribute__((section(".sdata")));
extern const f32 D_0047D2D0 __attribute__((section(".sdata")));

typedef struct S387 {
    s32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
} S387;


void MenuObjParamsInit_387fd0(S387 *p)
{
    p->f20 = 0;
    p->f04 = D_0047D2CC;
    p->f08 = D_0047D2BC;
    p->f0C = D_0047D2D0;
    p->f10 = 180;
    p->f14 = p->f10 + 180;
    p->f18 = 2;
    p->f1C = p->f18 + 3;
}

#include "types.h"

/* MAIN BlockHeapPoolInit_1c2700 -- divide cohort.  `addiu $3,$0,0x14 / bnez $3 / divu /
   break 0,7` is the divbyzerocheck expansion of `n / 20`.
   Store block order 0x10, 0xC, 0x00, 0x08, 0x04 is SOURCE order. */

#pragma divbyzerocheck on

typedef struct El1C2700 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
} El1C2700;

typedef struct Ctx1C2700 {
    s32 m00;
    El1C2700 *m04;
} Ctx1C2700;

void BlockHeapPoolInit_1c2700(Ctx1C2700 *c, El1C2700 *p, u32 n)
{
    El1C2700 *e;
    s32 i;

    c->m04 = p;
    c->m00 = n / 20;
    for (i = 0; i < c->m00; i++) {
        e = &c->m04[i];
        e->m10 = 0;
        e->m0C = 0;
        e->m00 = 0;
        e->m08 = 0;
        e->m04 = 0;
    }
}

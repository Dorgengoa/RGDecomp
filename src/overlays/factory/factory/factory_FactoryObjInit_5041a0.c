#include "types.h"

/* factory.bin overlay, 0x005041A0 -- 168 B / 42 words.  One unconditional
 * call, a null guard on the second parameter, then three identical four-arg
 * calls over three parallel sub-blocks of the context.
 *
 * `beql $19,$0,<epilogue>` is the guard PAST the whole body, so it is a single
 * `if (b != 0) { ... }` with no else.
 * `sw $19,0x0($20)` sits in the FIRST call's delay slot, so `c->f000 = b;` is
 * the first statement inside the guard, sunk one slot by the scheduler.
 * The three (dst, src) pairs are 0x58 apart every time: 0x68/0xC0,
 * 0x238/0x290, 0x304/0x35C -- three copies of the same sub-layout.
 */

typedef struct Ctx41A0 {
    void *f000;                     /* 0x000 */
    u8    pad004[0x68 - 0x04];
    u8    f068[0x58];               /* 0x068 */
    u8    f0C0[0x238 - 0xC0];       /* 0x0C0 */
    u8    f238[0x58];               /* 0x238 */
    u8    f290[0x304 - 0x290];      /* 0x290 */
    u8    f304[0x58];               /* 0x304 */
    u8    f35C[0x40];               /* 0x35C */
} Ctx41A0;

extern u8 D_0050CE28[];
extern u8 D_0050CE38[];
extern u8 D_0050CE48[];

extern void factory_FactoryObjReset_5049b0(Ctx41A0 *c);
extern void func_201D80(void *dst, void *src, void *tab, s32 n);

void factory_FactoryObjInit_5041a0(Ctx41A0 *c, void *b, s32 x, s32 y, s32 z)
{
    factory_FactoryObjReset_5049b0(c);
    if (b != NULL) {
        c->f000 = b;
        func_201D80(c->f068, c->f0C0, D_0050CE28, x);
        func_201D80(c->f238, c->f290, D_0050CE38, y);
        func_201D80(c->f304, c->f35C, D_0050CE48, z);
    }
}

#include "types.h"

/* factory.bin overlay, 0x005049B0 -- construct the factory panel: reset the
 * seven header words, run the four slot ctors and the four block ctors, then
 * clear the whole cursor/timer tail.
 * 364 bytes, 92 instructions, 3 conditional branches, 7 calls.
 *
 * * The three loops carry their strides in the ADDRESSING, so the element size
 * is readable off the shift chain: `sll 1 / addu / sll 2` is `i * 12` (a
 * 12-byte record), `sll 2` is an `s32` array, and `sll 6` is a 0x40 block.
 *
 * * TWO counters, not one.  The two call loops keep theirs in `$16` and the
 * middle store loop keeps its own in the caller-saved `$3`; one shared counter
 * is [[factory-counter-split-then-decl-order]]'s 3-cycle.
 *
 * * The store run is NOT in address order -- 0x14 before 0x0C, 0x2CC before
 * 0x2C8, 0x2E0 before 0x2DC, 0x2FA/0x2FC before 0x2EA.  mwcc does not reorder
 * stores to one object, so the listing order IS the source order; transcribe
 * it literally.
 */

typedef struct Slot {
    u8 pad00[0xC];
} Slot;                                         /* 0x0C */

typedef struct Blk {
    u8 pad00[0x40];
} Blk;                                          /* 0x40 */

typedef struct Panel {
    s32  f00;
    s32  f04;
    s32  f08;
    s32  f0C;
    u8   pad10[0x4];
    s32  f14;
    s32  f18;
    s32  f1C;
    Slot f20[4];
    s32  f50;
    s32  f54[3];
    s32  f60;
    s32  f64;
    u8   f68[0x58];
    s32  fC0;
    s32  fC4;
    s32  fC8;
    s32  fCC;
    s32  fD0;
    s32  fD4;
    s32  fD8;
    u8   padDC[0x4];
    Blk  fE0[4];
    u8   pad1E0[0x10];
    Blk  f1F0;
    s8   f230;
    u8   pad231[0x7];
    u8   f238[0x58];
    s32  f290;
    u8   pad294[0x34];
    s32  f2C8;
    s32  f2CC;
    s32  f2D0;
    s32  f2D4;
    s32  f2D8;
    s32  f2DC;
    s32  f2E0;
    u8   pad2E4[0x2];
    s16  f2E6;
    s16  f2E8;
    s16  f2EA;
    s16  f2EC;
    s16  f2EE;
    s16  f2F0;
    s16  f2F2;
    s16  f2F4;
    s16  f2F6;
    s16  f2F8;
    s16  f2FA;
    s16  f2FC;
    u8   pad2FE[0x6];
    u8   f304[0x58];
    s32  f35C;
} Panel;

extern void func_14DFF0(void *p);
extern void func_1CCC10(Slot *s);
extern void factory_FactorySlotClear_4ff5d0(Blk *b);
extern void factory_FactoryFloorRelease_503c10(Panel *o);

void factory_FactoryObjReset_5049b0(Panel *o)
{
    s32 i;
    s32 j;

    o->f00 = 0;
    o->f04 = -1;
    o->f08 = -1;
    o->f14 = 0;
    o->f0C = -1;
    o->f18 = 0;
    o->f1C = 0;
    for (i = 0; i < 4; i++) {
        func_1CCC10(&o->f20[i]);
    }
    o->f50 = 0;
    for (j = 0; j < 3; j++) {
        o->f54[j] = 0;
    }
    o->f60 = 0;
    o->f64 = 0;
    for (i = 0; i < 4; i++) {
        factory_FactorySlotClear_4ff5d0(&o->fE0[i]);
    }
    factory_FactorySlotClear_4ff5d0(&o->f1F0);
    o->f230 = 0;
    func_14DFF0(o->f68);
    o->fC0 = -1;
    o->fC4 = 0;
    o->fC8 = 0;
    o->fCC = 0;
    o->fD0 = 0;
    o->fD4 = 0;
    o->fD8 = 0;
    o->f2CC = -1;
    o->f2C8 = -1;
    o->f2D0 = 0;
    o->f2D4 = 0;
    o->f2D8 = 0;
    o->f2E0 = 0;
    o->f2DC = 0;
    o->f2E6 = -1;
    o->f2E8 = -1;
    o->f2FA = 0;
    o->f2FC = 0;
    o->f2EA = 0;
    o->f2EE = 0;
    o->f2EC = 0;
    o->f2F0 = 0;
    o->f2F2 = 0;
    o->f2F6 = 0;
    o->f2F4 = 0;
    o->f2F8 = 0;
    func_14DFF0(o->f238);
    o->f290 = -1;
    factory_FactoryFloorRelease_503c10(o);
    func_14DFF0(o->f304);
    o->f35C = -1;
}

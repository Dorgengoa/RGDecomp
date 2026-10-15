#include "types.h"

/* factory.bin overlay, 0x005003B0 -- drop the four held blocks: release each
 * one's ghost and reset it.
 * 80 bytes, 20 instructions, 1 conditional branch, 2 calls.
 *
 * * `p = o->f0E0` is `addiu $17, $4, 0xE0` -- the array base, not an index,
 * and the walk carries the 0x40 stride in the pointer (`addiu $17,$17,0x40`
 * in the branch's delay slot).  The four-block array at 0xE0 is
 * `factory_FUN_005002C0`'s.
 *
 * * `slti $3, $16, 0x4` into a GENERAL register is the non-strict compare, so
 * the loop bound is `i < 4` as written.
 */

typedef struct Blk {
    u8  pad00[0x8];
    s16 f08;
    u8  pad0A[0x36];
} Blk;                                          /* 0x40 */

typedef struct Panel {
    u8  pad000[0xE0];
    Blk f0E0[4];
} Panel;

extern void factory_FactoryMarkerRemove_4ea140(s32 id, s32 a);
extern void factory_FactorySlotClear_4ff5d0(Blk *b);

void factory_FactorySlotClearAll_5003b0(Panel *o)
{
    Blk *p;
    s32  i;

    p = o->f0E0;
    for (i = 0; i < 4; i++, p++) {
        factory_FactoryMarkerRemove_4ea140(p->f08, 1);
        factory_FactorySlotClear_4ff5d0(p);
    }
}

/* rgp:protos */
#define RGP_SELF_factory_FactorySlotPickUp_5000f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x005000F0 -- pick the block under a grid coordinate,
 * flag the panel as dragging, reset its ghost and copy it into the staging
 * block.
 * 108 bytes, 27 instructions, 1 conditional branch, 4 calls.
 *
 * * `factory_FactorySlotFindAt_502ad0` takes THREE parameters and this call marshals NONE
 * -- `x`/`y` pass straight through in `$5`/`$6`, the same shape
 * `factory_FactoryPartCentreZ_501d70` reads on `factory_FactoryPartGroupFindById_504080`.
 *
 * * `o->f230 = 0` sits in the jal's DELAY SLOT because `$4` is still the
 * panel; it is the first source statement, not a post-call store.
 *
 * * The guard is the INVERTED early return: retail branches INTO the body
 * (`bnel $16, $0`) and lets the failure fall through to `b <epilogue>` with
 * `daddu $2,$0,$0` in the slot -- 0x004ED6D0's shape.
 *
 * * The `1` is materialised ONCE (`addiu $5,$0,1` in the bnel's delay slot)
 * and serves both `o->f230 = 1` and the second argument of
 * `factory_FactoryMarkerRemove_4ea140`, so the store comes FIRST in source order.
 *
 * * The 0x40 copy is `func_1319A8`, the same memcpy `factory_FUN_004FFFE0`
 * uses on the same `&o->f1F0` in the other direction.
 */

typedef struct Blk {
    u8  pad00[0x8];
    s16 f08;
    u8  pad0A[0x36];
} Blk;                                          /* 0x40 */

typedef struct Panel {
    u8  pad000[0x1F0];
    Blk f1F0;
    s8  f230;
} Panel;

/*rgp*/
/*rgp*/
/*rgp*/
extern void memcpy(void *dst, const void *src, s32 n);

s32 factory_FactorySlotPickUp_5000f0(Panel *o, s32 x, s32 y)
{
    Blk *b;

    o->f230 = 0;
    b = ((Blk *)factory_FactorySlotFindAt_502ad0(o, x, y));
    if (b == 0) {
        return 0;
    }
    o->f230 = 1;
    factory_FactoryMarkerRemove_4ea140(b->f08, 1);
    memcpy(&o->f1F0, b, 0x40);
    factory_FactorySlotClear_4ff5d0(b);
    return 1;
}

#include "types.h"

/* factory.bin overlay, 0x004FEA80 -- 76 bytes / 19 words, 3 branches.
 * Bounds-checked element lookup into the list at 0x10 (0x40 stride, count
 * 0x0A); NULL list or out-of-range index gives NULL.
 *
 * TWIN of the MATCHED factory_FUN_004FF180 (identical field offsets 0x10/0x0A,
 * 0x34 stride there): ALL THREE tests are ONE `if` joined by `||`, the NULL
 * guard included.  A separate `if (p == 0) return 0;` makes the sign test a
 * folded `bltzl <epilogue>` + `daddu $2,$0,$0`; retail wants the non-likely
 * `bltz` into the SHARED `return 0` block, which only the three-arm `||` gives.
 */

typedef struct Slot {
    u8  pad00[0x40];
} Slot;

typedef struct Ctx {
    u8    pad00[0xA];
    s16   f0A;
    u8    pad0C[0x4];
    Slot *f10;
} Ctx;

Slot *factory_FactoryPartGroupGetObj_4fea80(Ctx *c, s32 i)
{
    Slot *p;

    p = c->f10;
    if (p == 0 || i < 0 || c->f0A <= i) {
        return 0;
    }
    return &p[i];
}

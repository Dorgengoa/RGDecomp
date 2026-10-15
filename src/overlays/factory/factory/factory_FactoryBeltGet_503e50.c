#include "types.h"

/* factory.bin overlay, 0x00503E50 -- 68 bytes / 17 words, 3 branches, 0 calls.
 * Bounds-checked element lookup into the part list at `0x2AC` (0xC stride,
 * count `0x2B0`); NULL list or out-of-range index gives NULL.
 *
 * SEED of sub-family A of lane fy04 with `factory_FUN_004FF180` (same shape,
 * list at `0x10` / count `0xA` / 0x34 stride).
 *
 * ** ALL THREE tests are ONE `if` joined by `||` -- the NULL guard included.
 *   Written as a separate `if (p == 0) return 0;` the unit is TWO WORDS LONG
 *   (`bnez`/`nop`/`b`/`move` where retail has `beql` + the zero in its likely
 *   slot), because only inside the `||` chain will mwcc fold the first arm's
 *   `daddu $2,$0,$0` into the delay slot and let arms 2 and 3 share the one
 *   `return 0` block at 0x00503E74.  This is the same join that settled the
 *   `00503F00` quad next door, extended to a POINTER first arm.
 * ** `slt` into `$at` is the member-on-the-LEFT spelling: `o->nparts <= i`
 *   and `!(o->nparts > i)` are the same object and match, while `i >= n`,
 *   `!(i < n)`, `i >= (s32)n` are all one object two words wrong (the `slt`
 *   lands in `$v0`).  So on THIS compare it is operand ORDER that picks the
 *   `$at` class, not strictness -- `i >= n` and `n <= i` are NOT the same
 *   object, which qualifies the [[at-compare-class]] reading.
 * * `(u32)i >= (u32)o->nparts` folds the two range tests into one and comes
 *   out two words SHORT -- the `bltz` is a real separate arm.
 * * The `&&` form (`if (p && i >= 0 && i < n) return &p[i]; return 0;`) is 9
 *   bad words: mwcc puts the body first and the shape does not recover.
 * * `sll,1 / addu / sll,2 / addu` is the 12-byte stride strength reduction,
 *   i.e. `&p[i]`; `p + i` is the same object.
 */

typedef struct Part {
    u8  pad00[0xC];
} Part;

typedef struct Obj {
    u8    pad000[0x2AC];
    Part *parts;
    s16   nparts;
} Obj;

Part *factory_FactoryBeltGet_503e50(Obj *o, s32 i)
{
    Part *p;

    p = o->parts;
    if (p == 0 || i < 0 || o->nparts <= i) {
        return 0;
    }
    return &p[i];
}

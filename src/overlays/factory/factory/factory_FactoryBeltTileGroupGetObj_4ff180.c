#include "types.h"

/* factory.bin overlay, 0x004FF180 -- 76 bytes / 19 words, 3 branches, 0 calls.
 * Bounds-checked element lookup into the list at `0x10` (0x34 stride, count
 * `0xA`); NULL list or out-of-range index gives NULL.
 *
 * TWIN of `factory_FUN_00503E50` at ratio 1.000 apart from the three field
 * offsets and the stride, so the two residues measured there apply verbatim:
 * the NULL guard must be the FIRST ARM of one `||` chain (a separate `if` is
 * two words long), and the range compare must be written MEMBER-FIRST,
 * `c->f0A <= i`, to put the `slt` in `$at` (`i >= c->f0A` is two words wrong).
 *
 * * `sll,1 / addu / sll,2 / addu / sll,2 / addu` is *52, the strength
 *   reduction for a 0x34-byte element -- two more words than the twin's *12
 *   and the entire size difference between the pair.
 */

typedef struct Slot {
    u8  pad00[0x34];
} Slot;

typedef struct Ctx {
    u8     pad00[0xA];
    s16    f0A;
    u8     pad0C[0x4];
    Slot  *f10;
} Ctx;

Slot *factory_FactoryBeltTileGroupGetObj_4ff180(Ctx *c, s32 i)
{
    Slot *p;

    p = c->f10;
    if (p == 0 || i < 0 || c->f0A <= i) {
        return 0;
    }
    return &p[i];
}

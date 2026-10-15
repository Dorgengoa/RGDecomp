#include "types.h"

/* factory.bin overlay, 0x00502AD0 -- 72 bytes / 18 words, 3 branches, 0 calls.
 * Search the four inline 0x40-byte cells starting at `0xE0` for the one whose
 * `0x0A` and `0x0C` halves both match; NULL if none does.
 *
 * Sub-family D of lane fy04 -- the only member whose table is an INLINE ARRAY
 * (`addiu $2, $4, 0xE0`, no load) and the only one with a two-term `&&`.
 *
 * * The `&&` join is visible in the branch FORMS: the first arm is `bnel` PAST
 * the second test (likely, with the shared `i++` in the slot) and the second is
 * a plain `bne`.  Two nested `if`s give the same words here, but the join is
 * the [[factory `||`/`&&` join]] spelling and it keeps the single `i++` at
 * `0x00502AF8` from being duplicated a second time.
 * * `bnel $3, $5` / `bne $3, $6` both put the FIELD in `rs`, so both compares
 * are written field-first -- the opposite of the `00504080` cousin, where the
 * key is on the left and lands in `rs`.  Same rule, different source.
 * * `slti $3, $4, 0x4` into a GENERAL register is the non-strict class: the
 * loop bound is a literal `4`, not a member read.
 */

typedef struct Cell {
    u8   pad00[0xA];
    s16  f0A;
    s16  f0C;
    u8   pad0E[0x32];
} Cell;

typedef struct Ctx {
    u8    pad00[0xE0];
    Cell  cells[4];
} Ctx;

Cell *factory_FactorySlotFindAt_502ad0(Ctx *c, s32 a, s32 b)
{
    Cell *p;
    s32   i;

    p = c->cells;
    for (i = 0; i < 4; i++, p++) {
        if (p->f0A == a && p->f0C == b) {
            return p;
        }
    }
    return 0;
}

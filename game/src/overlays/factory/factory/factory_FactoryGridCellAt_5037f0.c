/* rgp:protos */
#define RGP_SELF_factory_FactoryGridCellAt_5037f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x005037F0 -- bounds-checked lookup of one cell in
 * the expanded blueprint grid.  144 bytes / 33 words, byte-identical.
 *
 * ** CLOSED by the guard JOIN, not by block order: the two index tests of each
 * axis are ONE `if` with a short-circuit `||`.  As five separate `if`s the sign
 * test compiles to `bgezl` branch-AROUND with the next `lh` in its slot and the
 * `return 0` gets its own `b <epilogue>` / `daddu $2,$0,$0` -- 16 bad at the
 * RIGHT LENGTH (words 0x00503804.. and 0x00503828..).  Joined with `||`, mwcc folds
 * the first arm into `bltzl <epilogue>` + `daddu $2,$0,$0` in the LIKELY slot
 * and lets the second arm keep the shared `daddu / b / nop` block, which is
 * retail exactly.  Same join as the MATCHED factory_FUN_004FE3A0 / 004FE410 /
 * 004FF180 / 00503E50 family; the parked note that called this a pure
 * BLOCK-LAYOUT tie-break, and its "compound && form" and "x < 0 || w <= x"
 * cells, are OVERTURNED -- what those cells missed is that the BOUND must be
 * read INSIDE the `||`, not into a named `s16 w` beforehand.
 *
 * ** `o->f2A4` must be read at BOTH uses (the guard and the row multiply);
 * mwcc CSEs the two into the one `lh` retail keeps live in `$3`.  Capturing it
 * as `(w = o->f2A4) <= x` inside the condition is TWO WORDS LONG.
 * * The bound test is `o->f2A4 <= x`, member-on-the-LEFT: that token is what
 * puts the `slt` in `$at` -- [[at-compare-class]].
 * * The row and column offsets are strength-reduced SEPARATELY (two `x*2 + x`
 * chains), so the source adds two subscripts: `&base[y * w] + x`.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    s16 f04;
} Cell;                                         /* 6 */

typedef struct Grid {
    u8    pad000[0x2A0];
    Cell *f2A0;
    s16   f2A4;
    s16   f2A6;
} Grid;

Cell *factory_FactoryGridCellAt_5037f0(Grid *o, s32 x, s32 y)
{
    Cell *base;

    base = o->f2A0;
    if (base == 0) {
        return 0;
    }
    if (x < 0 || o->f2A4 <= x) {
        return 0;
    }
    if (y < 0 || o->f2A6 <= y) {
        return 0;
    }
    return &base[y * o->f2A4] + x;
}

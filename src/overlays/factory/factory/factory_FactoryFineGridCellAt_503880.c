#include "types.h"

/* factory.bin overlay, 0x00503880 -- bounds-checked lookup of one cell in
 * the recipe grid.  144 bytes / 33 words, byte-identical.
 *
 * ** CLOSED by the guard JOIN, not by block order: the two index tests of each
 * axis are ONE `if` with a short-circuit `||`.  As five separate `if`s the sign
 * test compiles to `bgezl` branch-AROUND with the next `lh` in its slot and the
 * `return 0` gets its own `b <epilogue>` / `daddu $2,$0,$0` -- 16 bad at the
 * RIGHT LENGTH (words 0x00503894.. and 0x005038B8..).  Joined with `||`, mwcc folds
 * the first arm into `bltzl <epilogue>` + `daddu $2,$0,$0` in the LIKELY slot
 * and lets the second arm keep the shared `daddu / b / nop` block, which is
 * retail exactly.  Same join as the MATCHED factory_FUN_004FE3A0 / 004FE410 /
 * 004FF180 / 00503E50 family; the parked note that called this a pure
 * BLOCK-LAYOUT tie-break, and its "compound && form" and "x < 0 || w <= x"
 * cells, are OVERTURNED -- what those cells missed is that the BOUND must be
 * read INSIDE the `||`, not into a named `s16 w` beforehand.
 *
 * ** `o->f298` must be read at BOTH uses (the guard and the row multiply);
 * mwcc CSEs the two into the one `lh` retail keeps live in `$3`.  Capturing it
 * as `(w = o->f298) <= x` inside the condition is TWO WORDS LONG.
 * * The bound test is `o->f298 <= x`, member-on-the-LEFT: that token is what
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
    u8    pad000[0x294];
    Cell *f294;
    s16   f298;
    s16   f29A;
} Grid;

Cell *factory_FactoryFineGridCellAt_503880(Grid *o, s32 x, s32 y)
{
    Cell *base;

    base = o->f294;
    if (base == 0) {
        return 0;
    }
    if (x < 0 || o->f298 <= x) {
        return 0;
    }
    if (y < 0 || o->f29A <= y) {
        return 0;
    }
    return &base[y * o->f298] + x;
}

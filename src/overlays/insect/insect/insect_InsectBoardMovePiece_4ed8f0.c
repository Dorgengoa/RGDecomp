#include "types.h"
/* insect 0x004ED8F0 -- 220 bytes, 55 instructions, 2 calls, 2 conditional
 * branches, br/ins 0.036.  From x_band.py's branch-light band.
 *
 * `sll 2 / addu / sll 2` is a multiply by 20 and the second index scales by 4,
 * so the base is a `s32 [7][5]` grid -- the same one overlay-c-pipeline reads
 * off insect_InsectBoardInBounds_4efac0's bounds check (5 and 7).  Written as the two-index
 * array both address chains come out in retail's operand order for free.
 *
 * `dsll32 16 / dsra32 16` on all four coordinates is the CALLEE's `s16`
 * parameters doing the narrowing, not a cast here -- the recorded rule from
 * insect_FUN_00509B00: keep the caller's value wide and declare the parameter
 * narrow.
 *
 * ** The two guards are ONE `if` with `||`. **  They return the same constant,
 * and joined they give retail's shape exactly: a `beql` to the epilogue with
 * `daddu $2, $0, $0` in the delay slot for the first test, then a `beql` INTO
 * the store block for the second.  Written as two separate early returns the
 * unit is one word LONG; as a wrapping `if (a != 0)`, or with either guard
 * spelled as a `goto` to a shared `zero:` label, it is one word SHORT.  Seven
 * structures measured.  Same lever as factory-or-join-folds-the-return, first
 * instance in this overlay.
 */

typedef struct Grid {
    s32 c[7][5];
} Grid;

extern s32 insect_InsectBoardGetPiece_4ee9a0(Grid *g, s16 x, s16 y);

s32 insect_InsectBoardMovePiece_4ed8f0(Grid *g, s32 x1, s32 y1, s32 x2, s32 y2)
{
    s32 a;
    s32 b;

    a = insect_InsectBoardGetPiece_4ee9a0(g, x1, y1);
    b = insect_InsectBoardGetPiece_4ee9a0(g, x2, y2);
    if ((a == 0) || (b != 0)) {
        return 0;
    }
    g->c[y1][x1] = 0;
    g->c[y2][x2] = a;
    return a;
}

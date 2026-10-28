/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuCursorLeft_512940 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00512940 -- the cursor's LEFT-hand neighbour search on the
 * occupancy grid at +0x24: walk the column cursor left until a cell in the
 * current row is occupied, falling back to the paired row `(row + 1) % 2`,
 * and write the chosen (col,row) back into f3C/f3E.  Returns 1 when either
 * coordinate actually moved.  Column twin of normal_FUN_005126A0.
 *
 * SESSION 65: 68 -> MATCH.  Four facts, in the order they paid:
 *  1. `u8 done` + the BARE `!done` test -- supplies retail's `daddiu $8,$0,1`
 *     (an s32 flag emits `addiu`) and costs nothing on the test.
 *  2. the paired-row index is an `s32` expression, NOT an s16 local: retail
 *     feeds `$11` straight into `sll $10,$11,3` with no narrowing, and only
 *     narrows it at `nrow = o` (the s16 assignment).
 *  3. `col0 = (s16)col0;` before the compare -- the redundant self-cast that
 *     buys retail's second dsll32/dsra32 pair at 0x00512A30.
 *  4. ★ the `(row0 + 1) % 2` index is SPELLED INLINE at both uses, not named
 *     in a local.  A named `o` creates its vreg before the `p->f24[row0][c]`
 *     row-offset web, so `sll <rowoff>` -- not `sll <o*8>` -- lands in the
 *     `beql` delay slot at 0x005129A4 and the whole $9..$13 map shifts.
 *     Inline, the modulo web is created at its first USE and the order is
 *     retail's.  That one edit is 14 bad -> MATCH.
 *  Declaration order `col0; row0; c; nrow;` is also load-bearing: `c` must be
 *  declared before `nrow` (37 bad -> 14; 120 permutations measured).
 */

typedef struct M {
    u8  pad000[0x24];
    s16 f24[3][4];
    s16 f3C;
    s16 f3E;
} M;

s32 normal_SpaceMenuCursorLeft_512940(M *p)
{
    s16 col0; s16 row0; s16 c; s16 nrow;
    u8 done; s32 moved;

    col0 = p->f3C;
    done = 0;
    row0 = p->f3E;
    c = col0 - 1;
    nrow = row0;
    if (c < 0) {
        done = 1;
        c = 0;
        if (p->f24[row0][0] < 0) c = col0;
    }
    if (!done) {
        do {
            if (p->f24[row0][c] >= 0) goto out;
            if (p->f24[(row0 + 1) % 2][c] >= 0) { nrow = (row0 + 1) % 2; goto out; }
            c -= 1;
        } while (c >= 0);
        c = 0;
        if (p->f24[row0][0] < 0) c = col0;
        else if (p->f24[(row0 + 1) % 2][0] < 0) c = col0;
    out: ;
    }
    col0 = (s16)col0;
    moved = 0;
    if (col0 != c || row0 != nrow) moved = 1;
    p->f3C = c;
    p->f3E = nrow;
    return moved;
}

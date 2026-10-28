/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuCursorMove_5123f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* normal 0x005123F0 -- checks a 3x4 occupancy grid for any occupied row 0/1
 * cell, then dispatches to one of four sub-handlers by mode.
 *
 * MATCHED (s24), 284 B.  Two levers, in this order:
 *  1. Every dispatch arm assigns `r` and falls through to ONE shared exit
 *     (`else if` + `return r`), NOT `return f(p)` per arm.  Retail's arms are
 *     `jal` + `b .L00512500` to a single epilogue, so `r` is allocated to $2
 *     and both the assignment and the return are free.  Per-arm returns made
 *     the trailing `return 0` a separate `move v0,zero` that mwcc duplicated
 *     into an annulled delay slot and then needed a `b` to skip -- the
 *     orphaned-dead-code shape of [[mwcc-branch-likely-duplication]].
 *     LEN/ERR -> right length, 11 bad.
 *  2. `s32 r = 0;` must be the FIRST declaration, WITH its initialiser: that
 *     is what emits retail's `daddu $2,$0,$0` at 0x005123F4, ahead of the
 *     flags clear loop.  11 bad -> MATCH.
 *     !! `s32 r;` declared first with `r = 0;` as the first STATEMENT is the
 *     BASE OBJECT, as are r-in-the-middle and r-declared-last.  It is the
 *     DECLARATION-WITH-INITIALISER IN POSITION 1 that hoists the store, not
 *     the assignment's statement position -- 5 arms, 2 objects. */

typedef struct Obj {
    u8  pad00[0x24];
    s16 field[3][4];
    s16 f3C;
    s16 f3E;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_SpaceMenuCursorMove_5123f0(Obj *p, s32 mode)
{
    s32 r = 0;
    s16 flags[3] = { 0, 0, 0 };
    s32 row, col;

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 4; col++) {
            if (p->field[row][col] == -1)
                continue;
            flags[row] = 1;
        }
    }

    if (flags[0] == 0 && flags[1] == 0)
        return 0;

    if ((s16)mode == 0)
        r = normal_SpaceMenuCursorLeft_512940(p);
    else if ((s16)mode == 1)
        r = normal_SpaceMenuCursorRight_512800(p);
    else if ((s16)mode == 2)
        r = normal_SpaceMenuCursorUp_5126a0(p);
    else if ((s16)mode == 3)
        r = normal_SpaceMenuCursorDown_512510(p);
    return r;
}

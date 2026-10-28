/* rgp:protos */
#define RGP_SELF_insect_InsectBoardTimerSet_4ee320 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE320 -- 35 instructions.  A nibble writer into a
 * [.][7][5] u8 table at +0x1A4 (i stride 35, k stride 5).  Both arms
 * recompute the element address from scratch and mwcc TAIL-MERGES the final
 * read-modify-write.  MEASURED: the `|=` must be written ONCE, AFTER the
 * if/else, and the value must go through a `u8` local assigned BEFORE the if
 * (`t = v;`) -- that is what puts the same register on both arms' `or` and
 * lets the tails cross-jump.  Duplicating `arr |= t;` inside both arms costs 2
 * words; naming the element address in a `u8 *p` costs 1-4 words and 28 bad
 * words; widening `v` to s32 costs 3. */

typedef struct Obj {
    u8 pad00[0x1A4];
    u8 m1A4[1][7][5];               /* +0x1A4 */
} Obj;

void insect_InsectBoardTimerSet_4ee320(Obj *o, s32 i, s32 j, s32 k, u8 v, s32 hi)
{
    u8 t;

    t = v;
    if (hi != 0) {
        t = (u8)(t << 4);
        o->m1A4[i][k][j] &= 0xF;
    } else {
        o->m1A4[i][k][j] &= 0xF0;
    }
    o->m1A4[i][k][j] |= t;
}

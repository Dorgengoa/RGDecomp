/* rgp:protos */
#define RGP_SELF_insect_InsectBoardTakeAt_4ef770 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/* insect 0x004EF770 -- 128 bytes, 32 instructions.  Clear one cell of the
 * 5-wide grid if the coordinate is legal and the cell is occupied; return the
 * old contents.  The two `dsll32/dsra32 ..,16` pairs are in the PROLOGUE and
 * their results feed both the call and the indexing, so the coordinates are
 * word parameters narrowed ONCE into named locals -- not `s16` parameters,
 * which mwcc narrows lazily at the arithmetic and sinks past the call. */

/*rgp*/

s32 insect_InsectBoardTakeAt_4ef770(s32 (*g)[5], s32 px, s32 py)
{
    s32 y;
    s32 x;
    s32 v;

    y = (s16)py;
    x = (s16)px;
    if (insect_InsectBoardInBounds_4efac0(g, (long long)(x), (long long)(y)) == 0) {
        return 0;
    }
    v = g[y][x];
    if (v != 0) {
        g[y][x] = 0;
    }
    return v;
}

/* rgp:protos */
#define RGP_SELF_insect_InsectBoardGetPiece_4ee9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE9A0 -- 112 bytes.  Both index parameters arrive sign-extended
 * with `dsll32/dsra32 ..,16`, so they are s16.  The address is `y*5` then
 * `<<2` then `+ x*4`, i.e. a s32[..][5] grid at offset 0. */
typedef struct Grid {
    s32 c[7][5];                    /* +0x00 */
} Grid;

/*rgp*/

s32 insect_InsectBoardGetPiece_4ee9a0(Grid *g, s16 x, s16 y)
{
    if (insect_InsectBoardInBounds_4efac0(g, (long long)(x), (long long)(y)) != 0) {
        return g->c[y][x];
    }
    return 0;
}

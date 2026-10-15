#include "types.h"
/* insect 0x004EE9A0 -- 112 bytes.  Both index parameters arrive sign-extended
 * with `dsll32/dsra32 ..,16`, so they are s16.  The address is `y*5` then
 * `<<2` then `+ x*4`, i.e. a s32[..][5] grid at offset 0. */
typedef struct Grid {
    s32 c[7][5];                    /* +0x00 */
} Grid;

extern s32 insect_InsectBoardInBounds_4efac0(Grid *g, s32 x, s32 y);

s32 insect_InsectBoardGetPiece_4ee9a0(Grid *g, s16 x, s16 y)
{
    if (insect_InsectBoardInBounds_4efac0(g, x, y) != 0) {
        return g->c[y][x];
    }
    return 0;
}

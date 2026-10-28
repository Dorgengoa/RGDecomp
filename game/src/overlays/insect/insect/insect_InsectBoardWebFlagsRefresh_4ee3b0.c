/* rgp:protos */
#define RGP_SELF_insect_InsectBoardWebFlagsRefresh_4ee3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE3B0 -- 204 bytes.  A 7x5 sweep over the grid handle
 * (`(u8 *)o + 0x4960` in its callers); the high nibble of the 0x1A4 plane is
 * the occupancy and the 0x13B plane takes the bit. */

typedef struct Grid {
    s32 f0[7][5];                   /* +0x000 */
    u8  pad008C[0x13B - 0x8C];
    u8  f13B[7][5];                 /* +0x13B */
    u8  pad015E[0x1A4 - 0x15E];
    u8  f1A4[7][5];                 /* +0x1A4 */
} Grid;

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBoardWebFlagsRefresh_4ee3b0(Grid *g)
{
    s32 y;
    s32 x;

    insect_InsectBoardWebFlagsClear_4ee480(g);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (((g->f1A4[y][x] & 0xF0) >> 4) != 0) {
                if (insect_InsectBoardInBounds_4efac0(g, (long long)(x), (long long)(y)) != 0) {
                    if (insect_InsectBoardIsHole_4ee7e0(g, x, y) == 0) {
                        g->f13B[y][x] |= 8;
                    }
                }
            }
        }
    }
}

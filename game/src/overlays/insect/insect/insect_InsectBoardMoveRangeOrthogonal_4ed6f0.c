/* rgp:protos */
#define RGP_SELF_insect_InsectBoardMoveRangeOrthogonal_4ed6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004ED6F0 -- 500 bytes, 125 instructions.
 *
 * Four identical rays out of (x, y) across a 5-wide byte grid: +x, -x, -y, +y.
 * 0x13B - 0x118 = 0x23 = 35 = 5 * 7, so the two grids are u8[35] side by side
 * and the index is `row * 5 + col`.  `a + y*5` (loops 1/2) and `a + x`
 * (loops 3/4) are mwcc's own CSE of the fixed half of that index. */

typedef struct Grid {
    u8 pad00[0x118];
    u8 f118[35];                    /* +0x118 */
    u8 f13B[35];                    /* +0x13B */
} Grid;

/*rgp*/

void insect_InsectBoardMoveRangeOrthogonal_4ed6f0(Grid *g, s32 x, s32 y, s32 n)
{
    s32 i;
    s32 k;
    u8 c;

    for (i = 1; i <= n; i++) {
        k = x + i;
        if (insect_InsectBoardInBounds_4efac0(g, (long long)(k), (long long)(y)) != 0) {
            c = g->f118[(y * 5) + k];
            if ((c & 4) != 0) {
                break;
            }
            g->f118[(y * 5) + k] = c | 2;
            if ((g->f13B[(y * 5) + k] & 8) != 0) {
                break;
            }
        }
    }
    for (i = 1; i <= n; i++) {
        k = x - i;
        if (insect_InsectBoardInBounds_4efac0(g, (long long)(k), (long long)(y)) != 0) {
            c = g->f118[(y * 5) + k];
            if ((c & 4) != 0) {
                break;
            }
            g->f118[(y * 5) + k] = c | 2;
            if ((g->f13B[(y * 5) + k] & 8) != 0) {
                break;
            }
        }
    }
    for (i = 1; i <= n; i++) {
        k = y - i;
        if (insect_InsectBoardInBounds_4efac0(g, (long long)(x), (long long)(k)) != 0) {
            c = g->f118[(k * 5) + x];
            if ((c & 4) != 0) {
                break;
            }
            g->f118[(k * 5) + x] = c | 2;
            if ((g->f13B[(k * 5) + x] & 8) != 0) {
                break;
            }
        }
    }
    for (i = 1; i <= n; i++) {
        k = y + i;
        if (insect_InsectBoardInBounds_4efac0(g, (long long)(x), (long long)(k)) != 0) {
            c = g->f118[(k * 5) + x];
            if ((c & 4) != 0) {
                break;
            }
            g->f118[(k * 5) + x] = c | 2;
            if ((g->f13B[(k * 5) + x] & 8) != 0) {
                break;
            }
        }
    }
}

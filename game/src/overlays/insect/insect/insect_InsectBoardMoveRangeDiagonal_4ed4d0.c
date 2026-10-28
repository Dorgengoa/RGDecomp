/* rgp:protos */
#define RGP_SELF_insect_InsectBoardMoveRangeDiagonal_4ed4d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004ED4D0 -- 536 bytes, 134 instructions.
 *
 * Four diagonal scans out from (cx, cy), each `for (i = 1; i <= n; i++)` and
 * each ended by either of two `break`s.  The latch is `slt $1, $18, $17` into
 * $at with a `beql` consumer, which at-compare-class reads as the "or-equal"
 * latch spelling `i <= n` (a strict `i < n` would take a GPR).
 *
 * The grid stride is 5 (`sll 2` + `addu`) and 0x13B - 0x118 = 0x23 = 7 * 5,
 * so the two flag planes are 7x5 byte arrays.
 */

typedef struct Obj {
    u8 pad000[0x118];
    u8 f118[7][5];                  /* +0x118 */
    u8 f13B[7][5];                  /* +0x13B */
} Obj;

/*rgp*/

void insect_InsectBoardMoveRangeDiagonal_4ed4d0(Obj *o, s32 cy, s32 cx, s32 n)
{
    s32 i;
    s32 x;
    s32 y;
    u8  c;

    for (i = 1; i <= n; i++) {
        y = cy + i;
        x = cx - i;
        if (insect_InsectBoardInBounds_4efac0(o, (long long)(y), (long long)(x)) == 0) {
            continue;
        }
        c = o->f118[x][y];
        if (c & 4) {
            break;
        }
        o->f118[x][y] = c | 2;
        if (o->f13B[x][y] & 8) {
            break;
        }
    }
    for (i = 1; i <= n; i++) {
        y = cy - i;
        x = cx - i;
        if (insect_InsectBoardInBounds_4efac0(o, (long long)(y), (long long)(x)) == 0) {
            continue;
        }
        c = o->f118[x][y];
        if (c & 4) {
            break;
        }
        o->f118[x][y] = c | 2;
        if (o->f13B[x][y] & 8) {
            break;
        }
    }
    for (i = 1; i <= n; i++) {
        y = cy + i;
        x = cx + i;
        if (insect_InsectBoardInBounds_4efac0(o, (long long)(y), (long long)(x)) == 0) {
            continue;
        }
        c = o->f118[x][y];
        if (c & 4) {
            break;
        }
        o->f118[x][y] = c | 2;
        if (o->f13B[x][y] & 8) {
            break;
        }
    }
    for (i = 1; i <= n; i++) {
        y = cy - i;
        x = cx + i;
        if (insect_InsectBoardInBounds_4efac0(o, (long long)(y), (long long)(x)) == 0) {
            continue;
        }
        c = o->f118[x][y];
        if (c & 4) {
            break;
        }
        o->f118[x][y] = c | 2;
        if (o->f13B[x][y] & 8) {
            break;
        }
    }
}

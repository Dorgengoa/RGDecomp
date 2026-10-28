/* rgp:protos */
#define RGP_SELF_insect_InsectBoardClearMoveMarks_4efa70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFA70 -- 76 bytes.  A 7x5 double loop over two BYTE grids that
 * are adjacent in the object: 0x118 + 7*5 = 0x13B.  The address is formed as
 * `j*4 + j` then `+ i`, so the row stride is 5 and both grids are u8[7][5]. */
typedef struct Board {
    u8 pad000[0x118];
    u8 a[7][5];                     /* +0x118 */
    u8 b[7][5];                     /* +0x13B */
} Board;

void insect_InsectBoardClearMoveMarks_4efa70(Board *t)
{
    s32 j;
    s32 i;

    for (j = 0; j < 7; j++) {
        for (i = 0; i < 5; i++) {
            t->a[j][i] = 0;
            t->b[j][i] &= 0xFC;
        }
    }
}

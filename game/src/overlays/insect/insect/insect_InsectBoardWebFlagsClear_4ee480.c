/* rgp:protos */
#define RGP_SELF_insect_InsectBoardWebFlagsClear_4ee480 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE480 -- 72 bytes.  Clears bit 3 across the u8 7x5 grid at
 * +0x13B (the same grid insect_InsectBoardClearMoveMarks_4efa70 and insect_InsectBoardHoleSet_4ee700 use);
 * row stride 5, outer counter declared first. */

typedef struct Board {
    u8  pad000[0x13B];
    u8  b[7][5];                    /* +0x013B */
} Board;

void insect_InsectBoardWebFlagsClear_4ee480(Board *t)
{
    s32 j;
    s32 i;

    for (j = 0; j < 7; j++) {
        for (i = 0; i < 5; i++) {
            t->b[j][i] = t->b[j][i] & 0xF7;
        }
    }
}

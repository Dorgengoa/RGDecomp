/* rgp:protos */
#define RGP_SELF_insect_InsectBoardFindPiece_4ee190 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE190 -- 112 bytes.  A 7x5 word grid searched for a value.  The compare's
 * operand order comes from NAMING the loaded cell: `g[i][j] == v` and six
 * other spellings are one INERT object with the loaded value in rt. */

s32 insect_InsectBoardFindPiece_4ee190(s32 (*g)[5], s32 v, s32 *px, s32 *py)
{
    s32 i;
    s32 j;
    s32 c;

    *px = -1;
    *py = -1;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 5; j++) {
            c = g[i][j];
            if (c == v) {
                *px = j;
                *py = i;
                return 1;
            }
        }
    }
    return 0;
}

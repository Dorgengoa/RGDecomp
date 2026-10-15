#include "types.h"
/* insect 0x004EF670 -- 248 bytes, 62 instructions.
 * Scans the 3x3 neighbourhood of the cell returned through the two
 * out-parameters. */

extern s32 insect_InsectBoardFindPiece_4ee190(void *a, void *b, s32 *px, s32 *py);
extern void *insect_InsectBoardGetPiece_4ee9a0(void *a, s16 x, s16 y);
extern s32 insect_InsectBoardInBounds_4efac0(void *a, s32 x, s32 y);
extern s32 insect_InsectPieceIsEnemyOf_5149b0(void *b, void *e);

s32 insect_InsectBoardHasAdjacentEnemy_4ef670(void *a, void *b)
{
    s32 cx;
    s32 cy;
    s32 j;
    s32 i;
    s32 x;
    s32 y;
    void *e;

    if (b == 0) {
        return 0;
    }
    if (insect_InsectBoardFindPiece_4ee190(a, b, &cx, &cy) == 0) {
        return 0;
    }
    for (j = -1; j <= 1; j++) {
        for (i = -1; i <= 1; i++) {
            x = cx + i;
            y = cy + j;
            if (insect_InsectBoardInBounds_4efac0(a, x, y) != 0) {
                e = insect_InsectBoardGetPiece_4ee9a0(a, (s16)x, (s16)y);
                if (insect_InsectPieceIsEnemyOf_5149b0(b, e) != 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

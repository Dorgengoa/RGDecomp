#include "types.h"
/* insect 0x004EDA20 -- 76 bytes, 19 instructions.  Row stride is i*5*4 = 20
 * and the store carries a constant +0x8C = 7*5*4, i.e. the destination grid
 * sits immediately after the source grid. */

typedef struct Obj {
    s32 src[7][5];                  /* +0x000 */
    s32 dst[7][5];                  /* +0x08C */
} Obj;

void insect_InsectBoardBackup_4eda20(Obj *o)
{
    s32 i;
    s32 j;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 5; j++) {
            o->dst[i][j] = o->src[i][j];
        }
    }
}

/* rgp:protos */
#define RGP_SELF_insect_InsectBoardRestore_4ed9d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004ED9D0 -- 19 instructions.  Two 7x5 s32 tables 0x8C apart
 * (7 * 5 * 4 = 0x8C); the row base is hoisted out of the inner loop, the
 * column index is not. */

typedef struct Obj {
    s32 m00[7][5];                  /* +0x00 */
    s32 m8C[7][5];                  /* +0x8C */
} Obj;

void insect_InsectBoardRestore_4ed9d0(Obj *o)
{
    s32 i;
    s32 j;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 5; j++) {
            o->m00[i][j] = o->m8C[i][j];
        }
    }
}

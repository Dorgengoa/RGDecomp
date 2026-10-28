/* rgp:protos */
#define RGP_SELF_insect_InsectTeamCountPlaced_5137c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005137C0 -- 120 bytes, 30 instructions. */

/*rgp*/
/*rgp*/

s32 insect_InsectTeamCountPlaced_5137c0(void *a)
{
    s32 n;
    s32 i;

    n = 0;
    for (i = 0; i < 5; i++) {
        void *p = insect_InsectTeamGetPiece_5138d0(a, i);
        if (p == 0) {
            continue;
        }
        if (insect_InsectPieceTestStatus_513280(p, 0x21) != 0) {
            n++;
        }
    }
    return n;
}

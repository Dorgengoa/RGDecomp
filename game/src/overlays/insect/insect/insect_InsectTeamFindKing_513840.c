/* rgp:protos */
#define RGP_SELF_insect_InsectTeamFindKing_513840 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513840 -- 104 bytes, 26 instructions, 1 call.  A five-slot linear
 * search; the stride is 0x1E8, built as ((i*16 - i)*4 + i)*8.  The `beql` back
 * to the loop test with the increment in its delay slot is the `!= 0` guard;
 * the hit exits with the index and the fall-out returns -1.
 */

typedef struct Slot { u8 raw[0x1E8]; } Slot;

/*rgp*/

s32 insect_InsectTeamFindKing_513840(Slot *a)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        if (insect_InsectPieceIsKing_514b00(&a[i]) != 0) {
            return i;
        }
    }
    return -1;
}

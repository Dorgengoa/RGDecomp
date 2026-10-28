/* rgp:protos */
#define RGP_SELF_CharaSetStat84_3b7bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct RowW { s16 e[2]; } RowW;



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaSetStat84_3b7bb0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    if (p3 >= 0) {
        if (p3 < 2) {
            if (p1 > 0) {
                if (p1 < 8) {
                    ((RowW *)((u8 *)p0 + 0x84))[p1].e[p3] = p2;
                }
            }
        }
    }
}

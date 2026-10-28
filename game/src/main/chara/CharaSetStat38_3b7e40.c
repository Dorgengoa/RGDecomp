/* rgp:protos */
#define RGP_SELF_CharaSetStat38_3b7e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaSetStat38_3b7e40(s32 p0, s32 p1, s32 p2)
{
    if (p2 >= 0) {
        if (p2 < 2) {
            *(s16 *)((u8 *)(p2 << 1) + p0 + 0x38) = p1;
        }
    }
}

/* rgp:protos */
#define RGP_SELF_CharaDataMgrGetMemStack_1ed3f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaDataMgrGetMemStack_1ed3f0(s32 p0, s32 p1)
{
    if ((u32)p1 >= 3) {
        return 0;
    }
    return ((p0 + (((p1 * 0xA) + p1) << 3)) + 0xE80);
}

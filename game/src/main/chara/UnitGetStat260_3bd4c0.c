/* rgp:protos */
#define RGP_SELF_UnitGetStat260_3bd4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UnitGetStat260_3bd4c0(s32 p0, s32 p1)
{
    return (s16)(*(s16 *)((u8 *)(p1 << 1) + p0 + 0x260));
}

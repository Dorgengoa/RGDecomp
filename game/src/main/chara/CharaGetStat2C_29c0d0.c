/* rgp:protos */
#define RGP_SELF_CharaGetStat2C_29c0d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u32 CharaGetStat2C_29c0d0(s32 p0, s32 p1)
{
    return (u16)(*(u16 *)((u8 *)(p1 << 1) + p0 + 0x2C));
}

/* rgp:protos */
#define RGP_SELF_MesWinGetCharCode_274dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u16 MesWinGetCharCode_274dd0(s32 p0, s32 p1)
{
    u16 t0;

    t0 = *(u16 *)((u8 *)(p1 << 3) + p0 + 0xC4);
    return t0;
}

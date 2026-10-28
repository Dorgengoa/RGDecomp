/* rgp:protos */
#define RGP_SELF_MesWinPushNumVar_275db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinPushNumVar_275db0(s32 p0, s32 p1, s32 p2, s32 p3, f32 fa0, f32 fa1, f32 fa2, f32 fa3, f32 fa4, f32 fa5, f32 fa6, f32 fa7)
{
    s16 t0;
    s32 t1;

    t0 = *(s16 *)((u8 *)(p1 << 1) + p0 + 0x1BF0);
    t1 = *(s32 *)((u8 *)(p1 << 2) + p0 + 0x1BA0);
    MesWinPushNumber_275de0(p0, t1, t0);
}

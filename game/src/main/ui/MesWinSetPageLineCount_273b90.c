/* rgp:protos */
#define RGP_SELF_MesWinSetPageLineCount_273b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinSetPageLineCount_273b90(s32 p0, s32 p1, s32 p2)
{
    s32 l0;
    s32 l1;
    s16 t0;
    s16 t1;

    *(s16 *)((u8 *)(p2 << 1) + p0 + 0x5C) = (p1 + 1);
    if (p2 > 0) {
        l0 = (p2 << 1);
        l1 = 0;
        while ((p2 + -1) >= l1) {
            t0 = *(s16 *)((u8 *)(p2 << 1) + p0 + 0x5C);
            t1 = *(s16 *)((u8 *)p0 + (l1 << 1) + 0x5C);
            *(s16 *)((u8 *)(p2 << 1) + p0 + 0x5C) = (t0 - t1);
            l0 = (t0 - t1);
            l1 = (l1 + 1);
        }
        return;
    }
}

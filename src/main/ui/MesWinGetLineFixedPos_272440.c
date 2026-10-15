#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MesWinGetLineFixedPos_272440(s32 p0, s32 p1)
{
    s32 rv1;
    s32 rv0;
    s8 t0;

    if (p1 < 0) {
        rv1 = 0;
    } else {
        if ((p1 < 0x14) == 0) {
            rv0 = 0;
        } else {
            t0 = *(s8 *)((u8 *)p1 + p0 + 0x1CD4);
            rv0 = t0;
        }
        rv1 = rv0;
    }
    return rv1;
}

#include "types.h"

extern s32 MesWinGetNameBuf_2712f0(s32);
extern void memset(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinClearName_2712c0(s32 p0)
{
    s32 r0;

    r0 = MesWinGetNameBuf_2712f0(p0);
    memset(r0, 0, 0x20);
}

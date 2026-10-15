#include "types.h"

extern void MesWinClearName_2712c0(s32);
extern s32 strlen(s32);
extern void strncpy(s32, s32, s32);
extern void strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinSetName_271300(s32 p0, s32 p1)
{
    s32 r1;

    MesWinClearName_2712c0(p0);
    r1 = strlen(p1);
    if ((u32)r1 >= 0x20) {
        strncpy((p0 + 0x1DC6), p1, 0x1F);
        return;
    }
    strcpy((p0 + 0x1DC6), p1);
}

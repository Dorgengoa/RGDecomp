#include "types.h"

extern void iSignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E248;
extern s32 D_0047E250;

void SysTickThreadSignalIsr_1c34f0(void)
{
    s32 t0;
    s32 t1;

    t0 = D_0047E250;
    if (t0 != 0) {
        t1 = D_0047E248;
        iSignalSema(t1);
        D_0047E250 = 0;
        return;
    }
}

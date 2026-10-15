#include "types.h"

extern s32 GetMapSunaKemu_201a60(void);
extern void SunaKemuDraw_33b750(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawSandStorm_1ffd20(void)
{
    s32 r0;

    r0 = GetMapSunaKemu_201a60();
    SunaKemuDraw_33b750(r0);
}

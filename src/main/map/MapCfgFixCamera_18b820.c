#include "types.h"

extern s32 MapCfgIsCameraSkipped_18cb00(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004812D0;

s32 MapCfgFixCamera_18b820(void)
{
    s32 r0;

    r0 = MapCfgIsCameraSkipped_18cb00();
    if (r0 != 0) {
        return 1;
    }
    D_004812D0 = 0;
    return 1;
}

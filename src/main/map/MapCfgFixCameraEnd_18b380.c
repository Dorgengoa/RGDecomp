#include "types.h"

extern s32 MapCfgIsCameraSkipped_18cb00(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004812CC;

s32 MapCfgFixCameraEnd_18b380(void)
{
    s32 r0;
    s32 t0;

    r0 = MapCfgIsCameraSkipped_18cb00();
    if (r0 != 0) {
        return 1;
    }
    t0 = D_004812CC;
    D_004812CC = (t0 + 1);
    return 1;
}

#include "types.h"

extern s32 AudioDecIsPreset_1d3050(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004817B8;
extern u8 D_004B32D0[];

s32 MovieAudioIsPreset_1d2490(void)
{
    u8 t0;
    s32 r0;

    t0 = D_004817B8;
    if (t0 != 0) {
        r0 = AudioDecIsPreset_1d3050(D_004B32D0);
        return r0;
    }
    return 1;
}

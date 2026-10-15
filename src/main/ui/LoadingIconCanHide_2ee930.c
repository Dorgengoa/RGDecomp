#include "types.h"

extern f32 LoadingIconGetTime_2ee9a0(void);
extern f32 LoadingIconGetMinTime_2ee990(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 LoadingIconCanHide_2ee930(void)
{
    f32 r0;
    f32 r1;
    s32 rv2;

    r0 = LoadingIconGetTime_2ee9a0();
    if (r0 < 0.0f) {
        return 1;
    }
    r1 = LoadingIconGetMinTime_2ee990();
    rv2 = 1;
    if (r0 < r1) {
        rv2 = 0;
    }
    return rv2;
}

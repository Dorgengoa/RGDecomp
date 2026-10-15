#include "types.h"

extern s32 MapMgrGetAuxAreaFwd_389e40(void);
extern s32 MapDataIsLoaded_1e79d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapMgrAuxAreaIsLoaded_389e10(void)
{
    s32 r0;
    s32 r1;

    r0 = MapMgrGetAuxAreaFwd_389e40();
    if (r0 != 0) {
        r1 = MapDataIsLoaded_1e79d0(r0);
        return (r1 & 0xFF);
    }
    return 1;
}

#include "types.h"

extern s32 MapIdIndexHasNames_1ddbc0(s32);
extern s32 MapIdIndexFindByName_1dda20(s32, s32);
extern s32 MapRecTableFindShareByName_1dd340(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaFindShareByName_1dc7c0(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = MapIdIndexHasNames_1ddbc0((p0 + 0xFC));
    rv3 = r2;
    if (r0 != 0) {
        r1 = MapIdIndexFindByName_1dda20((p0 + 0xFC), p1);
        rv3 = r1;
    } else {
        r2 = MapRecTableFindShareByName_1dd340((p0 + 0x54), p1);
        rv3 = r2;
    }
    return rv3;
}

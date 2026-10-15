#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004811AC;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 SkyCfgSkyMirrorOffCmd_17dcc0(void)
{
    D_004811AC->m00 = 1;
    return 1;
}

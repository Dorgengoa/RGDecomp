#include "types.h"

extern s32 MemStackNew_14e230(s32, s32);
extern s32 JdgGridNodeCtor_317290(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SpatialMgrNewGridNode_316910(s32 p0)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = MemStackNew_14e230(0x50, (p0 + 4));
    rv2 = r0;
    if (r0 != 0) {
        r1 = JdgGridNodeCtor_317290(r0);
        rv2 = r1;
    }
    return rv2;
}

#include "types.h"

extern void * CharaDataFindNode_1ed6d0(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
};

s32 CharaDataGetNodeModel_1ed540(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = CharaDataFindNode_1ed6d0(p0, p1, p2, 0);
    if (r0 == 0) {
        return 0;
    }
    t0 = r0->m20;
    return t0;
}

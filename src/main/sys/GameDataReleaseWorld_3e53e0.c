#include "types.h"

extern s32 WorldDataMgrRelease_3f0320(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0x5C];
    s32 m68;
};

s32 GameDataReleaseWorld_3e53e0(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;

    t0 = p0->m08;
    r0 = WorldDataMgrRelease_3f0320(t0, 1);
    p0->m68 = 0;
    return 1;
}

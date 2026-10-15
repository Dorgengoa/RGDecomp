#include "types.h"

extern s32 VariantGetInt_15f780(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004812F4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x98];
    s32 m98;
};

s32 MapSceneCfgActiveLightSet_193500(s32 p0)
{
    s32 r;

    r = VariantGetInt_15f780(p0);
    D_004812F4->m98 = r;
    return 1;
}

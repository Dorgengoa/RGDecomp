#include "types.h"

extern s32 EvObjResolveTarget_2f9a60(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ObjTypeMonographResolveTarget_372bb0(s32 p0)
{
    s32 r;

    r = EvObjResolveTarget_2f9a60(p0, 0);
    return 1;
}

#include "types.h"

extern s32 VariantGetInt_15f780(s32);
extern s32 DynClothAllocVertices_169270(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481154;
extern s32 D_00481158;
extern s32 D_0048117C;

s32 DynVertexStartCmd_168cd0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = VariantGetInt_15f780(p0);
    r1 = DynClothAllocVertices_169270(D_00481154, r0, D_00481158);
    D_0048117C = 0;
    return 1;
}

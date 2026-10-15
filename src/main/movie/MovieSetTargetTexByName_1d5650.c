#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 NameTableFindByName_159fb0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004817A4;
extern s32 D_004817A8;

s32 MovieSetTargetTexByName_1d5650(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;

    D_004817A4 = p1;
    r0 = GetDrawCtxNameTable_15de40();
    r1 = NameTableFindByName_159fb0(r0, D_004817A4, -1);
    D_004817A8 = r1;
    return r1;
}

#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461620[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
};

s32 EffectTimedSlotSetGuardTex_2d4ca0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtxNameTable_15de40();
    p0->m08 = p1;
    r1 = NameTableFindByName_159fb0(r0, D_00461620, p1);
    p0->m0C = r1;
    return r1;
}

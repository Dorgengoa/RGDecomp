#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461648[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s16 m08;
};

s32 LightningMgrSetTex_2d64a0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtxNameTable_15de40();
    r1 = NameTableFindByName_159fb0(r0, D_00461648, p1);
    p0->m04 = r1;
    p0->m08 = p1;
    return r1;
}

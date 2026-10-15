#include "types.h"

extern s32 AttackObjBaseCtor_3181b0(void *, s32, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471B40[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xB0];
    void *mB0;
};

struct Obj0 *AttackObjCtor_3175c0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, f32 fa0)
{
    s32 r0;

    r0 = AttackObjBaseCtor_3181b0(p0, p1, p2, p3, fa0);
    p0->mB0 = D_00471B40;
    return p0;
}

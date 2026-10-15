#include "types.h"

extern s32 NodeRefObjCtor_318ff0(void *, s32, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471C90[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xB0];
    void *mB0;
    u8 pad0B4[0x7DC];
    u8 m890;
    u8 pad891[0x1F];
    s32 m8B0;
    s32 m8B4;
};

struct Obj0 *NodeRefObjMotionGateCtor_3183f0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, f32 fa0)
{
    s32 r0;

    r0 = NodeRefObjCtor_318ff0(p0, p1, p2, p3, fa0);
    p0->mB0 = D_00471C90;
    p0->m890 = 0;
    p0->m8B0 = 0;
    p0->m8B4 = 0x3F800000;
    return p0;
}

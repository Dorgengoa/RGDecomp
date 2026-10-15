#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x180];
    f32 m180;
    f32 m184;
    f32 m188;
    s32 m18C;
};

void AttackObjBaseSetPos_27a1e0(struct Obj0 *p0, f32 fa0, f32 fa1, f32 fa2)
{
    p0->m180 = fa0;
    p0->m184 = fa1;
    p0->m188 = fa2;
    p0->m18C = 0x3F800000;
}

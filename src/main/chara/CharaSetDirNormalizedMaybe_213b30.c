#include "types.h"

extern void VecNormalize_1cbb80(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    f32 m00;
    f32 m04;
    f32 m08;
};

struct Obj1 {
    u8 pad000[0x440];
    f32 m440;
    f32 m444;
    f32 m448;
    s32 m44C;
};

void CharaSetDirNormalizedMaybe_213b30(struct Obj1 *p0, struct Obj0 *p1)
{
    f32 t0;
    f32 t1;
    f32 t2;

    t0 = p1->m08;
    t1 = p1->m04;
    t2 = p1->m00;
    p0->m440 = t2;
    p0->m444 = t1;
    p0->m448 = t0;
    p0->m44C = 0;
    VecNormalize_1cbb80((struct Obj1 *)((u8 *)p0 + 0x440), (struct Obj1 *)((u8 *)p0 + 0x440));
}

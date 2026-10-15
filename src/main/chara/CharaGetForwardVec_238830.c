#include "types.h"

extern f32 Sinf_128fd0(f32);
extern f32 Cosf_128d30(f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x64];
    f32 m64;
};

struct Obj1 {
    f32 m00;
    s32 m04;
    f32 m08;
    s32 m0C;
};

f32 CharaGetForwardVec_238830(struct Obj0 *p0, struct Obj1 *p1)
{
    f32 t0;
    f32 r0;
    f32 t1;
    f32 r1;

    t0 = p0->m64;
    r0 = Sinf_128fd0(t0);
    p1->m00 = r0;
    p1->m04 = 0;
    t1 = p0->m64;
    r1 = Cosf_128d30(t1);
    p1->m08 = r1;
    p1->m0C = 0;
    return r1;
}

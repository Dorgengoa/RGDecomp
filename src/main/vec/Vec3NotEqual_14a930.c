#include "types.h"



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
    f32 m00;
    f32 m04;
    f32 m08;
};

s32 Vec3NotEqual_14a930(struct Obj1 *p0, struct Obj0 *p1)
{
    f32 t0;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 t4;
    f32 t5;
    s32 rv0;

    t0 = p1->m00;
    t1 = p0->m00;
    if (t0 != t1) {
        return 1;
    }
    t2 = p1->m04;
    t3 = p0->m04;
    if (t2 != t3) {
        return 1;
    }
    t4 = p1->m08;
    t5 = p0->m08;
    rv0 = 1;
    if (t4 == t5) {
        rv0 = 0;
    }
    return (rv0 & 0xFF);
}

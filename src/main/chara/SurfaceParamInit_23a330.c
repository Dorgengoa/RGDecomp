#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
};

struct Obj0 *SurfaceParamInit_23a330(struct Obj0 *p0, s32 p1, f32 fa0, f32 fa1, f32 fa2)
{
    f32 rv3;
    f32 rv0;
    f32 rv1;
    f32 rv2;
    f32 t0;
    f32 t1;

    p0->m00 = -1;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    rv3 = 0.0f;
    if (p1 >= 0) {
        p0->m00 = p1;
        rv0 = fa0;
        if (fa0 < 0.0f) {
            rv0 = -fa0;
        }
        p0->m04 = rv0;
        rv1 = fa1;
        if (fa1 < 0.0f) {
            rv1 = -fa1;
        }
        p0->m08 = rv1;
        rv2 = fa2;
        if (fa2 < 0.0f) {
            rv2 = -fa2;
        }
        p0->m0C = rv2;
        t0 = p0->m08;
        t1 = p0->m0C;
        if (t1 > t0) {
            p0->m0C = t0;
        }
        rv3 = t1;
    }
    return p0;
}

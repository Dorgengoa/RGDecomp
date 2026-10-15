#include "types.h"

extern void * ParamTableGetRec_1cfbc0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    f32 m04;
    f32 m08;
};

struct Obj0 *ParamTableFadeTo_1cfa00(s32 p0, s32 p1, s32 p2, f32 fa0)
{
    struct Obj0 *r0;
    f32 rv1;
    f32 t0;
    f32 t1;

    r0 = ParamTableGetRec_1cfbc0(p0, p1);
    if (r0 != 0) {
        if (p2 <= 0) {
            t0 = r0->m04;
            r0->m08 = (fa0 - t0);
            rv1 = (fa0 - t0);
        } else {
            t1 = r0->m04;
            r0->m08 = ((fa0 - t1) / ((f32)p2));
            rv1 = ((fa0 - t1) / ((f32)p2));
        }
    }
    return r0;
}

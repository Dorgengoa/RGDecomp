#include "types.h"

extern void ModelObjTexAnimStartByName_1ac590(s32, s32);
extern s32 ModelObjTexAnimResetByName_1ac510(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

struct Obj1 {
    u8 pad000[0x28];
    s32 m28;
    s32 m2C;
};

s32 MotionEventTexAnimeFire_1b1130(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 rv3;
    s32 t1;
    s32 rv2;
    s32 t2;
    s32 r1;

    t0 = p0->m04;
    rv3 = rv2;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        t1 = p1->m28;
        rv2 = 1;
        if (t1 == 0) {
            rv2 = 0;
        } else {
            t2 = p1->m2C;
            if (t2 != 0) {
                ModelObjTexAnimStartByName_1ac590(t0, t1);
            } else {
                r1 = ModelObjTexAnimResetByName_1ac510(t0, t1);
            }
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}

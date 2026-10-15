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
    u8 pad000[0x28];
    s32 m28;
    s32 m2C;
    s32 m30;
};

struct Obj1 {
    u8 pad000[0x4];
    s32 m04;
};

s32 MotionEventTexAnimeBegin_1b10b0(struct Obj1 *p0, struct Obj0 *p1)
{
    s32 t0;
    s32 rv2;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 r1;

    t0 = p1->m30;
    rv2 = t0;
    if (t0 == 0) {
        t1 = p0->m04;
        if (t1 == 0) {
            return 0;
        }
        t2 = p1->m28;
        if (t2 == 0) {
            return 0;
        }
        t3 = p1->m2C;
        if (t3 != 0) {
            ModelObjTexAnimStartByName_1ac590(t1, t2);
        } else {
            r1 = ModelObjTexAnimResetByName_1ac510(t1, t2);
        }
        p1->m30 = 1;
        rv2 = 1;
    }
    return 1;
}

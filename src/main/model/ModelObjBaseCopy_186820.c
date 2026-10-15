#include "types.h"

extern s32 ModelCopy_151c40(void *, void *, s32);
extern void MotionListCopy_171cc0(void *, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x1C0];
    s32 m1C0;
    s32 m1C4;
    s32 m1C8;
    s32 m1CC;
    s32 m1D0;
    f32 m1D4;
    f32 m1D8;
    s32 m1DC;
    f32 m1E0;
    f32 m1E4;
    f32 m1E8;
};

struct Obj1 {
    u8 pad000[0x1C0];
    s32 m1C0;
    u8 pad1C4[0x4];
    s32 m1C8;
    s32 m1CC;
    s32 m1D0;
    f32 m1D4;
    f32 m1D8;
    s32 m1DC;
    f32 m1E0;
    f32 m1E4;
    f32 m1E8;
};

void ModelObjBaseCopy_186820(struct Obj0 *p0, struct Obj1 *p1, s32 p2)
{
    s32 r0;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    f32 t4;
    f32 t5;
    s32 t6;
    f32 t7;
    f32 t8;
    f32 t9;

    r0 = ModelCopy_151c40(p0, p1, p2);
    t0 = p0->m1C0;
    p1->m1C0 = t0;
    p0->m1C4 = 0xBF800000;
    t1 = p0->m1C8;
    p1->m1C8 = t1;
    t2 = p0->m1CC;
    p1->m1CC = t2;
    t3 = p0->m1D0;
    p1->m1D0 = t3;
    t4 = p0->m1D4;
    p1->m1D4 = t4;
    t5 = p0->m1D8;
    p1->m1D8 = t5;
    t6 = p0->m1DC;
    p1->m1DC = t6;
    t7 = p0->m1E0;
    p1->m1E0 = t7;
    t8 = p0->m1E4;
    p1->m1E4 = t8;
    t9 = p0->m1E8;
    p1->m1E8 = t9;
    MotionListCopy_171cc0((struct Obj0 *)((u8 *)p0 + 0x1F0), (struct Obj1 *)((u8 *)p1 + 0x1F0), p2);
}

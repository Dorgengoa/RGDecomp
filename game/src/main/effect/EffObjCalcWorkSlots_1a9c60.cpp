#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    s32 v1(s32 a0) { return VCM(s32, (void *, s32), 0xC, a0); }
};

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    u8 pad00C[0x8];
    s32 m14;
    u8 pad018[0x20];
    s32 m38;
};

struct Obj1 {
    struct Obj1 *m00;
    s32 m04;
};

extern "C" s32 EffObjCalcWorkSlots_1a9c60(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *l1;
    s32 l0;
    s32 t1;
    s32 r2;
    s32 t3;

    t0 = p0->m04;
    l1 = (struct Obj1 *)t0;
    l0 = 0;
    while (l1 != 0) {
        t1 = l1->m04;
        r2 = ((struct C0 *)t1)->v1(l0);
        l1 = l1->m00;
        l0 = l0 + r2;
    }
    t3 = p0->m38;
    if (t3 != 0) {
        p0->m14 = l0;
        l0 = l0 + 4;
        p0->m08 = l0;
    } else {
        p0->m08 = l0;
    }
    return l0;
}

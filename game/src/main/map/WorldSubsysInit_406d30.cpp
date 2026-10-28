#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    s32 v1(s32 a0, s32 a1, s32 a2, s32 a3) { return VCM(s32, (void *, s32, s32, s32, s32), 0xC, a0, a1, a2, a3); }
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_407900(s32);
extern "C" s32 DataTableInitWithCount_368b00(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_00465860;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x4];
    s32 m0C;
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

extern "C" s32 WorldSubsysInit_406d30(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv5;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 r3;
    s32 t4;
    s32 t5;
    s32 r4;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    p0->m04 = p2;
    t0 = p0->m00;
    r0 = MemStackNew_14e130(0x98, t0);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_407900(r0);
        p0->m0C = r1;
        rv2 = r1;
    } else {
        p0->m0C = r0;
        rv2 = r0;
    }
    rv5 = 1;
    if (rv2 == 0) {
        rv5 = 0;
    } else {
        p0->m10 = 0;
        p0->m18 = 0;
        t1 = p0->m0C;
        t2 = D_00465860;
        t3 = p0->m00;
        r3 = ((struct C0 *)t1)->v1(t3, 0, (t2 != 0), 0);
        t4 = p0->m04;
        t5 = p0->m0C;
        r4 = DataTableInitWithCount_368b00(t5, t4);
        rv5 = 1;
    }
    return rv5;
}

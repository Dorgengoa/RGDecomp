#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    s32 v1(s32 a0, s32 a1, s32 a2, s32 a3) { return VCM(s32, (void *, s32, s32, s32, s32), 0xC, a0, a1, a2, a3); }
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_3f8b80(s32);
extern "C" s32 DataTableCtor_3f85f0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_00465758;
extern "C" s32 D_00465760;

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
    s32 m0C;
};

extern "C" s32 WorldSubsysInit_3f8060(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv9;
    s32 t0;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 rv8;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 r6;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 r7;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    r0 = MemStackNew_14e130(0x94, p1);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_3f8b80(r0);
        p0->m08 = r1;
        rv2 = r1;
    } else {
        p0->m08 = r0;
        rv2 = r0;
    }
    if (rv2 == 0) {
        rv9 = 0;
    } else {
        t0 = p0->m00;
        r3 = MemStackNew_14e130(0x94, t0);
        rv5 = r3;
        if (r3 != 0) {
            r4 = DataTableCtor_3f85f0(r3);
            p0->m0C = r4;
            rv5 = r4;
        } else {
            p0->m0C = r3;
            rv5 = r3;
        }
        rv8 = 1;
        if (rv5 == 0) {
            rv8 = 0;
        } else {
            t1 = p0->m08;
            t2 = D_00465758;
            t3 = p0->m00;
            r6 = ((struct C0 *)t1)->v1(t3, 0, (t2 != 0), 0);
            t4 = p0->m0C;
            t5 = D_00465760;
            t6 = p0->m00;
            r7 = ((struct C0 *)t4)->v1(t6, 0, (t5 != 0), 0);
            rv8 = 1;
        }
        rv9 = rv8;
    }
    return rv9;
}

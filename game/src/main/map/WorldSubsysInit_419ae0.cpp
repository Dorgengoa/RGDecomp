#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    s32 v1(s32 a0, s32 a1, s32 a2, s32 a3) { return VCM(s32, (void *, s32, s32, s32, s32), 0xC, a0, a1, a2, a3); }
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_41b460(s32);
extern "C" s32 DataTableCtor_41b160(s32);
extern "C" s32 DataTableCtor_419d90(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_00465788;
extern "C" s32 D_00465790;
extern "C" s32 D_00465798;

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
    s32 m0C;
    s32 m10;
};

extern "C" s32 WorldSubsysInit_419ae0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv18;
    s32 t0;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 rv17;
    s32 t1;
    s32 r6;
    s32 rv8;
    s32 r7;
    s32 rv16;
    s32 t2;
    s32 rv10;
    s32 rv11;
    s32 t3;
    s32 t4;
    s32 r9;
    s32 t5;
    s32 t6;
    s32 rv13;
    s32 rv14;
    s32 t7;
    s32 t8;
    s32 r12;
    s32 t9;
    s32 t10;
    s32 t11;
    s32 t12;
    s32 r15;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    r0 = MemStackNew_14e130(0x94, p1);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_41b460(r0);
        p0->m08 = r1;
        rv2 = r1;
    } else {
        p0->m08 = r0;
        rv2 = r0;
    }
    if (rv2 == 0) {
        rv18 = 0;
    } else {
        t0 = p0->m00;
        r3 = MemStackNew_14e130(0x98, t0);
        rv5 = r3;
        if (r3 != 0) {
            r4 = DataTableCtor_41b160(r3);
            p0->m0C = r4;
            rv5 = r4;
        } else {
            p0->m0C = r3;
            rv5 = r3;
        }
        if (rv5 == 0) {
            rv17 = 0;
        } else {
            t1 = p0->m00;
            r6 = MemStackNew_14e130(0x94, t1);
            rv8 = r6;
            if (r6 != 0) {
                r7 = DataTableCtor_419d90(r6);
                p0->m10 = r7;
                rv8 = r7;
            } else {
                p0->m10 = r6;
                rv8 = r6;
            }
            rv16 = 1;
            if (rv8 == 0) {
                rv16 = 0;
            } else {
                t2 = p0->m08;
                rv10 = rv8;
                if (t2 != 0) {
                    t3 = D_00465788;
                    t4 = p0->m00;
                    r9 = ((struct C0 *)t2)->v1(t4, 0, (t3 != 0), 0);
                    t5 = p0->m0C;
                    rv10 = r9;
                    rv11 = t5;
                } else {
                    t6 = p0->m0C;
                    rv10 = rv8;
                    rv11 = t6;
                }
                rv13 = rv10;
                if (rv11 != 0) {
                    t7 = D_00465790;
                    t8 = p0->m00;
                    r12 = ((struct C0 *)rv11)->v1(t8, 0, (t7 != 0), 0);
                    t9 = p0->m10;
                    rv13 = r12;
                    rv14 = t9;
                } else {
                    t10 = p0->m10;
                    rv13 = rv10;
                    rv14 = t10;
                }
                if (rv14 != 0) {
                    t11 = D_00465798;
                    t12 = p0->m00;
                    r15 = ((struct C0 *)rv14)->v1(t12, 0, (t11 != 0), 0);
                }
                rv16 = 1;
            }
            rv17 = rv16;
        }
        rv18 = rv17;
    }
    return rv18;
}

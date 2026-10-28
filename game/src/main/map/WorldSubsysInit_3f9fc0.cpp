#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    s32 v1(s32 a0, s32 a1, s32 a2, s32 a3) { return VCM(s32, (void *, s32, s32, s32, s32), 0xC, a0, a1, a2, a3); }
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_3fb2b0(s32);
extern "C" s32 DataTableCtor_3fad30(s32);
extern "C" s32 DataTableCtor_3fa6b0(s32);
extern "C" s32 DataTableCtor_3fa390(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_00465728;
extern "C" s32 D_00465730;
extern "C" s32 D_00465738;
extern "C" s32 D_00465740;

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
};

extern "C" s32 WorldSubsysInit_3f9fc0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv19;
    s32 t0;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 rv18;
    s32 t1;
    s32 r6;
    s32 rv8;
    s32 r7;
    s32 rv17;
    s32 t2;
    s32 r9;
    s32 rv11;
    s32 r10;
    s32 rv16;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 r12;
    s32 t6;
    s32 t7;
    s32 t8;
    s32 r13;
    s32 t9;
    s32 t10;
    s32 t11;
    s32 r14;
    s32 t12;
    s32 t13;
    s32 t14;
    s32 r15;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    r0 = MemStackNew_14e130(0x98, p1);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_3fb2b0(r0);
        p0->m08 = r1;
        rv2 = r1;
    } else {
        p0->m08 = r0;
        rv2 = r0;
    }
    if (rv2 == 0) {
        rv19 = 0;
    } else {
        t0 = p0->m00;
        r3 = MemStackNew_14e130(0x94, t0);
        rv5 = r3;
        if (r3 != 0) {
            r4 = DataTableCtor_3fad30(r3);
            p0->m0C = r4;
            rv5 = r4;
        } else {
            p0->m0C = r3;
            rv5 = r3;
        }
        if (rv5 == 0) {
            rv18 = 0;
        } else {
            t1 = p0->m00;
            r6 = MemStackNew_14e130(0x94, t1);
            rv8 = r6;
            if (r6 != 0) {
                r7 = DataTableCtor_3fa6b0(r6);
                p0->m10 = r7;
                rv8 = r7;
            } else {
                p0->m10 = r6;
                rv8 = r6;
            }
            if (rv8 == 0) {
                rv17 = 0;
            } else {
                t2 = p0->m00;
                r9 = MemStackNew_14e130(0x94, t2);
                rv11 = r9;
                if (r9 != 0) {
                    r10 = DataTableCtor_3fa390(r9);
                    p0->m14 = r10;
                    rv11 = r10;
                } else {
                    p0->m14 = r9;
                    rv11 = r9;
                }
                rv16 = 1;
                if (rv11 == 0) {
                    rv16 = 0;
                } else {
                    t3 = p0->m08;
                    t4 = D_00465728;
                    t5 = p0->m00;
                    r12 = ((struct C0 *)t3)->v1(t5, 0, (t4 != 0), 0);
                    t6 = p0->m0C;
                    t7 = D_00465730;
                    t8 = p0->m00;
                    r13 = ((struct C0 *)t6)->v1(t8, 0, (t7 != 0), 0);
                    t9 = p0->m10;
                    t10 = D_00465738;
                    t11 = p0->m00;
                    r14 = ((struct C0 *)t9)->v1(t11, 0, (t10 != 0), 0);
                    t12 = p0->m14;
                    t13 = D_00465740;
                    t14 = p0->m00;
                    r15 = ((struct C0 *)t12)->v1(t14, 0, (t13 != 0), 0);
                    rv16 = 1;
                }
                rv17 = rv16;
            }
            rv18 = rv17;
        }
        rv19 = rv18;
    }
    return rv19;
}

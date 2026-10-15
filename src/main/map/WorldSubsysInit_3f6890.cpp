#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1(s32, s32, s32, s32);
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_3f7330(s32);
extern "C" s32 DataTableCtor_3f7110(s32);
extern "C" s32 DataTableCtor_3f6e20(s32);
extern "C" s32 DataTableCtor_3f6c50(s32);
extern "C" s32 DataTableInitWithCount_368b00(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" const s32 D_00465878;
extern "C" const s32 D_00465880;
extern "C" const s32 D_00465888;
extern "C" const s32 D_00465890;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x4];
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
};

extern "C" s32 WorldSubsysInit_3f6890(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv23;
    s32 t1;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 rv22;
    s32 t2;
    s32 r6;
    s32 rv8;
    s32 r7;
    s32 rv21;
    s32 t3;
    s32 r9;
    s32 rv11;
    s32 r10;
    s32 rv20;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 r12;
    s32 t7;
    s32 t8;
    s32 r13;
    s32 t9;
    s32 t10;
    s32 t11;
    s32 r14;
    s32 t12;
    s32 t13;
    s32 r15;
    s32 t14;
    s32 t15;
    s32 t16;
    s32 r16;
    s32 t17;
    s32 t18;
    s32 r17;
    s32 t19;
    s32 t20;
    s32 t21;
    s32 r18;
    s32 t22;
    s32 t23;
    s32 r19;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    p0->m04 = p2;
    t0 = p0->m00;
    r0 = MemStackNew_14e130(0x94, t0);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_3f7330(r0);
        p0->m0C = r1;
        rv2 = r1;
    } else {
        p0->m0C = r0;
        rv2 = r0;
    }
    if (rv2 == 0) {
        rv23 = 0;
    } else {
        t1 = p0->m00;
        r3 = MemStackNew_14e130(0x98, t1);
        rv5 = r3;
        if (r3 != 0) {
            r4 = DataTableCtor_3f7110(r3);
            p0->m10 = r4;
            rv5 = r4;
        } else {
            p0->m10 = r3;
            rv5 = r3;
        }
        if (rv5 == 0) {
            rv22 = 0;
        } else {
            t2 = p0->m00;
            r6 = MemStackNew_14e130(0x94, t2);
            rv8 = r6;
            if (r6 != 0) {
                r7 = DataTableCtor_3f6e20(r6);
                p0->m14 = r7;
                rv8 = r7;
            } else {
                p0->m14 = r6;
                rv8 = r6;
            }
            if (rv8 == 0) {
                rv21 = 0;
            } else {
                t3 = p0->m00;
                r9 = MemStackNew_14e130(0x94, t3);
                rv11 = r9;
                if (r9 != 0) {
                    r10 = DataTableCtor_3f6c50(r9);
                    p0->m18 = r10;
                    rv11 = r10;
                } else {
                    p0->m18 = r9;
                    rv11 = r9;
                }
                rv20 = 1;
                if (rv11 == 0) {
                    rv20 = 0;
                } else {
                    t4 = p0->m0C;
                    t5 = D_00465878;
                    t6 = p0->m00;
                    r12 = ((struct C0 *)t4)->v1(t6, 0, (t5 != 0), 0);
                    t7 = p0->m04;
                    t8 = p0->m0C;
                    r13 = DataTableInitWithCount_368b00(t8, t7);
                    t9 = p0->m10;
                    t10 = D_00465880;
                    t11 = p0->m00;
                    r14 = ((struct C0 *)t9)->v1(t11, 0, (t10 != 0), 0);
                    t12 = p0->m04;
                    t13 = p0->m10;
                    r15 = DataTableInitWithCount_368b00(t13, t12);
                    t14 = p0->m14;
                    t15 = D_00465888;
                    t16 = p0->m00;
                    r16 = ((struct C0 *)t14)->v1(t16, 0, (t15 != 0), 0);
                    t17 = p0->m04;
                    t18 = p0->m14;
                    r17 = DataTableInitWithCount_368b00(t18, t17);
                    t19 = p0->m18;
                    t20 = D_00465890;
                    t21 = p0->m00;
                    r18 = ((struct C0 *)t19)->v1(t21, 0, (t20 != 0), 0);
                    t22 = p0->m04;
                    t23 = p0->m18;
                    r19 = DataTableInitWithCount_368b00(t23, t22);
                    rv20 = 1;
                }
                rv21 = rv20;
            }
            rv22 = rv21;
        }
        rv23 = rv22;
    }
    return rv23;
}

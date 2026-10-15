#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1(s32, s32, s32, s32);
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_406530(s32);
extern "C" s32 DataTableCtor_4060b0(s32);
extern "C" s32 DataTableInitWithCount_368b00(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" const s32 D_004658A8;
extern "C" const s32 D_004658B0;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x4];
    s32 m0C;
    s32 m10;
};

extern "C" s32 WorldSubsysInit_405d50(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv11;
    s32 t1;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 rv10;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 r6;
    s32 t5;
    s32 t6;
    s32 r7;
    s32 t7;
    s32 t8;
    s32 t9;
    s32 r8;
    s32 t10;
    s32 t11;
    s32 r9;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    p0->m04 = p2;
    t0 = p0->m00;
    r0 = MemStackNew_14e130(0x94, t0);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_406530(r0);
        p0->m0C = r1;
        rv2 = r1;
    } else {
        p0->m0C = r0;
        rv2 = r0;
    }
    if (rv2 == 0) {
        rv11 = 0;
    } else {
        t1 = p0->m00;
        r3 = MemStackNew_14e130(0x94, t1);
        rv5 = r3;
        if (r3 != 0) {
            r4 = DataTableCtor_4060b0(r3);
            p0->m10 = r4;
            rv5 = r4;
        } else {
            p0->m10 = r3;
            rv5 = r3;
        }
        rv10 = 1;
        if (rv5 == 0) {
            rv10 = 0;
        } else {
            t2 = p0->m0C;
            t3 = D_004658A8;
            t4 = p0->m00;
            r6 = ((struct C0 *)t2)->v1(t4, 0, (t3 != 0), 0);
            t5 = p0->m04;
            t6 = p0->m0C;
            r7 = DataTableInitWithCount_368b00(t6, t5);
            t7 = p0->m10;
            t8 = D_004658B0;
            t9 = p0->m00;
            r8 = ((struct C0 *)t7)->v1(t9, 0, (t8 != 0), 0);
            t10 = p0->m04;
            t11 = p0->m10;
            r9 = DataTableInitWithCount_368b00(t11, t10);
            rv10 = 1;
        }
        rv11 = rv10;
    }
    return rv11;
}

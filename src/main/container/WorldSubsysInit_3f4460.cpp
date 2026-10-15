#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1(s32, s32, s32, s32);
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_3f5560(s32);
extern "C" s32 DataTableCtor_3f48f0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" const s32 D_00465710;
extern "C" const s32 D_00465718;

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
    s32 m0C;
};

extern "C" s32 WorldSubsysInit_3f4460(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv11;
    s32 t0;
    s32 r3;
    s32 rv5;
    s32 r4;
    s32 rv10;
    s32 t1;
    s32 rv7;
    s32 rv8;
    s32 t2;
    s32 t3;
    s32 r6;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    s32 r9;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    r0 = MemStackNew_14e130(0x94, p1);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_3f5560(r0);
        p0->m08 = r1;
        rv2 = r1;
    } else {
        p0->m08 = r0;
        rv2 = r0;
    }
    if (rv2 == 0) {
        rv11 = 0;
    } else {
        t0 = p0->m00;
        r3 = MemStackNew_14e130(0x98, t0);
        rv5 = r3;
        if (r3 != 0) {
            r4 = DataTableCtor_3f48f0(r3);
            p0->m0C = r4;
            rv5 = r4;
        } else {
            p0->m0C = r3;
            rv5 = r3;
        }
        rv10 = 1;
        if (rv5 == 0) {
            rv10 = 0;
        } else {
            t1 = p0->m08;
            rv7 = rv5;
            if (t1 != 0) {
                t2 = D_00465710;
                t3 = p0->m00;
                r6 = ((struct C0 *)t1)->v1(t3, 0, (t2 != 0), 0);
                t4 = p0->m0C;
                rv7 = r6;
                rv8 = t4;
            } else {
                t5 = p0->m0C;
                rv7 = rv5;
                rv8 = t5;
            }
            if (rv8 != 0) {
                t6 = D_00465718;
                t7 = p0->m00;
                r9 = ((struct C0 *)rv8)->v1(t7, 0, (t6 != 0), 0);
            }
            rv10 = 1;
        }
        rv11 = rv10;
    }
    return rv11;
}

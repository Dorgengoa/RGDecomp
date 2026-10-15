#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1(s32, s32, s32, s32);
};

extern "C" s32 MemStackNew_14e130(s32, s32);
extern "C" s32 DataTableCtor_40db20(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" const s32 D_00465708;

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
};

extern "C" s32 WorldSubsysInit_40c5c0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 rv4;
    s32 t0;
    s32 t1;
    s32 r3;

    if (p1 == 0) {
        return 0;
    }
    p0->m00 = p1;
    r0 = MemStackNew_14e130(0x9C, p1);
    rv2 = r0;
    if (r0 != 0) {
        r1 = DataTableCtor_40db20(r0);
        p0->m08 = r1;
        rv2 = r1;
    } else {
        p0->m08 = r0;
        rv2 = r0;
    }
    rv4 = 1;
    if (rv2 == 0) {
        rv4 = 0;
    } else {
        if (rv2 != 0) {
            t0 = D_00465708;
            t1 = p0->m00;
            r3 = ((struct C0 *)rv2)->v1(t1, 0, (t0 != 0), 0);
        }
        rv4 = 1;
    }
    return rv4;
}

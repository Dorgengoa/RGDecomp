#include "types.h"

extern void * CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj2 * D_004838E8;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x10];
    struct Obj1 *m10;
};

struct Obj1 {
    u8 pad000[0x8];
    s16 m08;
};

struct Obj2 {
    u8 pad000[0x14];
    s32 m14;
};

struct Obj3 {
    u8 pad000[0x234];
    u8 m234;
};

struct Obj3 *ItemFindOwnerChara_3d4d80(struct Obj0 *p0, s32 p1)
{
    struct Obj2 * t0;
    struct Obj3 * rv5;
    struct Obj1 * t1;
    struct Obj3 * rv4;
    s16 t2;
    s32 t3;
    struct Obj3 *r0;
    struct Obj3 * rv3;
    struct Obj3 * rv2;
    u8 t4;
    struct Obj3 * rv1;

    t0 = D_004838E8;
    if (t0 == 0) {
        rv5 = 0;
    } else {
        t1 = p0->m10;
        if (t1 == 0) {
            rv4 = 0;
        } else {
            t2 = p0->m10->m08;
            t3 = D_004838E8->m14;
            r0 = CharaMgrPoolFindByDataId_3a8a70(t3, t2, 1, 1, 0, 0, 0);
            if (r0 == 0) {
                rv3 = 0;
            } else {
                rv2 = r0;
                if (p1 != 0) {
                    t4 = r0->m234;
                    rv1 = r0;
                    if ((((u64)(((s64)t4) << 0x3E)) >> 0x3F) == 0) {
                        rv1 = 0;
                    }
                    rv2 = rv1;
                }
                rv3 = rv2;
            }
            rv4 = rv3;
        }
        rv5 = rv4;
    }
    return rv5;
}

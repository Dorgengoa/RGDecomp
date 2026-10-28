/* rgp:protos */
#define RGP_SELF_ExecInfoInitFromObj_3a7790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004837B0;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj1 *m08;
    u8 pad00C[0x10];
    s32 m1C;
};

struct Obj1 {
    u8 pad000[0x50];
    struct Obj2 *m50;
};

struct Obj2 {
    u8 pad000[0x8];
    s32 m08;
};

struct Obj3 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x2];
    s16 m08;
    u8 pad00A[0x2];
    s32 m0C;
};

s32 ExecInfoInitFromObj_3a7790(struct Obj3 *p0, s32 p1, s32 p2)
{
    s32 r0;
    struct Obj0 * t0;
    s32 rv5;
    s32 t1;
    s32 r1;
    s32 rv4;
    struct Obj0 * t2;
    struct Obj1 * t3;
    struct Obj2 * t4;
    s32 t5;
    s32 r2;
    s32 rv3;

    r0 = ((s32)ExecInfoInit_3a7940(p0));
    t0 = D_004837B0;
    rv5 = rv4;
    if (t0 == 0) {
        rv5 = 0;
    } else {
        t1 = D_004837B0->m1C;
        r1 = ((s32)ObjFindById_3bb3a0(t1, p1));
        rv4 = rv3;
        if (r1 == 0) {
            rv4 = 0;
        } else {
            t2 = D_004837B0;
            t3 = D_004837B0->m08;
            t4 = D_004837B0->m08->m50;
            t5 = D_004837B0->m08->m50->m08;
            r2 = ((s32)TableFindByNameHashed_3f86e0(t5, p2));
            rv3 = 1;
            if (r2 == 0) {
                rv3 = 0;
            } else {
                p0->m04 = 2;
                p0->m08 = p1;
                p0->m0C = r2;
                rv3 = 1;
            }
            rv4 = rv3;
        }
        rv5 = rv4;
    }
    return rv5;
}

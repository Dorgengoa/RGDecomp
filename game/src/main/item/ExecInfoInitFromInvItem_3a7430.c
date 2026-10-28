/* rgp:protos */
#define RGP_SELF_ExecInfoInitFromInvItem_3a7430 1
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
struct Obj4;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj2 *m08;
    u8 pad00C[0xC];
    s32 m18;
};

struct Obj1 {
    u8 pad000[0x10];
    s32 m10;
};

struct Obj2 {
    u8 pad000[0x50];
    struct Obj3 *m50;
};

struct Obj3 {
    u8 pad000[0x8];
    s32 m08;
};

struct Obj4 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x2];
    s16 m08;
    s16 m0A;
    s32 m0C;
    s32 m10;
};

s32 ExecInfoInitFromInvItem_3a7430(struct Obj4 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    struct Obj0 * t0;
    s32 t1;
    struct Obj1 *r1;
    s32 rv5;
    s32 t2;
    s32 rv4;
    s32 rv3;
    struct Obj0 * t3;
    struct Obj2 * t4;
    struct Obj3 * t5;
    s32 t6;
    s32 r2;

    r0 = ((s32)ExecInfoInit_3a7940(p0));
    t0 = D_004837B0;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_004837B0->m18;
    r1 = InvFindByUniqueId_3c85d0(t1, p2, -1, 0);
    if (r1 == 0) {
        rv5 = 0;
    } else {
        t2 = r1->m10;
        rv4 = 1;
        if (t2 == 0) {
            rv4 = 0;
        } else {
            rv3 = 0;
            if (p3 != 0) {
                t3 = D_004837B0;
                t4 = D_004837B0->m08;
                t5 = D_004837B0->m08->m50;
                t6 = D_004837B0->m08->m50->m08;
                r2 = ((s32)TableFindByNameHashed_3f86e0(t6, p3));
                rv3 = r2;
            }
            p0->m04 = 4;
            p0->m08 = p1;
            p0->m0A = p2;
            p0->m0C = t2;
            p0->m10 = rv3;
            rv4 = 1;
        }
        rv5 = rv4;
    }
    return rv5;
}

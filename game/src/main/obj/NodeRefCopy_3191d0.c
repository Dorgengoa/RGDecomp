/* rgp:protos */
#define RGP_SELF_NodeRefCopy_3191d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 pad006[0x22];
    f32 m28;
    f32 m2C;
    f32 m30;
};

struct Obj1 {
    u8 pad000[0x28];
    f32 m28;
    f32 m2C;
    f32 m30;
};

s32 NodeRefCopy_3191d0(struct Obj1 *p0, struct Obj0 *p1)
{
    s32 rv2;
    s16 t0;
    s16 t1;
    s16 t2;
    s32 r1;
    f32 t3;
    f32 t4;
    f32 t5;

    NodeRefReset_3193d0(p0);
    rv2 = 1;
    if (p1 == 0) {
        rv2 = 0;
    } else {
        t0 = p1->m00;
        t1 = p1->m02;
        t2 = p1->m04;
        r1 = (NodeRefSet_319390(p0, t0, t1, (struct Obj0 *)((u8 *)p1 + 8), t2), (s32)0);
        t3 = p1->m30;
        t4 = p1->m2C;
        t5 = p1->m28;
        p0->m28 = t5;
        p0->m2C = t4;
        p0->m30 = t3;
        rv2 = 1;
    }
    return rv2;
}

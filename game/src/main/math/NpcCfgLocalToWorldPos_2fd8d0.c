/* rgp:protos */
#define RGP_SELF_NpcCfgLocalToWorldPos_2fd8d0 1
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
    u8 pad000[0x18];
    u8 m18;
    u8 pad019[0x67];
    f32 m80;
};

struct Obj1 {
    u8 pad000[0x4];
    f32 m04;
};

f32 NpcCfgLocalToWorldPos_2fd8d0(struct Obj0 *p0, struct Obj1 *p1, s32 p2)
{
    u8 t0;
    f32 rv2;
    f32 t1;
    f32 t2;
    f32 rv3;
    f32 t3;

    t0 = p0->m18;
    if ((t0 & 1) != 0) {
        MatMulPoint_1cb8e0(p1, (struct Obj0 *)((u8 *)p0 + 0x40), (void *)p2);
        t1 = p0->m80;
        rv2 = t1;
    } else {
        VecCopy_1cbe30(p1, p2);
        t2 = p0->m80;
        rv2 = t2;
    }
    rv3 = 0.0f;
    if (0.0f != rv2) {
        t3 = p1->m04;
        p1->m04 = (t3 + rv2);
        rv3 = (t3 + rv2);
    }
    return rv3;
}

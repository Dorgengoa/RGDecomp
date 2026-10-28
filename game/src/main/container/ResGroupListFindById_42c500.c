/* rgp:protos */
#define RGP_SELF_ResGroupListFindById_42c500 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x180];
    s32 m180;
};

struct Obj1 {
    s32 m00;
    u8 pad004[0x4];
    u16 m08;
};

s32 ResGroupListFindById_42c500(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    struct Obj1 *l0;
    u16 t1;
    s32 t2;

    t0 = p0->m180;
    l0 = (struct Obj1 *)t0;
    while (l0 != 0) {
        t1 = l0->m08;
        if (p1 == t1) {
            return (s32)l0;
        }
        t2 = l0->m00;
        l0 = (struct Obj1 *)t2;
    }
    return 0;
}

/* rgp:protos */
#define RGP_SELF_ListCountFromNode_18e050 1
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
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

s32 ListCountFromNode_18e050(struct Obj0 *p0)
{
    s32 t0;
    s32 l0;
    struct Obj1 *l1;
    s32 t1;

    t0 = p0->m00;
    l0 = 1;
    l1 = (struct Obj1 *)t0;
    while (l1 != 0) {
        t1 = l1->m00;
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)t1;
    }
    return l0;
}

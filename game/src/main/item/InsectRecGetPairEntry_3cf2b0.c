/* rgp:protos */
#define RGP_SELF_InsectRecGetPairEntry_3cf2b0 1
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
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x20];
    s16 m20;
};

struct Obj1 *InsectRecGetPairEntry_3cf2b0(struct Obj0 *p0, s32 p1)
{
    struct Obj1 * t0;
    s16 t1;

    t0 = p0->m18;
    if (t0 == 0) {
        return (struct Obj1 *)0;
    }
    t1 = p0->m18->m20;
    if (t1 <= p1) {
        return (struct Obj1 *)0;
    }
    return (struct Obj1 *)((u8 *)(struct Obj1 *)((u8 *)p0->m18 + (p1 * 0x14)) + 0x24);
}

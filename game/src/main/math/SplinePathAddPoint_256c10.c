/* rgp:protos */
#define RGP_SELF_SplinePathAddPoint_256c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x104];
    s32 m104;
};

s32 SplinePathAddPoint_256c10(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 rv1;
    s32 r0;
    s32 t1;

    t0 = p0->m104;
    rv1 = 0;
    if (t0 >= 0x10) {
        rv1 = 1;
    } else {
        r0 = ((s32)sceVu0CopyVector((struct Obj0 *)((u8 *)p0 + (t0 << 4)), p1));
        t1 = p0->m104;
        p0->m104 = (t1 + 1);
        rv1 = 0;
    }
    return rv1;
}

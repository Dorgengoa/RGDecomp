/* rgp:protos */
#define RGP_SELF_BitWriterInit_370d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 pad006[0x2];
    s32 m08;
};

s32 BitWriterInit_370d20(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s16 t1;

    p0->m00 = 0;
    p0->m02 = 0;
    if (p1 != 0) {
        if (p2 > 0) {
            p0->m08 = p1;
            p0->m04 = p2;
        }
    }
    t0 = p0->m08;
    if (t0 != 0) {
        t1 = p0->m04;
        memset(t0, 0, t1);
    }
    return 1;
}

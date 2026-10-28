/* rgp:protos */
#define RGP_SELF_CharaResFindById_1f0530 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 CharaResFindById_1f0530(s32 p0, s32 p1)
{
    s32 l0;
    struct Obj0 *l1;
    s16 t0;

    l0 = 0;
    l1 = (struct Obj0 *)p0;
    while (l0 < 0x20) {
        t0 = l1->m00;
        if (p1 == t0) {
            return (s32)l1;
        }
        l0 = (l0 + 1);
        l1 = (struct Obj0 *)((u8 *)l1 + 0x68);
    }
    return 0;
}

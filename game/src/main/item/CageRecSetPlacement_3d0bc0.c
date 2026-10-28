/* rgp:protos */
#define RGP_SELF_CageRecSetPlacement_3d0bc0 1
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
    u8 pad000[0x6];
    s16 m06;
    s16 m08;
    u8 pad00A[0x6];
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    u8 pad020[0x7CC];
    s32 m7EC;
};

s32 CageRecSetPlacement_3d0bc0(struct Obj0 *p0, s32 p1, s32 p2, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    p0->m18->m06 = p1;
    p0->m18->m08 = p2;
    p0->m18->m10 = fa0;
    p0->m18->m14 = fa1;
    p0->m18->m18 = fa2;
    p0->m18->m1C = fa3;
    p0->m18->m7EC = 0;
    return 1;
}

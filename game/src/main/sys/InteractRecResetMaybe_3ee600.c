/* rgp:protos */
#define RGP_SELF_InteractRecResetMaybe_3ee600 1
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
    s16 m02;
    s16 m04;
    s16 m06;
    s16 m08;
    u8 pad00A[0x2];
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
};

void InteractRecResetMaybe_3ee600(struct Obj0 *p0)
{
    p0->m00 = -1;
    p0->m02 = -1;
    p0->m04 = -1;
    p0->m06 = -1;
    p0->m08 = -1;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m20 = 0;
}

/* rgp:protos */
#define RGP_SELF_EvMapObjPointReset_3644f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    u128 m00;
    u128 m10;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
};

void EvMapObjPointReset_3644f0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m10 = 0;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m30 = 0x3F800000;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m3C = 0;
}

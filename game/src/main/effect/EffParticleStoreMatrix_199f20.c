/* rgp:protos */
#define RGP_SELF_EffParticleStoreMatrix_199f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xB0];
    s32 mB0;
    s32 mB4;
};

struct Obj1 {
    u128 m00;
    u128 m10;
    u128 m20;
    u128 m30;
};

void EffParticleStoreMatrix_199f20(struct Obj0 *p0, s32 p1, struct Obj1 *p2)
{
    s32 t0;
    u128 t1;
    u128 t2;
    u128 t3;
    u128 t4;

    if (p1 >= 0) {
        t0 = p0->mB4;
        t1 = p2->m00;
        *(u128 *)((u8 *)t0 + (p1 << 4)) = t1;
        t2 = p2->m10;
        *(u128 *)((u8 *)t0 + (p1 << 4) + 0x10) = t2;
        t3 = p2->m20;
        *(u128 *)((u8 *)t0 + (p1 << 4) + 0x20) = t3;
        t4 = p2->m30;
        *(u128 *)((u8 *)t0 + (p1 << 4) + 0x30) = t4;
        p0->mB0 = p1;
    }
}

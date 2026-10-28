/* rgp:protos */
#define RGP_SELF_AttackChainStateInit_382ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s16 m04;
    s16 m06;
    s16 m08;
    s16 m0A;
    s16 m0C;
    s16 m0E;
    s32 m10;
    s32 m14;
    s32 m18;
    u8 pad01C[0xC];
    s32 m28;
    u8 m2C;
    u8 pad02D[0x3];
    s32 m30;
};

void AttackChainStateInit_382ed0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m06 = 0;
    p0->m04 = 0;
    p0->m08 = 1;
    p0->m14 = 0x3F800000;
    p0->m18 = 0;
    p0->m0A = 0;
    p0->m0C = 0;
    p0->m0E = 0;
    p0->m10 = 0;
    p0->m28 = 0x3F800000;
    p0->m30 = 0;
    p0->m2C = 0;
}

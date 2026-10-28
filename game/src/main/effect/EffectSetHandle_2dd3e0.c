/* rgp:protos */
#define RGP_SELF_EffectSetHandle_2dd3e0 1
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
    s16 m00;
    u8 pad002[0x2];
    s32 m04;
    s32 m08;
    f32 m0C;
    s32 m10;
};

struct Obj1 {
    u8 pad000[0x20];
    s16 m20;
    u8 pad022[0x2];
    s32 m24;
    s32 m28;
    f32 m2C;
    s32 m30;
};

void EffectSetHandle_2dd3e0(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m20 = p1->m00;
    p0->m24 = p1->m04;
    p0->m28 = p1->m08;
    p0->m2C = p1->m0C;
    p0->m30 = p1->m10;
}

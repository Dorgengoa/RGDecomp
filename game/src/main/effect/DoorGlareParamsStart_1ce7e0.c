/* rgp:protos */
#define RGP_SELF_DoorGlareParamsStart_1ce7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    f32 m20;
    u8 pad024[0x8];
    f32 m2C;
    s32 m30;
};

void DoorGlareParamsStart_1ce7e0(struct Obj0 *p0)
{
    p0->m30 = 1;
    p0->m2C = p0->m20;
}

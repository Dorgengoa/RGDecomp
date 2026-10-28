/* rgp:protos */
#define RGP_SELF_DoorCursorShow_304a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
    u8 pad014[0xA];
    s16 m1E;
    s16 m20;
    s16 m22;
};

void DoorCursorShow_304a40(struct Obj0 *p0)
{
    if (p0->m1E == 0) {
        p0->m0C = 0x3FC00000;
        p0->m10 = 0;
        p0->m1E = 1;
        p0->m20 = 0;
        p0->m22 = 0;
    }
}

/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetRot_230080 1
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
    u8 pad000[0x3C];
    f32 m3C;
    f32 m40;
    f32 m44;
    u8 pad048[0x18];
    u16 m60;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
};

void CharaEffEntrySetRot_230080(struct Obj0 *p0, struct Obj1 *p1)
{
    p0->m60 = (p0->m60 | 0x1000);
    p0->m3C = p1->m00;
    p0->m40 = p1->m04;
    p0->m44 = p1->m08;
}

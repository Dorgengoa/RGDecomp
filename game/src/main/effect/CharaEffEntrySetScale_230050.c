/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetScale_230050 1
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
    u8 pad000[0x48];
    f32 m48;
    f32 m4C;
    f32 m50;
    u8 pad054[0xC];
    u16 m60;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
};

void CharaEffEntrySetScale_230050(struct Obj0 *p0, struct Obj1 *p1)
{
    p0->m60 = (p0->m60 | 0x2000);
    p0->m48 = p1->m00;
    p0->m4C = p1->m04;
    p0->m50 = p1->m08;
}

/* rgp:protos */
#define RGP_SELF_TextStyleSetFixedCell_26f0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3];
    u8 m03;
    u8 m04;
};

void TextStyleSetFixedCell_26f0e0(struct Obj0 *p0, s32 p1, s32 p2)
{
    TextStyleSetFixedPitch_26f140(p0, 1);
    p0->m03 = p1;
    p0->m04 = p2;
}

/* rgp:protos */
#define RGP_SELF_CharaRefInit_312330 1
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
    u8 pad000[0x4];
    s32 m04;
    s16 m08;
    s16 m0A;
};

void CharaRefInit_312330(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    CharaRefReset_312390(p0);
    p0->m0A = p1;
    p0->m04 = p2;
    p0->m08 = p3;
}

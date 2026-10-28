/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetWorkName_2301e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x5C];
    s32 m5C;
    u16 m60;
};

void CharaEffEntrySetWorkName_2301e0(struct Obj0 *p0, s32 p1)
{
    p0->m60 = (p0->m60 | 8);
    p0->m5C = p1;
}

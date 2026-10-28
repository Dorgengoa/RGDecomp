/* rgp:protos */
#define RGP_SELF_XformPairResetDelta_19a200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    u8 pad000[0x60];
    u128 m60;
    u128 m70;
    u8 pad080[0x20];
    u128 mA0;
};

void XformPairResetDelta_19a200(struct Obj0 *p0)
{
    p0->m60 = 0;
    p0->m70 = 0;
    VecSetOnes_13e180((struct Obj0 *)((u8 *)p0 + 0x80));
    VecSetOnes4_13e170((struct Obj0 *)((u8 *)p0 + 0x90));
    p0->mA0 = 0;
}

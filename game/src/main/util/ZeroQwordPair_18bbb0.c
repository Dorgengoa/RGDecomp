/* rgp:protos */
#define RGP_SELF_ZeroQwordPair_18bbb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    u128 m00;
    u128 m10;
};

struct Obj0 *ZeroQwordPair_18bbb0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m10 = 0;
    return p0;
}

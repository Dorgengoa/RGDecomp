/* rgp:protos */
#define RGP_SELF_BitArrayCtor_2d1bc0 1
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
    s32 m00;
    s32 m04;
};

struct Obj0 *BitArrayCtor_2d1bc0(struct Obj0 *p0)
{
    s32 r0;

    p0->m00 = 0;
    p0->m04 = 0;
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m00 = 0;
    p0->m04 = 0;
    r0 = (Zero12Bytes_42cfb0(p0), (s32)0);
    return p0;
}

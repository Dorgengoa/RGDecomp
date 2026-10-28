/* rgp:protos */
#define RGP_SELF_ActTimeAttrGetFlags_227740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u32 m00;
    u32 m04;
};

s64 ActTimeAttrGetFlags_227740(struct Obj0 *p0)
{
    return ((((s64)p0->m04) << 0x20) | p0->m00);
}

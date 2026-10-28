/* rgp:protos */
#define RGP_SELF_GsEnvSetAlpha_157140 1
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
    s64 m00;
};

struct Obj1 {
    u8 pad000[0x10];
    s64 m10;
};

void GsEnvSetAlpha_157140(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m10 = p1->m00;
}

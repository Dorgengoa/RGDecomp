/* rgp:protos */
#define RGP_SELF_TargetRefPairReset_337080 1
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
    u8 pad000[0x60];
    s32 m60;
    s32 m64;
};

void TargetRefPairReset_337080(struct Obj0 *p0)
{
    TargetRefClear_2e71d0(p0);
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0x30));
    p0->m60 = 0;
    p0->m64 = 3;
}

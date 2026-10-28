/* rgp:protos */
#define RGP_SELF_GsPktSetZWriteMask_13e430 1
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
    u8 pad000[0xE4];
    s32 mE4;
};

void GsPktSetZWriteMask_13e430(struct Obj0 *p0, s32 p1)
{
    s32 t0;

    p0->mE4 = p1;
    t0 = p0->mE4;
    GsZbufSetZMask_156ee0((struct Obj0 *)((u8 *)p0 + 0x10), t0);
}

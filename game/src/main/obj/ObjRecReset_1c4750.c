/* rgp:protos */
#define RGP_SELF_ObjRecReset_1c4750 1
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
    u8 pad000[0x24];
    s32 m24;
};

void ObjRecReset_1c4750(struct Obj0 *p0)
{
    p0->m24 = 0;
    ObjRecResetBase_1c47c0(p0);
}

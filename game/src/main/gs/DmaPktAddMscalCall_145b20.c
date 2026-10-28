/* rgp:protos */
#define RGP_SELF_DmaPktAddMscalCall_145b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047DE60;

void DmaPktAddMscalCall_145b20(s32 p0, s32 p1)
{
    DmaPktPushQword_141b60(p0, &D_0047DE60);
    DmaPktAddCallTag_141b80(p0, p1);
}

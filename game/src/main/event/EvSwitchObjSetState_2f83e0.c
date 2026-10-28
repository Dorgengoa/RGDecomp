/* rgp:protos */
#define RGP_SELF_EvSwitchObjSetState_2f83e0 1
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
    u8 pad000[0x158];
    u8 m158;
};

void EvSwitchObjSetState_2f83e0(struct Obj0 *p0, s32 p1)
{
    p0->m158 = p1;
    EvSwitchObjApplyState_2f8240(p0);
}

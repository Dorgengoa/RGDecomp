/* rgp:protos */
#define RGP_SELF_EvObjSwitchSetState_2f89d0 1
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
    u8 pad000[0xE0];
    u8 mE0;
};

void EvObjSwitchSetState_2f89d0(struct Obj0 *p0, s32 p1)
{
    p0->mE0 = p1;
    EvObjSwitchApplyState_2f8890(p0);
}

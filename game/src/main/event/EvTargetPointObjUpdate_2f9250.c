/* rgp:protos */
#define RGP_SELF_EvTargetPointObjUpdate_2f9250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EvTargetPointObjUpdate_2f9250(s32 p0)
{
    EvObjUpdateBase_2f9910(p0);
    TargetRefApplyToEventObj_2e6810((p0 + 0xA0), (p0 + 0x10));
}

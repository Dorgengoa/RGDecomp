/* rgp:protos */
#define RGP_SELF_CharaAimUpdate_20a780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaAimUpdate_20a780(s32 p0)
{
    s32 r0;

    r0 = GetCurrentScene_1f5be0();
    XformRecUpdateMaybe_1c5ee0((p0 + 0x500), r0);
    CharaAimCtrlUpdate_1d81b0((p0 + 0x4D0));
}

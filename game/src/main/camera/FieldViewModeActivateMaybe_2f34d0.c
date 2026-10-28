/* rgp:protos */
#define RGP_SELF_FieldViewModeActivateMaybe_2f34d0 1
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

s32 FieldViewModeActivateMaybe_2f34d0(void)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = FieldViewModeGet_2f35a0();
    rv3 = r0;
    if (r0 != 1) {
        r1 = FieldResetNpcDataStack_2f3560(0x33200);
        r2 = (FieldViewModeSet_2f3590(1), (s32)0);
        rv3 = r2;
    }
    return rv3;
}

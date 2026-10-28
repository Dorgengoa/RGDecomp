/* rgp:protos */
#define RGP_SELF_FieldViewModeReset_2f3510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FieldViewModeReset_2f3510(void)
{
    s32 r0;
    s32 rv5;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = FieldViewModeGet_2f35a0();
    rv5 = r0;
    if (r0 != 0) {
        r1 = FieldResetNpcDataStack_2f3560(0x26400);
        r2 = (FieldViewModeSet_2f3590(0), (s32)0);
        r3 = ((s32)GetInsectCageMgr_1fdb30());
        r4 = (InsectCageMgrSetEnabled_39b180(r3, 1), (s32)0);
        rv5 = r4;
    }
    return rv5;
}

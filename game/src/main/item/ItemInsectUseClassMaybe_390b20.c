/* rgp:protos */
#define RGP_SELF_ItemInsectUseClassMaybe_390b20 1
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

s32 ItemInsectUseClassMaybe_390b20(s32 p0)
{
    s32 r0;
    s32 rv4;
    s32 r1;
    s32 rv3;
    s32 r2;

    if (p0 == 0) {
        return -1;
    }
    r0 = ItemIsKindDId514_3d4530(p0);
    if (r0 != 0) {
        rv4 = 1;
    } else {
        r1 = ItemIsKindDId515_3d4570(p0);
        if (r1 != 0) {
            rv3 = 2;
        } else {
            r2 = ((unsigned char)ItemIsInsectFood_3d45b0(p0));
            rv3 = -((r2 & 0xFF) == 0);
        }
        rv4 = rv3;
    }
    return rv4;
}

/* rgp:protos */
#define RGP_SELF_InsectCageMenuSwitchCageCancel_38c930 1
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

s32 InsectCageMenuSwitchCageCancel_38c930(s32 p0, s32 p1)
{
    s32 r3;

    UiSetWidgetVisible_290010(p1, 0x7576, 0, -1);
    InsectCageMenuSetCursorVisible_389d00(0);
    UiSetWidgetVisible_290010(p1, 0x754E, 0, -1);
    r3 = InsectCageMenuSelectEntry_390d40(0x7532, 0);
    return 1;
}

/* rgp:protos */
#define RGP_SELF_InsectCageMenuMoveCageCancel_38d120 1
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

s32 InsectCageMenuMoveCageCancel_38d120(s32 p0, s32 p1)
{
    s32 r0;
    s32 r5;

    r0 = ((signed char)InsectCageGetType_3910c0());
    InsectCageMenuSetRowMarker_389a80(0, 1, r0, -1);
    UiSetWidgetVisible_290010(p1, 0x7576, 0, -1);
    UiSetWidgetVisible_290010(p1, 0x754E, 0, -1);
    InsectCageMenuSetCursorVisible_389d00(0);
    r5 = InsectCageMenuSelectEntry_390d40(0x7532, 0);
    return 1;
}

/* rgp:protos */
#define RGP_SELF_InsectCageMenuInfoOpen_38fd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuInfoOpen_38fd50(s32 p0, s32 p1)
{
    s32 r2;
    s32 r3;

    InsectCageMenuSetCursorVisible_389d00(0);
    UiSetWidgetVisible_290010(p1, 0xC350, 1, -1);
    r2 = InsectCageMenuGetCursorObj_390f70();
    r3 = (InsectCageMenuRefreshPreview_3896a0(r2), (s32)0);
    return 1;
}

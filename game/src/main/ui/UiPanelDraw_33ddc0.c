/* rgp:protos */
#define RGP_SELF_UiPanelDraw_33ddc0 1
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

s32 UiPanelDraw_33ddc0(s32 p0)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = ((unsigned char)Bit64Test_33de60(p0, 0));
    rv3 = 1;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        r1 = ((s32)UiPanelGetWidgetList_33e860(p0));
        r2 = (UiDrawWidgets_291910(r1), (s32)0);
        rv3 = 1;
    }
    return rv3;
}

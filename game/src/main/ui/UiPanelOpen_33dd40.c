/* rgp:protos */
#define RGP_SELF_UiPanelOpen_33dd40 1
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

void UiPanelOpen_33dd40(s32 p0)
{
    s32 r3;

    Bit64Assign_33de80(p0, 0, 1);
    Bit64Assign_33de80(p0, 1, 1);
    Bit64Assign_33de80(p0, 2, 1);
    r3 = ((s32)UiPanelGetWidgetList_33e860(p0));
    UiSetWidgetVisible_290010(r3, 1, 1, 1);
    Bit64Assign_33de80(p0, 3, 1);
    UiPanelReloadTimers_33e8c0(p0);
}

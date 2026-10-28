/* rgp:protos */
#define RGP_SELF_UiPanelResetWidgets_33e970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Straight-line re-bind of an object's three sub-handles. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void UiPanelResetWidgets_33e970(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;

    r0 = ((s32)UiPanelGetWidgetList_33e860(p0));
    UiWidgetListReset_2912e0(r0);
    r1 = ((s32)UiPanelGetWidgetList_33e860(p0));
    r2 = UiPanelGetWidgetPoolSize_33e950(p0);
    UiInitWidgetPool_290390(r1, r2, 0x23);
    r3 = ((s32)UiPanelGetWidgetList_33e860(p0));
    r4 = UiPanelGetWidgetDefs_33e960(p0);
    UiAddWidgets_2901d0(r3, r4, 0);
    r5 = UiPanelGetTexGroup_33ea90(p0);
    r6 = ((s32)UiPanelGetWidgetList_33e860(p0));
    *(s32 *)(r6 + 0x8) = r5;
}

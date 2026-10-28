/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadSlotListEnterCb_4f61d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F61D0 (124 bytes, 31 instructions, 5 calls) -- the sibling of
 * insmenu_InsectVsTeamListEnterCb_4f4fd0 with a different pane id and a different tail.
 */

typedef struct Pane Pane;
struct Pane {
    u8 pad00[0xA];
    s16 field00A;
    u8 pad00C[0x2];
    s16 field00E;
    u8 pad010[0x2];
    s16 field012;
    u8 pad014[0x2];
    s16 field016;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadSlotListEnterCb_4f61d0(Pane *o, void *w)
{
    o->field00E = 0x31;
    o->field00A = 2;
    SaveUiWidgetFadeIn_37b490(0x890D);
    insmenu_InsectVsLoadSlotCursorBob_4f6810(o, w, 1);
    insmenu_InsectVsSaveHighlightOption_4f6bb0(o->field012);
    SaveUiScrollBarThumbPlace_3777a0(o, 0x890C, 0);
    insmenu_InsectVsSaveListRefresh_4ebc30(o->field016, 0);
    return 1;
}

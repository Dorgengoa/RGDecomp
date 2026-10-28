/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadSlotListCancel_4f5f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F5F30 -- two calls, return 1. */
extern u8 insmenu_D_004FA1A0[];
/*rgp*/
/*rgp*/
s32 insmenu_InsectVsLoadSlotListCancel_4f5f30(void)
{
    insmenu_InsectVsLoadWidgetsFade_4f6ac0(2);
    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88B9, 0);
    return 1;
}

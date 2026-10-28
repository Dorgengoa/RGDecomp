/* rgp:protos */
#define RGP_SELF_title_TitleLoadSlotListCancel_4ee8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE8C0 -- two calls, one to a sibling overlay
 * function and one into main, then return 1.
 */

extern void *D_004841E8;
/*rgp*/
/*rgp*/

s32 title_TitleLoadSlotListCancel_4ee8c0(void)
{
    title_TitleLoadFadeWidgets_4eda30(2);
    UiEntryListSelectByTag_28ea90(D_004841E8, 0x7532, 0);
    return 1;
}

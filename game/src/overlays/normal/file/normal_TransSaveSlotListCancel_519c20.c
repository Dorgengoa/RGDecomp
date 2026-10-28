/* rgp:protos */
#define RGP_SELF_normal_TransSaveSlotListCancel_519c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519C20 -- three-call entry, returns 1.  `$4` is never read. */

extern void *D_004847D8;          /* gp - 0x998 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveSlotListCancel_519c20(void)
{
    PlayMenuSeThunk_289ef0(6);
    normal_TransSavePanelFade_518700(2);
    UiEntryListSelectByTag_28ea90(D_004847D8, 2, 0);
    return 1;
}

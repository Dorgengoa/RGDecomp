/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadCardScanEnterCb_4f6410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F6410 (80 bytes, 20 instructions, 5 calls) -- leave the detail
 * pane: drop the page, clear every selector, reset the flag.  The `sb $0` is
 * written BEFORE the call it shares a delay slot with.
 */

extern u8 D_00484390;       /* gp - 0xDE0 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadCardScanEnterCb_4f6410(void)
{
    SaveUiHideWidget_37b460(0x890D);
    SaveSlotRecordsClear_37b800(-1);
    insmenu_InsectVsSaveListRefresh_4ebc30(0, 0);
    D_00484390 = 0;
    SaveMgrSetMode_37b9e0(0);
    insmenu_InsectVsSaveShowMsg_4f6e00(3, 0, -1);
    return 1;
}

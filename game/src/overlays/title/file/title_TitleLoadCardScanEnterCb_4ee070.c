/* rgp:protos */
#define RGP_SELF_title_TitleLoadCardScanEnterCb_4ee070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE070 -- a straight run of six calls with constant
 * arguments and one byte store that rides in a call's delay slot.
 */

extern u8 D_0048421C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadCardScanEnterCb_4ee070(void)
{
    SaveUiHideWidget_37b460(0x43);
    SaveSlotRecordsClear_37b800(-1);
    title_TitleLoadSlotListRefreshMaybe_4edeb0(0);
    D_0048421C = 0;
    SaveMgrSetMode_37b9e0(0);
    title_TitleLoadShowMsg_4eeb60(3);
    title_TitleSetNoAnalogPause_4f13b0(1);
    return 1;
}

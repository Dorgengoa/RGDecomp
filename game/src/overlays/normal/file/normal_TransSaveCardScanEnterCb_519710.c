/* rgp:protos */
#define RGP_SELF_normal_TransSaveCardScanEnterCb_519710 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519710 -- leaves the shop's browse mode: drops the held item,
 * re-arms the 0x75A2 cursor and returns to phase 3.  Pass-33 LIST rank:
 * 60 bytes, 15 instructions, ZERO branches, 4 calls -- a registration LIST.
 *
 * `D_0048480C = 0;` is written BEFORE func_37B460 in the source, which is what
 * sinks its `sb` into that call's delay slot. */

extern s8 D_0048480C;             /* gp - 0x964 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 normal_TransSaveCardScanEnterCb_519710(void);

s32 normal_TransSaveCardScanEnterCb_519710(void)
{
    SaveSlotRecordsClear_37b800(-1);
    D_0048480C = 0;
    SaveUiHideWidget_37b460(0x75A2);
    SaveMgrSetMode_37b9e0(0);
    normal_TransSaveShowMsg_519ff0(3);
    return 1;
}

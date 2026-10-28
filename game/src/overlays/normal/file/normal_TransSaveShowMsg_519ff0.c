/* rgp:protos */
#define RGP_SELF_normal_TransSaveShowMsg_519ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519FF0 -- leaf tail call, gp handle in slot two. */

extern void *D_00484714;          /* gp - 0xA5C */

/*rgp*/

void normal_TransSaveShowMsg_519ff0(s32 a)
{
    SaveMsgBoxShowSlotInfo_376b60(a, D_00484714, 0, (long long)(-1));
}

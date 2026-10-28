/* rgp:protos */
#define RGP_SELF_HeadLookBindNodes_1c5b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void HeadLookBindNodes_1c5b70(void *arg0, s32 arg1, s64 arg2, s32 arg3)
{
    s32 *temp_16;
    s32 *temp_17;
    s32 temp_2;

    *(s16 *)((u8 *)arg0 + 0x46) = (s16) arg2;
    temp_2 = ((s32)ObjRecGetLiveObject_1c4a90(arg1, (int)((s64) (arg2 << 0x30) >> 0x30)));
    if (temp_2 == 0) {
        return;
    }
    temp_17 = ((s32 *)ObjFindNthAttachPoint_1addc0(temp_2, 5, 0));
    temp_16 = ((s32 *)ObjFindNthAttachPoint_1addc0(temp_2, 6, 0));
    if (temp_17 == NULL || temp_16 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x20) = ((s32)ModelGetFrame_1511f0(temp_2, *temp_17));
    *(s32 *)((u8 *)arg0 + 0x24) = ((s32)ModelGetFrame_1511f0(temp_2, *temp_16));
    *(s32 *)((u8 *)arg0 + 0x28) = ((s32)ModelGetFrame_1511f0(temp_2, ModelFindFrameIndexByName_151220(temp_2, arg3)));
}

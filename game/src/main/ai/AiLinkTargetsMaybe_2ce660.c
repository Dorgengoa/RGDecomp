/* rgp:protos */
#define RGP_SELF_AiLinkTargetsMaybe_2ce660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T002ce660 {
    u8 pad0[0x148];
    s16 unk148;
} T002ce660;

/*rgp*/
/*rgp*/

s16 AiLinkTargetsMaybe_2ce660(s16 arg0, s16 arg1, s32 arg2)
{
    T002ce660 *temp_20;
    T002ce660 *temp_16;

    temp_20 = ((T002ce660 *)CharaGetAiById_2cedd0(arg0));
    temp_16 = ((T002ce660 *)CharaGetAiById_2cedd0(arg1));
    if (temp_20 != NULL && temp_16 != NULL) {
        temp_20->unk148 = arg1;
        AiLinkListPushMaybe_2bb560(temp_16, arg0);
        if (arg2 == 1) {
            temp_16->unk148 = arg0;
        } else {
            if (arg2 == 2) {
                if (temp_16->unk148 < 0) {
                    temp_16->unk148 = arg0;
                }
            }
        }
        return arg1;
    }
    return -1;
}

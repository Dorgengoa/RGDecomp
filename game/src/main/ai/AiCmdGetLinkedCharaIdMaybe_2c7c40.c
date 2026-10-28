/* rgp:protos */
#define RGP_SELF_AiCmdGetLinkedCharaIdMaybe_2c7c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004DB928[0x400];

s32 AiCmdGetLinkedCharaIdMaybe_2c7c40(s32 arg0, s32 arg1) {
    s32 temp_16;
    void *temp_2;
    void *temp_2_2;

    if (arg1 == 1) {
        temp_2 = CharaGetAiById_2cedd0((*(s32 *)D_004DB928));
        if (temp_2 == NULL) {
            ScriptSlotStoreIntRef_2cc900(arg0, -1);
            goto gpt_return;
            goto gpt_return;
        } else {
            ScriptSlotStoreIntRef_2cc900(arg0, *(s16 *)((u8 *)temp_2 + 0x148));
            return 1;
            return 1;
        }
    } else if (arg1 == 2) {
        temp_16 = arg0 + 8;
        temp_2_2 = CharaGetAiById_2cedd0(ScriptSlotGetInt_2cc9c0((void *)arg0));
        if (temp_2_2 == NULL) {
            ScriptSlotStoreIntRef_2cc900(temp_16, -1);
            return 1;
            return 1;
        } else {
            ScriptSlotStoreIntRef_2cc900(temp_16, *(s16 *)((u8 *)temp_2_2 + 0x148));
            goto gpt_return;
            return 1;
        }
    }
    goto gpt_return;

gpt_return: return 1;
}

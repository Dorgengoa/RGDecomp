/* rgp:protos */
#define RGP_SELF_AiCmdGetTargetCharaId_2c7cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB930[0x100];

s32 AiCmdGetTargetCharaId_2c7cf0(s64 *arg0, s32 arg1)
{
    s32 t;

    if (arg1 == 1) {
        if (D_004DB930[0] == 0) {
            return 0;
        }
        ScriptSlotStoreIntRef_2cc900((s32)arg0, AiGetTargetCharaId_2c0fd0(D_004DB930[0]));
    } else if (arg1 == 2) {
        t = CharaGetAiById_2cedd0(ScriptSlotGetInt_2cc9c0((s32)arg0++));
        if (t == 0) {
            return 0;
        }
        ScriptSlotStoreIntRef_2cc900((s32)arg0, AiGetTargetCharaId_2c0fd0(t));
    }
    return 1;
}

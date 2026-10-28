/* rgp:protos */
#define RGP_SELF_AiScriptResume_2c15f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad3C[0x3C];
    s32 unk3C;
} S002c15f0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB920;
extern s32 D_004DB928;
extern s32 D_004DB92C;
extern s32 D_004DB930;
extern s32 D_004DB974;
extern s32 D_004DB978;

s32 AiScriptResume_2c15f0(S002c15f0 *arg0, s32 arg1) {
    s32 temp_18;
    s32 temp_2;

    temp_18 = GetCurrentScene_1f5be0();
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), arg1));
    if (temp_2 == 0) {
        return 0;
    }
    *(s32 *)&D_004DB920 = temp_18;
    *(s32 *)&D_004DB92C = temp_2;
    *(s32 *)&D_004DB930 = ((s32)CharaGetAi_214a10(temp_2));
    *(s32 *)&D_004DB928 = arg1;
    *(s32 *)&D_004DB974 = 0;
    *(s32 *)&D_004DB978 = 0;
    ScriptVmResume_176ab0(arg0);
    return arg0->unk3C;
}

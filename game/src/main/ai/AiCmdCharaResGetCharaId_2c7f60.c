/* rgp:protos */
#define RGP_SELF_AiCmdCharaResGetCharaId_2c7f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB928;

s32 AiCmdCharaResGetCharaId_2c7f60(s32 arg0, s32 arg1) {
    s32 temp_18;
    s16 var_17;
    s32 temp_4;
    s32 var_16;
    u8 *var_2;

    var_16 = arg0;
    temp_18 = ((s32)GetCharaResMgr_1fdb60());
    var_17 = -1;
    if (arg1 == 1) {
        var_2 = CharaResFindById_1f0530(temp_18, D_004DB928);
        if (var_2 != NULL) {
            goto block_5;
        }
    } else if (arg1 == 2) {
        temp_4 = var_16;
        var_16 += 8;
        var_2 = CharaResFindById_1f0530(temp_18, ScriptSlotGetInt_2cc9c0(temp_4));
        if (var_2 != NULL) {
block_5:
            var_17 = *(s16 *)(var_2 + 0x2);
        }
    }
    ScriptSlotStoreIntRef_2cc900(var_16, var_17);
    return 1;
}

/* rgp:protos */
#define RGP_SELF_AiCmdTargetInReachMaybe_2c6d30 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB92C[];
extern f32 D_0045B080[];

s32 AiCmdTargetInReachMaybe_2c6d30(s32 arg0)
{
    u8 sp60[0x10] __attribute__((aligned(16)));
    u8 sp50[0x10] __attribute__((aligned(16)));
    s32 temp_17;
    s32 temp_16;

    temp_17 = D_004DB92C[0];
    CharaGetPos_2388a0(temp_17, &sp60);
    CharaGetRot_2388b0(temp_17, &sp50);
    temp_16 = ((s32)CharaGetFrontTargetRefMaybe_214a20(temp_17));
    if (TargetFindInFrontMaybe_2d0aa0(temp_16, &sp60, *(f32 *)&sp50[4],
                      CharaGetCollRadius_2386a0(temp_17) + 1.5f * D_0045B080[0]) != 0) {
        ScriptSlotStoreIntRef_2cc900(arg0, 1);
    } else {
        ScriptSlotStoreIntRef_2cc900(arg0, 0);
    }
    return 0;
}

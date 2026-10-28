/* rgp:protos */
#define RGP_SELF_AiCmdCharaGetRot_2c9530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB92C[];

s32 AiCmdCharaGetRot_2c9530(s32 arg0, s32 arg1)
{
    f32 sp20[4] __attribute__((aligned(16)));

    if (D_004DB92C[0] == 0) {
        return 0;
    }
    switch (arg1) {
    case 1:
        CharaGetRot_2388b0(D_004DB92C[0], sp20);
        ScriptSlotStoreFloatRef_2cc8e0(arg0, sp20[1]);
        break;
    case 3:
        CharaGetRot_2388b0(D_004DB92C[0], sp20);
        ScriptSlotStoreVec3_2cc8a0(arg0, sp20);
        break;
    default:
        return 0;
    }
    return 1;
}

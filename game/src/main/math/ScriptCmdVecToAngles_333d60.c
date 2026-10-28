/* rgp:protos */
#define RGP_SELF_ScriptCmdVecToAngles_333d60 1
#include "port/game_protos.h"
#line 1

#include "types.h"


/*rgp*/
extern f32 sqrtf(f32);
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdVecToAngles_333d60(s64 *arg0, s32 arg1)
{
    f32 sp40[4] __attribute__((aligned(16)));
    f32 temp_f12;
    f32 temp_f20;
    s32 temp_17;

    if ((arg1 != 4) && (arg1 != 6)) {
        return 0;
    }
    ScriptSlotsToVec4_334810(sp40, (s32)arg0);
    arg0 += 3;
    VecNormalize_13bd90(sp40, sp40);
    temp_f20 = Atan2f_1291a8(sp40[0], sp40[2]);
    temp_f12 = -Atan2f_1291a8(sp40[1], sqrtf(sp40[0] * sp40[0] + sp40[2] * sp40[2]));
    switch (arg1) {
    case 4:
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, temp_f20);
        goto gpt_return;
    case 6:
        ScriptSlotStoreFloatRef_3347d0((s32)arg0++, temp_f12);
        ScriptSlotStoreFloatRef_3347d0((s32)arg0++, temp_f20);
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, 0.0f);
        break;
    default:
        return 0;
    }
    goto gpt_return;

gpt_return: return 1;
}

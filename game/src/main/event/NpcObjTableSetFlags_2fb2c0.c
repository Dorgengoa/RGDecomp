/* rgp:protos */
#define RGP_SELF_NpcObjTableSetFlags_2fb2c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void NpcObjTableSetFlags_2fb2c0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_18;
    s32 var_18;
    s32 var_17;
    s32 temp_2;

    *(s16 *)(arg0 + 0x222) = *(s16 *)(arg0 + 0x220);
    InsectCageMgrReleaseAll_39a2e0(((s32)GetInsectCageMgr_1fdb30()));
    if (arg2 != 0) {
        *(s16 *)(arg0 + 0x220) |= (s16)arg1;
        if (arg1 & 4) {
            var_18 = *(s32 *)(arg0 + 0x4);
            for (var_17 = 0; var_17 < *(s16 *)(arg0 + 0x8); var_17++, var_18 += 0xE0) {
                NpcObjResetSlot_2fb8b0(var_18);
            }
            temp_18 = ((s32)GetStaticScene_1c6c70());
            temp_2 = ((s32)GetCharaResMgr_1fdb60());
            if (temp_2 != 0) {
                CharaResReleaseAllNpc_1f1070(temp_2, temp_18);
                CharaResReleaseHeapData_1f0f70(temp_2);
                *(u16 *)(arg0 + 0x218) = 0;
            }
        }
    } else {
        *(s16 *)(arg0 + 0x220) &= (s16)~arg1;
    }
}

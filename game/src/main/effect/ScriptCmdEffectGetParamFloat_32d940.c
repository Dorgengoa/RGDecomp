/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectGetParamFloat_32d940 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode on

/*rgp*/                                 /* extern */
/*rgp*/                           /* extern */
/*rgp*/               /* extern */
/*rgp*/                           /* extern */
/*rgp*/                              /* extern */
extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamFloat_32d940(s64 *arg0, s32 arg1) {
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(s32[4])]; char m1[0x1c + sizeof(f32)]; char m2[0x14]; char m3[0x20]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(s32[4]) <= (0x1c) && (0x0) >= 0 ? 1 : -1];
    
    s32 temp_18;
    s32 temp_2;
    s32 var_3;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    var_3 = 0;
    switch (arg1) {
    case 2:
        var_3 = D_004826E0;
        break;
    case 3:
        var_3 = D_004826E0;
        break;
    }
    if (var_3 == 0) {
        return 0;
    }
    (*(f32 *)(rgp_blk1 + 0x1c)) = 0;
    temp_18 = ScriptSlotGetInt_3348b0(arg0++);
    if (D_004826E0 == 0) {
        return 0;
    }
    temp_2 = ((s32)GetEffectMgr_2d9040());
    if (temp_2 == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0((u8 *)(*(s32 (*)[4])(rgp_blk1 + 0x0)), D_004826E0);
    EffectGetParamFloat_2e0460(temp_2, (u8 *)(*(s32 (*)[4])(rgp_blk1 + 0x0)), temp_18, &(*(f32 *)(rgp_blk1 + 0x1c)));
    ScriptSlotStoreFloatRef_3347d0(arg0, (*(f32 *)(rgp_blk1 + 0x1c)));
    return 1;
}

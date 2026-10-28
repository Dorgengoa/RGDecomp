/* rgp:protos */
#define RGP_SELF_CharaCmdSetShipPos_22d430 1
#include "port/game_protos.h"
#line 1
/* PARK 1/3: length-wrong (76w vs retail 75w, ours LONGER), close. Rewrote the m2c goto/block_13 shared-tail as separate returns (lesson from EventPathTemplateAddPath_300b90) but still off by 1 word. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047E6A0;
extern f32 D_0047E6A4;
extern f32 D_0047E6A8;
extern f32 D_0047E6AC;

s32 CharaCmdSetShipPos_22d430(s32 *arg0, s32 arg1, s32 arg2) {
    f32 sp60[0x10] __attribute__((aligned(16)));
    f32 sp50[4] __attribute__((aligned(16)));
    s32 temp_2;
    s32 temp_2_2;

    if ((arg2 != 0) && (arg2 != 3)) {
        return 0;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == 0) {
        return 1;
    }
    temp_2_2 = MapGetAreaSlot1_1e5750(((s32)GetMapMgr_201a90()));
    if ((temp_2_2 == 0) || (((unsigned char)MapDataIsLoaded_1e79d0(temp_2_2)) == 0)) return 1;
    MapDataGetMatrix_1e7670(temp_2_2, sp60);
    sp50[0] = D_0047E6A0;
    sp50[1] = D_0047E6A4;
    sp50[2] = D_0047E6A8;
    sp50[3] = D_0047E6AC;
    if (arg2 == 3) {
        sp50[0] = ScriptArgGetFloat_302cf0(arg1);
        sp50[1] = ScriptArgGetFloat_302cf0(arg1 + 5);
        sp50[2] = ScriptArgGetFloat_302cf0(arg1 + 0xA);
    }
    MatMulPoint_1cb8e0(sp50, sp60, sp50);
    CharaSetPos_213a40(temp_2, sp50);
    return 1;
}

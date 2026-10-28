/* rgp:protos */
#define RGP_SELF_AiCmdCharaSetPosById_2c9ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdCharaSetPosById_2c9ee0(s64 *arg0, s32 arg1) {
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    s32 temp_16;
    s32 temp_2;

    if (arg1 != 4) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[0] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[1] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    (*(f32 (*)[3])(rgp_blk1 + 0x0))[2] = ScriptSlotGetFloat_2cc9a0((s32)arg0);
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), temp_16));
    if (temp_2 != 0) {
        CharaSetPosVec_2387a0(temp_2, (*(f32 (*)[3])(rgp_blk1 + 0x0)));
    }
    return 1;
}

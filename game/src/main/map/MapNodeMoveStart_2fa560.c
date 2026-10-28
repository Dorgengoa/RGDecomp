/* rgp:protos */
#define RGP_SELF_MapNodeMoveStart_2fa560 1
#include "port/game_protos.h"
#line 1
/* PARK 1/3: length-wrong (81w vs retail 80w, ours LONGER), close. */
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
/*rgp*/
/*rgp*/

void MapNodeMoveStart_2fa560(u8 *arg0, s32 arg1) {
    u8 sp70[16] __attribute__((aligned(16)));
    u8 sp60[16] __attribute__((aligned(16)));
    u8 sp50[16] __attribute__((aligned(16)));
    u8 sp40[16] __attribute__((aligned(16)));
    s32 temp_2;
    s32 temp_3;
    u8 *temp_4;

    *(s32 *)(arg0 + 0x48) = -1;
    if ((arg1 != 0) && (temp_2 = MapFindObjInAreaById_1e44b0(((s32)GetMapMgr_201a90()), *(s32 *)(arg0 + 0x24), arg0 + 0x28), (temp_2 != 0))) {
        *(s32 *)(arg0 + 0x48) = MapNodeMoveReqGetFrames_2fa8b0(arg1);
        MapNodeMoveReqGetPos_2fa8a0(arg1, sp70);
        MapNodeMoveReqGetRot_2fa890(arg1, sp50);
        if (!(*(s32 *)(arg0 + 0x48) > 0)) {
            *(s32 *)(arg0 + 0) = 0;
            *(s32 *)(arg0 + 4) = 0;
            *(s32 *)(arg0 + 8) = 0;
            *(s32 *)(arg0 + 0xC) = 0;
            *(s32 *)(arg0 + 0x10) = 0;
            *(s32 *)(arg0 + 0x14) = 0;
            *(s32 *)(arg0 + 0x18) = 0;
            *(s32 *)(arg0 + 0x1C) = 0;
            NodeSetTranslation_1866b0(temp_2, sp70);
            NodeSetRotation_186620(temp_2, sp50);
            *(s32 *)(arg0 + 0x48) = -1;
        } else {
            NodeGetTranslation_186650(temp_2, sp60);
            NodeGetRotation_1865e0(temp_2, sp40);
            VecSubXyzW0_1cbce0(arg0, sp70, sp60);
            VecSubXyzW0_1cbce0(arg0 + 0x10, sp50, sp40);
            temp_3 = *(s32 *)(arg0 + 0x48);
            if (temp_3 > 0) {
                VecDivScalar_1cbbf0(arg0, arg0, (f32) temp_3);
                temp_4 = arg0 + 0x10;
                VecDivScalar_1cbbf0(temp_4, temp_4, (f32) *(s32 *)(arg0 + 0x48));
            }
        }
    }
}

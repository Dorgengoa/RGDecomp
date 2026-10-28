/* rgp:protos */
#define RGP_SELF_ScriptCmdGetObjAttachPointPos_3323b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdGetObjAttachPointPos_3323b0(s32 arg0, s32 arg1) {
    s32 temp_2_2;
    s32 temp_2;
    s32 temp_16;
    u8 sp40[0x10] __attribute__((aligned(16)));

    if (arg1 != 6) {
        return 0;
    }
    temp_2 = (s32)GetCurrentScene_1f5be0();
    if (temp_2 == 0) {
        return 0;
    }
    temp_2_2 = ((s32)ObjRecGetLiveObject_1c4a90(temp_2, ScriptSlotGetInt_3348b0(arg0)));
    if (temp_2_2 == 0) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_3348b0(arg0 + 8);
    if (!(((s32)ObjGetNthAttachPointPos_1ade20(temp_2_2, temp_16, ScriptSlotGetInt_3348b0(arg0 + 0x10), sp40)) != 0)) {
        return 0;
    }
    ScriptSlotStoreVec3_334790(arg0 + 0x18, sp40);
    return 1;
    return 0;
}

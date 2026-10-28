/* rgp:protos */
#define RGP_SELF_ScriptCmdGetNodeIndex_333670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdGetNodeIndex_333670(s64 *arg0) {
    s32 temp_16_2;
    s32 temp_2;
    s32 temp_17;
    s32 temp_16;

    temp_17 = GetCurrentScene_1f5be0();
    temp_16 = ScriptSlotGetInt_3348b0((s32)arg0++);
    temp_16_2 = ScriptSlotGetCodeAddr_334870((s32)arg0++);
    temp_2 = ((s32)ObjRecGetLiveObject_1c4a90(temp_17, temp_16));
    if (temp_2 == 0) {
        return 0;
    }
    ScriptSlotStoreIntRef_3347f0((s32)arg0, ModelFindFrameIndexByName_151220(temp_2, temp_16_2));
    return 1;
}

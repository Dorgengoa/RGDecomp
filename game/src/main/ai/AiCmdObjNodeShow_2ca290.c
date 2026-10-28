/* rgp:protos */
#define RGP_SELF_AiCmdObjNodeShow_2ca290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004DB920[0x400];

s32 AiCmdObjNodeShow_2ca290(s32 arg0) {
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_2;
    s8 v;
    void *temp_2_2;

    temp_16 = (*(s32 *)D_004DB920);
    temp_2 = ((s32)ObjRecGetLiveObject_1c4a90(temp_16, ScriptSlotGetInt_2cc9c0(arg0)));
    if (temp_2 == 0) {
        return 0;
    }
    temp_16_2 = ModelGetRootFrame_1511a0(temp_2);
    temp_2_2 = FrameFindByName_149ed0(temp_16_2, ScriptSlotGetCodeAddr_2cc980(arg0 + 8));
    if (temp_2_2 == NULL) {
        return 0;
    }
    if (ScriptSlotGetInt_2cc9c0(arg0 + 0x10) != 0) {
        v = 1;
    } else {
        v = 2;
    }
    *(s8 *)((u8 *)temp_2_2 + 0x24) = v;
    return 1;
    return 0;
}

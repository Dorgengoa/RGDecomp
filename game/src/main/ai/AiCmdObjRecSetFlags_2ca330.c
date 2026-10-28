/* rgp:protos */
#define RGP_SELF_AiCmdObjRecSetFlags_2ca330 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004DB920[0x400];

s32 AiCmdObjRecSetFlags_2ca330(s32 arg0, s32 arg1)
{
    s32 var_2;
    s32 temp_19;
    s32 temp_18;
    s32 temp_17;
    s32 temp_16;
    s32 temp_4;

    temp_19 = (*(s32 *)D_004DB920);
    temp_16 = arg0;
    temp_4 = temp_16;
    temp_16 += 8;
    temp_18 = ScriptSlotGetInt_2cc9c0(temp_4);
    temp_4 = temp_16;
    temp_16 += 8;
    temp_17 = ScriptSlotGetInt_2cc9c0(temp_4);
    var_2 = 1;
    if (arg1 >= 3) {
        temp_4 = temp_16;
        temp_16 += 8;
        var_2 = ScriptSlotGetInt_2cc9c0(temp_4);
    }
    if (var_2 != 0) {
        ObjRecSetFlags_1c3e00(temp_19, 1, temp_18, temp_17);
    } else {
        ObjRecClearFlags_1c3dc0(temp_19, 1, temp_18, temp_17);
    }
    return 1;
}

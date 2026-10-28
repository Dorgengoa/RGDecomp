/* rgp:protos */
#define RGP_SELF_NavCfgCmdAddEdge_30a770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00452330[0x10];
extern s32 D_0048296C;

s32 NavCfgCmdAddEdge_30a770(s32 arg0, s32 arg1) {
    s32 temp_18;
    s32 temp_2;
    s32 temp_2_2;

    if ((arg1 < 2) && (arg1 > 4)) {
        return 0;
    }
    if (D_0048296C == 0) {
        return 1;
    }
    temp_18 = VariantGetInt_30ab50(arg0);
    temp_2 = NavGraphAddEdge_30f450(D_0048296C, temp_18, VariantGetInt_30ab50(arg0 + 8), 0);
    if (temp_2 < 0) {
        return 1;
    }
    temp_2_2 = ((s32)NavGraphGetEdge_310c20(D_0048296C, temp_2));
    if (temp_2_2 == 0) {
        return 1;
    }
    if (arg1 == 3) {
        NavEdgeSetFlags_311650(temp_2_2, ParseFlagNames_1ca700(ScriptArgGetStr_30aaf0(arg0 + 0x10), D_00452330, 0));
    } else if (arg1 == 4) {
        NavEdgeSetFlags_311650(temp_2_2, ParseFlagNames_1ca700(ScriptArgGetStr_30aaf0(arg0 + 0x10), D_00452330, 0));
        NavEdgeSetCost_311640(temp_2_2, VariantGetFloat_30ab10(arg0 + 0x18));
    }
    return 1;
}

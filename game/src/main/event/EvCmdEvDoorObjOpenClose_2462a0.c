/* rgp:protos */
#define RGP_SELF_EvCmdEvDoorObjOpenClose_2462a0 1
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
extern u8 D_0045EAE0[];
extern u8 D_0045EAE8[];
extern u8 D_0045EAF0[];
extern u8 D_0045EAF8[];

s32 EvCmdEvDoorObjOpenClose_2462a0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 var_18;
    s32 temp_17;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    temp_2 = ScriptGetCodeAddr_249050(arg0 + 8);
    if (temp_2 == 0) {
        return 1;
    }
    var_18 = 0;
    if (arg1 >= 3) {
        var_18 = ScriptGetInt_2490f0(arg0 + 0x10) != 0;
    }
    temp_17 = ((s32)GetEventObjMgr_2d1960());
    if (!(((unsigned char)StrEqualNoCase_1ca610(temp_2, D_0045EAE0)) == 0)) {
    EvDoorObjOpenByName_2e8f30(temp_17, ScriptGetCodeAddr_249050(arg0), var_18);
    } else {
        if (((unsigned char)StrEqualNoCase_1ca610(temp_2, D_0045EAE8)) != 0) {
            EvDoorObjSetOpenedByName_2e8e70(temp_17, ScriptGetCodeAddr_249050(arg0), var_18);return 1;
        } else {
            if (((unsigned char)StrEqualNoCase_1ca610(temp_2, D_0045EAF0)) != 0) {
                EvDoorObjCloseByName_2e8e30(temp_17, ScriptGetCodeAddr_249050(arg0));return 1;
            } else {
                if (((unsigned char)StrEqualNoCase_1ca610(temp_2, D_0045EAF8)) != 0) {
                    EvDoorObjSetClosedByName_2e8d80(temp_17, ScriptGetCodeAddr_249050(arg0));
                } else {return 1;}
            }
        }
    }
    return 1;
}

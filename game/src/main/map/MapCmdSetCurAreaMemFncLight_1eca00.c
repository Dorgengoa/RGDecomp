/* rgp:protos */
#define RGP_SELF_MapCmdSetCurAreaMemFncLight_1eca00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044B390[0x20];
extern u8 D_0044B3B0[0x20];
extern u8 D_0044B3D0[0x20];
extern s32 D_004818FC;

s32 MapCmdSetCurAreaMemFncLight_1eca00(s32 arg0, s32 arg1)
{
    s32 a;

    if (arg1 != 2 && arg1 != 4) {
        return 0;
    }
    if (D_004818FC == 0) {
        return 1;
    }
    a = LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0), D_0044B390, 0);
    MapDataSetMemFncFlags_1e74c0(D_004818FC, a | LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 8), D_0044B3B0, 0));
    if (arg1 == 4) {
        MapDataSetLightRef_1e74a0(D_004818FC, LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x10), D_0044B3D0, 0));
        MapDataSetDefaultLightSet_1e7490(D_004818FC, ScriptArgGetInt_1ecbe0(arg0 + 0x18));
    }
    return 1;
}

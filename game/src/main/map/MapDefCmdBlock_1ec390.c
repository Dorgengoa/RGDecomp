/* rgp:protos */
#define RGP_SELF_MapDefCmdBlock_1ec390 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044B390[0x400];
extern u8 D_0044B3B0[0x400];
extern u8 D_0044B3D0[0x400];
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;
extern s16 D_00481908;
extern s16 D_0048190C;

s32 MapDefCmdBlock_1ec390(s32 arg0, s32 arg1)
{
    u8 sp40[0x10] __attribute__((aligned(16)));
    s32 temp_17;
    s32 temp_18;
    s32 temp_5;
    void *temp_2;

    if (arg1 != 6) {
        return 0;
    }
    if ((D_004818FC == 0) || (D_004818F8 == 0)) return 1;
    temp_2 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    temp_5 = *(s32 *)((u8 *)temp_2 + 0x44);
    if ((temp_5 == 0) || (*(s16 *)((u8 *)temp_2 + 0x3A) <= D_00481904)) return 1;
    temp_18 = temp_5 + (D_00481904 * 0xCC);
    MapDataSetId_1e74e0(temp_18, ScriptArgGetInt_1ecbe0(arg0));
    MapDataSetName_1e7500(temp_18, ((s32)MemStackStrDup_14cff0(ScriptArgGetStr_1ecb80(arg0 + 8), D_004818F8)));
    MapDataSetFileName_1e74f0(temp_18, MapDataGetName_1e7bf0(temp_18));
    temp_17 = LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x10), &(*(u8 *)D_0044B390), 0);
    MapDataSetMemFncFlags_1e74c0(temp_18, temp_17 | LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x18), &(*(u8 *)D_0044B3B0), 0));
    MapDataSetKeyMaybe_1e74d0(temp_18, ((short)MapDataGetId_1e7bd0(temp_18)));
    MapDataSetLightRef_1e74a0(temp_18, LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x20), &(*(u8 *)D_0044B3D0), 0));
    MapDataSetDefaultLightSet_1e7490(temp_18, ScriptArgGetInt_1ecbe0(arg0 + 0x28));
    MapDataGetColorVec4_1e7610(D_004818FC, sp40);
    MapDataSetColorVec_1e73b0(temp_18, sp40);
    D_00481908 = 0;
    D_0048190C = 0;
    return 1;
    return 1;
}

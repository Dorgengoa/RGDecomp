/* rgp:protos */
#define RGP_SELF_MapDefCmdShare_1ec540 1
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
extern u8 D_0044B390[0x20];
extern u8 D_0044B3B0[0x20];
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481900;

s32 MapDefCmdShare_1ec540(s32 arg0, s32 arg1)
{
    u8 sp60[16] __attribute__((aligned(16)));
    u8 *info;
    s32 base;
    s32 rec;
    s32 a;
    s32 b;
    s32 c;
    s32 f;

    if (arg1 != 4 && arg1 != 9) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    info = ((u8 *)MapAreaDefGetRecTable_1dcf20(D_004818FC));
    base = *(s32 *)(info + 0x40);
    if (base == 0 || *(s16 *)(info + 0x38) <= D_00481900) {
        return 1;
    }
    rec = base + D_00481900 * 0x58;
    MapDataSetId_1e74e0(rec, ScriptArgGetInt_1ecbe0(arg0));
    MapDataSetName_1e7500(rec, ((s32)MemStackStrDup_14cff0(ScriptArgGetStr_1ecb80(arg0 + 8), D_004818F8)));
    MapDataSetFileName_1e74f0(rec, MapDataGetName_1e7bf0(rec));
    switch (arg1) {
    case 4:
        f = LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x10), D_0044B390, 0);
        MapDataSetMemFncFlags_1e74c0(rec, f | LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x18), D_0044B3B0, 0));
        break;
    case 9:
        f = LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x10), D_0044B390, 0);
        MapDataSetMemFncFlags_1e74c0(rec, f | LookupNameValueNoCase_1cab50(ScriptArgGetStr_1ecb80(arg0 + 0x18), D_0044B3B0, 0));
        break;
    }
    if (arg1 == 9 && ScriptArgGetInt_1ecbe0(arg0 + 0x20) != 0) {
        a = ScriptArgGetInt_1ecbe0(arg0 + 0x28);
        b = ScriptArgGetInt_1ecbe0(arg0 + 0x30);
        c = ScriptArgGetInt_1ecbe0(arg0 + 0x38);
        MapDataSetColor_1e72d0(rec, a, b, c, ScriptArgGetInt_1ecbe0(arg0 + 0x40));
    } else {
        MapDataGetColorVec4_1e7610(D_004818FC, sp60);
        MapDataSetColorVec_1e73b0(rec, sp60);
    }
    D_00481900++;
    return 1;
}

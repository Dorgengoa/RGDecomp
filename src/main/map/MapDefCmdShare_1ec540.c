#include "types.h"

extern s32 MemStackStrDup_14cff0(s32, s32);
extern s32 LookupNameValueNoCase_1cab50(s32, void *, s32);
extern u8 *MapAreaDefGetRecTable_1dcf20(s32);
extern void MapDataSetColor_1e72d0(s32, s32, s32, s32, s32);
extern void MapDataSetColorVec_1e73b0(s32, void *);
extern void MapDataSetMemFncFlags_1e74c0(s32, s32);
extern void MapDataSetId_1e74e0(s32, s32);
extern void MapDataSetFileName_1e74f0(s32, s32);
extern void MapDataSetName_1e7500(s32, s32);
extern void MapDataGetColorVec4_1e7610(s32, void *);
extern s32 MapDataGetName_1e7bf0(s32);
extern s32 ScriptArgGetStr_1ecb80(s32);
extern s32 ScriptArgGetInt_1ecbe0(s32);
extern u8 D_0044B390[0x20];
extern u8 D_0044B3B0[0x20];
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481900;

s32 MapDefCmdShare_1ec540(s32 arg0, s32 arg1)
{
    u8 sp60[16];
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
    info = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    base = *(s32 *)(info + 0x40);
    if (base == 0 || *(s16 *)(info + 0x38) <= D_00481900) {
        return 1;
    }
    rec = base + D_00481900 * 0x58;
    MapDataSetId_1e74e0(rec, ScriptArgGetInt_1ecbe0(arg0));
    MapDataSetName_1e7500(rec, MemStackStrDup_14cff0(ScriptArgGetStr_1ecb80(arg0 + 8), D_004818F8));
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

#include "types.h"
#pragma divbyzerocheck on

s32 CharaTableSetStepCount_225400(void *, s32);
s32 CharaTableGetStepCount_225410(void *);
s32 CharaTableGetStepArray_225470(void *);
void CharaTableEntrySetEndLandOrHit_226020(s32);
void CharaTableEntrySetEndCommandOff_226030(s32, u64);
void CharaTableEntrySetEndCommandOn_226060(s32, u64);
void CharaTableEntrySetEndWaitFrame_226090(s32, s32, s32);
void CharaTableEntrySetEndMotionEnd_2260b0(s32);
void CharaTableDataSetTimeCnctCount_2268d0(s32, s32);
void CharaTableDataSetTimePrmtCount_2268e0(s32, s32);
void CharaTableDataSetTimeAttrCount_2268f0(s32, s32);
void CharaTableDataSetTimeMoveCount_226900(s32, s32);
void CharaTableDataSetTimeAcclCount_226910(s32, s32);
void CharaTableDataSetTimeClsnCount_226920(s32, s32);
void CharaTableDataSetTimeEvntCount_226930(s32, s32);
void CharaTableDataSetReferenceCount_226940(s32, s32);
s32 CharaTableDataGetTimeCnctList_226960(s32);
s32 CharaTableDataGetTimePrmtList_226970(s32);
s32 CharaTableDataGetTimeAttrList_226980(s32);
s32 CharaTableDataGetTimeMoveList_226990(s32);
s32 CharaTableDataGetTimeAcclList_2269a0(s32);
s32 CharaTableDataGetTimeClsnList_2269b0(s32);
s32 CharaTableDataGetTimeEvntList_2269c0(s32);
s32 CharaTableDataGetReferenceList_2269d0(s32);
u32 ParseFlagNames_1ca700(s32, void *, s32);
u32 LookupNameValueNoCase_1cab50(s32, void *, s32);
s32 ScriptArgGetStr_23fba0(u8 *);
s32 ScriptArgGetInt_23fc00(u8 *);
extern u8 D_0044BB40[0x400];
extern u8 D_0044BDA0[0x400];
extern u8 D_0044C810[0x400];
extern s32 D_00481EA0;
extern s32 D_00481EA4;
extern s32 D_00481EA8;
extern s32 D_00481EAC;
extern s32 D_00481EB0;
extern s32 D_00481EB4;
extern s32 D_00481EB8;
extern s32 D_00481EBC;
extern s32 D_00481EC0;
extern s32 D_00481EC4;
extern s32 D_00481EC8;
extern s32 D_00481ECC;
extern s32 D_00481ED0;
extern s32 D_00481ED4;
extern s32 D_00481ED8;
extern s32 D_00481EDC;
extern u8 D_004BCDE0[0x400];

s32 CharaTableMtnDefineEnd_23c150(u8 *arg0, s32 arg1) {
    s32 p;
    s32 x;
    u64 t;

    if (arg1 != 0 && arg1 != 1 && arg1 != 2 && arg1 != 3) {
        return 0;
    }
    if (CharaTableGetStepArray_225470(D_004BCDE0) == 0 || CharaTableGetStepCount_225410(D_004BCDE0) >= 16) {
        return 1;
    }
    p = CharaTableGetStepArray_225470(D_004BCDE0) + CharaTableGetStepCount_225410(D_004BCDE0) * 0x44;
    CharaTableDataSetReferenceCount_226940(p, D_00481EA4 + (D_00481EA0 - CharaTableDataGetReferenceList_2269d0(p)) / 8);
    CharaTableDataSetTimeEvntCount_226930(p, D_00481EAC + (D_00481EA8 - CharaTableDataGetTimeEvntList_2269c0(p)) / 16);
    CharaTableDataSetTimeClsnCount_226920(p, D_00481EB4 + (D_00481EB0 - CharaTableDataGetTimeClsnList_2269b0(p)) / 32);
    CharaTableDataSetTimeAcclCount_226910(p, D_00481EBC + (D_00481EB8 - CharaTableDataGetTimeAcclList_2269a0(p)) / 16);
    CharaTableDataSetTimeMoveCount_226900(p, D_00481EC4 + (D_00481EC0 - CharaTableDataGetTimeMoveList_226990(p)) / 20);
    CharaTableDataSetTimeAttrCount_2268f0(p, D_00481ECC + (D_00481EC8 - CharaTableDataGetTimeAttrList_226980(p)) / 16);
    CharaTableDataSetTimePrmtCount_2268e0(p, D_00481ED4 + (D_00481ED0 - CharaTableDataGetTimePrmtList_226970(p)) / 20);
    CharaTableDataSetTimeCnctCount_2268d0(p, D_00481EDC + (D_00481ED8 - CharaTableDataGetTimeCnctList_226960(p)) / 20);
    if (arg1 > 0) {
        switch (LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(arg0), D_0044C810, 0)) {
        case 1:
            if (arg1 > 2) {
                x = ScriptArgGetInt_23fc00(arg0 + 0x10);
            } else {
                x = 0;
            }
            CharaTableEntrySetEndWaitFrame_226090(p, ScriptArgGetInt_23fc00(arg0 + 8), x);
            break;
        case 2:
            t = (u64)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044BB40, 0) << 32;
            t |= ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044BDA0, 0);
            if (t != 0) {
                CharaTableEntrySetEndCommandOn_226060(p, t);
            }
            break;
        case 3:
            t = (u64)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044BB40, 0) << 32;
            t |= ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044BDA0, 0);
            if (t == 0) {
                return 1;
            }
            CharaTableEntrySetEndCommandOff_226030(p, t);
            break;
        case 4:
            CharaTableEntrySetEndLandOrHit_226020(p);
            break;
        case 5:
            CharaTableEntrySetEndLandOrHit_226020(p);
            break;
        case 0:
        default:
            CharaTableEntrySetEndMotionEnd_2260b0(p);
            break;
        }
    }
    CharaTableSetStepCount_225400(D_004BCDE0, CharaTableGetStepCount_225410(D_004BCDE0) + 1);
    return 1;
}

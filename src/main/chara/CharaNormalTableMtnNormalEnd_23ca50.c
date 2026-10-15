#include "types.h"

#pragma divbyzerocheck on
#pragma optimize_for_size on

extern s32 CharaNormalTableSetCount_225800(void *, s32);
extern s32 CharaNormalTableGetCount_225810(void *);
extern s32 CharaNormalTableGetArray_225820(void *);
extern s32 CharaTableDataSetTimeCnctCount_2268d0(s32, s32);
extern s32 CharaTableDataSetTimePrmtCount_2268e0(s32, s32);
extern s32 CharaTableDataSetTimeAttrCount_2268f0(s32, s32);
extern s32 CharaTableDataSetTimeMoveCount_226900(s32, s32);
extern s32 CharaTableDataSetTimeAcclCount_226910(s32, s32);
extern s32 CharaTableDataSetTimeClsnCount_226920(s32, s32);
extern s32 CharaTableDataSetTimeEvntCount_226930(s32, s32);
extern s32 CharaTableDataSetReferenceCount_226940(s32, s32);
extern s32 CharaTableDataGetTimeCnctList_226960(s32);
extern s32 CharaTableDataGetTimePrmtList_226970(s32);
extern s32 CharaTableDataGetTimeAttrList_226980(s32);
extern s32 CharaTableDataGetTimeMoveList_226990(s32);
extern s32 CharaTableDataGetTimeAcclList_2269a0(s32);
extern s32 CharaTableDataGetTimeClsnList_2269b0(s32);
extern s32 CharaTableDataGetTimeEvntList_2269c0(s32);
extern s32 CharaTableDataGetReferenceList_2269d0(s32);
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
extern s32 D_00481F00;
extern u8 D_004BCDB0[];

s32 CharaNormalTableMtnNormalEnd_23ca50(s32 arg0, s32 arg1)
{
    s32 p;
    s32 i;

    if (arg1 != 0) {
        return 0;
    }
    if (D_00481F00 <= 0) {
        return 0;
    }
    if (CharaNormalTableGetArray_225820(D_004BCDB0) == 0 || CharaNormalTableGetCount_225810(D_004BCDB0) >= 16) {
        return 1;
    }
    p = CharaNormalTableGetArray_225820(D_004BCDB0);
    p += CharaNormalTableGetCount_225810(D_004BCDB0) * 0x34;
    for (i = 0; i < D_00481F00; i++, p += 0x34) {
        CharaTableDataSetReferenceCount_226940(p, D_00481EA4 + (D_00481EA0 - CharaTableDataGetReferenceList_2269d0(p)) / 8);
        CharaTableDataSetTimeEvntCount_226930(p, D_00481EAC + (D_00481EA8 - CharaTableDataGetTimeEvntList_2269c0(p)) / 16);
        CharaTableDataSetTimeClsnCount_226920(p, D_00481EB4 + (D_00481EB0 - CharaTableDataGetTimeClsnList_2269b0(p)) / 32);
        CharaTableDataSetTimeAcclCount_226910(p, D_00481EBC + (D_00481EB8 - CharaTableDataGetTimeAcclList_2269a0(p)) / 16);
        CharaTableDataSetTimeMoveCount_226900(p, D_00481EC4 + (D_00481EC0 - CharaTableDataGetTimeMoveList_226990(p)) / 20);
        CharaTableDataSetTimeAttrCount_2268f0(p, D_00481ECC + (D_00481EC8 - CharaTableDataGetTimeAttrList_226980(p)) / 16);
        CharaTableDataSetTimePrmtCount_2268e0(p, D_00481ED4 + (D_00481ED0 - CharaTableDataGetTimePrmtList_226970(p)) / 20);
        CharaTableDataSetTimeCnctCount_2268d0(p, D_00481EDC + (D_00481ED8 - CharaTableDataGetTimeCnctList_226960(p)) / 20);
    }
    CharaNormalTableSetCount_225800(D_004BCDB0, D_00481F00 + CharaNormalTableGetCount_225810(D_004BCDB0));
    return 1;
}

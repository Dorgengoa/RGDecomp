#include "types.h"

extern void WorldSubsysPlanetEntryLink_4023b0(s32, s32);
extern void WorldSubsysPlanetEntryLink_40ecd0(s32, s32);
extern void WorldSubsysPlanetEntryLink_4119c0(s32, s32);
extern void WorldSubsysPlanetEntryLink_41fd30(s32, s32);
extern void WorldSubsysPlanetEntryLink_425740(s32, s32);

s32 WorldDataMgrPlanetEntryLink_3f2640(void *arg0, s32 arg1, s32 arg2)
{
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;
    s32 temp_4_4;
    s32 temp_4_5;

    if (arg1 == 0) {
        return 0;
    }
    temp_4 = *(s32 *)((u8 *)arg0 + 0x34);
    if ((temp_4 != 0) && ((arg2 == 1) || (arg2 < 0))) {
        WorldSubsysPlanetEntryLink_4119c0(temp_4, arg1);
    }
    temp_4_2 = *(s32 *)((u8 *)arg0 + 0x74);
    if ((temp_4_2 != 0) && ((arg2 == 2) || (arg2 < 0))) {
        WorldSubsysPlanetEntryLink_425740(temp_4_2, arg1);
    }
    temp_4_3 = *(s32 *)((u8 *)arg0 + 0x70);
    if ((temp_4_3 != 0) && ((arg2 == 3) || (arg2 < 0))) {
        WorldSubsysPlanetEntryLink_4023b0(temp_4_3, arg1);
    }
    temp_4_4 = *(s32 *)((u8 *)arg0 + 0x7C);
    if ((temp_4_4 != 0) && ((arg2 == 4) || (arg2 < 0))) {
        WorldSubsysPlanetEntryLink_41fd30(temp_4_4, arg1);
    }
    temp_4_5 = *(s32 *)((u8 *)arg0 + 0x84);
    if ((temp_4_5 != 0) && ((arg2 == 5) || (arg2 < 0))) {
        WorldSubsysPlanetEntryLink_40ecd0(temp_4_5, arg1);
    }
    return 1;
}

#include "types.h"

extern void MemStackReset_14d830(s32);
extern void WorldSubsysPlanetEntryAttach_402440(s32, void *);
extern void WorldSubsysPlanetEntryAttach_40ed50(s32, void *);
extern void WorldSubsysPlanetEntryAttach_411a40(s32, void *);
extern void WorldSubsysPlanetEntryAttach_41fdb0(s32, void *);
extern void WorldSubsysPlanetEntryAttach_4257c0(s32, void *);

s32 WorldDataMgrPlanetEntryAttach_3f2770(u8 *arg0, u8 *arg1, s32 arg2)
{
    s16 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;
    s32 temp_4_4;
    s32 temp_4_5;
    s32 temp_4_6;
    s32 temp_4_7;

    if (arg1 == NULL) {
        return 0;
    }
    temp_4 = *(s16 *)(arg1 + 8);
    if ((temp_4 < 0) || (temp_4 >= 2)) return 0;
    temp_4_2 = *(s32 *)(arg0 + 8) + temp_4 * 0x58;
    if (temp_4_2 == 0) {
        return 0;
    }
    {
        if ((arg2 == 1) || (arg2 < 0)) {
            MemStackReset_14d830(temp_4_2);
        }
        temp_4_3 = *(s32 *)(arg0 + 0x34);
        if ((temp_4_3 != 0) && ((arg2 == 1) || (arg2 < 0))) {
            WorldSubsysPlanetEntryAttach_411a40(temp_4_3, arg1);
        }
        temp_4_4 = *(s32 *)(arg0 + 0x74);
        if ((temp_4_4 != 0) && ((arg2 == 2) || (arg2 < 0))) {
            WorldSubsysPlanetEntryAttach_4257c0(temp_4_4, arg1);
        }
        temp_4_5 = *(s32 *)(arg0 + 0x70);
        if ((temp_4_5 != 0) && ((arg2 == 3) || (arg2 < 0))) {
            WorldSubsysPlanetEntryAttach_402440(temp_4_5, arg1);
        }
        temp_4_6 = *(s32 *)(arg0 + 0x7C);
        if ((temp_4_6 != 0) && ((arg2 == 4) || (arg2 < 0))) {
            WorldSubsysPlanetEntryAttach_41fdb0(temp_4_6, arg1);
        }
        temp_4_7 = *(s32 *)(arg0 + 0x84);
        if ((temp_4_7 != 0) && ((arg2 == 5) || (arg2 < 0))) {
            WorldSubsysPlanetEntryAttach_40ed50(temp_4_7, arg1);
        }
        return 1;
    }
}

#include "types.h"

extern s32 GetGameData_1fede0(void);
extern void SaveSlotEntriesClear_373590(s32 arg0);
extern void SlotRecordResetById_3e4e20(s32 arg0, s32 arg1);
extern void SlotRecordRingPush_3e4f90(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_004831D0;

void SaveSlotRecordsClear_37b800(s32 arg0)
{
    s32 temp_2;
    s32 i;
    s32 j;

    temp_2 = GetGameData_1fede0();
    if (temp_2 != 0) {
        i = 0x31;
        do {
            if ((arg0 < 0) || (i == arg0)) {
                SlotRecordResetById_3e4e20(temp_2, i);
            }
            i -= 1;
        } while (i >= 0);
        j = 0;
        do {
            if ((arg0 < 0) || (j == arg0)) {
                SlotRecordRingPush_3e4f90(temp_2, j, 1, 0);
            }
            j += 1;
        } while (j < 0x32);
    }
    if (D_004831D0 != 0) {
        SaveSlotEntriesClear_373590(D_004831D0);
    }
}

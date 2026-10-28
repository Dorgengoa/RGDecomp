/* rgp:protos */
#define RGP_SELF_SaveSlotRecordsClear_37b800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004831D0;

void SaveSlotRecordsClear_37b800(s32 arg0)
{
    s32 temp_2;
    s32 i;
    s32 j;

    temp_2 = ((s32)GetGameData_1fede0());
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
                SlotRecordRingPush_3e4f90(temp_2, j, 1);
            }
            j += 1;
        } while (j < 0x32);
    }
    if (D_004831D0 != 0) {
        SaveSlotEntriesClear_373590(D_004831D0);
    }
}

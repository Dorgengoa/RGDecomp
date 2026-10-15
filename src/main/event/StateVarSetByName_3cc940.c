/* main s27m: CLOSED -- unused leading param arg1 (retail reads $a2/$a3). */
#include "types.h"

extern s32 StateVarSet_3cc9c0(void *arg0, s16 arg1, s32 arg2, s32 arg3);
extern s16 *TableFindByName_421fb0(s32 arg0);

s32 StateVarSetByName_3cc940(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s16 *temp_2;
    void *temp_2_2;

    temp_2_2 = *(void **)((u8 *)arg0 + 4);
    if (temp_2_2 == NULL) {
        return 1;
    }
    temp_2 = TableFindByName_421fb0(*(s32 *)((u8 *)temp_2_2 + 0x10));
    if (temp_2 != NULL) {
        return StateVarSet_3cc9c0(arg0, *temp_2, arg2, arg3);
    }
    return 1;
    return StateVarSet_3cc9c0(arg0, *temp_2, arg2, arg3);
}

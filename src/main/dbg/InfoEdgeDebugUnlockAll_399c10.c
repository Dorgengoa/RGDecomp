#include "types.h"
#pragma optimization_level 3

extern s32 PadIsHeld_183a20(void *, s32);
extern s32 ReturnZero_207fe0(void);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern void *GetGameData_1fede0(void);
extern void StateFlagSet_3ccb70(s32, s64, s32, s32);
extern s16 D_00454560[];
extern u8 D_004B2570[];

void InfoEdgeDebugUnlockAll_399c10(void) {
    s16 sp30[65];
    s32 var_17;
    s32 i;
    void *temp_16;

    temp_16 = GetGameData_1fede0();
    if (ReturnZero_207fe0() != 0 && PadIsHeld_183a20(D_004B2570, 8) != 0 && PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
        {
            s16 *src;
            s16 *dst;
            s32 n;
            src = D_00454560;
            dst = sp30;
            n = 65;
            do {
                *dst++ = *src++;
            } while (--n > 0);
        }
        var_17 = 0;
        while (sp30[var_17] != -1) {
            StateFlagSet_3ccb70(*(s32 *)((u8 *)temp_16 + 0x10), sp30[var_17], 1, 0);
            var_17 += 1;
        }
    }
}

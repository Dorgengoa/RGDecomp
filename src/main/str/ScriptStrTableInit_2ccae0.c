#include "types.h"

extern void MemStackInit_14d810(u8 *, s32, s32);
extern s32 MemStackAllocAligned64_14da10(u8 *, s32);
extern s32 MemStackHeapAllocFront_14dd10(s32, s32);
extern void MemStackCtor_14e030(u8 *);
extern s32 AlignUp64_1cacb0(s32);
extern u8 *GetCharaResMgr_1fdb60(void);
extern u8 *GetGameData_1fede0(void);
extern void StateVarSet_3cc9c0(s32, s32, s32, s32);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern s32 D_004825DC;
extern s32 D_004825E0;

void ScriptStrTableInit_2ccae0(void)
{
    u8 sp30[0x60];
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_17;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_5;
    s32 var_16;
    s32 var_17;
    s32 var_17_2;
    u8 *temp_16_3;

    temp_17 = *(s32 *)(GetCharaResMgr_1fdb60() + 0xD00);
    MemStackCtor_14e030(sp30);
    if (temp_17 != 0) {
        temp_16 = AlignUp64_1cacb0(0x31);
        temp_16_2 = temp_16 + (AlignUp64_1cacb0(0x51) * 0xC);
        temp_2 = MemStackHeapAllocFront_14dd10(temp_17, temp_16_2);
        if (temp_2 != 0) {
            MemStackInit_14d810(sp30, temp_2, temp_16_2);
            temp_2_2 = MemStackAllocAligned64_14da10(sp30, 0x31);
            D_004825DC = temp_2_2;
            if (temp_2_2 != 0) {
                var_16 = 0;
                do {
                    temp_2 = MemStackAllocAligned64_14da10(sp30, 0x51);
                    temp_5 = var_16 * 4;
                    var_16 += 1;
                    *(s32 *)(D_004825DC + temp_5) = temp_2;
                    *(s8 *)(*(s32 *)(D_004825DC + temp_5)) = 0;
                } while (var_16 < 0xc);
            }
        }
    }
    D_004825E0 = 0;
    temp_16_3 = GetGameData_1fede0();
    var_17 = 0x7D0;
    do {
        StateFlagSet_3ccb70(*(s32 *)(temp_16_3 + 0x10), var_17, 0, 1);
        var_17 += 1;
    } while (var_17 <= 0x7e0);
    var_17_2 = 0x50;
    do {
        StateVarSet_3cc9c0(*(s32 *)(temp_16_3 + 0x10), var_17_2, 0, 1);
        var_17_2 += 1;
    } while (var_17_2 <= 0x5f);
    StateVarSet_3cc9c0(*(s32 *)(temp_16_3 + 0x10), 0x60, -1, 1);
}

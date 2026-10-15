#include "types.h"

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackAllocAligned64_14da10(s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern void MesWinSetMode_276e00(u8 *, s32);
extern void MesWinSetMsgData_276ea0(u8 *, s32);
extern void MesWinInit_276f20(u8 *);
extern u8 *MesMgrGetSharedWin_277710(void);
extern void MesSlotInit_277e10(s32);
typedef struct O58 {
    u8 d[0x58];
} O58;
extern void *memcpy(void *, const void *, s32);
extern void MesWinCtor_276ef0();
extern void MesSlotCtor_277cf0();

void MesMgrInit_277b30(u8 *arg0, s32 arg1, s32 arg2, s64 arg3)
{
    u8 *temp_21;
    s32 temp_4;
    s32 temp_2;
    s64 temp_16_2;
    s32 temp_18;
    s32 temp_16;
    s32 *slot;
    s32 var_19;
    u8 *temp_3;
    s32 var_21;

    *(s32 *)(arg0 + 0x1E20) = 7;
    temp_16 = ConstructNewArray_100710(MemStackNew_14e1b0(0x2D0, arg1), MesSlotCtor_277cf0, 0, 0x58, 8);
    var_21 = 0;
    do {
        *(s32 *)(arg0 + (var_21 * 4) + 0x1E00) = temp_16 + (var_21 * 0x58);
        MesSlotInit_277e10(*(s32 *)(arg0 + (var_21 * 4) + 0x1E00));
        var_21 += 1;
    } while (var_21 < 8);
    *(s32 *)(*(s32 *)(arg0 + 0x1E00) + 0x4) = (s32) arg0;
    MesWinInit_276f20(arg0);
    temp_16_2 = arg3;
    *(s32 *)(*(s32 *)(arg0 + 0x1E04) + 0x4) = (s32) MesMgrGetSharedWin_277710();
    *(s16 *)(MesMgrGetSharedWin_277710() + 0x1DF8) = (s16) temp_16_2;
    *(s32 *)(*(s32 *)(arg0 + 0x1E08) + 0x4) = (s32) MesMgrGetSharedWin_277710();
    *(s16 *)(MesMgrGetSharedWin_277710() + 0x1DF8) = (s16) temp_16_2;
    *(s32 *)(*(s32 *)(arg0 + 0x1E0C) + 0x4) = (s32) MesMgrGetSharedWin_277710();
    *(s16 *)(MesMgrGetSharedWin_277710() + 0x1DF8) = (s16) temp_16_2;
    temp_2 = MemStackAllocAligned64_14da10(arg1, 0x401);
    memcpy((void *)(s32) temp_2, (void *)(s32) arg2, 0x4000);
    MesWinSetMsgData_276ea0(arg0, temp_2);
    temp_18 = ConstructNewArray_100710(MemStackNew_14e1b0(0x7810, arg1), MesWinCtor_276ef0, 0, 0x1E00, 4);
    var_19 = 0;
    do {
        temp_21 = (u8 *)(s32)(temp_18 + (var_19 * 0x1E00));
        MesWinInit_276f20(temp_21);
        MesWinSetMode_276e00(temp_21, 0);
        *(s16 *)(temp_21 + 0x1DF8) = (s16) arg3;
        MesWinSetMsgData_276ea0(temp_21, (s32) temp_2);
        temp_3 = arg0 + (var_19 * 4);
        var_19 += 1;
        *(s32 *)(*(s32 *)(temp_3 + 0x1E10) + 0x4) = (s32) temp_21;
    } while (var_19 < 4);
}

#include "types.h"

extern s32 MemStackAllocQw_14d950(s32, u32);
extern s32 SlotGetInt_15f720(void);
extern void strcat(s32, void *);
extern void strcpy(s32, s32);
extern s32 strlen(s32);
extern u8 D_004591C0[0x400];
extern s32 D_0048118C;
extern void *D_00481198;

s32 AmixerCfgClipActionCmd_16f8a0(void)
{
    s32 temp_2;
    u32 temp_3;
    u32 var_5;

    if (D_00481198 == NULL) {
        return 0;
    }
    temp_2 = SlotGetInt_15f720();
    if (temp_2 == 0) {
        return 0;
    }
    temp_3 = strlen(temp_2) + 5;
    if (!(temp_3 & 0xF)) {
        var_5 = temp_3 >> 4;
    } else {
        var_5 = (temp_3 >> 4) + 1;
    }
    *(s32 *)((u8 *)D_00481198 + 4) = MemStackAllocQw_14d950(D_0048118C, var_5);
    strcpy(*(s32 *)((u8 *)D_00481198 + 4), temp_2);
    strcat(*(s32 *)((u8 *)D_00481198 + 4), &(*(u8 *)D_004591C0));
    return 1;
    return 0;
}

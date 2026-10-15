#pragma opt_propagation off
#include "types.h"

extern s32 ConstructNewArray_100710(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 VariantGetInt_15f780(s32 xa0, s16 arg0);
extern s32 ArenaNew_4235b0(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern void *D_004830F8;
extern s16 D_004830FC;
extern void DataTableRowCtor_423000(void);

s32 DataTableCmdAllocSubEntries_422f40(void)
{
    s32 u_0;
    s16 temp_5;
    s32 temp_2;
    s32 temp_3;
    void *temp_16;
    u8 *temp_17;

    temp_16 = D_004830F8;
    temp_5 = *(s16 *)((u8 *)temp_16 + 0x7C);
    if (temp_5 <= 0) {
        return 1;
    }
    temp_3 = D_004830FC - 1;
    if (temp_3 >= temp_5) {
        return 1;
    }
    {
        temp_17 = (u8 *)(*(s32 *)((u8 *)temp_16 + 0x8C)) + (temp_3 << 5);
        *(s32 *)(temp_17 + 0x14) = VariantGetInt_15f780(u_0, temp_5);
        if (*(s32 *)(temp_17 + 0x14) > 0) {
            temp_2 = *(s32 *)(temp_17 + 0x14);
            *(s32 *)(temp_17 + 0x18) = ConstructNewArray_100710(
                ArenaNew_4235b0((temp_2 << 5) + 0x10, (u8 *)temp_16 + 0x6C, 4, -1),
                (void *)DataTableRowCtor_423000, 0, 0x20, temp_2);
        } else {
            *(s32 *)(temp_17 + 0x18) = 0;
        }
        *(s32 *)((u8 *)temp_16 + 0xBC) = 0;
        *(s32 *)((u8 *)temp_16 + 0xC0) = 0;
        return 1;
    }
    return 1;
    return 1;
}

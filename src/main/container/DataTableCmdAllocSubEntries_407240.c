#pragma opt_arithtransformation off
#include "types.h"

s32 ConstructNewArray_100710(s32, u8 *, s32, s32, u8);               /* extern */
u8 VariantGetInt_15f780(s32 xa0, u8, u8 *);                        /* extern */
s32 ArenaNew_407f50(s32, u8 *, s32, s32);              /* extern */
extern u8 *D_004830F8;
extern s16 D_004830FC;
extern u8 D_00483C78;
extern s8 D_00483C80;
extern s8 D_00483C84;
extern void DataTableRowCtor_407340();

typedef struct Elem00407240 {
    u8 pad0[2];
    u8 cnt;
    u8 pad3;
    s32 x4;
    s32 x8;
} Elem00407240;

s32 DataTableCmdAllocSubEntries_407240(void) {
    s32 u_0;
    s32 temp_5;
    s32 temp_2;
    s32 temp_3;
    u8 temp_18;
    u8 *temp_16;
    Elem00407240 *temp_17;
    u8 *temp_6;

    temp_16 = D_004830F8;
    temp_5 = (*(s16 *)((u8 *)temp_16 + 0x7C));
    if (temp_5 <= 0) {
        return 1;
    }
    temp_3 = D_004830FC - 1;
    if (temp_3 >= temp_5) {
        return 1;
    }
    temp_6 = (u8 *)((*(s32 *)((u8 *)temp_16 + 0x8C)) + (temp_3 * 8));
    if ((D_00483C78 - 1) >= (*(s16 *)((u8 *)temp_6 + 0x2))) {
        return 1;
    }
    temp_17 = (Elem00407240 *)(((*(s32 *)((u8 *)temp_6 + 0x4)) + (D_00483C78 * 0xC)) - 0xC);
    temp_17->cnt = VariantGetInt_15f780(u_0, D_00483C78, temp_6);
    temp_18 = temp_17->cnt;
    if ((s32) temp_18 > 0) {
        temp_2 = ConstructNewArray_100710(ArenaNew_407f50((temp_18 * 8) + 0x10, temp_16 + 0x6C, (*(s16 *)((u8 *)temp_16 + 0x80)), -1), (u8 *)DataTableRowCtor_407340, 0, 8, temp_18);
        temp_17->x8 = temp_2;
        if (temp_2 == 0) {
            return 1;
        }
    }
    D_00483C80 = 0;
    D_00483C84 = 0;
    return 1;
}

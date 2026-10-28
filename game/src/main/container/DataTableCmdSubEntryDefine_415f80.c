/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_415f80 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: RIGHT LENGTH (104w), 61 bad -- large residue. */
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdSubEntryDefine_415f80(s64 *arg0) {
    u8 *temp_2;
    u8 *temp_18;
    u8 *temp_16;
    s8 *temp_21;
    s8 *temp_20;
    s8 *temp_19_3;
    s32 temp_6;
    s32 temp_5_2;
    s32 temp_5;
    s32 temp_3_2;
    s32 temp_17;
    s16 temp_3;
    s32 temp_22;

    temp_16 = D_004830F8;
    temp_3 = *(s16 *)(temp_16 + 0x7C);
    if (temp_3 <= 0) {
        return 1;
    }
    temp_5 = D_004830FC - 1;
    if (temp_5 >= temp_3) {
        return 1;
    }
    temp_2 = *(u8 **)(temp_16 + 0x8C) + (temp_5 * 0x28);
    temp_6 = *(s32 *)(temp_2 + 0x20);
    if (temp_6 == 0) {
        return 1;
    }
    temp_5_2 = *(s32 *)(temp_2 + 0x1C);
    if (temp_5_2 <= 0) {
        return 1;
    }
    temp_3_2 = *(s32 *)(temp_16 + 0x94);
    if ((temp_3_2 - 1) >= temp_5_2) {
        return 1;
    }
    temp_18 = (u8 *)(temp_6 + (temp_3_2 * 0x14));
    temp_22 = VariantGetInt_15f780((s32)arg0++);
    temp_17 = *(s32 *)(temp_16 + 0x9C);
    temp_21 = ((s8 *)SlotGetInt_15f720((s32)arg0++));
    temp_20 = ((s8 *)SlotGetInt_15f720((s32)arg0++));
    temp_19_3 = ((s8 *)SlotGetInt_15f720((s32)arg0));
    if ((temp_17 < 0) || (temp_17 >= 0x8C)) {
        return 1;
    }
    if (temp_20 == NULL) {
        return 1;
    }
    if (*temp_20 == 0) {
        return 1;
    }
    *(s16 *)(temp_18 + 0) = temp_22;
    *(s16 *)(temp_18 + 2) = temp_17;
    *(s32 *)(temp_18 + 4) = DataTableStoreString_368ab0(temp_16, temp_21);
    *(s32 *)(temp_18 + 8) = DataTableStoreString_368ab0(temp_16, temp_20);
    *(s32 *)(temp_18 + 0xC) = DataTableStoreString_368ab0(temp_16, temp_19_3);
    *(s32 *)(temp_18 + 0x10) = 0;
    *(s32 *)(temp_16 + 0x94) = *(s32 *)(temp_16 + 0x94) + 1;
    *(s32 *)(temp_16 + 0x9C) = *(s32 *)(temp_16 + 0x9C) + 1;
    return 1;
}

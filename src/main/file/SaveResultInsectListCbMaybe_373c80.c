#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

typedef struct S00373c80 {
    u8 pad0[0x24];
    s32 unk24;
    u8 pad28[0x4EE - 0x28];
    s16 unk4EE;
} S00373c80;

typedef struct Item00373c80 {
    u8 pad0[0x23];
    u8 unk23;
} Item00373c80;

typedef struct Slot00373c80 {
    u8 pad0[0x348];
    u8 unk348;
} Slot00373c80;

extern void *GetGameData_1fede0(void);
extern void InsectVsRecSetSaveLoadedFlagsMaybe_373ea0(void *arg0);
extern void SaveRecordSetSlotMaybe_374000(void *arg0);
extern s32 SaveResultSetFromDataError_374070(void *arg0);
extern void SaveFileReadInsectList_3e45c0(void *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4);
extern s32 SlotRecordFindById_3e4e80(void *arg0, s16 arg1);
extern s8 *RecordGetCageInsectCountsMaybe_42fec0(s32 arg0);
extern Item00373c80 *RecordGetInsectListMaybe_42ff70(s32 arg0, s32 arg1);
extern void RecordSetInsectListCountMaybe_430070(s32 arg0, s32 arg1, s32 arg2);

s32 SaveResultInsectListCbMaybe_373c80(S00373c80 *arg0, s32 arg1, s32 arg2)
{
        void * arg_h0;

    s8 *var_5;
    u16 var_18;
    Item00373c80 *temp_2;
    s32 var_4_2;
    u8 *temp_23;
    void *base;
    s32 sp9C;
    s8 *temp_16;
    s32 var_4;
    s8 *temp_3;
    s32 temp_17;
    s8 neg;
    u32 temp_2_2;

    base = GetGameData_1fede0();
    sp9C = 0;
    var_18 = 0;
    temp_23 = (u8 *) SlotRecordFindById_3e4e80(base, arg0->unk4EE);
    temp_2 = RecordGetInsectListMaybe_42ff70(*(s32 *)((u8 *)base + 0x24), 0);
    temp_16 = RecordGetCageInsectCountsMaybe_42fec0(*(s32 *)((u8 *)base + 0x24));
    if ((s32) temp_2 != 0) {
        var_18 = 1;
        arg_h0 = base;
        SaveFileReadInsectList_3e45c0(arg_h0, (s32) temp_2, &sp9C, arg1, arg2);
        RecordSetInsectListCountMaybe_430070(*(s32 *)((u8 *)base + 0x24), sp9C, 0);
        var_5 = temp_16;
        var_4 = 0;
        neg = -1;
        do {
            if ((temp_23 + var_4 * 2)[0x348] & 1) {
                *var_5 = 0;
            } else {
                *var_5 = neg;
            }
            var_5 += 1;
            var_4 += 1;
        } while (var_4 < 3);
        for (var_4_2 = 0; var_4_2 < sp9C; var_4_2++) {
            temp_2_2 = *(u8 *) (((u8 *) temp_2) + (var_4_2 * 0x28) + 0x23);
            if (temp_2_2 == 0) {
                continue;
            }
            temp_3 = &temp_16[temp_2_2];
            *(temp_3 - 1) = (s8) (*(temp_3 - 1) + 1);
        }
    }
    temp_17 = SaveResultSetFromDataError_374070(arg0);
    if ((var_18) && ((temp_17 == 0) || (temp_17 == 0xA))) {
        SaveRecordSetSlotMaybe_374000(arg0);
        InsectVsRecSetSaveLoadedFlagsMaybe_373ea0(arg0);
    }
    return 1;
}

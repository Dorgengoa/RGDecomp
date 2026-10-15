#include "types.h"
#pragma opt_propagation off

typedef struct Ctx002fd6e0 {
    u8 pad0[0x48];
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    u16 unk54;
} Ctx002fd6e0;

typedef struct Inner002fd6e0 {
    u8 pad0[0x6C];
    s32 unk6C;
} Inner002fd6e0;

typedef struct Root002fd6e0 {
    u8 pad0[0x8];
    Inner002fd6e0 *unk8;
} Root002fd6e0;

extern s32 VariantGetInt_15f780();
extern Root002fd6e0 *GetGameData_1fede0(void);
extern Ctx002fd6e0 *GroupGetRecordById_41c2a0(s32 arg0, s16 arg1, s16 arg2, s32 arg3);
extern u8 D_004E6620[0x400];
extern Ctx002fd6e0 *D_004E6628[0x100];

s32 NpcCfgCmdSelectDef_2fd6e0(s32 arg0, s32 arg1)
{
    s16 *temp_2;
    s32 var_18;
    s32 temp_17;
    s32 var_16;
    Ctx002fd6e0 *temp_2_2;

    if (!((arg1 > 0) && (arg1 <= 2))) {
        return 0;
    }
    arg0 += 8;
    temp_17 = VariantGetInt_15f780();
    var_16 = 0;
    if (arg1 == 2) {
        var_16 = VariantGetInt_15f780(arg0);
    }
    var_18 = -1;
    if ((*(s16 ** *)D_004E6620) != NULL) {
        temp_2 = *(*(s16 ** *)D_004E6620);
        if (temp_2 != NULL) {
            var_18 = *temp_2;
        }
    }
    temp_2_2 = GroupGetRecordById_41c2a0(GetGameData_1fede0()->unk8->unk6C, temp_17, var_18, 0);
    if (temp_2_2 == NULL) {
        return 0;
    }
    D_004E6628[0] = temp_2_2;
    temp_2_2->unk48 = temp_2_2->unk48 | 1;
    temp_2_2->unk4C = 0;
    temp_2_2->unk50 = 0;
    temp_2_2->unk54 = 0;
    if (var_16 != 0) {
        temp_2_2->unk48 = temp_2_2->unk48 | 2;
    }
    return 1;
}

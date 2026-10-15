#include "types.h"
#pragma optimization_level 3

void *GetGameData_1fede0(void);
s32 TreasureBoxIsOpened_33a240();
s32 TreasureBoxIsEncounterBox_33aac0(s8 *);
s32 TreasureBoxGetItemCount_33ad70(s8 *);
s32 TreasureBoxGetItemId_33ad90(s8 *);
void VariantInit_36ff00(void *);
s32 InvAddItemRepeat_3c47b0(s32, s32, s32, s32);
s32 StateFlag2Set_3cc6d0(s32, s16, s32);
s8 *ScriptExecOpStream_3dffa0(void *, s32, s32, s32);
s32 VariantPoolReset_3e01f0(void *);
s32 TreasureBoxCanOpenThunkMaybe_33abd0(s8 *);

typedef struct { u8 d[0x38]; } E33a;
typedef struct { s32 a; s32 b; E33a e[64]; } S33a;

s32 TreasureBoxGiveItem_33a2b0(s8 *arg0) {
    S33a s;
    E33a *p;
    s8 *t;
    s8 *q;
    s16 id;
    s32 x;

    if (*(s32 *)(arg0 + 0x68) == 0) {
        return 0;
    }
    if (TreasureBoxIsOpened_33a240() != 0) {
        return 0;
    }
    if (TreasureBoxCanOpenThunkMaybe_33abd0(arg0) == 0) {
        return 0;
    }
    t = GetGameData_1fede0();
    if (t == NULL) {
        return 0;
    }
    id = *(s16 *)(*(s8 **)(arg0 + 0x68) + 8);
    if (id < 0) {
        return 0;
    }
    if (TreasureBoxIsEncounterBox_33aac0(arg0) == 0) {
        x = TreasureBoxGetItemId_33ad90(arg0);
        InvAddItemRepeat_3c47b0(*(s32 *)(t + 0x18), x, 0, TreasureBoxGetItemCount_33ad70(arg0));
    }
    StateFlag2Set_3cc6d0(*(s32 *)(t + 0x10), id, 1);
    q = *(s8 **)(arg0 + 0x68);
    if (*(s16 *)(q + 0x2C) > 0 && *(s32 *)(q + 0x38) != 0) {
        p = s.e;
        do {
            VariantInit_36ff00(p);
            p++;
        } while (p < &s.e[64]);
        VariantPoolReset_3e01f0(&s);
        q = *(s8 **)(arg0 + 0x68);
        ScriptExecOpStream_3dffa0(&s, *(s16 *)(q + 0x2C), *(s32 *)(q + 0x38), 0);
    }
    return 1;
}

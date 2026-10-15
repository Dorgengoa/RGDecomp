#include "types.h"
typedef struct Item0033abd0 {
    u8 pad0[0xC];
    s16 unkC;
    u8 pad40_gap[0x40 - 0xE];
    s32 unk40;
} Item0033abd0;

typedef struct S0033abd0 {
    u8 pad0[0x68];
    Item0033abd0 *unk68;
} S0033abd0;

typedef struct Ctx0033abd0 {
    u8 pad0[0x18];
    s32 unk18;
} Ctx0033abd0;

extern Ctx0033abd0 *GetGameData_1fede0(void);
extern s32 TreasureBoxIsOpened_33a240(void);
extern s32 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);

s32 TreasureBoxCanOpenMaybe_33abd0(S0033abd0 *arg0) {
    Ctx0033abd0 *temp_2;

    if (arg0->unk68 == NULL) {
        return 0;
    }
    if (TreasureBoxIsOpened_33a240() != 0) {
        return 0;
    }
    if (!(arg0->unk68->unk40 & 4)) {
        return 0;
    }
    temp_2 = GetGameData_1fede0();
    if (temp_2 == NULL) {
        return 0;
    }
    switch (arg0->unk68->unkC) {
        case 1:
            if (InvHasItemInCategory_3c7f40(temp_2->unk18, 0x4101, 0, 0) != 0) {
                return 1;
            }
            break;
        case 2:
            if (InvHasItemInCategory_3c7f40(temp_2->unk18, 0x4102, 0, 0) != 0) {
                return 1;
            }
            break;
        case 3:
            if (InvHasItemInCategory_3c7f40(temp_2->unk18, 0x4103, 0, 0) != 0) {
                return 1;
            }
            break;
        default:
            return 1;
    }
    return 0;
}

#include "types.h"

typedef struct Sub001b40f0 {
    u8 pad000[4];
    s32 unk4;
} Sub001b40f0;

typedef struct T001b40f0 {
    u8 pad000[0x2C];
    s32 unk2C;
    s32 unk30;
    u8 pad034[0x40 - 0x34];
    Sub001b40f0 *unk40;
} T001b40f0;

extern s32 MemStackStrDup_14cf10(s32, s32);
extern s32 SlotGetInt_15f720(void);

s32 MotionEventCfgEventNameCmd_1b40f0(s32 unused0, s32 unused1, T001b40f0 **arg2)
{
    T001b40f0 *temp16;
    s32 temp17;

    temp16 = *arg2;
    temp17 = temp16->unk30;
    if (temp16->unk40 == 0) {
        return 0;
    }
    if (temp16->unk2C != 0) {
        return 1;
    }
    temp16->unk40->unk4 = MemStackStrDup_14cf10(SlotGetInt_15f720(), temp17);
    return 1;
}

#include "types.h"

extern s32 MemStackStrDup_14cf10(s32 arg0, s32 arg1);
extern s32 SlotGetInt_15f720(void);
extern s32 VariantGetInt_15f780(s32 arg0);

s32 MotionEventCfgTexAnimeCmd_1b3f80(s32 arg0, s32 unused1, void **arg2)
{
    u8 *temp_16;

    temp_16 = *(u8 **)arg2;
    if (*(u8 **)(temp_16 + 0x4C) == NULL) {
        return 0;
    }
    *(s32 *)(*(u8 **)(temp_16 + 0x4C) + 0x28) = MemStackStrDup_14cf10(SlotGetInt_15f720(), *(s32 *)(temp_16 + 0x30));
    *(s32 *)(*(u8 **)(temp_16 + 0x4C) + 0x2C) = VariantGetInt_15f780(arg0 + 8);
    return 1;
}

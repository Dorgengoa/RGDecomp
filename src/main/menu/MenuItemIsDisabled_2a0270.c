#include "types.h"

extern s32 ItemRecKindIs6_3d4510(void *);
extern s32 ItemRecKindIs12_3d45f0(void *);

s32 MenuItemIsDisabled_2a0270(s32 arg0, void *arg1)
{
    s32 temp_16;

    temp_16 = *(s8 *)((u8 *)*(void **)((u8 *)arg1 + 0x10) + 2);
    if (ItemRecKindIs6_3d4510(arg1) != 0 || ItemRecKindIs12_3d45f0(arg1) != 0 || temp_16 == 0xE) {
        return 1;
    }
    return 0;
}

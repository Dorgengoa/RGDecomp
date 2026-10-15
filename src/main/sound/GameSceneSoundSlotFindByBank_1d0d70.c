#include "types.h"

extern s32 SoundSlotGetBankId_1d2130(s32);

s32 GameSceneSoundSlotFindByBank_1d0d70(s32 p0, s32 p1)
{
    s32 l1;
    s32 l0;
    s32 r2;

    l1 = (s32)((u8 *)p0 + 0xB0B0);
    l0 = 0;
    while (l0 < 7) {
        r2 = SoundSlotGetBankId_1d2130(l1);
        if (p1 == r2) {
            return l1;
        }
        l0 = (l0 + 1);
        l1 = (l1 + 0x88);
    }
    return 0;
}

#include "types.h"

extern u8 D_004E0DD0[];
extern s32 D_004826A0;
extern void GuardEffectStart_2d53e0(u8 *slot, void *a, void *b, s32 i);

void GuardEffectSpawn_2d8fb0(void *a, void *b)
{
    s32 i;

    i = D_004826A0;
    GuardEffectStart_2d53e0(&D_004E0DD0[i * 832], a, b, i);
    D_004826A0 = D_004826A0 + 1;
    if (D_004826A0 >= 0xC) {
        D_004826A0 = 0;
    }
}

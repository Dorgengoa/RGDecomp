#include "types.h"

extern void DestroyArray_1005b0(void *, void (*)(void), s32, s32);

extern u8 D_004A25F0[];
extern void SoundStreamSlotDtor_1bf6c0(void);

void SoundStreamSlotsDtor_1bf6a0(void)
{
    DestroyArray_1005b0(D_004A25F0, SoundStreamSlotDtor_1bf6c0, 0x128, 4);
}

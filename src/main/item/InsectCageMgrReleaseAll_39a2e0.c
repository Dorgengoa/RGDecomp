#include "types.h"

extern void InsectCageSlotRelease_39b9c0(u8 *q);

void InsectCageMgrReleaseAll_39a2e0(u8 *p)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        InsectCageSlotRelease_39b9c0(p + i * 48);
    }
}

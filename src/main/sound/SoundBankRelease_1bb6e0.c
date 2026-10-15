#include "types.h"

/* Known-positive sibling shape of AreaBoxInit_1e01f0 (byte-identical, in cunits). */

extern void SoundBankStopAll_1bad70(void);
extern void SoundBankFree_1b9c00(s32);

void SoundBankRelease_1bb6e0(s32 p0)
{
    SoundBankStopAll_1bad70();
    SoundBankFree_1b9c00(p0);
}

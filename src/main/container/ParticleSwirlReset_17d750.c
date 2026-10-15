#include "types.h"
#pragma vu0_mmi_reg_binding on
extern __int128 vz17d750 asm("vf0");

extern s32 memset(void *, s32, s32);

void ParticleSwirlReset_17d750(s32 *arg0)
{
    s32 i;

    *arg0 = 1;
    if (arg0) { arg0 = (s32 *)(s32)(u32)arg0; }
    *(__int128 *)(arg0 + 4) = vz17d750;
    i = 0;
    do {
        memset((u8 *)arg0 + (i << 5) + 0x90, 0, 0x20);
        i++;
    } while (i < 0x14);
}

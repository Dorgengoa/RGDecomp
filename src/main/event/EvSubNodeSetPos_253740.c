#include "types.h"

extern void sceVu0CopyVector(void *, void *);

s32 EvSubNodeSetPos_253740(void *a, void *b)
{
    sceVu0CopyVector((u8 *)b + 0x70, (u8 *)a + 0x10);
    return 0;
}

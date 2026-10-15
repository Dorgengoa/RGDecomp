#include "types.h"

extern void sceVu0CopyVector(void *, void *);

s32 EvSubNodeSetRot_252dc0(void *a, void *b)
{
    sceVu0CopyVector((u8 *)b + 0x80, (u8 *)a + 0x10);
    return 0;
}

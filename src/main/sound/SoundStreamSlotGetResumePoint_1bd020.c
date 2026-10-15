#include "types.h"

extern u8 D_004A25F0[];
extern s32 D_004814F0;
extern void *memcpy(void *, const void *, s32);

typedef struct Dest001bd020 {
    s32 f0;
    u8 f4[0x18];
    u8 f1C[0x18];
} Dest001bd020;

void SoundStreamSlotGetResumePoint_1bd020(s32 idx, Dest001bd020 *dest)
{
    u8 *ptr;

    if (idx < 0 || idx >= 4) {
        ptr = 0;
    } else {
        ptr = D_004A25F0 + idx * 0x128;
    }
    if (ptr == 0 || *(s32 *)((u8 *)&D_004814F0 + idx * 4) == 0) {
        ptr = 0;
    }
    if (ptr == 0) {
        dest->f0 = -1;
        return;
    }
    if (*(void **)(ptr + 8) == 0) {
        dest->f0 = -1;
        return;
    }
    dest->f0 = *(s32 *)((u8 *)*(void **)(ptr + 8) + 0x5C);
    memcpy(dest->f4, (u8 *)*(void **)(ptr + 8) + 0x60, 0x18);
    memcpy(dest->f1C, (u8 *)*(void **)(ptr + 8) + 0x38, 0x18);
}

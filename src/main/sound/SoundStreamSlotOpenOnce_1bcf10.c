#include "types.h"

extern s32 SoundStreamSlotQueueOpen_1be8a0(void *, s32, s32);
extern s32 D_004814F0;
extern u8 D_004A25F0[];

static inline u8 *get0(s32 i)
{
    if (i < 0 || i >= 4) {
        return NULL;
    }
    return D_004A25F0 + i * 0x128;
}

static inline u8 *get1(s32 i)
{
    u8 *p = get0(i);
    if (p == NULL || (&D_004814F0)[i] == 0) {
        return NULL;
    }
    return p;
}

s32 SoundStreamSlotOpenOnce_1bcf10(s32 arg0, s32 arg1)
{
    u8 *p = get1(arg0);

    if (p == NULL) {
        return -1;
    }
    return SoundStreamSlotQueueOpen_1be8a0(p, arg1, 0) & 0xFF;
}

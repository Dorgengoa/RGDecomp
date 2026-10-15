#include "types.h"
extern void ExitDeleteThread(void);
extern s32 SoundStreamSlotUpdate_1bea70(void *);
extern void WaitSema(s32);
extern s32 D_0047E214;
extern s32 D_00481500;
extern s32 D_0048150C;
extern s32 D_004814F0[2];
extern u8 D_004A25F0[];

void SoundStreamSlotThreadMain_1bc520(void)
{
    s32 *p;
    s32 i;

    while (!D_00481500) {
        WaitSema(D_0047E214);
        if (D_0048150C != 0) {
            continue;
        }
        for (i = 0; i < 4; i++) {
            p = &D_004814F0[i];
            if (*p != 0 && SoundStreamSlotUpdate_1bea70(D_004A25F0 + i * 0x128) != 0) {
                *p = 0;
            }
        }
    }
    ExitDeleteThread();
}

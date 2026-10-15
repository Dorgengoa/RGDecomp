#include "types.h"

typedef struct { s32 f0; s32 f4; s32 f8, fC, f10; } E_00249eb0;

extern void SoundSetEntryVolumeScaled_1b9820(s32, s32, s32, f32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);

void EventSoundTableStopAll_249eb0(E_00249eb0 *arr)
{
    s32 i;
    E_00249eb0 *e;

    for (i = 0; i < 0x40; i++) {
        e = &arr[i];
        if (e->f0 != -1) {
            SoundSetEntryVolumeScaled_1b9820(e->f0, e->f4, 0, 0.0f);
            SoundStopEntry_1b8bc0(e->f0, e->f4, 0);
        }
    }
}

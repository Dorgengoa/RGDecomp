#include "types.h"

extern void SoundStreamSetMasterVolumeThunkMaybe_1bc6f0(void *, f32);
extern void SoundStreamSlotThreadResumeThunk_1bd660(void *);
extern void StreamMgrCloseChan_1d67a0(void *, s32);

void StreamMgrCloseAll_1d6740(void *p)
{
    s32 i;

    SoundStreamSetMasterVolumeThunkMaybe_1bc6f0(p, 0.0f);
    SoundStreamSlotThreadResumeThunk_1bd660(p);
    for (i = 0; i < 4; i++) {
        StreamMgrCloseChan_1d67a0(p, i);
    }
}

#include "types.h"

/* MAIN SoundEnvPresetApplyWaitLoad_2f48c0 -- spin until LoaderCountQueued_1cd620 stops returning a
   positive count, sleeping 10 between polls.  The `blezl` exit with
   `ld $31` in the delay slot is the `break`. */

extern void *GetLoaderMgr_1f59d0(void);
extern void TaskUpdateSoundSet_206ff0(void);
extern void LoaderTickGlobal_2f74c0(void);
extern void TaskLoadSound_207a80(void);
extern s32 LoaderCountQueued_1cd620(void *);
extern void DelayThread_117618(s32);

void SoundEnvPresetApplyWaitLoad_2f48c0(void)
{
    void *o;

    o = GetLoaderMgr_1f59d0();
    TaskUpdateSoundSet_206ff0();
    for (;;) {
        LoaderTickGlobal_2f74c0();
        TaskLoadSound_207a80();
        if (LoaderCountQueued_1cd620(o) <= 0) {
            break;
        }
        DelayThread_117618(10);
    }
}

/* rgp:protos */
#define RGP_SELF_SoundEnvPresetApplyWaitLoad_2f48c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN SoundEnvPresetApplyWaitLoad_2f48c0 -- spin until LoaderCountQueued_1cd620 stops returning a
   positive count, sleeping 10 between polls.  The `blezl` exit with
   `ld $31` in the delay slot is the `break`. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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

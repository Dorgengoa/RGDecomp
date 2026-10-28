/* rg-override: replaces game/src/main/sys/SysTickThreadMain_1c33f0.c sha256 7ee9e2090591da7460eb2d0bfbb95685f03d1af5c7a294ba3583bc3c63081a1d
 * why: native threads (docs/NATIVE-THREADS.md): the loop body is split out as
 *      rg_SysTickStep / rg_SysTickWait so the thread can run as a fiberless service step
 *      (slice 1, RG_THREADS=service) or as a step of the frame driver (RG_THREADS=native,
 *      registered below); the thread entry is the original loop over them (RG_THREADS=hle) */
/* rgp:protos */
#define RGP_SELF_SysTickThreadMain_1c33f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */
#include "port/native_audio.h"   /* rg-override */

extern s32 WaitSema(s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00481554;
extern s32 D_0047E248;
extern s32 D_0047E250;

/* rg-override: the loop's condition (the sema to wait on, or -1 = leave the loop) */
int rg_SysTickWait(void *arg)
{
    (void)arg;
    return D_0047E248 >= 0 ? D_0047E248 : -1;
}

/* rg-override: the loop body, unchanged; runs to completion (no kernel call when
 * RG_AUDIO=native: SoundSetCategoryVolume's command 0x12 goes to the engine) */
void rg_SysTickStep(void *arg)
{
    (void)arg;
    PadVibrationTick_1837a0();
    if (D_00481554 != 0) {
        SoundSeqPlayersUpdateAll_1bb110(1.0f);
    }
    {
        u8 *q = ((u8 *)GetStaticScene_1c6c70()) + 0xAE20U;
        SoundCategoryFadeUpdate_1b5f20(q, 1.0f);
    }
    D_0047E250 = 1;
}

void SysTickThreadMain_1c33f0(void)
{
    s32 s;

    while ((s = rg_SysTickWait(0)) >= 0) {
        WaitSema(s);
        rg_SysTickStep(0);
    }
}

/* rg-override: frame driver conversion.  The step is driven only when it cannot block:
 * with RG_AUDIO=native its one kernel-reaching callee (command 0x12) goes to the engine. */
static int rg_SysTickAllowed(void) { return rg_audio_mode() == RG_AUDIO_NATIVE; }
static const rg_thread_conv rg_SysTickConv = {
    (void *)SysTickThreadMain_1c33f0, "SysTickThreadMain_1c33f0", rg_SysTickWait, rg_SysTickStep, 0, 0,
    rg_SysTickAllowed, 18 /* P-2 */, 0, 0, 0, 0, 1 /* anywhere: no kernel call, no lock */
};
__attribute__((constructor)) static void rg_SysTickRegister(void) { rg_threads_convertible(&rg_SysTickConv); }

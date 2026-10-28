/* rg-override: replaces game/src/main/sound/SoundStreamThreadMain_1c1050.c sha256 f78949765c6b75fc4ec1ca8ecb5679aa11b635d42b5bd22954f338f36e43cd3c
 * why: native frame driver (docs/NATIVE-THREADS.md "Slice 3"): the three stream threads are
 *      driven steps (wait / step in the SoundStreamProcessCmds_1c05f0 override), run at the
 *      main flow's command signal as the HLE switched to these priority-15 threads there */
/* rgp:protos */
#define RGP_SELF_SoundStreamThreadMain_1c1050 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */
#include "port/native_audio.h"   /* rg-override */

extern s32 SoundStreamProcessCmds_1c05f0(void *p);

void SoundStreamThreadMain_1c1050(void *p)
{
    s32 ok;

    do {
        ok = !SoundStreamProcessCmds_1c05f0(p);
    } while (ok);
}

/* rg-override: frame driver conversion (old priority P-5 = 15); driven with RG_AUDIO=native */
extern int rg_StreamWait(void *arg);
extern void rg_StreamStep(void *arg);
static int rg_StreamAllowed(void) { return rg_audio_mode() == RG_AUDIO_NATIVE; }
static const rg_thread_conv rg_StreamConv = {
    (void *)SoundStreamThreadMain_1c1050, "SoundStreamThreadMain_1c1050", rg_StreamWait, rg_StreamStep, 0, 0,
    rg_StreamAllowed, 15, 1 /* sync */
};
__attribute__((constructor)) static void rg_StreamRegister(void) { rg_threads_convertible(&rg_StreamConv); }

/* rg-override: replaces game/src/main/sound/SoundCmdWorkerThread_1b6c10.c sha256 6b49042d46f4eca85a946624ae70dc0688575f517a483f9a373263bac0ea2fd8
 * why: native threads (docs/NATIVE-THREADS.md "Slice 5"): the sound command worker becomes a
 *      frame-driver step: its prologue (D_00481444 = 1) / loop condition / body / tail are split
 *      out (rg_SndWorker*) and the entry is the original loop over them (RG_THREADS=hle).  With
 *      RG_AUDIO=native it is never woken (the queue runs commands on the caller); a direct
 *      command (SoundQueueCmd_1b6d60's second path) signals it from a lower-priority flow, so
 *      the step runs there at once (sync), as the HLE switched to this priority-10 thread. */
/* rgp:protos */
#define RGP_SELF_SoundCmdWorkerThread_1b6c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */
#include "port/native_audio.h"   /* rg-override */

extern s32 SignalSema(s32);
extern s32 WaitSema(s32);
extern s32 (*D_0044AE10[])(void *);
extern s32 D_0048142C;
extern s32 D_00481434;
extern s32 D_00481440;
extern s32 D_00481444;
extern s32 D_00481448;
extern u8 D_0049D510[];

/* rg-override: the loop's `done` (a local of the entry): model state of the step */
static s32 rg_SndWorkerDone;

static void rg_SndWorkerPrologue(void *arg)
{
    (void)arg;
    rg_SndWorkerDone = 0;
    D_00481444 = 1;
}

static int rg_SndWorkerWait(void *arg)
{
    (void)arg;
    return rg_SndWorkerDone ? -1 : D_0048142C;
}

static void rg_SndWorkerStep(void *arg)
{
    s32 (*fn)(void *);

    (void)arg;
    D_00481448 = 0;
    if (D_00481440 > 0 && D_00481440 < 0x27) {
        fn = D_0044AE10[D_00481440];
        if (fn != NULL) {
            D_00481448 = fn(D_0049D510);
        }
    }
    switch (D_00481440) {
    case -1:
        rg_SndWorkerDone++;
    }
    SignalSema(D_00481434);
}

static void rg_SndWorkerExit(void *arg)
{
    (void)arg;
    D_00481444 = 2;
}

void SoundCmdWorkerThread_1b6c10(void)
{
    s32 s;

    rg_SndWorkerPrologue(0);
    while ((s = rg_SndWorkerWait(0)) >= 0) {
        WaitSema(s);
        rg_SndWorkerStep(0);
    }
    rg_SndWorkerExit(0);
}

/* rg-override: frame driver conversion (old priority P-10 = 10); driven with RG_THREADS=native
 * and RG_AUDIO=native (RG_THREADS=frame keeps it an HLE thread, as verified there) */
static int rg_SndWorkerAllowed(void) { return rg_threads_kernel_native() && rg_audio_mode() == RG_AUDIO_NATIVE; }
static const rg_thread_conv rg_SndWorkerConv = {
    (void *)SoundCmdWorkerThread_1b6c10, "SoundCmdWorkerThread_1b6c10", rg_SndWorkerWait, rg_SndWorkerStep,
    rg_SndWorkerExit, 0, rg_SndWorkerAllowed, 10, 1 /* sync */, 0, 0, rg_SndWorkerPrologue
};
__attribute__((constructor)) static void rg_SndWorkerRegister(void) { rg_threads_convertible(&rg_SndWorkerConv); }

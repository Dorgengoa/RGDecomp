/* rg-override: replaces game/src/main/sound/SoundStreamSlotThreadMain_1bc520.c sha256 add568ac885a1f9c5945fed6f5ebb8eab1b7efe41e9fd6dd67a4e7024a56df20
 * why: native frame driver (docs/NATIVE-THREADS.md "Frame driver", slice 2): the loop is split
 *      into its condition (rg_SlotWait) and body (rg_SlotStep) so the stream-slot thread can be a
 *      driven step: its VBLANK_END ISR still signals the semaphore, the driver runs the body at
 *      the next driver point.  The thread entry is the original loop over them (other modes). */
/* rgp:protos */
#define RGP_SELF_SoundStreamSlotThreadMain_1bc520 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */
#include "port/native_audio.h"   /* rg-override */
extern void ExitDeleteThread(void);
/*rgp*/
extern void WaitSema(s32);
extern s32 D_0047E214;
extern s32 D_00481500;
extern s32 D_0048150C;
extern s32 D_004814F0[2];
extern u8 D_004A25F0[];

/* rg-override: the loop's condition (the sema to wait on, or -1 = leave the loop) */
int rg_SlotWait(void *arg)
{
    (void)arg;
    return !D_00481500 ? D_0047E214 : -1;
}

/* rg-override: the loop body after WaitSema, unchanged */
void rg_SlotStep(void *arg)
{
    s32 *p;
    s32 i;

    (void)arg;
    if (D_0048150C != 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        p = &D_004814F0[i];
        if (*p != 0 && SoundStreamSlotUpdate_1bea70(D_004A25F0 + i * 0x128) != 0) {
            *p = 0;
        }
    }
}

void SoundStreamSlotThreadMain_1bc520(void)
{
    s32 s;

    while ((s = rg_SlotWait(0)) >= 0) {
        WaitSema(s);
        rg_SlotStep(0);
    }
    ExitDeleteThread();
}

/* rg-override: frame driver conversion (old priority P-5 = 15).  Driven only with
 * RG_AUDIO=native (the body's sound calls reach no IOP RPC there). */
static int rg_SlotAllowed(void) { return rg_audio_mode() == RG_AUDIO_NATIVE; }
static const rg_thread_conv rg_SlotConv = {
    (void *)SoundStreamSlotThreadMain_1bc520, "SoundStreamSlotThreadMain_1bc520", rg_SlotWait, rg_SlotStep,
    0, 1 /* ExitDeleteThread */, rg_SlotAllowed, 15
};
__attribute__((constructor)) static void rg_SlotRegister(void) { rg_threads_convertible(&rg_SlotConv); }

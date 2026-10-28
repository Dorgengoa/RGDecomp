/* rg-override: replaces game/src/main/sound/SoundThreadMain_1b6260.cpp sha256 f0b9c91811c26f3ca53c2afdf05d4a8b520010ed9d96544dd49d86d323c718a8
 * why: native threads (docs/NATIVE-THREADS.md "Slice 5"): the sound queue thread becomes a
 *      frame-driver step: the loop's wait (queue empty -> WaitSema(D_00481450)) and the body
 *      (dequeue, hand the command to the worker, wait for its reply) are split out
 *      (rg_SndThr*); the entry is the original loop over them (RG_THREADS=hle|frame).  Driven
 *      only with RG_THREADS=native and RG_AUDIO=native, where it is never woken (the queue runs
 *      commands on the caller); if it is, its wait for the worker's reply runs the worker's
 *      step first (the kernel's block hook), as the HLE ran the worker while this thread waited. */
#pragma opt_propagation off
#include "types.h"
#include "port/native_threads.h" /* rg-override */
#include "port/native_audio.h"   /* rg-override */
extern "C" {

typedef struct {
    s32 b[10];
} Data001B6260;

typedef struct {
    s32 id;
    Data001B6260 data;
} Msg001B6260;

typedef struct {
    u8 empty;
    s32 rd;
    s32 wr;
    Msg001B6260 q[64];
} Queue001B6260;

void DeleteSema(s32);
void ExitDeleteThread(void);
s32 SignalSema(s32);
s32 WaitSema(s32);
void *memcpy(void *, const void *, u32);
extern s32 D_0048142C;
extern s32 D_00481430;
extern s32 D_00481434;
extern s32 D_00481440;
extern s32 D_0048144C;
extern s32 D_00481450;
extern u8 D_00481458;
extern u8 D_0049D510[0x28];
extern Queue001B6260 D_0049DD70;
}

/* rg-override: the loop's `break` (id -1) as model state of the step */
static s32 rg_SndThrBreak;

/* rg-override: the loop condition and the first half of an iteration (is the queue
 * empty?): the sema to wait on (empty), RG_CONV_READY (not empty), or -1 (loop ends) */
static int rg_SndThrWait(void *arg)
{
    u8 full;
    s32 t;

    (void)arg;
    if (rg_SndThrBreak || !D_00481458) {
        return -1;
    }
    WaitSema(D_0048144C);
    t = D_0049DD70.empty != 0;
    if (t) {
        t = D_0049DD70.rd == D_0049DD70.wr;
    }
    full = t;
    SignalSema(D_0048144C);
    return full ? D_00481450 : RG_CONV_READY;
}

/* rg-override: the rest of an iteration, after its WaitSema(D_00481450) (if any) */
static void rg_SndThrStep(void *arg)
{
    Msg001B6260 msg __attribute__((aligned(16)));
    bool ok;
    s32 id;
    Msg001B6260 *row;
    s32 n;
    Data001B6260 *src;

    (void)arg;
    msg.id = 0;
    WaitSema(D_0048144C);
    if (D_0049DD70.empty != 0 && D_0049DD70.rd == D_0049DD70.wr) {
        ok = false;
    } else {
        row = &D_0049DD70.q[D_0049DD70.rd];
        msg.id = row->id;
        msg.data = row->data;
        n = (D_0049DD70.rd + 1) & 0x3F;
        D_0049DD70.rd = n;
        if (n == D_0049DD70.wr) {
            D_0049DD70.empty = 1;
        }
        ok = true;
    }
    SignalSema(D_0048144C);
    if ((ok & 0xFF) == 0) {
        return;
    }
    id = msg.id;
    if (id == -1) {
        rg_SndThrBreak = 1;
        return;
    }
    if (WaitSema(D_00481430) < 0) {
        return;
    }
    D_00481440 = id;
    src = &msg.data;
    if (src) {
        memcpy(D_0049D510, src, 0x28);
    }
    SignalSema(D_0048142C);
    WaitSema(D_00481434);
    SignalSema(D_00481430);
}

/* rg-override: after the loop (ExitDeleteThread follows: the conversion's exit_delete) */
static void rg_SndThrExit(void *arg)
{
    (void)arg;
    if (D_0048144C > 0) {
        DeleteSema(D_0048144C);
    }
    if (D_00481450 > 0) {
        DeleteSema(D_00481450);
    }
    D_0048144C = -1;
    D_00481450 = -1;
}

extern "C" void SoundThreadMain_1b6260(void) {
    s32 s;

    rg_SndThrBreak = 0;
    while ((s = rg_SndThrWait(0)) >= 0) {
        if (s != RG_CONV_READY) {
            WaitSema(s);
        }
        rg_SndThrStep(0);
    }
    rg_SndThrExit(0);
    ExitDeleteThread();
}

/* rg-override: frame driver conversion (old priority 9: the worker's priority - 1);
 * native kernel + native audio only (see the header) */
static int rg_SndThrAllowed(void) { return rg_threads_kernel_native() && rg_audio_mode() == RG_AUDIO_NATIVE; }
static void rg_SndThrPrologue(void *arg)
{
    (void)arg;
    rg_SndThrBreak = 0;
}
static const rg_thread_conv rg_SndThrConv = {
    (void *)SoundThreadMain_1b6260, "SoundThreadMain_1b6260", rg_SndThrWait, rg_SndThrStep, rg_SndThrExit, 1,
    rg_SndThrAllowed, 9, 1 /* sync */, 0, 0, rg_SndThrPrologue
};
__attribute__((constructor)) static void rg_SndThrRegister(void) { rg_threads_convertible(&rg_SndThrConv); }

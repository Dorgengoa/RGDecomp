/* rg-override: replaces game/src/main/file/CdDiskWatchThread_17fdc0.c sha256 3a618c355e08889b3c539fbe343676eb31e06ebd537b953907da0b178508b53a
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): the data folder cannot be ejected, so the
 *      watch no longer polls sceCdGetDiskType (it never saw "no disc" on the host); the
 *      thread, its wake semaphore and the file-layer lock are kept as they were.
 *      Native threads (docs/NATIVE-THREADS.md): the loop is split into rg_DiskWatchWait (the
 *      wait at the current point: the wake sema, the file-layer lock, or -1 = leave),
 *      rg_DiskWatchStep (the body after that wait) and rg_DiskWatchExit (the tail), registered
 *      below as a frame-driver step; the thread entry is the original loop over them
 *      (RG_THREADS=hle: the same kernel calls in the same order). */
/* rgp:protos */
#define RGP_SELF_CdDiskWatchThread_17fdc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */

/*rgp*/
extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 D_0047E028;
extern s32 D_0047E038;
extern s32 D_004811C4;
extern s32 D_0048121C;
extern s32 D_00481220;
extern s32 D_00481224;
extern s32 D_00481228;

/* rg-override: where the loop is: 0 = at its top (waits for the wake), 1 = woken, waiting
 * for the file-layer lock (the body's WaitSema(D_0047E028) as a wait of its own, so a driven
 * step never blocks: it is a real waiter on the lock, as the thread was) */
static s32 rg_DiskWatchAt;

/* rg-override: the wait at the current point (the wake sema; the lock; -1 = the loop ends) */
static int rg_DiskWatchWait(void *arg)
{
    (void)arg;
    if (rg_DiskWatchAt == 1)
        return D_0047E028;
    return D_00481220 != 0 ? -1 : D_0047E038;
}

/* rg-override: the body after the lock is held (or there is none) */
static void rg_DiskWatchLocked(void)
{
    D_004811C4 += 1;
    /* rg-override: was if (sceCdGetDiskType_12a9d8() == 0) CdWaitFileFound_180290(); */
    if (D_0047E028 >= 0) {
        SignalSema(D_0047E028);
    }
    D_004811C4 -= 1;
}

/* rg-override: the body after the current wait returned */
static void rg_DiskWatchStep(void *arg)
{
    (void)arg;
    if (rg_DiskWatchAt == 1) { /* WaitSema(D_0047E028) returned */
        rg_DiskWatchAt = 0;
        rg_DiskWatchLocked();
        return;
    }
    if (D_0048121C != 0 && D_00481228 == 0) {
        if (D_0047E028 >= 0) {
            rg_DiskWatchAt = 1; /* next: WaitSema(D_0047E028) */
            return;
        }
        rg_DiskWatchLocked();
    }
}

/* rg-override: after the loop */
static void rg_DiskWatchExit(void *arg)
{
    (void)arg;
    D_00481224 = 1;
}

void CdDiskWatchThread_17fdc0(void) {
    s32 s;

    rg_DiskWatchAt = 0;
    while ((s = rg_DiskWatchWait(0)) >= 0) {
        WaitSema(s);
        rg_DiskWatchStep(0);
    }
    rg_DiskWatchExit(0);
}

/* rg-override: frame driver conversion (woken every 30th VBLANK_START by CdDiskWatchWakeIsr_17ff10;
 * the HLE switched to this priority-15 thread when a flow released the lock it waited for) */
static const rg_thread_conv rg_DiskWatchConv = {
    (void *)CdDiskWatchThread_17fdc0, "CdDiskWatchThread_17fdc0", rg_DiskWatchWait, rg_DiskWatchStep,
    rg_DiskWatchExit, 0, 0, 15 /* P-5 */, 1 /* sync: the lock's release from a flow */, 0, 0, 0,
    1 /* anywhere: its lock wait is a real wait */
};
__attribute__((constructor)) static void rg_DiskWatchRegister(void) { rg_threads_convertible(&rg_DiskWatchConv); }

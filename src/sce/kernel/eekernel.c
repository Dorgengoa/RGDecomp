/* SPDX-License-Identifier: CC0-1.0
 * EE kernel SDK surface: thin wrappers over ps2k (src/ps2/kernel).
 * Do not include <windows.h> here (see eekernel.h). */
#include "eekernel.h"

#include "ps2k.h"
#include "kcensus.h" /* RG_KCENSUS (docs/NATIVE-THREADS.md): one branch per call when off */
#include "rg_threads.h" /* frame driver (src/native/threads) */

typedef char check_tp_size[sizeof(struct ThreadParam) == 48 || sizeof(void *) != 4 ? 1 : -1];
typedef char check_sp_size[sizeof(struct SemaParam) == 24 ? 1 : -1];

/* ---- threads --------------------------------------------------------- */

int CreateThread(struct ThreadParam *p)
{
    if (!p)
        return -1;
    int id = ps2k_create_thread((ps2k_entry_fn)p->entry, p->stack, p->stackSize, p->gpReg,
                                p->initPriority, p->attr, p->option);
    RG_KC("CT", id, p->initPriority, p->stackSize, p->entry);
    return id;
}

int DeleteThread(int id) { RG_KC("DT", id, 0, 0, 0); return ps2k_delete_thread(id); }
int StartThread(int id, void *arg)
{
    /* libkernl StartThread returns -1 when Status.IE == 0 (handler context)
     * instead of issuing the syscall. */
    if (ps2k_in_handler())
        return -1;
    RG_KC("ST", id, 0, 0, 0);
    return ps2k_start_thread(id, arg);
}
void ExitThread(void) { RG_KC("XT", 0, 0, 0, 0); ps2k_exit_thread(); }
void ExitDeleteThread(void) { RG_KC("XD", 0, 0, 0, 0); ps2k_exit_delete_thread(); }
int TerminateThread(int id) { RG_KC("TT", id, 0, 0, 0); return ps2k_terminate_thread(id, 0); }
int iTerminateThread(int id) { RG_KC("iTT", id, 0, 0, 0); return ps2k_terminate_thread(id, 1); }
int ChangeThreadPriority(int id, int prio) { RG_KC("CP", id, prio, 0, 0); return ps2k_change_thread_priority(id, prio, 0); }
int iChangeThreadPriority(int id, int prio) { RG_KC("iCP", id, prio, 0, 0); return ps2k_change_thread_priority(id, prio, 1); }
/* RG_THREADS=native|frame: a rotate (ThreadYield_1d2b70: RotateThreadReadyQueue(own
 * priority)) is a frame-driver point; natively a yield with no other flow ready waits
 * until anything else ran (docs/NATIVE-THREADS.md). */
int RotateThreadReadyQueue(int prio)
{
    RG_KC("RQ", prio, 0, 0, 0);
    if (rg_frame_native() && !ps2k_in_handler() && ps2k_get_thread_id() > 0) {
        rg_frame_yield(prio);
        return prio;
    }
    return ps2k_rotate_thread_ready_queue(prio, 0);
}
int iRotateThreadReadyQueue(int prio) { RG_KC("iRQ", prio, 0, 0, 0); return ps2k_rotate_thread_ready_queue(prio, 1); }
int ReleaseWaitThread(int id) { RG_KC("RW", id, 0, 0, 0); return ps2k_release_wait_thread(id, 0); }
int iReleaseWaitThread(int id) { RG_KC("iRW", id, 0, 0, 0); return ps2k_release_wait_thread(id, 1); }
int GetThreadId(void) { return ps2k_get_thread_id(); }

static int refer_thread(int id, struct ThreadParam *out, int isr)
{
    ps2k_thread_info i;
    int r = ps2k_refer_thread_status(id, &i, isr);
    if (r >= 0 && out) {
        out->status = i.status;
        out->entry = i.entry;
        out->stack = i.stack;
        out->stackSize = i.stack_size;
        out->gpReg = i.gp;
        out->initPriority = i.init_priority;
        out->currentPriority = i.current_priority;
        out->attr = i.attr;
        out->option = i.option;
        out->waitType = i.wait_type;
        out->waitId = i.wait_id;
        out->wakeupCount = i.wakeup_count;
    }
    return r;
}

int ReferThreadStatus(int id, struct ThreadParam *out) { RG_KC("RT", id, 0, 0, 0); return refer_thread(id, out, 0); }
int iReferThreadStatus(int id, struct ThreadParam *out) { RG_KC("iRT", id, 0, 0, 0); return refer_thread(id, out, 1); }
/* Bring-up diagnostics (docs/BRINGUP.md "Diagnostics"): the code address
 * that last called a blocking kernel service, per guest thread id, so a stuck
 * thread can be located (rg_game_main RG_STATUS_THREADS, resolve the RVA with
 * rg-game.map).  Two frames: the direct caller and, when the direct caller is
 * a game-tree alias (DelayThread_117618), its caller. */
#define RG_WAIT_SLOTS 64
uintptr_t rg_kernel_wait_caller[RG_WAIT_SLOTS];
static void note_wait(void *ra)
{
    int t = ps2k_get_thread_id();
    if (t >= 0 && t < RG_WAIT_SLOTS)
        rg_kernel_wait_caller[t] = (uintptr_t)ra;
}
int SleepThread(void) { RG_KC("SL", 0, 0, 0, 0); note_wait(__builtin_return_address(0)); return ps2k_sleep_thread(); }
int WakeupThread(int id) { RG_KC("WK", id, 0, 0, 0); return ps2k_wakeup_thread(id, 0); }
int iWakeupThread(int id) { RG_KC("iWK", id, 0, 0, 0); return ps2k_wakeup_thread(id, 1); }
int CancelWakeupThread(int id) { RG_KC("CW", id, 0, 0, 0); return ps2k_cancel_wakeup_thread(id, 0); }
int iCancelWakeupThread(int id) { RG_KC("iCW", id, 0, 0, 0); return ps2k_cancel_wakeup_thread(id, 1); }
int SuspendThread(int id) { RG_KC("SU", id, 0, 0, 0); return ps2k_suspend_thread(id, 0); }
int iSuspendThread(int id) { RG_KC("iSU", id, 0, 0, 0); return ps2k_suspend_thread(id, 1); }
int ResumeThread(int id) { RG_KC("RS", id, 0, 0, 0); return ps2k_resume_thread(id, 0); }
int iResumeThread(int id) { RG_KC("iRS", id, 0, 0, 0); return ps2k_resume_thread(id, 1); }
/* RG_THREADS=native: DelayThread is a frame-driver point + a timed wait
 * (docs/NATIVE-THREADS.md "Frame driver"); otherwise libkernl's algorithm. */
static int delay_thread(int usec)
{
    if (rg_frame_native())
        return rg_frame_delay((unsigned)usec);
    return ps2k_delay_thread((unsigned)usec);
}
int DelayThread(int usec) { RG_KC("DL", usec, 0, 0, 0); note_wait(__builtin_return_address(0)); return delay_thread(usec); }

/* ---- semaphores ------------------------------------------------------ */

int CreateSema(struct SemaParam *p)
{
    if (!p)
        return -1;
    int id = ps2k_create_sema(p->initCount, p->maxCount, p->attr, p->option);
    RG_KC("CS", id, p->initCount, p->maxCount, 0);
    return id;
}

/* census rows carry the count and waiter number before the call (peeked,
 * no kernel call) */
#define KC_SEMA(kind, id)                                                        \
    do {                                                                         \
        if (rg_kcensus_on) {                                                     \
            int32_t c_ = -1, w_ = -1;                                            \
            ps2k_peek_sema((id), &c_, &w_);                                      \
            rg_kcensus_ev((kind), __builtin_return_address(0), (id), c_, w_, 0); \
        }                                                                        \
    } while (0)
int DeleteSema(int id) { KC_SEMA("DS", id); return ps2k_delete_sema(id, 0); }
int iDeleteSema(int id) { KC_SEMA("iDS", id); return ps2k_delete_sema(id, 1); }
int SignalSema(int id) { KC_SEMA("SS", id); return ps2k_signal_sema(id, 0); }
int iSignalSema(int id) { KC_SEMA("iSS", id); return ps2k_signal_sema(id, 1); }
int WaitSema(int id) { KC_SEMA("WS", id); note_wait(__builtin_return_address(0)); return ps2k_wait_sema(id); }
int PollSema(int id) { KC_SEMA("PS", id); return ps2k_poll_sema(id, 0); }
int iPollSema(int id) { KC_SEMA("iPS", id); return ps2k_poll_sema(id, 1); }

static int refer_sema(int id, struct SemaParam *out, int isr)
{
    ps2k_sema_info i;
    int r = ps2k_refer_sema_status(id, &i, isr);
    if (r >= 0 && out) {
        out->currentCount = i.current_count;
        out->maxCount = i.max_count;
        out->initCount = i.init_count;
        out->numWaitThreads = i.num_wait_threads;
        out->attr = i.attr;
        out->option = i.option;
    }
    return r;
}

int ReferSemaStatus(int id, struct SemaParam *out) { KC_SEMA("RS?", id); return refer_sema(id, out, 0); }
int iReferSemaStatus(int id, struct SemaParam *out) { KC_SEMA("iRS?", id); return refer_sema(id, out, 1); }

/* ---- interrupts ------------------------------------------------------ */

int AddIntcHandler(int cause, int (*h)(int), int next)
{
    int id = ps2k_add_intc_handler(cause, h, next);
    RG_KC("AI", cause, next, id, h);
    return id;
}
int AddIntcHandler2(int cause, int (*h)(int, void *, void *), int next, void *arg)
{
    int id = ps2k_add_intc_handler2(cause, h, next, arg);
    RG_KC("AI", cause, next, id, h);
    return id;
}
int RemoveIntcHandler(int cause, int id) { RG_KC("RI", cause, id, 0, 0); return ps2k_remove_intc_handler(cause, id); }
int AddDmacHandler(int ch, int (*h)(int), int next)
{
    int id = ps2k_add_dmac_handler(ch, h, next);
    RG_KC("AD", ch, next, id, h);
    return id;
}
int AddDmacHandler2(int ch, int (*h)(int, void *, void *), int next, void *arg)
{
    int id = ps2k_add_dmac_handler2(ch, h, next, arg);
    RG_KC("AD", ch, next, id, h);
    return id;
}
int RemoveDmacHandler(int ch, int id) { RG_KC("RD", ch, id, 0, 0); return ps2k_remove_dmac_handler(ch, id); }
int EnableIntc(int cause) { RG_KC("EI", cause, 0, 0, 0); return ps2k_enable_intc(cause, 0); }
int DisableIntc(int cause) { RG_KC("DI", cause, 0, 0, 0); return ps2k_disable_intc(cause, 0); }
int iEnableIntc(int cause) { RG_KC("iEI", cause, 0, 0, 0); return ps2k_enable_intc(cause, 1); }
int iDisableIntc(int cause) { RG_KC("iDI", cause, 0, 0, 0); return ps2k_disable_intc(cause, 1); }
int EnableDmac(int ch) { RG_KC("ED", ch, 0, 0, 0); return ps2k_enable_dmac(ch, 0); }
int DisableDmac(int ch) { RG_KC("DD", ch, 0, 0, 0); return ps2k_disable_dmac(ch, 0); }
int iEnableDmac(int ch) { RG_KC("iED", ch, 0, 0, 0); return ps2k_enable_dmac(ch, 1); }
int iDisableDmac(int ch) { RG_KC("iDD", ch, 0, 0, 0); return ps2k_disable_dmac(ch, 1); }
int DIntr(void) { RG_KC("DX", 0, 0, 0, 0); return ps2k_di(); }
int EIntr(void) { RG_KC("EX", 0, 0, 0, 0); return ps2k_ei(); }

/* ---- alarms ---------------------------------------------------------- */

int SetAlarm(unsigned short time, void (*h)(int, unsigned short, void *), void *arg)
{
    RG_KC("SA", time, 0, 0, h);
    return ps2k_set_alarm(time, (ps2k_alarm_fn)h, arg, 0);
}
int iSetAlarm(unsigned short time, void (*h)(int, unsigned short, void *), void *arg)
{
    RG_KC("iSA", time, 0, 0, h);
    return ps2k_set_alarm(time, (ps2k_alarm_fn)h, arg, 1);
}
int ReleaseAlarm(int id) { RG_KC("RA", id, 0, 0, 0); return ps2k_release_alarm(id, 0); }
int iReleaseAlarm(int id) { RG_KC("iRA", id, 0, 0, 0); return ps2k_release_alarm(id, 1); }

/* ---- cache ----------------------------------------------------------- */

/* FlushCache(mode) writes back (0) / invalidates (2) the EE data or
 * instruction cache before DMA or after loading code (FixedTexUploadImpl,
 * GfxEndFrame, Vif1DmaStart, crt0, the overlay loader, ...).  Host memory is
 * coherent and the DMA models read it directly: a no-op.  (Moved here from
 * src/crt/crt_ee.c.)  iFlushCache is the handler-context form. */
void FlushCache(int mode) { (void)mode; }
void iFlushCache(int mode) { (void)mode; }
/* SyncDCache(start, end) / InvalidDCache: the same for an address range
 * (GfxFlipBuffersMaybe_143650 syncs its DBuff before the GS reads it):
 * no-ops for the same reason. */
void SyncDCache(void *start, void *end) { (void)start; (void)end; }
void iSyncDCache(void *start, void *end) { (void)start; (void)end; }
void InvalidDCache(void *start, void *end) { (void)start; (void)end; }
void iInvalidDCache(void *start, void *end) { (void)start; (void)end; }

/* ---- game-tree symbol names ------------------------------------------ */
/* Each logs its own census row so the row's caller is the game function. */

int StartThread_1176e0(int id, void *arg)
{
    if (ps2k_in_handler())
        return -1;
    RG_KC("ST", id, 0, 0, 0);
    return ps2k_start_thread(id, arg);
}
int DelayThread_117618(int usec) { RG_KC("DL", usec, 0, 0, 0); note_wait(__builtin_return_address(0)); return delay_thread(usec); }
int EnableIntc_1170e8(int cause) { RG_KC("EI", cause, 0, 0, 0); return ps2k_enable_intc(cause, 0); }
int DisableIntc_117080(int cause) { RG_KC("DI", cause, 0, 0, 0); return ps2k_disable_intc(cause, 0); }
int EnableDmac_1171b8(int ch) { RG_KC("ED", ch, 0, 0, 0); return ps2k_enable_dmac(ch, 0); }
int DisableDmac_117150(int ch) { RG_KC("DD", ch, 0, 0, 0); return ps2k_disable_dmac(ch, 0); }
int DisableIntr_120660(void) { RG_KC("DX", 0, 0, 0, 0); return ps2k_di(); }
int EnableIntr_1206b0(void) { RG_KC("EX", 0, 0, 0, 0); return ps2k_ei(); }
int CpuIntrDisabled_117070(void) { return (ps2k_cop0_status() & 1u) == 0; }

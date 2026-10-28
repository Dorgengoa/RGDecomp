/* SPDX-License-Identifier: CC0-1.0
 * Native threads and timing (de-emulation lane, docs/NATIVE-THREADS.md).
 *
 * Mode switch, the native frame driver and the registry of game threads that
 * already run natively.  Still hosted by the EE kernel HLE (src/ps2/kernel):
 * the HLE keeps the clock and schedules the game threads that are not
 * converted yet, so it stays the oracle (RG_THREADS=hle).
 *
 *   RG_THREADS=native  (default) slice 5: no EE scheduler.  The kernel runs in
 *                      its frame-driven mode (ps2k cfg.native): two game
 *                      coroutines ("flows": main and the loading screen) at
 *                      fixed addresses, every other game thread a driven step,
 *                      interrupts as explicit calls in the driver's pass, logic
 *                      time moved only by waits (nominal frame cost).  Needs
 *                      RG_AUDIO=native (else the runtime falls back to frame).
 *   RG_THREADS=frame   slices 2-3: the frame driver over the HLE scheduler:
 *                      converted game threads are "driven" (never scheduled;
 *                      their bodies run as plain steps at driver points of the
 *                      game flows: the waits WaitVsyncCount, DelayThread,
 *                      condition waits); loading-screen condition polls are
 *                      condition waits; main / loading screen are HLE threads.
 *   RG_THREADS=service slice 1 (identity check): SysTick runs as a fiberless
 *                      service thread that the HLE scheduler still places.
 *   RG_THREADS=hle     every game thread is an HLE thread (fiber): the oracle.
 *
 * The game-side view (plain C types) is include/port/native_threads.h. */
#ifndef RG_THREADS_H
#define RG_THREADS_H

#include <stdint.h>

#include "rg_threads_oracle.h" /* RG_THREADS_ORACLE: 0 in RG_NATIVE_ONLY builds (native only) */

#ifdef __cplusplus
extern "C" {
#endif

#define RG_THREADS_HLE     0 /* every game thread is an EE-kernel HLE thread (fiber) */
#define RG_THREADS_NATIVE  1 /* the frame driver (default) */
#define RG_THREADS_SERVICE 2 /* slice 1: service steps hosted by the HLE scheduler */
#define RG_THREADS_FRAME   3 /* slices 2-3: the frame driver over the HLE scheduler */

/* RG_THREADS=native|frame|service|hle, read once (default native).  RG_NATIVE_ONLY builds
 * (RG_THREADS_ORACLE 0) have native only: other values are refused with a message. */
int rg_threads_mode(void);
/* The runtime's fallback (before the kernel starts): native needs RG_AUDIO=native. */
void rg_threads_force_mode(int mode, const char *why);
const char *rg_threads_mode_name(int mode);

/* Slice 1 (RG_THREADS=service): register game thread `tid` (created, not
 * started) as a fiberless service step hosted by the HLE scheduler: the loop
 * `while ((s = wait(arg)) >= 0) { WaitSema(s); step(arg); }`.  Returns 1 when
 * the thread is now a service step, 0 when it stays an HLE thread (other
 * mode, or `allowed` = 0: the step could block under the current
 * configuration, e.g. RG_AUDIO=hle). */
int rg_threads_service(int tid, int (*wait)(void *arg), void (*step)(void *arg), int allowed,
                       const char *name);

/* ---- convertible threads (RG_THREADS=native) ---------------------------
 * A game thread whose entry is
 *     while ((s = wait(arg)) >= 0) { WaitSema(s); step(arg); }  exit_tail(arg);
 * (then ExitThread, or ExitDeleteThread when exit_delete) is registered by
 * the game-side override of that entry (a constructor), keyed by the entry
 * address.  When the game starts such a thread in native mode it is parked
 * (ps2k_thread_set_driven) and stays a real waiter on the semaphore of its
 * loop (ps2k_driven_wait), so the game's SignalSema / PollSema see the HLE's
 * semaphore state.  When its WaitSema returns (a signal), the frame driver
 * runs one step at the next driver point, in `order` (the old priority, then
 * thread id), or at once on the signalling game thread when `sync` and the
 * HLE would have switched to it there.  wait() may return RG_CONV_READY
 * (runnable without waiting).  step() runs on a game flow; it may block on
 * the HLE (a contended mutex) but should run to completion. */
typedef struct rg_thread_conv {
    void       *entry;
    const char *name;
    int  (*wait)(void *arg);      /* the loop's sema, or < 0 = the loop ends */
    void (*step)(void *arg);      /* the body after WaitSema returned */
    void (*exit_tail)(void *arg); /* after the loop (NULL = nothing) */
    int   exit_delete;            /* the body ends in ExitDeleteThread */
    int  (*allowed)(void);        /* NULL = always; 0 = stays an HLE thread now */
    int   order;                  /* run order at a driver point (old priority) */
    /* optional */
    int   sync;                   /* also run at once when a lower-priority game thread
                                     signals its sema (the HLE switched to it there) */
    void (*point)(void *arg);     /* at every driver point, before the steps (async
                                     completions); arg = NULL */
    void (*drain)(void);          /* host side: finish its host jobs (field end) */
    void (*prologue)(void *arg);  /* the entry's code before its loop (NULL = none); runs
                                     once, before the first wait() */
    int   anywhere;               /* RG_THREADS=native: the step may also run in the driver's
                                     pass, whatever the flows hold (it takes no lock a waiting
                                     flow could hold, or waits for it as a real waiter); 0 = only
                                     at a flow's driver point or at its signal (sync) */
} rg_thread_conv;
void rg_threads_convertible(const rg_thread_conv *c);
#define RG_CONV_READY 0x7FFFFFFF /* wait(): runnable now, no semaphore to wait on */
/* A game thread that stays a game coroutine in native mode ("flow", e.g. the loading
 * screen's frame loop, docs/NATIVE-THREADS.md "Slice 4"): registered from the game
 * side so the log can tell intended flows from unconverted threads (which also run
 * as flows, as a fallback, and are listed). */
void rg_threads_flow(void *entry, const char *name);

/* ---- frame driver (src/native/threads/rg_frame.c) ----------------------
 * Driver points: every wait of a game flow goes through one of these.  In
 * modes other than native they are not called (the overrides keep the
 * original code). */
int  rg_frame_native(void);            /* the frame driver is on: RG_THREADS=native or frame */
int  rg_threads_kernel_native(void);   /* RG_THREADS=native: no EE scheduler (slice 5) */
void rg_frame_yield(int prio);         /* ThreadYield / RotateThreadReadyQueue(own prio) */
void rg_frame_point(void);             /* run the driven steps that are due */
int  rg_frame_is_driven(void *entry);  /* a thread with this entry is parked for the driver */
int  rg_frame_delay(uint32_t usec);    /* DelayThread: driver point + timed wait */
/* Block the calling game flow until cond(arg) != 0; the condition is
 * re-checked whenever anything else ran (another thread, a handler, a driven
 * step), never by time polling.  Driver points before each check. */
void rg_frame_wait_cond(int (*cond)(void *arg), void *arg, const char *what);
/* Logic ticks: the main flow's frame waits (WaitVsyncCount on thread 1), i.e. game main-loop
 * iterations; paced mode reports them against host time (docs/NATIVE-THREADS.md "Paced mode") */
void     rg_frame_frame_wait(void);
uint64_t rg_frame_logic_ticks(void);
/* Field end (src/runtime, after each field): the drain() of every conversion,
 * so no host job is in flight at a field boundary (save states). */
void rg_threads_field_end(void);

/* counters for logs and tests */
typedef struct rg_threads_stats {
    int      mode;
    int      services;      /* slice 1: threads registered as service steps */
    int      refused;       /* stayed HLE threads (allowed = 0) */
    uint32_t steps;         /* slice 1 service steps run (kernel count) */
    uint32_t deferred;      /* preemptions deferred to a step's end (should be 0) */
    int      driven;        /* threads parked for the frame driver */
    uint64_t driven_steps;  /* steps the driver ran */
    uint64_t points;        /* driver points */
    uint64_t delays;        /* DelayThread calls through the driver */
    uint64_t cond_waits;    /* condition waits */
    uint64_t cond_wakes;    /* wakes inside condition waits (re-checks) */
} rg_threads_stats;
void rg_threads_get_stats(rg_threads_stats *out);

#ifdef __cplusplus
}
#endif
#endif

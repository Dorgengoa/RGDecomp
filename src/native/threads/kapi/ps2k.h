/* SPDX-License-Identifier: CC0-1.0
 *
 * ps2k: the EE kernel service API.  Two implementations (docs/NATIVE-THREADS.md
 * "Native kernel table"): the EE kernel HLE core (src/ps2/kernel, PLAN.md P2 "EE
 * kernel": the oracle, RG_THREADS=hle|service|frame; semantics, deviations and open
 * questions in docs/KERNEL.md) and the native kernel table (src/native/threads/rg_nk*.c:
 * cfg.native, RG_THREADS=native, the only one RG_NATIVE_ONLY builds link).  A default
 * build's src/ps2/kernel/kdispatch.c picks one at ps2k_init.  The description below is
 * the HLE's; the native table keeps its records and ids but has no scheduler (see
 * cfg.native).  After a prototype change: python tools/native/thread_api.py.
 *
 * - Priority-based, NON-preemptive scheduling; exactly one guest thread runs
 *   at a time.  Each guest thread is a host fiber.
 * - A deterministic virtual clock (EE bus cycles, 147.456 MHz).  It advances
 *   only when every thread is blocked (idle: jump to the next event) or when a
 *   model explicitly charges time (ps2k_charge).  There is no wall-clock input;
 *   a pacing hook may throttle the idle jumps to real time.
 * - Interrupts (INTC causes, DMAC channels, kernel alarms) are latched and
 *   delivered only at DEFINED POINTS: the entry of every thread-context kernel
 *   call, EI / EnableIntc / EnableDmac, ps2k_poll / ps2k_charge, and idle.
 *   Delivery in thread context needs the thread's EIE (DI/EI) set.
 *
 * Calls are split into thread-context calls (isr == 0) and handler-context
 * "i" calls (isr == 1).  Calling one in the wrong context is a violation: the
 * violation hook runs (default: print + abort) and the call returns -1.
 *
 * Nothing here is thread-safe across HOST threads: one host thread owns the
 * kernel (it runs ps2k_run).
 */
#ifndef PS2K_H
#define PS2K_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- clock constants ------------------------------------------------- */
#define PS2K_BUSCLK 147456000u /* virtual clock unit = 1 bus cycle */
/* NTSC field = 2,460,060 bus cycles: matches PCSX2: BUSCLK/59.94 (the
 * reference oracle; tools/trace measures 4,920,120 EE cycles per field), so
 * virtual time lines up with reference traces.  (Exact NTSC would be
 * BUSCLK*1001/60000 = 2,460,057.6.)  hsync = field/262.5 = 9,371.66.  Both
 * are kept exact in units of 1/2625 bus cycle. */
#define PS2K_SUB          2625u
#define PS2K_FIELD_SUB    6457657500ull /* field  * 2625 = 2460060 * 2625 */
#define PS2K_HSYNC_SUB    24600600ull   /* hsync  * 2625 = field * 10 */

/* ---- limits ---------------------------------------------------------- */
#define PS2K_MAX_THREADS  256
#define PS2K_MAX_SEMAS    256
#define PS2K_MAX_ALARMS   64
#define PS2K_MAX_HANDLERS 64
#define PS2K_HANDLER_ID_MAX 128 /* INTC+DMAC handler ids share 1..128 (VALIDATION.md 2c) */
#define PS2K_PRIO_MAX     127 /* 0 = highest, 127 = lowest */

/* ---- thread status (EE THS_*) ---------------------------------------- */
#define PS2K_THS_RUN         0x01
#define PS2K_THS_READY       0x02
#define PS2K_THS_WAIT        0x04
#define PS2K_THS_SUSPEND     0x08
#define PS2K_THS_WAITSUSPEND 0x0C
#define PS2K_THS_DORMANT     0x10

#define PS2K_TSW_NONE  0
#define PS2K_TSW_SLEEP 1
#define PS2K_TSW_SEMA  2

#define PS2K_TH_SELF 0

/* ---- INTC causes / DMAC channels ------------------------------------- */
enum {
    PS2K_INTC_GS = 0, PS2K_INTC_SBUS, PS2K_INTC_VBLANK_START, PS2K_INTC_VBLANK_END,
    PS2K_INTC_VIF0, PS2K_INTC_VIF1, PS2K_INTC_VU0, PS2K_INTC_VU1, PS2K_INTC_IPU,
    PS2K_INTC_TIMER0, PS2K_INTC_TIMER1, PS2K_INTC_TIMER2, PS2K_INTC_TIMER3,
    PS2K_INTC_SFIFO, PS2K_INTC_VU0WD, PS2K_INTC_COUNT
};
enum {
    PS2K_DMAC_VIF0 = 0, PS2K_DMAC_VIF1, PS2K_DMAC_GIF, PS2K_DMAC_FROM_IPU, PS2K_DMAC_TO_IPU,
    PS2K_DMAC_SIF0, PS2K_DMAC_SIF1, PS2K_DMAC_SIF2, PS2K_DMAC_FROM_SPR, PS2K_DMAC_TO_SPR,
    PS2K_DMAC_COUNT
};

/* ---- errors ---------------------------------------------------------- */
#define PS2K_ERR              (-1)
#define PS2K_DELAY_E_DISABLED ((int32_t)0x80008008u) /* DelayThread with EIE=0 (libkernl) */
#define PS2K_DELAY_E_NOSEMA   ((int32_t)0x80008003u) /* DelayThread could not create its sema */

/* ---- callbacks ------------------------------------------------------- */
struct ps2k_trace_rec;
typedef void (*ps2k_entry_fn)(void *arg);
typedef int (*ps2k_handler_fn)(int cause);                    /* AddIntcHandler  */
typedef int (*ps2k_handler2_fn)(int cause, void *arg, void *addr); /* ...Handler2 */
typedef void (*ps2k_alarm_fn)(int32_t id, uint16_t time, void *arg);
typedef void (*ps2k_violation_fn)(const char *call, const char *why);
typedef void (*ps2k_pacing_fn)(uint64_t from_cycles, uint64_t to_cycles, void *user);
typedef void (*ps2k_trace_fn)(const struct ps2k_trace_rec *rec, void *user);

/* ---- configuration / lifetime ---------------------------------------- */
typedef struct ps2k_config {
    size_t   host_stack_size;   /* host fiber stack reserve per guest thread (default 1 MiB) */
    int      vblank_enable;     /* deliver VBLANK_START/END at NTSC rate (default 1) */
    uint32_t vblank_start_line; /* hsync of VBLANK_START within a field (default 240) */
    uint64_t stop_at_cycles;    /* ps2k_run returns TIME_LIMIT before passing this (0 = none) */
    uint64_t stall_cycles;      /* continuous idle this long => STALL (0 = never) */
    uint32_t kcall_cycles;      /* virtual cycles charged per thread kernel call (default 0) */
    /* COP0 Status.EIE model.  0 (default) = retail as measured on the real
     * BIOS kernel (VALIDATION.md 2e): EIE is global thread-context state that
     * a context switch does not save or restore, and new threads inherit it.
     * 1 = the earlier per-thread model (saved on switch-out, restored on
     * switch-in, new threads start with EIE = 1). */
    int      eie_per_thread;
    /* Frame-driven mode (docs/NATIVE-THREADS.md "Slice 5", RG_THREADS=native).  0 (default)
     * = the EE kernel HLE above.  1 = no EE scheduler: only "flows" (game threads that are
     * neither driven nor service threads: main and the loading screen) have a fiber; a flow
     * runs until it waits (semaphore, kernel-private wait, sleep, DelayThread, a charge) and
     * is never preempted; a ready flow runs when the running one waits (FIFO, priorities only
     * order simultaneous wakes).  Interrupts are delivered only in the driver's pass (no
     * delivery at kernel calls / EI / ps2k_poll), which then calls the phase hook (driven
     * steps); virtual time moves only when every flow waits ("nominal logic time": a flow's
     * own work costs nothing, so T0_COUNT reads give the nominal frame profile);
     * ps2k_charge from a flow is a timed wait (callers that charge pure costs, DMAC / hwbus,
     * are configured with zero cost by the runtime); DelayThread is a kernel-private timed
     * wait (no semaphore / alarm). */
    int      native;
} ps2k_config;

enum {
    PS2K_RUN_MAIN_EXIT = 0, /* main thread exited (returned / ExitThread) */
    PS2K_RUN_STOPPED,       /* ps2k_request_stop() */
    PS2K_RUN_TIME_LIMIT,    /* config.stop_at_cycles reached */
    PS2K_RUN_DEADLOCK,      /* no ready thread and no future event */
    PS2K_RUN_STALL,         /* idle longer than config.stall_cycles */
    PS2K_RUN_ERROR,
    PS2K_RUN_YIELD          /* ps2k_step only: the VBlank target was reached; threads intact */
};

void ps2k_default_config(ps2k_config *cfg);
int  ps2k_init(const ps2k_config *cfg); /* resets ALL kernel state; 0 = ok */
void ps2k_shutdown(void);
/* Runs the scheduler on the calling host thread.  main_entry becomes thread
 * id 1 at main_priority.  Returns a PS2K_RUN_* code. */
int  ps2k_run(ps2k_entry_fn main_entry, void *arg, int main_priority);
/* ps2k_run in pieces, so a host loop can run the scheduler a field at a time
 * (src/runtime).  ps2k_run == ps2k_start + ps2k_step(0) + ps2k_finish.
 *   ps2k_start   adopts the calling host thread as the scheduler fiber and
 *                creates/starts main as thread 1.  0 or PS2K_RUN_ERROR.
 *   ps2k_step    runs the scheduler loop.  until_vblank != 0: returns
 *                PS2K_RUN_YIELD at the first scheduler-context point where
 *                ps2k_vblank_count() >= until_vblank (after that VBLANK_START
 *                was processed and its interrupts delivered).  Guest threads
 *                stay intact; call ps2k_step again to continue.  Any other
 *                return is terminal: call ps2k_finish.
 *   ps2k_finish  destroys every thread fiber, releases the host thread and
 *                records the stop code.  Must run on the ps2k_start thread. */
int  ps2k_start(ps2k_entry_fn main_entry, void *arg, int main_priority);
int  ps2k_step(uint64_t until_vblank);
void ps2k_finish(int code);
int  ps2k_running(void);
void ps2k_request_stop(void);
int  ps2k_stop_code(void); /* last ps2k_run result */

/* ---- threads --------------------------------------------------------- */
typedef struct ps2k_thread_info { /* same field order as SDK ThreadParam */
    int32_t  status;
    void    *entry;
    void    *stack;
    int32_t  stack_size;
    void    *gp;
    int32_t  init_priority;
    int32_t  current_priority;
    uint32_t attr;
    uint32_t option;
    int32_t  wait_type;
    int32_t  wait_id;
    int32_t  wakeup_count;
} ps2k_thread_info;

int ps2k_create_thread(ps2k_entry_fn entry, void *stack, int32_t stack_size, void *gp,
                       int32_t priority, uint32_t attr, uint32_t option);
int ps2k_delete_thread(int id);
int ps2k_start_thread(int id, void *arg);
void ps2k_exit_thread(void);        /* never returns */
void ps2k_exit_delete_thread(void); /* never returns */
int ps2k_terminate_thread(int id, int isr);
int ps2k_change_thread_priority(int id, int priority, int isr);
int ps2k_rotate_thread_ready_queue(int priority, int isr);
int ps2k_release_wait_thread(int id, int isr);
int ps2k_get_thread_id(void);
int ps2k_refer_thread_status(int id, ps2k_thread_info *out, int isr);
int ps2k_sleep_thread(void);
int ps2k_wakeup_thread(int id, int isr);
int ps2k_cancel_wakeup_thread(int id, int isr);
int ps2k_suspend_thread(int id, int isr);
int ps2k_resume_thread(int id, int isr);

/* ---- service threads (docs/NATIVE-THREADS.md "Slice 1") ----------------
 * A game thread whose body is exactly
 *     for (;;) { s = wait(arg); if (s < 0) break; WaitSema(s); step(arg); }
 * can run without a fiber: the kernel keeps its thread object (id, priority,
 * status, wait lists, trace records: all unchanged) and, when the scheduler
 * switches it in, runs the loop itself on the scheduler's host stack, calling
 * step() as a plain function.  step() must not block (a blocking call in it
 * is fatal: "service step blocked"); a preemption it causes is deferred to
 * the end of the step (counted, ps2k_svc_deferred_count()).  Set on a DORMANT
 * thread before StartThread.  0, or -1. */
typedef int (*ps2k_svc_wait_fn)(void *arg); /* sema id to wait on; < 0 = the loop ends, thread exits */
int      ps2k_thread_set_service(int id, ps2k_svc_wait_fn wait, ps2k_entry_fn step);
uint32_t ps2k_svc_deferred_count(void);
uint32_t ps2k_svc_step_count(void);

/* ---- frame driver support (docs/NATIVE-THREADS.md "Frame driver") ------
 * Driven threads: a created, not started thread marked with
 * ps2k_thread_set_driven is never scheduled.  StartThread parks it (status
 * WAIT, wait type 0, no fiber); its body runs elsewhere, as plain calls from
 * the native frame driver (src/native/threads/rg_frame.c) on whichever game
 * flow is at a driver point.  The thread object stays for the game (id,
 * ReferThreadStatus, TerminateThread, DeleteThread).  ps2k_driven_exit ends
 * it as its body's own exit would (ExitThread: DORMANT; ExitDeleteThread:
 * deleted).  ReleaseWaitThread / ResumeThread cannot run a parked thread.
 * The start hook is called by StartThread for every thread before it is
 * readied; it may call ps2k_thread_set_driven(id) (host state, kept by a
 * save-state load). */
typedef void (*ps2k_start_hook_fn)(int id, ps2k_entry_fn entry, void *arg);
void ps2k_set_start_hook(ps2k_start_hook_fn fn);
int  ps2k_thread_set_driven(int id);   /* DORMANT thread; 0 or -1 */
int  ps2k_thread_driven_state(int id); /* 0 not driven, 1 marked (dormant), 2 parked (started) */
int  ps2k_driven_exit(int id, int del);/* parked thread -> DORMANT (del: deleted); 0 or -1 */
/* The parked thread enters the WaitSema of its loop: it becomes a real waiter
 * on `sema` (or takes a count at once), so the game's SignalSema / PollSema
 * see exactly the HLE's semaphore state; a signal marks it woken (no ready
 * queue).  ps2k_driven_take: 1 once if its WaitSema has returned. */
int  ps2k_driven_wait(int id, int sema);
int  ps2k_driven_take(int id);
int  ps2k_driven_woken(int id); /* the same test without taking it */
/* Signal hook: called by a thread-context SignalSema that woke a parked
 * driven thread, on the signalling thread: the frame driver runs the step
 * there when the HLE would have switched to that thread at once (its
 * priority is higher than the signaller's). */
typedef void (*ps2k_signal_hook_fn)(int sema);
void ps2k_set_signal_hook(ps2k_signal_hook_fn fn);
/* Poll wait (the frame driver's DelayThread): block until virtual time >=
 * `time` AND something else has happened since this thread last returned
 * from ps2k_wait_poll (another thread was switched in, or a handler / alarm
 * ran).
 * When something already happened, it is a plain timed wait.  A loop that
 * polls memory written by other threads or handlers therefore sees every
 * change at the same virtual time as with 10 us DelayThread polling, with
 * one wake per change instead of one per 10 us.  If nothing at all can
 * happen any more (no event queued) it wakes at its time.  0 or -1. */
int      ps2k_wait_poll(uint64_t time);
uint64_t ps2k_activity(void);
uint64_t ps2k_vblank_end_count(void);  /* VBLANK_END events processed */

/* ---- frame-driven mode (cfg.native, docs/NATIVE-THREADS.md "Slice 5") --------
 * Phase hook: called by the driver loop in kernel context (no flow running) after
 * each pass delivered the latched interrupts, before any flow resumes: the frame
 * driver runs the driven steps that are due (VBlank services in the HLE's order:
 * handlers first, then steps by old priority).  Parked hook: called by StartThread
 * on the starter after it parked a driven thread (the frame driver runs the
 * thread's first part at once when the HLE would have switched to it).  Block
 * hook: a driven step (step context, below) is about to wait on semaphore `sema`
 * with no count: the frame driver may run other woken steps; if the count is still
 * 0 afterwards the step cannot block (no stack of its own): fatal.  All three are
 * host state (constant per exe). */
typedef void (*ps2k_phase_hook_fn)(void);
typedef void (*ps2k_parked_hook_fn)(int id);
typedef void (*ps2k_block_hook_fn)(int sema);
void ps2k_set_phase_hook(ps2k_phase_hook_fn fn);
void ps2k_set_parked_hook(ps2k_parked_hook_fn fn);
void ps2k_set_block_hook(ps2k_block_hook_fn fn);
int  ps2k_native(void); /* cfg.native of the current kernel */
/* Step context: while a driven thread's step runs (on a flow or in the driver
 * pass), the kernel's current thread is that thread (GetThreadId, its priority,
 * its own semaphore calls).  enter returns a token for leave.  Native mode only. */
void *ps2k_step_enter(int id);
void  ps2k_step_leave(void *token);
int   ps2k_in_step(void);
int   ps2k_ready_at(int priority); /* 1 if a thread of that priority is ready (not running) */
/* counters (RG_THREADS_LOG) */
typedef struct ps2k_native_stats {
    uint64_t passes;       /* driver passes */
    uint64_t flow_switches;/* switches into a flow */
    uint32_t flows;        /* threads that got a fiber (flows) since init */
    uint64_t charge_waits; /* ps2k_charge calls that became timed waits */
    uint64_t charges_dropped; /* ps2k_charge calls outside a flow (no time) */
    uint64_t delays;       /* DelayThread timed waits */
} ps2k_native_stats;
void ps2k_get_native_stats(ps2k_native_stats *out);

/* ---- semaphores ------------------------------------------------------ */
typedef struct ps2k_sema_info { /* same field order as SDK SemaParam */
    int32_t  current_count;
    int32_t  max_count;
    int32_t  init_count;
    int32_t  num_wait_threads;
    uint32_t attr;
    uint32_t option;
} ps2k_sema_info;

int ps2k_create_sema(int32_t init_count, int32_t max_count, uint32_t attr, uint32_t option);
int ps2k_delete_sema(int id, int isr);
int ps2k_signal_sema(int id, int isr);
int ps2k_wait_sema(int id);
int ps2k_poll_sema(int id, int isr);
int ps2k_refer_sema_status(int id, ps2k_sema_info *out, int isr);

/* ---- interrupts ------------------------------------------------------ */
/* next == 0: insert at the head of the chain; otherwise (e.g. -1) at the
 * tail.  Returns a handler id > 0.  The chain stops at the first handler
 * that returns non-zero. */
int ps2k_add_intc_handler(int cause, ps2k_handler_fn fn, int next);
int ps2k_add_intc_handler2(int cause, ps2k_handler2_fn fn, int next, void *arg);
int ps2k_remove_intc_handler(int cause, int handler_id);
int ps2k_add_dmac_handler(int ch, ps2k_handler_fn fn, int next);
int ps2k_add_dmac_handler2(int ch, ps2k_handler2_fn fn, int next, void *arg);
int ps2k_remove_dmac_handler(int ch, int handler_id);
/* return 1 if the mask bit changed, 0 if it was already in that state */
int ps2k_enable_intc(int cause, int isr);
int ps2k_disable_intc(int cause, int isr);
int ps2k_enable_dmac(int ch, int isr);
int ps2k_disable_dmac(int ch, int isr);
/* DI / EI on the current context's EIE.  Return the previous EIE (1/0).
 * EI in thread context is a delivery point. */
int ps2k_di(void);
int ps2k_ei(void);
int ps2k_in_handler(void);
/* Synthesised COP0 Status: bit 0 IE (0 inside a handler), bit 16 EIE. */
uint32_t ps2k_cop0_status(void);

/* raised by other models; latched until delivered */
void ps2k_raise_intc(int cause);
void ps2k_raise_dmac(int ch);
/* raise after `delay` bus cycles of virtual time */
void ps2k_post_intc(int cause, uint64_t delay);
void ps2k_post_dmac(int ch, uint64_t delay);

/* A defined point for models / overrides: process due events and deliver
 * pending interrupts if the current context allows it. */
void ps2k_poll(void);
/* Advance virtual time by `cycles` while a thread runs (busy-wait models,
 * cost accounting), then behave like ps2k_poll(). */
void ps2k_charge(uint64_t cycles);

/* ---- alarms / delay -------------------------------------------------- */
/* EE SetAlarm: `time` in hsync units.  Returns alarm id >= 0, or -1. */
int ps2k_set_alarm(uint16_t time, ps2k_alarm_fn fn, void *arg, int isr);
int ps2k_release_alarm(int id, int isr);
/* Bus-cycle alarm (the libkernl timer-alarm path DelayThread uses). */
int ps2k_set_cycle_alarm(uint64_t cycles, ps2k_alarm_fn fn, void *arg, int isr);
/* libkernl DelayThread: 0, or PS2K_DELAY_E_*.  Virtual delay is
 * floor(usec * 147456 / 1000) bus cycles. */
int ps2k_delay_thread(uint32_t usec);
uint64_t ps2k_usec_to_cycles(uint32_t usec);

/* ---- hardware registers (timers, INTC, DMAC STAT/MASK) --------------- */
int      ps2k_hw_claims(uint32_t addr); /* 1 if ps2k models this register */
uint32_t ps2k_hw_read32(uint32_t addr);
void     ps2k_hw_write32(uint32_t addr, uint32_t value);
#define PS2K_T0_COUNT   0x10000000u
#define PS2K_T0_MODE    0x10000010u
#define PS2K_T0_COMP    0x10000020u
#define PS2K_T0_HOLD    0x10000030u
#define PS2K_T1_BASE    0x10000800u
#define PS2K_T2_BASE    0x10001000u
#define PS2K_T3_BASE    0x10001800u
#define PS2K_INTC_STAT  0x1000F000u
#define PS2K_INTC_MASK  0x1000F010u
#define PS2K_D_STAT     0x1000E010u

/* ---- clock ----------------------------------------------------------- */
uint64_t ps2k_now(void);           /* bus cycles since ps2k_init */
uint64_t ps2k_hsync_count(void);   /* hsyncs elapsed */
uint64_t ps2k_vblank_count(void);  /* VBLANK_START events processed */
void     ps2k_set_pacing_hook(ps2k_pacing_fn fn, void *user);
uint32_t ps2k_vblank_start_line(void);       /* cfg.vblank_start_line in effect */
int      ps2k_vblank_enabled(void);
/* Bus-cycle time of VBLANK_START / VBLANK_END of field k (exact NTSC arithmetic). */
uint64_t ps2k_vblank_start_time(uint64_t field);
uint64_t ps2k_vblank_end_time(uint64_t field);

/* ---- VBlank observers (platform glue) --------------------------------
 * Called when the kernel PROCESSES a VBLANK_START (which = PS2K_VBLANK_START,
 * field = index of that field, i.e. ps2k_vblank_count() - 1) or VBLANK_END
 * event, at its exact virtual time, after the INTC cause is latched and
 * BEFORE any game handler for it runs.  Observers run in registration
 * order.  They run inside the kernel's event processing, which can be on a
 * guest thread's fiber (a kernel call that crossed the event) or in the
 * scheduler: they must not make thread-context or blocking kernel calls.
 * Raising causes (ps2k_raise_intc and friends), reading the clock and host work are
 * fine.  Up to PS2K_MAX_OBSERVERS. */
#define PS2K_MAX_OBSERVERS 16
enum { PS2K_VBLANK_START = 0, PS2K_VBLANK_END = 1 };
typedef void (*ps2k_vblank_fn)(int which, uint64_t field, void *user);
int  ps2k_add_vblank_observer(ps2k_vblank_fn fn, void *user); /* id > 0, or -1 */
int  ps2k_remove_vblank_observer(int id);

/* ---- devices: models with their own completion clock ------------------
 * next(user, &due) returns 1 and the bus-cycle time it next needs a poll
 * (0 when idle); the scheduler's idle jump stops at the earliest due time,
 * and an idle kernel with a due device is not deadlocked.  poll(user, now)
 * runs from every event-processing pass (after the kernel's own events at
 * that time), in HANDLER context: completion callbacks may use "i" calls.
 * Up to PS2K_MAX_DEVICES. */
#define PS2K_MAX_DEVICES 8
typedef struct ps2k_device {
    const char *name;
    int  (*next)(void *user, uint64_t *due);
    void (*poll)(void *user, uint64_t now);
    void *user;
} ps2k_device;
int  ps2k_add_device(const ps2k_device *dev); /* id > 0, or -1 */
int  ps2k_remove_device(int id);

/* ---- kernel-private waits (no game-visible ids) -----------------------
 * Block the calling guest thread without creating a semaphore or alarm id
 * (the game can observe both).  While waiting the thread reads as
 * status WAIT, wait_type 0.
 *   ps2k_wait_vblank: until the next VBLANK_START has been processed; the
 *     thread is readied after that VBLANK_START's handlers and the alarms due
 *     with it were delivered (the order the old sceGsSyncV alarm had).
 *     0, or -1 outside a guest thread / in a handler / with VBlank off.
 *   ps2k_wait_until: until virtual time >= `time` (bus cycles).  Readied
 *     when the event pass at that time runs, before devices are polled.
 *     0, or -1 outside a guest thread / in a handler. */
int ps2k_wait_vblank(void);
int ps2k_wait_until(uint64_t time);

/* ---- trace ----------------------------------------------------------- */
enum {
    PS2K_TR_SWITCH = 1,  /* a = thread id switched in (0 = idle) */
    PS2K_TR_IDLE_JUMP,   /* a,b = low/high 32 bits of the new time */
    PS2K_TR_INTC,        /* a = cause delivered */
    PS2K_TR_DMAC,        /* a = channel delivered */
    PS2K_TR_ALARM,       /* a = alarm id fired */
    PS2K_TR_THREAD,      /* a = id, b = new status */
    PS2K_TR_SEMA_SIGNAL, /* a = sema, b = woken thread (0 = none) */
    PS2K_TR_SEMA_WAIT,   /* a = sema, b = thread (blocked) */
    PS2K_TR_WAKEUP,      /* a = thread, b = wakeup count after */
    PS2K_TR_PREEMPT,     /* a = preempted thread, b = new thread */
    PS2K_TR_RAISE,       /* a = cause (or 0x100+ch), b = 0 */
    PS2K_TR_VIOLATION    /* a = 0 */
};
typedef struct ps2k_trace_rec {
    uint64_t seq;
    uint64_t time;
    int32_t  type;
    int32_t  a;
    int32_t  b;
} ps2k_trace_rec;
uint64_t ps2k_trace_hash(void);  /* FNV-1a over every record since init */
uint64_t ps2k_trace_count(void);
void     ps2k_set_trace_hook(ps2k_trace_fn fn, void *user);
void     ps2k_trace_dump(FILE *f, int last_n);

/* ---- census tap (docs/NATIVE-THREADS.md, tools/native/thread_census.py) --
 * Measurement only: called at kernel-side events that the SDK wrappers
 * cannot see.  Not part of the trace hash; never changes behaviour.  The tap
 * pointer is host state (save states keep the loading process's tap). */
enum {
    PS2K_TAP_SWITCH = 1, /* a = thread id switched in, b = priority */
    PS2K_TAP_HANDLER,    /* a = cause (INTC) or 0x100 + channel (DMAC), fn = handler */
    PS2K_TAP_ALARM,      /* a = alarm id, fn = callback */
    PS2K_TAP_KWAIT,      /* a = 1 vblank wait, 2 timed wait; b = target (low 32 bits) */
    PS2K_TAP_TIMER_READ, /* a = timer register address */
    PS2K_TAP_VBLANK,     /* a = 0 start / 1 end, b = field */
    PS2K_TAP_RUN_AS_HANDLER /* a = tag, fn = function (ps2k_run_as_handler) */
};
typedef void (*ps2k_tap_fn)(int kind, int32_t a, int32_t b, const void *fn);
void ps2k_set_census_tap(ps2k_tap_fn fn);
/* Side-effect-free peeks for measurement (no k_enter, no delivery point):
 * the semaphore's count and number of waiters (-1 if the id is unused), and
 * the current thread's priority (-1 outside a thread). */
int ps2k_peek_sema(int id, int32_t *count, int32_t *nwait);
int ps2k_peek_priority(void);

/* ---- context violations ---------------------------------------------- */
void     ps2k_set_violation_hook(ps2k_violation_fn fn); /* NULL = default (abort) */
uint32_t ps2k_violation_count(void);

/* ---- debug ----------------------------------------------------------- */
/* DELIBERATELY WRONG: deliver interrupts and preempt the running thread right
 * now, as a preemptive kernel would.  Exists only so tests can prove their
 * non-preemption checks are armed. */
void ps2k_debug_force_preempt(void);
const char *ps2k_backend_name(void);

#ifdef __cplusplus
}
#endif
#endif

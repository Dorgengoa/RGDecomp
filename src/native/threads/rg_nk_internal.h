/* SPDX-License-Identifier: CC0-1.0
 * The native kernel table (docs/NATIVE-THREADS.md "Native kernel table"): private state
 * shared by rg_nk.c (flows, the driver loop, the game-visible thread / semaphore ids,
 * waits, trace) and rg_nk_irq.c (logic clock, event list, handler ids and their chains,
 * timers T0..T3).
 *
 * The frame-driven implementation of the ps2k API (kapi/ps2k.h, RG_THREADS=native): no
 * EE scheduler, no priorities beyond the order of simultaneous wakes, no preemption, no
 * service threads.  Its definitions are named rg_nk_* in a default build (kapi/
 * ps2k_rename.h; src/ps2/kernel/kdispatch.c forwards ps2k_* here when the kernel is
 * initialised with cfg.native) and ps2k_* in an RG_NATIVE_ONLY build (RG_NK_REAL_NAMES:
 * target rg_native_kernel_ps2k replaces the HLE library rg_ps2_kernel).  The records it
 * keeps (thread objects, semaphores, handler chains, the event list) exist because game
 * code stores and passes their ids; their semantics and the trace records are the ones
 * the HLE's frame-driven mode produced, so a run hash is identical in both builds. */
#ifndef RG_NK_INTERNAL_H
#define RG_NK_INTERNAL_H

#ifndef RG_NK_REAL_NAMES
#define PS2K_RENAME_PREFIX rg_nk_
#include "ps2k_rename.h"
#endif
#include "fiber.h"
#include "ps2k.h"

typedef struct nkthread nkthread;
struct nkthread {
    int           used;
    int           id;
    int           status;
    int           wait_type;
    int           wait_id;
    int           init_prio;
    int           prio;
    ps2k_entry_fn entry;
    void         *arg;
    void         *stack;
    int32_t       stack_size;
    void         *gp;
    uint32_t      attr, option;
    int           wakeup_count;
    int           eie;        /* saved COP0 Status.EIE (cfg.eie_per_thread only) */
    ps2k_fiber   *fiber;      /* flows only; NULL until first switch-in */
    int           fiber_dead; /* exited: destroy fiber at next reap */
    int           delete_pending;
    int           wait_result;
    int           kwait;         /* KW_* kernel-private wait kind (PS2K_TSW_KWAIT) */
    uint64_t      kwait_arg;     /* KW_VBLANK: target vblank_count; KW_TIME/KW_POLL: due time */
    int           driven;        /* 1 marked, 2 parked (the frame driver runs its body) */
    int           driven_woken;  /* parked thread: its WaitSema returned */
    int           poll_due;      /* KW_POLL: the due time has passed */
    uint64_t      poll_seen;     /* NK.activity when this thread last woke from a poll wait */
    nkthread     *qnext, *qprev; /* ready flows */
    nkthread     *wnext;         /* semaphore wait list */
};

typedef struct nksema {
    int       used;
    int       free_next; /* LIFO free list link (index, -1 = end) */
    int32_t   count, max, init;
    int32_t   nwait;
    uint32_t  attr, option;
    nkthread *whead, *wtail;
} nksema;

typedef struct nkhandler {
    int   id;
    int   v2;
    void *fn;
    void *arg;
} nkhandler;

#define NKCHAINS   (PS2K_INTC_COUNT + PS2K_DMAC_COUNT)
#define NKCHAINMAX 16

typedef struct nkalarm {
    int           used;
    int           fired;
    uint64_t      time;
    ps2k_alarm_fn fn;
    void         *arg;
} nkalarm;

typedef struct nktimer {
    uint32_t mode, comp, hold;
    uint32_t count_base;
    uint64_t tick_base;
} nktimer;

/* event kinds (the same numbering as the HLE's, so the event order is identical) */
enum { NEV_VBS = 1, NEV_VBE, NEV_TCMP, NEV_TOVF, NEV_ALARM, NEV_POST_INTC, NEV_POST_DMAC, NEV_KWAKE };

#define PS2K_TSW_KWAIT 0x100 /* kernel-private wait: ReferThreadStatus reports wait type 0 */
enum { KW_NONE = 0, KW_VBLANK, KW_TIME, KW_POLL, KW_DRIVEN };

typedef struct nkobserver {
    int            id;
    ps2k_vblank_fn fn;
    void          *user;
} nkobserver;

typedef struct nkdevice {
    int         id;
    ps2k_device d;
} nkdevice;

typedef struct nkevent {
    uint64_t time;
    uint64_t seq;
    int      kind;
    int      a;
} nkevent;
#define NKEVMAX 512
#define NKTRACE_RING 4096

typedef struct nkstate {
    int         inited;
    ps2k_config cfg;

    /* the driver */
    ps2k_fiber *sched;        /* the host thread (driver loop) */
    nkthread   *cur;          /* running flow, or the driven thread in step context; NULL = driver */
    int         in_handler;
    int         eie;
    int         running;
    int         stop_req;
    int         stop_reason;
    int         stop_code;
    int         main_id;
    nkthread    threads[PS2K_MAX_THREADS];
    nkthread   *rq_head[PS2K_PRIO_MAX + 1], *rq_tail[PS2K_PRIO_MAX + 1];
    nksema      semas[PS2K_MAX_SEMAS];
    int         sema_free;
    int         next_thread_id;
    int         want_main_id;
    int         thread_eie;
    uint64_t    activity;     /* flow switch-ins, handler / alarm runs, step contexts */
    int         in_step;
    ps2k_native_stats nst;

    /* interrupts: game-visible handler ids and their chains, the STAT / MASK latch */
    uint32_t  intc_stat, intc_mask;
    uint32_t  dmac_stat, dmac_mask;
    nkhandler chain[NKCHAINS][NKCHAINMAX];
    int       chain_len[NKCHAINS];
    int       next_handler_id;
    nkalarm   alarms[PS2K_MAX_ALARMS];
    int       fired_fifo[PS2K_MAX_ALARMS];
    int       fired_n;

    /* logic clock and event list */
    uint64_t now;
    uint64_t ev_seq;
    nkevent  ev[NKEVMAX];
    int      nev;
    uint64_t vbs_k, vbe_k;
    uint64_t vblank_count;
    nktimer  timers[4];
    ps2k_pacing_fn pacing;
    void          *pacing_user;
    uint64_t       idle_since;

    /* platform glue */
    nkobserver obs[PS2K_MAX_OBSERVERS];
    int        nobs;
    nkdevice   dev[PS2K_MAX_DEVICES];
    int        ndev;
    int        next_glue_id;
    int        kwait_fifo[PS2K_MAX_THREADS];
    int        kwait_n;
    int        in_device_poll;

    /* trace (folded into the run hash) */
    uint64_t       trace_hash;
    uint64_t       trace_n;
    ps2k_trace_rec ring[NKTRACE_RING];
    ps2k_trace_fn  trace_hook;
    void          *trace_user;

    ps2k_violation_fn violation;
    uint32_t          violations;
} nkstate;

extern nkstate NK;

/* host state (outside NK: a save-state load keeps the loading process's) */
extern ps2k_tap_fn nk_tap;
extern ps2k_start_hook_fn nk_start_hook;
extern ps2k_signal_hook_fn nk_signal_hook;
extern ps2k_phase_hook_fn nk_phase_hook;
extern ps2k_parked_hook_fn nk_parked_hook;
extern ps2k_block_hook_fn nk_block_hook;
#define NK_TAP(kind, a, b, fn) do { if (nk_tap) nk_tap((kind), (a), (b), (fn)); } while (0)

/* rg_nk.c */
int  nk_enter(const char *call, int isr);
void nk_trace(int type, int32_t a, int32_t b);
int  nk_violation(const char *call, const char *why);
void nk_make_ready(nkthread *t);
void nk_kwait_wake(int tid, int kind);
void nk_poll_wake(int idle);

/* rg_nk_irq.c */
void nk_irq_reset(void);
void nk_process_due(void);
void nk_deliver(void);
int  nk_ev_add(uint64_t time, int kind, int a);
void nk_ev_remove(int kind, int a);
uint64_t nk_hsync_index(uint64_t t);
int  nk_next_due(uint64_t *due);

/* EE FPU arithmetic for game code (docs/BRINGUP.md "Retail parity"): the EE FPU rounds
 * every single-precision result toward zero and has no denormals; PCSX2 runs it as SSE
 * with MXCSR = round toward zero + FTZ + DAZ.  nk_guest_csr is that MXCSR (0 = leave the
 * host's round-to-nearest, RG_EE_FPU=ieee; the EE mode is the default since 2026-10-24); the kernel step (flows, handler chains,
 * alarms, the frame driver's driven steps) runs under it, the host outside it keeps its
 * own.  Retail's double arithmetic (gcc fp-bit soft float) also rounds toward zero
 * (verified: dptofp, src/crt/crt_math.c), so native doubles under this MXCSR match it. */
extern unsigned nk_guest_csr;
#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
static inline unsigned nk_fpu_enter(void)
{
    unsigned o = _mm_getcsr();
    if (nk_guest_csr)
        _mm_setcsr(nk_guest_csr);
    return o;
}
static inline void nk_fpu_leave(unsigned o)
{
    if (nk_guest_csr)
        _mm_setcsr(o);
}
#else
static inline unsigned nk_fpu_enter(void) { return 0; }
static inline void nk_fpu_leave(unsigned o) { (void)o; }
#endif

#endif

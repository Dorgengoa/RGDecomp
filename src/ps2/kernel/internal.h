/* SPDX-License-Identifier: CC0-1.0
 * ps2k private state shared by kcore.c (scheduler, threads, semaphores,
 * trace) and kirq.c (clock, events, interrupts, alarms, timers). */
#ifndef PS2K_INTERNAL_H
#define PS2K_INTERNAL_H

/* The HLE defines the ps2k API as ps2k_hle_* (kapi/ps2k_rename.h); kdispatch.c defines the
 * real names and forwards to it, or to the native kernel table when the kernel is
 * initialised frame-driven (docs/NATIVE-THREADS.md "Native kernel table"). */
#define PS2K_RENAME_PREFIX ps2k_hle_
#include "ps2k_rename.h"
#include "fiber.h"
#include "ps2k.h"

typedef struct kthread kthread;
struct kthread {
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
    int           eie;        /* saved COP0 Status.EIE of this thread */
    ps2k_fiber   *fiber;      /* NULL until first switch-in */
    int           fiber_dead; /* exited: destroy fiber at next reap */
    int           delete_pending;
    int           wait_result;
    ps2k_svc_wait_fn svc_wait;   /* service thread (no fiber): ps2k_thread_set_service */
    ps2k_entry_fn svc_step;
    int           svc_pc;        /* SVC_* resume point of the service loop */
    int           svc_sid;       /* the sema of the WaitSema in progress */
    int           kwait;         /* KW_* kernel-private wait kind (PS2K_TSW_KWAIT) */
    uint64_t      kwait_arg;     /* KW_VBLANK: target vblank_count; KW_TIME/KW_POLL: due time */
    int           driven;        /* ps2k_thread_set_driven: StartThread parks it (KW_DRIVEN) */
    int           driven_woken;  /* parked thread: its WaitSema returned (ps2k_driven_take) */
    int           poll_due;      /* KW_POLL: the due time has passed */
    uint64_t      poll_seen;     /* K.activity when this thread last woke from a wait */
    kthread      *qnext, *qprev; /* ready queue */
    kthread      *wnext;         /* semaphore wait list */
};

typedef struct ksema {
    int      used;
    int      free_next;  /* LIFO free list link (index, -1 = end) */
    int32_t  count, max, init;
    int32_t  nwait;
    uint32_t attr, option;
    kthread *whead, *wtail;
} ksema;

typedef struct khandler {
    int   id;
    int   v2;
    void *fn;
    void *arg;
} khandler;

#define KCHAINS   (PS2K_INTC_COUNT + PS2K_DMAC_COUNT)
#define KCHAINMAX 16

typedef struct kalarm {
    int           used;
    int           fired; /* due; waiting for delivery */
    uint64_t      time;
    ps2k_alarm_fn fn;
    void         *arg;
} kalarm;

typedef struct ktimer {
    uint32_t mode, comp, hold;
    uint32_t count_base; /* count at tick_base */
    uint64_t tick_base;  /* absolute tick index at last rebase */
} ktimer;

enum { EV_VBS = 1, EV_VBE, EV_TCMP, EV_TOVF, EV_ALARM, EV_POST_INTC, EV_POST_DMAC, EV_KWAKE };

/* kernel-private wait (ps2k_wait_vblank / ps2k_wait_until): not an SDK wait
 * type; ReferThreadStatus reports wait_type 0 for it */
#define PS2K_TSW_KWAIT 0x100
enum { KW_NONE = 0, KW_VBLANK, KW_TIME, KW_POLL, KW_DRIVEN };
/* service loop resume points */
enum { SVC_TOP = 0, SVC_WAIT_ENTERED, SVC_WOKEN, SVC_EXIT_ENTERED };

typedef struct kobserver {
    int            id;
    ps2k_vblank_fn fn;
    void          *user;
} kobserver;

typedef struct kdevice {
    int         id;
    ps2k_device d;
} kdevice;
typedef struct kevent {
    uint64_t time;
    uint64_t seq;
    int      kind;
    int      a;
} kevent;
#define KEVMAX 512

#define KTRACE_RING 4096

typedef struct kstate {
    int         inited;
    ps2k_config cfg;

    /* scheduler */
    ps2k_fiber *sched;
    kthread    *cur;          /* thread whose fiber is running, NULL = scheduler/idle */
    int         in_handler;
    int         eie;          /* EIE of the running context */
    int         running;      /* inside ps2k_run */
    int         stop_req;
    int         stop_reason;
    int         stop_code;
    int         main_id;
    int         yield_req;    /* iRotateThreadReadyQueue hit the interrupted thread */
    kthread     threads[PS2K_MAX_THREADS];
    kthread    *rq_head[PS2K_PRIO_MAX + 1], *rq_tail[PS2K_PRIO_MAX + 1];
    ksema       semas[PS2K_MAX_SEMAS];
    int         sema_free;     /* head of the LIFO free list (VALIDATION.md 2c) */
    int         next_thread_id;/* next-fit thread id cursor (VALIDATION.md 2c) */
    int         want_main_id;  /* ps2k_start: create main as this id if free */
    int         thread_eie;    /* global thread-context EIE (eie_per_thread = 0) */
    int         svc_yield;     /* the running service thread switched out (preempt / stop) */
    int         svc_in_step;   /* inside a service thread's step() */
    uint64_t    activity;      /* thread switch-ins + handler/alarm runs (ps2k_wait_poll) */

    /* interrupts */
    uint32_t intc_stat, intc_mask;
    uint32_t dmac_stat, dmac_mask;
    khandler chain[KCHAINS][KCHAINMAX];
    int      chain_len[KCHAINS];
    int      next_handler_id; /* shared INTC/DMAC next-fit cursor, 1..PS2K_HANDLER_ID_MAX */
    kalarm   alarms[PS2K_MAX_ALARMS];
    int      fired_fifo[PS2K_MAX_ALARMS];
    int      fired_n;

    /* clock */
    uint64_t now;
    uint64_t ev_seq;
    kevent   ev[KEVMAX];
    int      nev;
    uint64_t vbs_k, vbe_k; /* next field index for VBLANK_START / END */
    uint64_t vblank_count;
    ktimer   timers[4];
    ps2k_pacing_fn pacing;
    void          *pacing_user;
    uint64_t       idle_since;

    /* platform glue: VBlank observers, devices, kernel-private waits */
    kobserver obs[PS2K_MAX_OBSERVERS];
    int       nobs;
    kdevice   dev[PS2K_MAX_DEVICES];
    int       ndev;
    int       next_glue_id;
    int       kwait_fifo[PS2K_MAX_THREADS]; /* thread ids in wait order */
    int       kwait_n;
    int       in_device_poll;

    /* trace */
    uint64_t       trace_hash;
    uint64_t       trace_n;
    ps2k_trace_rec ring[KTRACE_RING];
    ps2k_trace_fn  trace_hook;
    void          *trace_user;

    ps2k_violation_fn violation;
    uint32_t          violations;
} kstate;

extern kstate K;

/* census tap (host state, outside K so a state load keeps it) */
extern ps2k_tap_fn k_tap;
extern ps2k_start_hook_fn k_start_hook; /* host state, like k_tap */
extern ps2k_signal_hook_fn k_signal_hook;
#define K_TAP(kind, a, b, fn) do { if (k_tap) k_tap((kind), (a), (b), (fn)); } while (0)

/* kcore.c */
int  k_enter(const char *call, int isr); /* kernel-call entry; delivery point */
void k_trace(int type, int32_t a, int32_t b);
int  k_violation(const char *call, const char *why);
void k_make_ready(kthread *t);
void k_maybe_preempt(void);
kthread *k_ready_top(void);

/* kirq.c */
void k_irq_reset(void);
void k_process_due(void);
void k_deliver(void);
int  k_deliverable(void);
int  k_ev_add(uint64_t time, int kind, int a);
void k_ev_remove(int kind, int a);
uint64_t k_hsync_index(uint64_t t);
int  k_next_due(uint64_t *due);       /* earliest event or device due time; 0 if none */

/* kcore.c: kernel-private waits */
void k_kwait_wake(int tid, int kind); /* KW_TIME: thread tid; KW_VBLANK: all due waiters */
void k_poll_wake(int idle);           /* KW_POLL waiters whose time passed and saw activity */

#endif

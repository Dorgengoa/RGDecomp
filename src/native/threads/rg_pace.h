/* SPDX-License-Identifier: CC0-1.0
 * Host-clock pacing of the frame driver (PLAN.md "Unlocked frame rate", docs/NATIVE-THREADS.md
 * "Paced mode").
 *
 * Four clocks: host time, VBlank time, logic tick, audio time.  The frame driver's fixed step
 * is the VBlank phase (one NTSC field, 2,460,060 bus cycles = 1/59.94 s, exact: the kernel's
 * PS2K_FIELD_SUB); the game's logic tick runs on its own 1- / 2-VBlank interval inside those
 * phases, so a phase is never shorter or longer than retail's.  Host time only decides HOW
 * MANY phases are due: a bounded fixed-step accumulator.
 *
 *   RG_PACE_RETAIL  (Original preset, and every run without a host clock: tests, traces, save
 *                   states, --headless / --unthrottled) one phase per step, one present per
 *                   phase; with throttle on, the kernel's idle jumps are slept to wall time
 *                   (src/host host_pace.c).  The deterministic retail cadence.
 *   RG_PACE_HOST    the accumulator: before a phase, wait until host time owes one; after it,
 *                   present only when no further phase is owed right now (0..k phases per
 *                   present, k = max_ticks; older debt is dropped, never run fast) and the
 *                   frame cap allows; between phases a presenter may show interpolated frames
 *                   at its own slots (N presents per phase: rg_pace_between, the renderer
 *                   lane's later work; one present per phase today).
 *
 * The game's state is a function of its inputs per phase in both modes: pacing changes
 * only when phases run relative to host time and to presents.  Pure logic (host time is
 * passed in), unit-tested by rg-kernel-tests `pace`. */
#ifndef RG_PACE_H
#define RG_PACE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RG_PACE_RETAIL 0
#define RG_PACE_HOST   1

/* one VBlank phase in units of 1/2304 ns: 2,460,060 cycles * 15625 (1e9/147.456e6 = 15625/2304) */
#define RG_PACE_FIELD_U 38438437500ull
#define RG_PACE_HIST    9 /* phases-per-present histogram: 0..7, 8+ */

typedef struct rg_pace_config {
    int      mode;       /* RG_PACE_* */
    uint32_t max_ticks;  /* k: most phases run back to back without a present (default 4) */
    uint32_t catchup;    /* skip presents to catch up only while at least this many phases are
                            owed (default 2: one 30 Hz logic tick; 1 = the first design: any
                            owed phase skips the present) AND the host runs a phase faster than
                            real time (cost estimate below): a host that is a little behind
                            presents every phase it runs and catches up by not sleeping; a host
                            that cannot catch up at all presents every phase and the debt beyond
                            k is dropped (the game slows down evenly instead of batches of k
                            phases whose rendered game frames are never shown); after a hitch on
                            a fast host the catch-up burst stays (docs/PERF-3D.md "Transition
                            stutter") */
    uint32_t cap_fps;    /* presents per second at most (0: one per batch of phases) */
    int      vsync;      /* the present waits for the display: never sleep for a present slot */
    int      cost_at_decision; /* control: ignore rg_pace_phase_done (the cost sample stops at the
                                  present decision, before the GS worker wait: the design before
                                  2026-10-22; $RG_PACE_COST_AT_DECISION=1) */
} rg_pace_config;

typedef struct rg_pace {
    rg_pace_config cfg;
    int      anchored;
    uint64_t last_ns;         /* host time of the last accumulate */
    uint64_t acc;             /* owed host time, 1/2304 ns units (< (max_ticks + 1) phases) */
    uint64_t next_present_ns; /* the frame cap's next slot (0: none yet) */
    uint32_t batch;           /* phases since the last present */
    uint64_t phase_start_ns;  /* host time the current phase started (until_tick returned 0) */
    uint64_t cost_ns;         /* moving average of a phase's host cost (start -> rg_pace_phase_done,
                                 else start -> present decision) */
    int      cost_ext;        /* rg_pace_phase_done has been called: it alone samples cost_ns */
    uint64_t skipped_slow;    /* presents not skipped although owed: the host could not catch up */
    /* statistics */
    uint64_t t0_ns;           /* first accumulate */
    uint64_t ticks, presents, between_presents;
    uint64_t waits, slept_ns; /* host waits before a phase */
    uint64_t resyncs;         /* hitches: at least a whole phase of debt dropped at once */
    uint64_t dropped_u;       /* all debt dropped beyond k phases (units) */
    uint64_t dropped_ticks;   /* ... in phases */
    uint64_t forced;          /* presents forced after k phases (host slower than 59.94 Hz) */
    uint64_t hist[RG_PACE_HIST];
} rg_pace;

void rg_pace_default_config(rg_pace_config *c);
void rg_pace_init(rg_pace *p, const rg_pace_config *c);
/* new settings (mode / cap / vsync) without losing the statistics; a mode change re-anchors */
void rg_pace_configure(rg_pace *p, const rg_pace_config *c);
/* forget the host time anchor (after a pause, a load, a hitch the caller knows of) */
void rg_pace_reset(rg_pace *p);

/* Before a phase: 0 when a phase is owed at host time now_ns (retail: always), else the
 * nanoseconds until it is.  Accumulates host time and drops debt beyond max_ticks phases. */
uint64_t rg_pace_until_tick(rg_pace *p, uint64_t now_ns);
/* the phase runs: consume it (call once per phase run, after until_tick returned 0) */
void rg_pace_take_tick(rg_pace *p);
/* After a phase: 1 = present now.  Retail: always.  Host: when no further phase is owed now
 * (or k phases ran since the last present) and the cap's slot has come. */
int rg_pace_present_now(rg_pace *p, uint64_t now_ns);
/* Host: the phase's work is done, including waits for work it handed to other threads (the GS
 * worker) that happen after the present decision.  Once called, it alone samples the phase
 * cost the catch-up decision uses; callers that never call it keep the present_now sample,
 * which misses those waits (a GS-worker-bound phase then looks cheap and catch-up batches
 * of k phases follow: the shop close, docs/PERF-3D.md "Transition stutter"). */
void rg_pace_phase_done(rg_pace *p, uint64_t now_ns);
/* the caller presented (after present_now said so, or between phases) */
void rg_pace_presented(rg_pace *p, uint64_t now_ns);
/* Between phases (host mode, no phase owed): 1 when a present slot has come; *alpha = the
 * owed fraction of the next phase in 1/65536 (the interpolation weight).  A presenter that
 * can show a new image between phases presents and calls rg_pace_presented. */
int rg_pace_between(rg_pace *p, uint64_t now_ns, uint32_t *alpha);
/* how long the host may sleep now: min(until the next phase, until the next present slot
 * when `between` presents are wanted) */
uint64_t rg_pace_sleep_ns(const rg_pace *p, uint64_t until_tick_ns, uint64_t now_ns, int between);

#ifdef __cplusplus
}
#endif
#endif

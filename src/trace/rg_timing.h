/* SPDX-License-Identifier: CC0-1.0
 *
 * rg_timing: the port half of the timing record (docs/TIMING-LOCKSTEP.md).
 * Writes the JSONL schema tools/trace/probe.py writes with `--hooks timing`,
 * so `tools/trace/timing.py build` turns a port run into the same ticks /
 * events / milestones TSVs as a PCSX2 capture and `timing.py align` compares
 * the two.
 *
 *   {"t":"meta","hooks":["timing"],"sites":{...},"side":"port",...}
 *   {"t":"r","seq":N,"k":"entry|ret","fn":SITE,"vbl":V,"cnt":C,"a":[a0..a3],
 *    "v0":V0,"pair":P,"d":[w0..w5] [,"ra_rva":R] [,"ra_name":F] [,"src":S]}
 *
 *   vbl   the game counter D_004810C4 through the trace address map
 *         (rg_trace_read_vbl), the kernel field index before it maps
 *   cnt   (u32)(2 * ps2k_now()): EE-cycle units of the virtual clock
 *   a     u32 arguments; pointer arguments reverse-mapped to PS2 addresses
 *   pair  entry/return pairing id (guest thread id << 8 | call depth)
 *
 * Sources today, without wrapping game functions:
 *   VblankStart      kernel VBlank observer, VBLANK_START, same six words
 *   MemState         port-only: interval, game mode, overlay, scene time-scale
 *                    words read from game memory at each VBlank (on change)
 *   GfxEndFrame      synthesised from the frame context's flip counter
 *                    (+0xF00) when it moves ("src":"mem"), until the
 *                    probe_wrap stage wraps GfxEndFrame_141c20
 *   OverlayLoad      the overlay manager's load observer (src/ps2/overlay)
 *   sceCdRead        the SDK HLE (src/sce/cdvd)
 *   scePadRead       the SDK HLE (src/sce/padmc), port-only record
 *   MovieOpen/MovieShutdown   the movie service (src/movie)
 *   VsyncWait        counted per VBlank from the kernel trace (vsync sema)
 * A site the stage wraps (rg_timing_enter seen for it) silences the
 * equivalent built-in source, so no record is written twice.
 *
 * Enabled by RG_TIMING=<path> (or rg_runtime_config.timing_out); everything
 * else is inert: the game-side wrappers test `rg_timing_on` first.
 */
#ifndef RG_TIMING_H
#define RG_TIMING_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Generated from probe.py (tools/trace/gen_timing_sites.py): one word of a
 * site's six-word dump, and a site. */
enum { RG_TW_NONE = 0, RG_TW_ABS, RG_TW_ARG, RG_TW_FPR };
typedef struct rg_timing_word {
    uint8_t kind;       /* RG_TW_* */
    uint8_t noffs;      /* 0: the start value itself; else a dereference chain */
    uint32_t base;      /* ABS: PS2 address; ARG: argument index; FPR: register */
    uint32_t offs[4];
} rg_timing_word;
#define RG_TS_ENTRY 1   /* log the entry */
#define RG_TS_RET   2   /* log the return */
typedef struct rg_timing_site {
    const char *name;   /* PCSX2 site name ("GfxEndFrame"), the record's "fn" */
    const char *func;   /* game function ("GfxEndFrame_141c20") */
    uint32_t ps2_addr;
    int flags;          /* RG_TS_* */
    int skip_zero_arg;  /* leaf sites: log only when this argument is non-zero (-1: always) */
    int nent, nret;
    rg_timing_word ent[6], ret[6];
} rg_timing_site;

/* Site ids: RG_TIMING_<Site> (generated into the build: rg_timing_sites.h). */
#include "rg_timing_sites.h"
int rg_timing_site_count(void);                     /* RG_TIMING_NSITES - 1 */
const rg_timing_site *rg_timing_site_at(int id);    /* NULL out of range */
int rg_timing_site_find(const char *name);          /* site name or game function -> id, 0 if none */

/* ---------------------------------------------------------------- the wrapper API
 * What the probe_wrap stage's wrappers call (docs/TIMING-LOCKSTEP.md):
 *
 *   T Fn_141c20(A0 a0, A1 a1) {
 *       if (!rg_timing_on) return Fn_141c20__rg_body(a0, a1);
 *       rg_timing_enter(RG_TIMING_GfxEndFrame, RG_TIMING_ARGPTR(0), __builtin_return_address(0),
 *                       (uint32_t)(uintptr_t)a0, (uint32_t)a1, 0, 0, 0);
 *       T r = Fn_141c20__rg_body(a0, a1);
 *       rg_timing_leave(RG_TIMING_GfxEndFrame, 0, (uint32_t)r);
 *       return r;
 *   }
 *
 * Every wrapped call does both enter and leave, whatever the site logs: the
 * runtime keeps the arguments for the return dump (W_stk) and the pairing id.
 * flags: which arguments (and the result) are host pointers; those are
 * reverse-mapped to PS2 addresses in "a"/"v0" and used as host pointers by the
 * dump chains.  ra: the wrapper's return address (written as "ra_rva",
 * resolved offline with the link map: timing.py build --map).  f12: the bits
 * of the first float argument (W_fpr(12)), 0 if none. */
extern int rg_timing_on;            /* nonzero while recording */
#define RG_TIMING_ARGPTR(n) (1u << (n))
#define RG_TIMING_RETPTR    (1u << 4)
void rg_timing_enter(int site, unsigned flags, const void *ra, uint32_t a0, uint32_t a1, uint32_t a2,
                     uint32_t a3, uint32_t f12);
void rg_timing_leave(int site, unsigned flags, uint32_t v0);

/* ---------------------------------------------------------------- setup */
typedef struct rg_timing_config {
    const char *out;        /* JSONL path (required) */
    const char *input;      /* input script, metadata only */
    uint32_t stop_vbl;      /* request quit once the game vbl >= this (0 = no) */
    int mem_ticks;          /* synthesise GfxEndFrame from the flip counter (default 1) */
    int pad_reads;          /* write scePadRead records (default 1) */
    int quiet;
} rg_timing_config;

void rg_timing_default_config(rg_timing_config *c);
/* RG_TIMING (path; enables), RG_TIMING_STOP_VBL, RG_TIMING_MEMTICKS=0,
 * RG_TIMING_PADREADS=0.  1 if RG_TIMING is set, 0 if not, -1 malformed. */
int rg_timing_config_from_env(rg_timing_config *c);

/* Open the record (writes the meta line).  0 ok, -1 (message on stderr). */
int  rg_timing_open(const rg_timing_config *c);
int  rg_timing_is_open(void);
/* Install the sources: kernel VBlank observer + trace hook, overlay, CDVD,
 * pad and movie observers.  Needs the kernel initialised (a runtime service
 * hook).  0 ok, -1. */
int  rg_timing_attach(void);
void rg_timing_detach(void);
/* Flush, write {"t":"end"}, close (idempotent). */
void rg_timing_close(const char *reason);

/* The VBLANK_START work (the observer calls it; tests call it directly):
 * synthetic tick, MemState, VblankStart.  Returns 1 once stop_vbl is reached. */
int  rg_timing_vblank(uint64_t field);

typedef struct rg_timing_stats {
    uint64_t records, vblanks, mem_ticks, mem_states, wrapped_calls;
    uint64_t overlay_loads, cd_reads, pad_reads, movie_events, vsync_waits;
    uint32_t first_vbl, last_vbl;
} rg_timing_stats;
const rg_timing_stats *rg_timing_get_stats(void);

/* Runtime glue (trace_runtime.c): called from rg_trace_apply_env.  Reads
 * cfg->timing_out / RG_TIMING and arms a service hook that opens and
 * attaches the record.  1 armed, 0 not, -1 error. */
struct rg_runtime_config;
int rg_timing_apply(struct rg_runtime_config *cfg);

#ifdef __cplusplus
}
#endif
#endif

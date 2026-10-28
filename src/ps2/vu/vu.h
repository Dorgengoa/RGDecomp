/* SPDX-License-Identifier: CC0-1.0 */
/* PS2 Vector Unit (VU0 micro mode / VU1) interpreter.  docs/VU.md.
 *
 * Written from public hardware descriptions (VU User's Manual semantics);
 * no emulator code was copied.  The model is an in-order cycle counter with
 * per-field VF ready times, so that the NON-interlocked state the
 * microprograms observe (MAC/status/clip flags, Q, P) changes at the same
 * point in the instruction stream as on hardware, including across stalls.
 */
#ifndef RG_PS2_VU_H
#define RG_PS2_VU_H

#include <stddef.h>
#include <stdint.h>

/* this vu.h has the VU1 block translator (vu_state.blocks, stats.blk_*) */
#define RG_VU_HAS_BLOCKS 1

#ifdef __cplusplus
extern "C" {
#endif

typedef union vu_vec {
    uint32_t u[4]; /* x, y, z, w */
    float f[4];
} vu_vec;

/* dest-field bits as encoded in instructions: x is the HIGH bit */
enum { VU_X = 8, VU_Y = 4, VU_Z = 2, VU_W = 1 };

/* latencies, in cycles from issue until the result is visible */
enum {
    VU_LAT_FMAC = 4,  /* VF results (interlocked) and MAC/status/clip flags */
    VU_LAT_DIV = 7,   /* DIV, SQRT -> Q */
    VU_LAT_RSQRT = 13 /* RSQRT -> Q */
};

/* status flag bits */
enum {
    VU_ST_Z = 1 << 0, VU_ST_S = 1 << 1, VU_ST_U = 1 << 2, VU_ST_O = 1 << 3,
    VU_ST_I = 1 << 4, VU_ST_D = 1 << 5,
    VU_ST_ZS = 1 << 6, VU_ST_SS = 1 << 7, VU_ST_US = 1 << 8, VU_ST_OS = 1 << 9,
    VU_ST_IS = 1 << 10, VU_ST_DS = 1 << 11
};

/* why vu_run returned */
typedef enum vu_stop {
    VU_STOP_IDLE = 0,    /* not running */
    VU_STOP_EBIT = 1,    /* program ended (E bit + delay slot) */
    VU_STOP_CYCLES = 2,  /* cycle budget exhausted; still running */
    VU_STOP_DBIT = 3,    /* D/T debug-break bit and break_on_dt set */
    VU_STOP_ERROR = 4    /* malformed state (see vu->error) */
} vu_stop;

struct vu_state;

/* XGKICK output: one complete GIF packet (all tags up to and including EOP),
 * snapshotted from VU memory at the moment XGKICK executes. */
typedef void (*vu_gif_sink_fn)(void *user, const uint8_t *data, uint32_t bytes,
                               uint32_t vu_addr);

typedef struct vu_flag_event {
    uint64_t t;        /* visible at issue cycle >= t */
    uint8_t kind;      /* 1 = MAC+status, 2 = clip */
    uint32_t value;    /* MAC (16 bits) or clip flags (6 bits) */
} vu_flag_event;

typedef struct vu_stats {
    uint64_t pairs;          /* instruction pairs executed */
    uint64_t cycles;         /* incl. stalls */
    uint64_t stall_cycles;
    uint64_t xgkicks;
    uint64_t xgkick_bytes;
    uint64_t runs;           /* program starts */
    uint64_t int_branch_quirks; /* branches that read the pre-write VI */
    uint64_t q_early_reads;  /* Q reads while a DIV was in flight */
    /* block translator (docs/VU.md "Block translator"); not part of the
     * interpreter's observable state */
    uint64_t blk_runs;       /* translated blocks executed */
    uint64_t blk_pairs;      /* pairs executed by translated blocks */
    uint64_t blk_interp_pairs; /* pairs interpreted while blocks were on (fallback) */
    uint64_t blk_builds;     /* blocks decoded (pool misses) */
    uint64_t blk_variants;   /* timing variants compiled */
} vu_stats;

typedef struct vu_state {
    int id;                  /* 0 or 1 */
    uint32_t mem_bytes;      /* 0x1000 (VU0) / 0x4000 (VU1) */
    uint32_t code_bytes;     /* 0x1000 (VU0) / 0x4000 (VU1) */
    uint8_t mem[0x4000];
    uint8_t code[0x4000];

    vu_vec vf[32];
    vu_vec acc;
    vu_vec blk_tmp, blk_junk; /* block translator scratch (vu_block.c) */
    uint16_t vi[16];
    uint32_t q, p, i, r;     /* raw bit patterns */
    uint32_t mac, status, clip;

    uint32_t pc;             /* byte address of the next pair */
    uint32_t tpc;            /* where MSCNT continues */
    int running;

    /* VIF1 double-buffer registers seen by XTOP / XITOP */
    uint16_t top, itop;

    /* ---- pipeline model ---- */
    uint64_t cycle;          /* next issue cycle */
    uint64_t vf_ready[32][4];
    vu_flag_event fq[16];
    unsigned fq_head, fq_n;
    uint32_t q_next; uint64_t q_done; int q_busy; uint32_t q_next_flags;
    uint32_t p_next; uint64_t p_done; int p_busy;
    /* branch / end state */
    int branch_pending; uint32_t branch_target;
    int ebit_pending;
    /* VI writes of the last 4 pairs, for the integer-branch quirk: entry
     * (vih_pos + k) & 3 is the pair k + 1 pairs ago, the VI its lower op
     * wrote (-1 none) and that VI's value before the write.  The VI file
     * as it was 4 pairs ago is the current one with these writes undone. */
    int8_t vih_reg[4];
    uint16_t vih_old[4];
    unsigned vih_pos;
    int prev_vi_write;       /* VI written by the previous pair's lower op, or -1 */

    /* ---- configuration ---- */
    int int_branch_quirk;    /* default 1: see docs/VU.md */
    int break_on_dt;         /* default 0 */
    int blocks;              /* VU1: run translated blocks (default 1; env RG_VU_BLOCKS=0 turns off) */
    int blocks_check;        /* lockstep-check every block against the interpreter (env RG_VU_BLOCKS_CHECK=1) */
    void *blk;               /* block cache (vu_block.c), allocated on first use */
    int stats_print;         /* env RG_VU_BLOCKS_STATS=1: summary lines on stderr (vu_block.c) */
    uint64_t stats_next;
    struct vu_state *vu1;    /* for VU0: VU1 register window at 0x4000 */
    vu_gif_sink_fn gif_sink;
    void *gif_user;

    vu_stats stats;
    char error[96];

    /* decoded-instruction cache (private to vu.c; invalidated by vu_load_code) */
    uint8_t dc_valid[2048];
    uint64_t dc_store[2048 * 12];
} vu_state;

void vu_init(vu_state *vu, int id);
/* free the block translator's cache (vu_init does not: call this before
 * re-initialising or discarding a vu_state that ran VU1 code) */
void vu_release(vu_state *vu);
/* power-on reset of registers (memories untouched); VF0 = (0,0,0,1) */
void vu_reset_regs(vu_state *vu);

/* Start a program at byte address pc (MSCAL/vcallms: pass imm*8). */
void vu_start(vu_state *vu, uint32_t pc);
/* MSCNT: continue at TPC. */
void vu_continue(vu_state *vu);
/* Run up to max_cycles cycles (0 = unbounded; dangerous). */
vu_stop vu_run(vu_state *vu, uint64_t max_cycles);
/* Execute exactly one pair (for tests); returns stop reason or VU_STOP_CYCLES. */
vu_stop vu_step(vu_state *vu);
/* Let every in-flight flag / Q / P write land (what the hardware pipeline
 * does by itself after the program ends). */
void vu_drain(vu_state *vu);

/* Upload microcode (MPG). addr and bytes in bytes, addr 8-aligned. */
void vu_load_code(vu_state *vu, uint32_t addr, const void *src, uint32_t bytes);

/* GIF packet length (bytes) starting at VU data address addr (bytes),
 * walking tags up to EOP; returns 0 if the walk runs past 16 KB. */
uint32_t vu_gif_packet_bytes(const vu_state *vu, uint32_t addr);

/* ---- VU float helpers (exposed for tests and the VU0 macro layer) ---- */
/* MAC-style condition bits of one lane result: bit0 Z, 1 S, 2 U, 3 O */
uint32_t vu_f_add(uint32_t a, uint32_t b, unsigned *cond);
uint32_t vu_f_sub(uint32_t a, uint32_t b, unsigned *cond);
uint32_t vu_f_mul(uint32_t a, uint32_t b, unsigned *cond);
double vu_f_to_d(uint32_t a);
uint32_t vu_f_from_d(double v, unsigned *cond);
uint32_t vu_ftoi(uint32_t a, int frac_bits);
uint32_t vu_itof(uint32_t a, int frac_bits);
/* -1 / 0 / +1 comparison under VU ordering (denormals compare as zero) */
int vu_f_cmp(uint32_t a, uint32_t b);

#ifdef __cplusplus
}
#endif
#endif

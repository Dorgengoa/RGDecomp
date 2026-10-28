/* SPDX-License-Identifier: CC0-1.0
 *
 * rg_trace: the port side of the state-trace lockstep (PLAN.md "Verification",
 * docs/TRACE-PORT.md).  At each VBLANK_START it hashes the same EE regions as
 * the PCSX2 harness (tools/trace/trace.py) and writes rows in the same TSV
 * format, so `trace.py compare --key vbl` judges a port run against a PCSX2
 * golden.
 *
 *   hash      BLAKE2b with an 8-byte digest (hashlib.blake2b(digest_size=8)),
 *             16 lower-case hex digits
 *   rows      frame <TAB> region <TAB> hash; '@cycle' (u32 hex), '@vbl'
 *             (decimal game VBlank counter) first, then regions in file order
 *   regions   the PCSX2 region files, parsed with trace.py's grammar
 *             (space name start end [chunk] | space name *PTR[+OFF] size |
 *             include file)
 *
 * PS2 addresses are resolved through an ADDRESS MAP (trace_map.c):
 *   1. symbols   PS2 address range -> host object (a generated table of
 *                `&D_xxxxxxxx`, tools/trace/gen_port_symtab.py, or symbols
 *                added at run time),
 *   2. arena     the overlay arena [0x004E9E80, 0x00528200) (bound overlay
 *                registry, docs/OVERLAY.md); with the native module table (no
 *                arena, docs/OVERLAY.md section 8) the ACTIVE module's data segment
 *                at its retail data start (arena base + 0x40 + the descriptor's text_size)
 *                .. + data + bss; text range unmapped,
 *   3. RAM       the crt0 RAM block (host base = PS2 address 0), mapped only
 *                from the heap start up (the statics below it live elsewhere).
 * The reverse map (host pointer -> PS2 address) uses the same three, and
 * translates host pointers stored in game memory (deref regions, pointer
 * slots).  Single-threaded: call from the kernel's thread only.
 */
#ifndef RG_TRACE_H
#define RG_TRACE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------- hash */
/* RFC 7693 BLAKE2b, unkeyed, outlen 1..64 (blake2b.c). */
void rg_trace_blake2b(void *out, size_t outlen, const void *in, size_t n);
/* trace.py's h(): hex of blake2b(digest_size=8); out gets 16 chars + NUL. */
void rg_trace_hash_hex(char out[17], const void *data, size_t n);

/* ---------------------------------------------------------------- address map */
#define RG_TRACE_EE_RAM_SIZE 0x02000000u
#define RG_TRACE_ARENA_BASE  0x004E9E80u
#define RG_TRACE_ARENA_END   0x00528200u
#define RG_TRACE_HEAP_START  0x00528200u

typedef struct rg_trace_sym {
    uint32_t addr;     /* PS2 address */
    uint32_t size;     /* bytes this host object covers */
    void *host;        /* host address of `addr` */
    const char *name;  /* for notes */
} rg_trace_sym;

/* Add symbols (copied; the names are not).  Overlapping PS2 ranges are an
 * error (-1, message on stderr).  The generated game table calls this. */
int  rg_trace_add_symbols(const rg_trace_sym *syms, int n);
int  rg_trace_add_symbol(uint32_t addr, uint32_t size, void *host, const char *name);
void rg_trace_clear_symbols(void);
/* The generated game table (rg_trace_symtab_game, gen_port_symtab.py); the
 * game exe calls it before rg_trace_apply_env.  0 ok. */
int  rg_trace_register_game_symtab(void);
int  rg_trace_symbol_count(void);
/* The symbol covering a PS2 address (NULL if none). */
const rg_trace_sym *rg_trace_symbol_at(uint32_t addr);

/* The game heap, an explicit mapping (docs/NATIVE-CPU.md section 8): PS2 addresses
 * [lo, lo + size) live at host [host_start, host_start + size).  The runtime passes
 * crt0's heap (RG_PS2_HEAP_START = 0x00528200, its host start and size).  NULL removes it. */
void rg_trace_set_heap(void *host_start, uint32_t lo, uint32_t size);
/* Older form (tests): host = host address of PS2 address 0, range [lo, hi) mapped
 * through it; the same as rg_trace_set_heap(host + lo, lo, hi - lo). */
void rg_trace_set_ram(void *host, uint32_t lo, uint32_t hi);
/* Overlay arena: host block for [base, base + size).  host NULL removes it.
 * When none was set, the bound overlay registry's arena is used. */
void rg_trace_set_arena(void *host, uint32_t base, uint32_t size);

/* Forward: host pointer for a PS2 address and the contiguous bytes from it
 * that the same mapping covers (*avail), or NULL when unmapped. */
void *rg_trace_host_ptr(uint32_t addr, uint32_t *avail);
/* Read [addr, addr + n) across mappings.  0 ok; -1 if any byte is unmapped
 * (*bad = the first unmapped address). */
int rg_trace_read(uint32_t addr, void *dst, uint32_t n, uint32_t *bad);
/* Reverse: PS2 address of a host pointer; 0 ok, -1 if no mapping covers it. */
int rg_trace_ps2_addr(const void *p, uint32_t *out);
/* 1 if [p, p + n) is committed, readable host memory (Windows VirtualQuery;
 * always 0 elsewhere).  For pointers the reverse map cannot translate. */
int rg_trace_host_readable(const void *p, size_t n);

/* ---------------------------------------------------------------- regions */
enum { RG_TRACE_SPACE_EE = 0, RG_TRACE_SPACE_IOP = 1, RG_TRACE_SPACE_SPR = 2 };
#define RG_TRACE_MAX_SLOTS 16

typedef struct rg_trace_region {
    char name[64];
    int space;            /* RG_TRACE_SPACE_* */
    uint32_t start, end;  /* range: [start, end); deref: start = 0, end = size */
    int deref;            /* 1: hash [*ptr + off, +size) */
    uint32_t ptr, off;
    /* port side (port_regions.cfg): */
    int ps2ptr;           /* stored pointer(s) are PS2 address values, not host pointers */
    int nslots;           /* 32-bit host pointer slots translated to PS2 addresses */
    uint32_t slots[RG_TRACE_MAX_SLOTS];
    /* recorder state */
    int noted;            /* an 'unmapped'/'deref' note was written */
} rg_trace_region;

typedef struct rg_trace_regions {
    rg_trace_region *r;
    int n, cap;
} rg_trace_regions;

/* Parse a region file (trace.py load_regions grammar, includes relative to
 * the including file).  0 ok, -1 with a message in err. */
int  rg_trace_regions_load(rg_trace_regions *rs, const char *path, char *err, size_t errcap);
/* Port-side annotations (tools/trace/port_regions.cfg):
 *   ptrs   <region> <off>[,<off>...]   host pointer slots -> PS2 addresses
 *   ps2ptr <region>                    the deref pointer / slots hold PS2 addresses
 *   exclude|pending <regex> <reason>   compare-side only (port_trace.py); ignored here
 * Unknown region names are an error.  0 ok, -1 with a message. */
int  rg_trace_portcfg_load(rg_trace_regions *rs, const char *path, char *err, size_t errcap);
void rg_trace_regions_free(rg_trace_regions *rs);
rg_trace_region *rg_trace_region_find(rg_trace_regions *rs, const char *name);

/* The bytes one region hashes, after pointer handling, into buf (cap bytes).
 * Returns the byte count, or -1 when the region is unmapped (reason in why).
 * ps2_pointers: treat every stored pointer as a PS2 address (PCSX2 image mode). */
/* A non-empty `why` with a byte count >= 0 is a note (a deref that read raw
 * host memory outside the map).  *untranslated (may be NULL) counts pointer
 * values the reverse map could not translate. */
int rg_trace_region_bytes(const rg_trace_region *rg, int ps2_pointers, uint8_t *buf, size_t cap,
                          char *why, size_t whycap, int *untranslated);
/* Bytes a region can need (range length, deref size, or a marker). */
size_t rg_trace_region_max_bytes(const rg_trace_region *rg);

/* ---------------------------------------------------------------- recorder */
#define RG_TRACE_GAME_VBL_ADDR 0x004810C4u   /* GfxVblankStartHandler_15df20's counter */
#define RG_TRACE_GAMEMODE_ADDR 0x004B51A0u   /* GameModeStack[0] */
#define RG_TRACE_OVERLAY_ADDR  0x0047E254u   /* LoadedOverlayId */

typedef struct rg_trace_config {
    const char *out;          /* TSV path (required) */
    const char *regions;      /* region file (required) */
    const char *portcfg;      /* port_regions.cfg (optional) */
    const char *input;        /* input script, metadata only */
    uint32_t vbl_addr;        /* game VBlank counter (default RG_TRACE_GAME_VBL_ADDR) */
    int vbl_kernel;           /* 1: key by the kernel VBlank count even if the counter maps */
    uint32_t every;           /* emit when vbl % every == 0 (default 1) */
    const char *keys;         /* file of vbl values to emit (one per line; overrides every) */
    uint32_t stop_vbl;        /* stop once vbl >= this (0 = no) */
    uint64_t stop_frames;     /* stop after this many samples (0 = no) */
    int ps2_pointers;         /* all stored pointers are PS2 addresses (image mode, tests) */
    int input_lead;           /* rg_trace_game_vblank returns counter + lead (default 1) */
    /* deliberate-fault control: xor fault_xor into the byte at fault_addr
     * (through the address map) at the first sample with vbl >= fault_vbl */
    int fault;
    uint32_t fault_addr, fault_vbl;
    uint8_t fault_xor;
    int quiet;
} rg_trace_config;

void rg_trace_default_config(rg_trace_config *c);
/* RG_TRACE_OUT (enables), RG_TRACE_REGIONS, RG_TRACE_PORTCFG, RG_TRACE_INPUT,
 * RG_TRACE_EVERY, RG_TRACE_KEYS, RG_TRACE_STOP_VBL, RG_TRACE_FRAMES,
 * RG_TRACE_VBL_ADDR, RG_TRACE_VBL_KERNEL, RG_TRACE_PS2PTRS, RG_TRACE_INPUT_LEAD,
 * RG_TRACE_FAULT=addr:vbl[:xor].  Returns 1 if RG_TRACE_OUT is set, 0 if not,
 * -1 on a malformed value (message on stderr).  Strings point into the
 * environment. */
int rg_trace_config_from_env(rg_trace_config *c);

/* Open the recorder: parse regions (+ portcfg), open the TSV, write the
 * header.  0 ok, -1 (message on stderr). */
int  rg_trace_open(const rg_trace_config *c);
int  rg_trace_is_open(void);
/* The game VBlank counter now (through the map), or `fallback` when it is
 * unmapped or cfg.vbl_kernel is set.  *from_game = 1 when it came from game memory. */
uint32_t rg_trace_read_vbl(uint32_t fallback, int *from_game);
/* One sample: frame = kernel field index, cycle = virtual bus cycle,
 * kernel_vbl = fallback key.  Writes rows if the vbl is wanted.  Returns 1
 * when a stop condition was reached (the trace is then closed), else 0. */
int  rg_trace_sample(uint64_t frame, uint64_t cycle, uint32_t kernel_vbl);
/* Write '# stop <reason>' and the sample count, close the file (idempotent). */
void rg_trace_close(const char *reason);

typedef struct rg_trace_stats {
    uint64_t samples, emitted, rows;
    uint64_t unmapped_skips;    /* region rows skipped (unmapped) */
    uint64_t untranslated;      /* pointer slots / derefs the reverse map missed */
    uint32_t first_vbl, last_vbl;
    int vbl_from_game;          /* the last sample keyed by the game counter */
} rg_trace_stats;
const rg_trace_stats *rg_trace_get_stats(void);

/* ---------------------------------------------------------------- runtime glue */
/* trace_runtime.c (needs rg_runtime).  Reads the RG_TRACE_* environment;
 * when RG_TRACE_OUT is set: headless (RG_TRACE_HEADLESS=0 keeps the window),
 * cfg->input_script from RG_TRACE_INPUT unless already set, cfg->game_vblank
 * = rg_trace_game_vblank, and a service hook that maps the RAM block, opens
 * the recorder and adds a VBLANK_START observer.  Call before
 * rg_runtime_init.  Returns 1 tracing, 0 not, -1 error. */
struct rg_runtime_config;
int rg_trace_apply_env(struct rg_runtime_config *cfg);
/* rg_game_vblank_fn: the game counter + input_lead (kernel count until mapped). */
uint32_t rg_trace_game_vblank(void *user, uint64_t kernel_vblank);

#ifdef __cplusplus
}
#endif
#endif

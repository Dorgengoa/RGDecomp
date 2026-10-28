/* SPDX-License-Identifier: CC0-1.0
 *
 * rg_savestate: port save states (docs/TEST-FIXTURES.md "Save states").
 *
 * A save state is the whole running game at a field boundary, for the SAME
 * build only (the exe's hash is in the file; any other build is refused):
 *
 *   ram      the game heap (crt0's one allocation, newlib malloc's arena; format 2)
 *   statics  every .data/.bss byte owned by game code or port models
 *            (ss_map.c classifies the link map; host libraries are skipped)
 *   heap     the state heap: every allocation game or model code made
 *            (ss_heap.c), allocator metadata included
 *   fibers   the guest threads' stacks and saved contexts (ps2k_ss.h)
 *   hooks    one section per subsystem whose state needs more than raw bytes
 *            (kernel, runtime; rg_ss_add_hook for more)
 *
 * Everything sits at the same address in every run of the build: the exe is
 * linked without ASLR, and rg_ss_init() reserves the game heap, the fiber
 * arena and the state heap at the start of main.  Loading writes the bytes
 * back and lets the hooks re-attach host resources (GPU renderer, GS worker
 * thread, ...).  The loading process must be started with the same
 * game-visible options (the init allocation fingerprint is compared).
 *
 * D9 (native end state): each native subsystem that replaces a model plugs
 * in its own hook (save its game-visible state, rebuild its host resources
 * on load); the raw sections shrink as models leave the executable.
 *
 * Original CC0 code.
 */
#ifndef RG_SAVESTATE_H
#define RG_SAVESTATE_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- process setup (first thing in main) ---- */
/* Parse the link map, reserve the state region and turn the state heap on.
 * 0 ok; -1: save states unavailable (rg_ss_error() says why), the program
 * runs normally on the CRT heap. */
int rg_ss_init(void);
int rg_ss_active(void);
const char *rg_ss_error(void);
/* crt0's RAM block provider: commits the reserved RAM range (NULL if none). */
void *rg_ss_ram_alloc(size_t size);
/* the fiber arena range (ps2k_fiber_arena_set) */
void rg_ss_arena(void **base, size_t *size);
/* End of init: the allocation fingerprint stops here (call after rg_runtime_init). */
void rg_ss_mark_init_done(void);

/* ---- subsystem hooks ---- */
typedef struct rg_ss_hook {
    const char *name;                       /* section name, <= 31 chars, unique */
    /* NULL or: 0 = may save now, else a reason in why (e.g. a transfer in flight) */
    int (*can_save)(char *why, size_t cap);
    void (*pre_save)(void);                 /* e.g. drain a worker thread */
    /* size of the blob, then fill it; NULL size: no section */
    size_t (*save_size)(void);
    int (*save)(void *buf, size_t cap);     /* bytes written or -1 */
    void (*pre_load)(void);                 /* before ANY bytes are written back */
    int (*load)(const void *buf, size_t n); /* after the raw sections; 0 ok */
    void (*post_load)(void);                /* after every hook's load */
} rg_ss_hook;
int rg_ss_add_hook(const rg_ss_hook *h);    /* copied; 0 ok, -1 full / duplicate */
/* The kernel ("kernel") and runtime ("runtime") hooks (ss_hooks.c). */
int rg_ss_register_default_hooks(void);
/* Host-pointer audit ($RG_SS_AUDIT): lists words in saved memory that point
 * into CRT (host) heap blocks, at most `limit` lines; returns the hit count. */
int rg_ss_audit(FILE *out, int limit);

/* ---- save / load ---- */
typedef struct rg_ss_meta {
    uint64_t field;           /* fields completed when saved (runtime stats) */
    uint32_t game_vbl;        /* the game's VBlank counter D_004810C4 */
    uint64_t kernel_vblank;
    uint64_t kernel_now;      /* virtual bus cycle */
    uint64_t run_hash;
    uint64_t created;         /* unix time */
    char note[128];           /* free text (milestone name, input script) */
    char input[256];          /* the input script the saver ran */
} rg_ss_meta;

/* Write a state now (between fields).  meta: what to record (field etc. are
 * filled by the caller).  0 ok; -1 with a message in err. */
int rg_ss_save(const char *path, const rg_ss_meta *meta, char *err, size_t cap);
/* Load a state into this process (after init, before the first field, or
 * between fields).  meta receives the saved header.  0 ok; -1 with a message;
 * a failure after bytes were written back leaves the process unusable
 * (rg-game exits). */
int rg_ss_load(const char *path, rg_ss_meta *meta, char *err, size_t cap);
/* Header only (no process change); also checks it against this build when
 * check_build is set.  0 ok. */
int rg_ss_peek(const char *path, rg_ss_meta *meta, int check_build, char *err, size_t cap);
/* The 128-bit build id of the running exe (hash of the file), hex, 33 bytes. */
const char *rg_ss_build_id(void);

#ifdef __cplusplus
}
#endif
#endif

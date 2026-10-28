/* SPDX-License-Identifier: CC0-1.0
 * Port save states: private interfaces (docs/TEST-FIXTURES.md). */
#ifndef RG_SS_INTERNAL_H
#define RG_SS_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/* What a piece of the executable is, for save states:
 *   GAME   game/, overrides/, missing/, the overlay arena: saved raw
 *   MODEL  port models and SDK replacements (rg_ps2_*, rg_sce_*, ...): saved raw
 *   HOST   window, GPU, audio device, settings, CRT, SDL, trace, file service,
 *          memory-card files, this module: never saved (the loading process
 *          keeps its own)
 *   HOOK   saved by a subsystem hook (kernel K, runtime R) */
enum { SS_GAME = 0, SS_MODEL = 1, SS_HOST = 2, SS_HOOK = 3 };

typedef struct ss_range {
    uintptr_t lo, hi;
    int cls;
} ss_range;

/* ---- ss_map.c: the link map next to the exe ---- */
typedef struct ss_image {
    uintptr_t base;                 /* actual module base */
    uintptr_t text_lo, text_hi;
    uintptr_t data_lo, data_hi;     /* .data incl. its .bss tail */
    uint32_t timestamp;             /* PE TimeDateStamp (= the map's) */
    uint32_t size_of_image;
    char exe_path[520];
} ss_image;

int ss_map_load(char *err, size_t cap);     /* parse rg-game.map once; 0 ok */
int ss_map_ready(void);
const ss_image *ss_map_image(void);
/* class of the code containing addr (a return address); SS_HOST if unknown */
int ss_map_code_class(uintptr_t addr);
/* merged data ranges [lo, hi) covering .data, each with its class */
int ss_map_data_ranges(const ss_range **out);
/* "symbol+0xoff (lib:obj)" for a data or code address (diagnostics) */
const char *ss_map_describe(uintptr_t addr, char *buf, size_t cap);

/* ---- ss_heap.c: the state region (RAM block, fiber arena, state heap) ---- */
typedef struct ss_region_info {
    uintptr_t ram, ram_size;        /* reserved for crt0 */
    uintptr_t arena, arena_size;    /* fiber stacks */
    uintptr_t heap, heap_size;      /* state heap reservation */
} ss_region_info;
const ss_region_info *ss_region(void);
int ss_heap_on(void);
/* [heap, top): the part of the state heap in use (chunks + metadata) */
uintptr_t ss_heap_top(void);
/* commit [heap, top) before a load writes it back */
int ss_heap_prepare(uintptr_t top);
void ss_heap_lock(void);
void ss_heap_unlock(void);
uint64_t ss_heap_init_fingerprint(void);
/* allocs, frees, live bytes, top bytes, host allocs, model allocs */
void ss_heap_stats(uint64_t out[6]);
/* chunks in use: fn(payload, requested bytes, allocating return address); heap locked */
void ss_heap_walk(void (*fn)(void *user, uintptr_t p, uint32_t n, uintptr_t caller), void *user);

/* ---- hashing ---- */
uint64_t ss_hash64(const void *p, size_t n, uint64_t seed);

#endif

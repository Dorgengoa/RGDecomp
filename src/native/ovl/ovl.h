/* SPDX-License-Identifier: CC0-1.0
 *
 * Overlay manager (PLAN.md P2 "Overlay manager", transform 7; docs/OVERLAY.md).
 *
 * Retail: MAIN loads one MWo3 overlay at a time into the 0x004E9E80 arena
 * (OverlayLoad_1c3210 -> OverlayLoadFile_100410): read the whole file
 * (header + text + data) over the arena, FlushCache, zero the bss after it,
 * run the header's .ctors range through RunStaticCtors_100df0.  No entry
 * point is jumped to, and no destructors run on a switch (every .dtors list
 * is empty).  MAIN then reaches overlay code through fixed addresses
 * (`jal func_4F6AB0`, 206 names), MAIN data slots (vtables / mode tables
 * holding overlay function addresses) and callbacks the overlay registers.
 *
 * Two managers implement this interface:
 *   src/native/ovl   the native module table (what a native-only rg-game links,
 *                    docs/OVERLAY.md section 8): every overlay is a statically linked
 *                    module with its own data segment; load = restore its .data, zero
 *                    its .bss, make it the active module, run its ctors.  Imports
 *                    dispatch through a build-time table (import x active module).
 *                    No retail address anywhere.
 *   src/ps2/overlay  the arena manager (bring-up; default builds and tests), below.
 *
 * Arena manager: all five overlays are linked into the executable.  Their .data/.bss
 * symbols are labels in ONE shared arena block at their retail offsets
 * (generated: ovl_arena_gen.c), so overlays alias each other's memory as on
 * the PS2.  load() = restore the overlay's pristine .data, zero its bss,
 * run its (lifted) ctors.  Calls into the arena by PS2 address go through
 * rg_ovl_resolve_fn() / the import trampolines, keyed by (resident overlay,
 * address).
 *
 * Single-threaded like the EE kernel model: call from guest context only.
 */
#ifndef RG_PS2_OVL_H
#define RG_PS2_OVL_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RG_OVL_HDR_SIZE 0x40u
#define RG_OVL_MAX 8

typedef void (*rg_ovl_fn)(void);

typedef struct rg_ovl_func {        /* one function entry, sorted by addr */
    uint32_t addr;
    const char *name;
    rg_ovl_fn fn;
} rg_ovl_func;

typedef struct rg_ovl_label {       /* a data/bss symbol, sorted by addr */
    uint32_t addr;
    const char *name;
} rg_ovl_label;

typedef struct rg_ovl_object {      /* object mode (overlay data as C, data2c) */
    uint32_t addr, size;
    unsigned char *ptr;             /* the live C object */
    const char *name;
} rg_ovl_object;

typedef struct rg_ovl_desc {
    const char *name;               /* "title" */
    const char *file;               /* "TITLE.BIN" */
    int index;                      /* loader index: OverlayLoad_1c3210's argument */
    uint32_t id;                    /* MWo3 id (header +4) */
    uint32_t load;                  /* 0x004E9E80 */
    uint32_t text_size, data_size, bss_size;   /* text includes the 0x40 nop pad */
    uint32_t ctor_start, dtor_start;           /* header +0x18 / +0x1C */
    /* arena mode: pristine .data (data_size bytes, relocated host words) */
    const uint32_t *data_image;
    /* object mode: the overlay's data objects; bss objects (addr >= bss) are zeroed */
    const rg_ovl_object *objects;
    int nobjects;
    const rg_ovl_fn *ctors;         /* .ctors, table order (= retail call order) */
    int nctors;
    const rg_ovl_fn *dtors;         /* .dtors: empty in all five retail overlays */
    int ndtors;
    const rg_ovl_func *funcs;
    int nfuncs;
    const rg_ovl_label *labels;
    int nlabels;
    /* native module (src/native/ovl): the overlay's own data segment, .data then
     * .bss (data_size + bss_size bytes, its data/bss symbols are labels in it).
     * NULL for the arena manager (src/ps2/overlay), which places every overlay in
     * the shared retail-address arena instead. */
    unsigned char *seg;
} rg_ovl_desc;

/* A MAIN -> arena call target that MAIN names by address. */
typedef struct rg_ovl_import {
    const char *name;               /* "func_4F6AB0" */
    uint32_t addr;
    int domain;                     /* overlay (descriptor index) the data2c slot
                                       was attributed to, or -1 (a MAIN call) */
    int kind;                       /* 0 MAIN code call, 1 MAIN data slot */
    /* native module table: the host function each overlay (descriptor index)
     * defines under this import, resolved at build time; NULL entries = none.
     * The arena manager keys on `addr` instead (0 in a native registry). */
    const rg_ovl_fn *fns;
} rg_ovl_import;

typedef struct rg_ovl_registry {
    const rg_ovl_desc *ovls;
    int novls;
    unsigned char *arena;           /* host block for [arena_base, arena_base+arena_size) */
    uint32_t arena_base, arena_size;
    const rg_ovl_import *imports;
    int nimports;
    const char *snapshot;
} rg_ovl_registry;

/* ---- binding ---- */
/* Validate and bind a registry (sorted tables, ranges inside the arena,
 * object-mode pristine snapshots taken now).  Unbinds the previous one.
 * Returns 0, or -1 with a message through the report hook. */
int rg_ovl_bind(const rg_ovl_registry *reg);
void rg_ovl_unbind(void);
const rg_ovl_registry *rg_ovl_bound(void);

/* ---- lookup ---- */
int rg_ovl_count(void);
const rg_ovl_desc *rg_ovl_desc_at(int ovl);
int rg_ovl_find(const char *name);              /* "normal" (case-insensitive) -> ovl, or -1 */
int rg_ovl_find_index(int loader_index);        /* OverlayLoad_1c3210 argument -> ovl */
int rg_ovl_find_file(const char *path);         /* "cdrom0:\\BIN\\NORMAL.BIN;1", "host0:BIN/..." */

/* ---- load / switch ---- */
/* Retail OverlayLoadFile semantics: the arena gets the overlay's header, its
 * text range is cleared (retail overwrites it with code), .data is restored
 * from the pristine image, bss is zeroed, then .ctors run in table order.
 * Reloading the resident overlay does all of it again (retail does).
 * Returns 0, or -1 (bad index). */
int rg_ovl_load(int ovl);
int rg_ovl_current(void);                       /* resident overlay, -1 before the first load */
uint64_t rg_ovl_load_count(int ovl);            /* loads of ovl (ovl < 0: all) */
/* Run the outgoing overlay's .dtors before a switch (default 0: retail never
 * does; the lists are empty anyway). */
void rg_ovl_set_run_dtors(int on);
/* Load observer (timing record, docs/TIMING-LOCKSTEP.md): called with done = 0
 * before and done = 1 after every rg_ovl_load of a valid overlay (ovl =
 * registry index; rg_ovl_desc_at(ovl)->index is the OverlayLoad_1c3210
 * argument).  NULL removes it.  One observer. */
typedef void (*rg_ovl_load_hook_fn)(void *user, int ovl, int done);
void rg_ovl_set_load_hook(rg_ovl_load_hook_fn fn, void *user);

/* ---- address map: ARENA MANAGER ONLY (src/ps2/overlay) ----
 * Keyed by retail PS2 addresses.  The native module table (src/native/ovl) does not
 * define these: a native-only rg-game that referenced one would not link. */
rg_ovl_fn rg_ovl_lookup_fn(int ovl, uint32_t addr);       /* exact entry, or NULL */
const char *rg_ovl_fn_name(int ovl, uint32_t addr);
/* Function at addr in the RESIDENT overlay; unknown -> reported, NULL. */
rg_ovl_fn rg_ovl_resolve_fn(uint32_t addr);
/* Host address of any arena address (whatever is resident there), or NULL. */
void *rg_ovl_host_ptr(uint32_t addr);
/* Host address of ovl's data/bss address while ovl is resident, else NULL. */
void *rg_ovl_resident_ptr(int ovl, uint32_t addr);
/* Inverse of rg_ovl_host_ptr (0 when p is not in the arena). */
uint32_t rg_ovl_ps2_addr(const void *p);
/* The label covering addr in ovl (nearest at or below), its offset in *off. */
const char *rg_ovl_label_at(int ovl, uint32_t addr, uint32_t *off);

/* hwbus_ovl_resolver_fn (docs/HWBUS.md): RG_OVL_DATA(T, ovl, sym, addr, off). */
void *rg_ovl_hwbus_resolve(void *user, const char *ovl, const char *sym, uint32_t sym_addr);

/* ---- MAIN -> overlay calls ---- */
/* Called by the generated trampolines (RG_OVL_TRAMPOLINE): the host function
 * for tab[idx] in the resident overlay.  Unknown -> reported; then abort()
 * when fatal (default), else a stub that returns 0. */
void *rg_ovl_call_import_at(const rg_ovl_import *tab, int idx);
void rg_ovl_set_fatal(int on);

/* ---- reporting ---- */
enum {
    RG_OVL_REP_UNKNOWN_FN = 1,      /* call to an address with no entry in the resident overlay */
    RG_OVL_REP_NOT_RESIDENT,        /* no overlay loaded / RG_OVL_DATA of a non-resident overlay */
    RG_OVL_REP_DOMAIN,              /* data-slot import called while another overlay is resident */
    RG_OVL_REP_BAD_FILE,            /* OverlayLoadFile path names no overlay */
    RG_OVL_REP_BIND                 /* registry validation */
};
typedef void (*rg_ovl_report_fn)(void *user, int kind, int ovl, uint32_t addr, const char *msg);
void rg_ovl_set_report(rg_ovl_report_fn fn, void *user);  /* NULL: stderr, once per (kind, addr) */

typedef struct rg_ovl_unknown {
    int kind, ovl;
    uint32_t addr;
    uint32_t count;
    const char *name;               /* import name or symbol, may be NULL */
} rg_ovl_unknown;
int rg_ovl_unknown_count(void);
const rg_ovl_unknown *rg_ovl_unknown_get(int i);
void rg_ovl_unknown_clear(void);

#ifdef __cplusplus
}
#endif
#endif

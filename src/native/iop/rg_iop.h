/* SPDX-License-Identifier: CC0-1.0 */
/* Native IOP lane (docs/NATIVE-IOP.md, PLAN.md D9): the switch between the native
 * path and the IOP/SIF HLE oracle, and the census counters that prove the native
 * path never enters the HLE.
 *
 *   RG_IOP=native (default)  libpad / libmc / IOP boot are native services: no SIF
 *                            RPC, no SIF DMA, no IOP RAM, no padman / mcserv server.
 *   RG_IOP=hle               the bring-up path (src/sce/sif -> src/ps2/sif + src/ps2/iop,
 *                            padman / mcserv servers): the oracle.
 *
 * The runtime forces hle when another lane still needs the IOP (a sound path left on
 * the HLE: RG_AUDIO=hle|compare, RG_AUDIO_PCM/MOVIE=hle) and says so.
 *
 * Census: every SDK entry the game reaches (sceSif*, sceFsReset, scePad*, sceMc*, ...)
 * counts itself with RG_IOP_API("name"); every entry into the HLE layers
 * (src/ps2/sif, src/ps2/iop, padman / mcserv, the sound HLE's runtime calls) with
 * RG_IOP_HLE("name").  RG_IOP_CENSUS=path writes both tables at shutdown;
 * rg_iop_hle_total() is the proof counter (0 on the native golden route), and
 * RG_IOP_ASSERT=1 makes the first HLE entry in native mode fatal.
 *
 * Kernel- and model-agnostic; host code only (counters are not game state). */
#ifndef RG_NATIVE_IOP_H
#define RG_NATIVE_IOP_H
#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

#define RG_IOP_MODE_NATIVE 0
#define RG_IOP_MODE_HLE    1

/* Mode: $RG_IOP on first use unless rg_iop_set_mode ran first. */
int rg_iop_mode(void);
int rg_iop_native(void);
int rg_iop_hle(void);
void rg_iop_set_mode(int mode);

/* RG_NATIVE_ONLY builds (cmake -DRG_NATIVE_ONLY=ON, docs/NATIVE-ONLY.md): the HLE oracle
 * is not compiled in.  RG_IOP_ORACLE is 0, the mode is the constant native (RG_IOP=hle is
 * refused with a message), every HLE-only block is inside `#if RG_IOP_ORACLE`, and
 * RG_IOP_PICK(native, hle) keeps only its native expression.  Default builds: unchanged
 * (RG_IOP_ORACLE 1, the run-time switch). */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
#define RG_IOP_ORACLE 0
#define rg_iop_native() 1
#define rg_iop_hle() 0
#define RG_IOP_PICK(native, hle) (native)
#else
#define RG_IOP_ORACLE 1
#define RG_IOP_PICK(native, hle) (rg_iop_native() ? (native) : (hle))
#endif
/* What $RG_IOP asked for (the runtime may force hle afterwards). */
int rg_iop_requested_mode(void);

/* Census.  `name` must be a string literal (counted by pointer).  `id` separates
 * rows of one name (RPC sid/fno, module index); 0 when unused. */
void rg_iop_count_api(const char *name, uint32_t id);
void rg_iop_count_hle(const char *name, uint32_t id);
#define RG_IOP_API(name) rg_iop_count_api(name, 0)
#define RG_IOP_API_ID(name, id) rg_iop_count_api(name, (uint32_t)(id))
#define RG_IOP_HLE(name) rg_iop_count_hle(name, 0)
#define RG_IOP_HLE_ID(name, id) rg_iop_count_hle(name, (uint32_t)(id))

/* A native-mode SDK call that would have needed the IOP and has no native meaning
 * (a SIF RPC to a server nothing native provides, SIF DMA, IOP heap, sdremote):
 * counted (layer "unconverted") and reported once per (name, id) on stderr.  0 on
 * the golden route; a non-zero count names an IOP user another lane still has. */
void rg_iop_unconverted(const char *name, uint32_t id);
uint64_t rg_iop_unconverted_total(void);
/* Native stand-in for an IOP heap address (a budget handle the game only stores and
 * gives back): 256-byte aligned, never 0, from a bump range; freeing is a no-op. */
uint32_t rg_iop_native_heap_handle(uint32_t size);

uint64_t rg_iop_hle_total(void);          /* HLE entries since start (or reset) */
uint64_t rg_iop_hle_total_native(void);   /* ... of them while the mode was native */
uint64_t rg_iop_api_count(const char *name); /* by string compare, all ids */
uint64_t rg_iop_hle_count(const char *name);
void rg_iop_census_reset(void);
/* TSV: layer, name, id (hex), count.  0 ok. */
int rg_iop_census_write(FILE *f);
/* Shutdown line ("rg_iop: mode native, 0 HLE entries, N native SDK calls") and the
 * $RG_IOP_CENSUS file.  quiet: only write the file. */
void rg_iop_report(int quiet);

#ifdef __cplusplus
}
#endif
#endif

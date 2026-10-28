/* SPDX-License-Identifier: CC0-1.0
 *
 * rg_runtime: the platform glue that boots the whole PS2 model stack under
 * the host shell and drives the virtual clock a field at a time
 * (PLAN.md P2/P3/P4, docs/RUNTIME.md).
 *
 *   rg_runtime_init(&cfg)      host, kernel, graphics models, CDVD, IOP/SIF,
 *                              pad/memcard/sound, VBlank observers, game RAM,
 *                              in a fixed, documented order (docs/RUNTIME.md)
 *   rg_runtime_run_field()     run the EE scheduler until the next
 *                              VBLANK_START, then do the host half of the
 *                              field (events, audio, present)
 *   rg_runtime_run(n)          run_field until quit / stop / n fields
 *   rg_runtime_shutdown()      tear down in reverse order, flush memory cards
 *
 * The EE side starts in rg_ps2_main (crt0 equivalent, crt0.c) on guest thread
 * 1, which calls the game's entry (rg_game_entry, weak; or cfg.entry).
 *
 * One runtime per process (the kernel and the IOP models are singletons).
 * Single host thread: everything runs on the thread that called init.
 */
#ifndef RG_RUNTIME_H
#define RG_RUNTIME_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rg_host;
struct gs_state;
struct dmac_state;
struct vu_state;
struct vif_state;

/* The game's entry: Main_15e700(argc, argv) once the game links (crt0.c). */
typedef int (*rg_game_entry_fn)(int argc, char **argv);

/* Maps the kernel VBlank count to the counter input scripts are keyed by
 * (the game's own VBlank counter [0x004810C4]; tools/trace/input.py). */
typedef uint32_t (*rg_game_vblank_fn)(void *user, uint64_t kernel_vblank);

typedef struct rg_runtime_config {
    /* ---- paths ---- */
    const char *data_dir;      /* extracted disc (MANIFEST.tsv); NULL -> $RG_DATA, else "data" */
    const char *saves_dir;     /* memory cards; NULL -> $RG_SAVES, else "saves" */
    int cdvd_model;            /* -1 (default): $RG_CDVD_MODEL, else 1.  1: also mount the
                                  CDVD sector model + drive (libcdvd callers: demo, tests).
                                  The game sets 0: its file layer reads data/ through the
                                  native file service (docs/NATIVE-FS.md), always mounted */

    /* ---- host ---- */
    int headless;              /* no window, no audio device, no live input */
    int throttle;              /* pace idle jumps to wall time (default 1; forced 0 headless) */
    int audio;                 /* open the audio device (default 1; ignored headless) */
    int present;               /* read the GS display out and present every field (default 1;
                                  headless: read-out only when hashing, see display_hash_every) */
    int scale;                 /* rg_scale_mode (default linear) */
    int fullscreen;
    const char *title;         /* window title (default "Rogue Galaxy") */
    const char *input_script;  /* tools/trace/input.py script file for port 0 (NULL = live) */
    rg_game_vblank_fn game_vblank; /* NULL: the kernel VBlank count (see docs/RUNTIME.md) */
    void *game_vblank_user;
    struct rg_settings *settings; /* optional (docs/SETTINGS.md): the host applies display,
                                  audio volume and input settings live and owns the
                                  settings overlay; must outlive the runtime */
    const char *settings_path; /* where the overlay's "Save" writes (NULL: no Save row) */

    /* ---- EE ---- */
    rg_game_entry_fn entry;    /* NULL -> rg_game_entry (weak; the game's Main) */
    int main_priority;         /* priority of guest thread 1 (default 1; Main_15e700 sets its own) */
    uint32_t vblank_start_line;/* default 240 */
    uint64_t stop_at_cycles;   /* kernel TIME_LIMIT (0 = none) */
    uint64_t stall_cycles;     /* kernel STALL detection (0 = never) */
    uint32_t kcall_cycles;     /* virtual cycles per kernel call (default 0) */
    size_t host_stack_size;    /* per guest thread (default 1 MiB) */

    /* ---- IOP ---- */
    uint64_t rpc_latency, sif_dma_setup, sif_dma_cycles_per_qword, iop_boot_latency; /* cycles */
    int start_analog;          /* pad powers up analog (default 0: digital, as hardware) */
    int pad_power_cycle;       /* 1: an unplugged pad comes back digital, as hardware.  Default
                                  0: once the game locked analog mode it stays 0x73 locked
                                  (padman keep_analog_lock), so the "analog required" pause
                                  never comes from a host device change (docs/INPUT.md) */

    /* ---- GS renderer (docs/GPU.md "Real game validation"; Windows/D3D11 builds) ---- */
    int gpu;                   /* -1 (default): $RG_GPU (hw | warp | 0); 0 software GS;
                                  1 GPU renderer on the hardware adapter; 2 on WARP */
    int gpu_scale;             /* internal resolution 1..8; 0 (default): $RG_GPU_SCALE, else 1 */

    /* ---- determinism / tests ---- */
    uint32_t display_hash_every; /* fold the display read-out into the run hash every N fields
                                    (0 = never; default 0) */
    int quiet;                 /* no informational stderr output */
    const char *timing_out;    /* timing record JSONL (docs/TIMING-LOCKSTEP.md); NULL -> $RG_TIMING.
                                  Read by rg_trace_apply_env (src/trace), not by the runtime */
} rg_runtime_config;

void rg_runtime_default_config(rg_runtime_config *cfg);
/* Copies the settings the runtime itself reads at init (system.throttle,
 * audio.enabled, display.window_mode -> fullscreen, display.scale) into cfg
 * and sets cfg->settings.  Ids that are not registered are left alone.
 * Window size, vsync and the rest are read by the host from cfg->settings. */
struct rg_settings;
void rg_runtime_config_from_settings(rg_runtime_config *cfg, struct rg_settings *s);

/* Init steps, in order (rg_runtime_init_order() lists the ones that ran). */
enum {
    RG_INIT_HOST = 1,      /* rg_host_create, input script, pacer */
    RG_INIT_KERNEL,        /* ps2k_init (+ violation hook default) */
    RG_INIT_GRAPHICS,      /* GS, VU1/VU0, VIF0/1, DMAC + sinks, sce_graphics_bind */
    RG_INIT_HWBUS,         /* hwbus_init + hwbus_bind (DMAC claimed before the kernel) */
    RG_INIT_CDVD,          /* rg_fs_mount(data) (native files, docs/NATIVE-FS.md); with
                              cfg.cdvd_model: sceCdHleMount(data), kernel device + wait hook */
    RG_INIT_CARDS,         /* mccard_init(saves), padman_reset, pad source + rumble */
    RG_INIT_IOP,           /* rg_sif_boot: SIF hooks, FILEIO/heap/LOADFILE + post-install:
                              padman, mcserv, sound (snd_install) */
    RG_INIT_OBSERVERS,     /* VBLANK_START/END observers, pacing hook */
    RG_INIT_GAME_RAM,      /* crt0: 32 MB game RAM block, heap bounds */
    RG_INIT_COUNT
};
const char *rg_runtime_init_step_name(int step);
/* The steps init ran, in order; returns the count (<= RG_INIT_COUNT - 1). */
int rg_runtime_init_order(int *out, int cap);

int rg_runtime_init(const rg_runtime_config *cfg); /* 0 ok, -1 (message on stderr) */
int rg_runtime_inited(void);

/* Run the EE until the next VBLANK_START has been processed (the kernel
 * yields at its first scheduler point after it), then the host half of the
 * field.  The first call starts the EE (rg_ps2_main on thread 1).
 * Returns 0 to keep going, or the kernel's PS2K_RUN_* stop code + 1
 * (main exited, stall, deadlock, time limit), or RG_RUN_QUIT. */
#define RG_RUN_QUIT 100
int rg_runtime_run_field(void);
/* run_field until it returns non-zero or `max_fields` fields ran (0 = no limit).
 * Returns the last run_field result (0 when the field limit ended it). */
int rg_runtime_run(uint64_t max_fields);
void rg_runtime_request_quit(void);
void rg_runtime_shutdown(void);

/* ---- per-field statistics (tests, the demo) ---- */
typedef struct rg_runtime_stats {
    uint64_t fields;            /* run_field calls that completed a field */
    uint64_t vblank_start, vblank_end;  /* observer calls */
    uint64_t audio_frames;      /* frames snd_output_read handed to the host */
    uint32_t audio_frames_last; /* in the last field */
    uint64_t audio_dropped;
    int32_t  audio_peak;        /* max |sample| pushed so far */
    uint64_t presents;
    uint64_t pad_reads;         /* padman input-source calls */
    uint64_t rumble_changes;
    uint64_t cdvd_polls, cdvd_completions, cdvd_waits;
    uint64_t run_hash;          /* FNV-1a: kernel trace hash, audio, pad words, display */
} rg_runtime_stats;
const rg_runtime_stats *rg_runtime_get_stats(void);
/* Read the GS display out now and write it as PNG (source resolution).
 * Also returns the FNV-1a of the RGBA pixels in *hash (may be NULL). 0 ok. */
int rg_runtime_screenshot(const char *path, uint64_t *hash, uint32_t *w, uint32_t *h);
/* The same read-out without a file: the pixels (RGBA8, valid until the next
 * field or read-out) or NULL.  Headless presented-aspect shots (docs/WIDESCREEN.md). */
const uint32_t *rg_runtime_read_display(uint32_t *w, uint32_t *h);

/* ---- access for tests, overrides and the other services ---- */
struct rg_host *rg_runtime_host(void);
struct gs_state *rg_runtime_gs(void);
struct dmac_state *rg_runtime_dmac(void);
struct vu_state *rg_runtime_vu1(void);
/* The GPU renderer drawing rg_runtime_gs() (src/gpu), or NULL when the
 * software GS rasterizes (the default) or the build has no GPU renderer.
 * Anyone reading gs->vram directly must gpu_sync() it first. */
struct gpu_renderer *rg_runtime_gpu(void);
const rg_runtime_config *rg_runtime_get_config(void);

/* ---- save states (docs/TEST-FIXTURES.md): the runtime's hook, registered by
 * src/savestate (rg_ss_hook "runtime").  Between fields only. */
int rg_runtime_ss_can_save(char *why, size_t cap);
size_t rg_runtime_ss_size(void);
void rg_runtime_ss_pre_save(void);
int rg_runtime_ss_save(void *buf, size_t cap);
void rg_runtime_ss_pre_load(void);
int rg_runtime_ss_load(const void *buf, size_t n);
void rg_runtime_ss_post_load(void);

/* ---- hooks left for services owned elsewhere ----
 * Overlay manager (src/ps2/overlay): installs hwbus_set_ovl_resolver itself;
 * the runtime calls this after init so it can bind (TODO when it lands).
 * Movie service (src/movie): IPU registers/FIFO via hwbus_set_ipu and the
 * fromIPU/toIPU DMAC channels (dmac_set_in/out on rg_runtime_dmac()). */
/* Up to 8 hooks; each runs once after init, in registration order (or at once
 * if the runtime is already up). */
typedef void (*rg_runtime_service_fn)(void *user);
void rg_runtime_set_service_hook(rg_runtime_service_fn after_init, void *user);

/* ======================================================================
 * crt0 equivalent (crt0.c, docs/RUNTIME.md "crt0")
 * ==================================================================== */

/* Retail layout (entry @0x00100008): BSS cleared [0x00481080, 0x00528200);
 * SetupThread(gp 0x00485170, stack 0x01FD0000, size 0x30000, args 0x00485280);
 * SetupHeap(0x00528200, -1) -> heap end = stack bottom 0x01FD0000;
 * InitSys; FlushCache(0); EI; Main_15e700(argc, argv); Exit(ret). */
#define RG_PS2_RAM_SIZE      0x02000000u
#define RG_PS2_BSS_START     0x00481080u
#define RG_PS2_BSS_END       0x00528200u  /* = heap start ("end") */
#define RG_PS2_GP            0x00485170u
#define RG_PS2_ARGS          0x00485280u
#define RG_PS2_STACK_BASE    0x01FD0000u  /* = EndOfHeap */
#define RG_PS2_STACK_SIZE    0x00030000u
#define RG_PS2_HEAP_START    RG_PS2_BSS_END
#define RG_PS2_HEAP_END      RG_PS2_STACK_BASE
#define RG_PS2_BOOT_PATH     "cdrom0:\\SCUS_974.90;1"

/* The game heap (docs/NATIVE-CPU.md section 8 "Memory map"): ONE ordinary host
 * allocation of the retail heap's size, not a 32 MB EE-RAM image.  Its start is
 * page + 0x200 (== RG_PS2_HEAP_START mod 4 KB), so the retail allocator (src/crt/crt_heap.c)
 * makes every page-rounding / trim decision as on the PS2 and the game's arena probe
 * (SysCalcFreeHeapMaybe: capacity) fits exactly as on retail.  Nothing else of the EE
 * address space exists: no block below the heap, no stack area above it. */
#define RG_PS2_HEAP_SIZE     (RG_PS2_HEAP_END - RG_PS2_HEAP_START)   /* 0x1AA7E00 */
/* bytes a heap provider (rg_crt0_set_ram_provider) must supply: the heap + one page of
 * slack for the page + 0x200 start */
#define RG_CRT0_HEAP_ALLOC   (RG_PS2_HEAP_SIZE + 0x1000u)

/* Placement rule kept ONLY for the oracle DMA path: DMA tags carry host pointers into the
 * heap, and the emulated path used to mask them to 28 bits (three render overrides, docs/
 * NATIVE-CPU.md section 6), so the heap had to end below 0x10000000 and not start inside the
 * PS2 RAM range.  The overrides keep the whole host pointer since 2026-10-18 and the native
 * frame walker reads tags whole (docs/NATIVE-RENDER.md "DMA addresses"): an RG_NATIVE_ONLY
 * build places the heap anywhere (RG_HEAP_DMA_PLACEMENT 0; crt0.c, the save-state region and
 * the runtime's warning follow it).  The oracle twin keeps the low placement. */
#ifndef RG_HEAP_DMA_PLACEMENT
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
#define RG_HEAP_DMA_PLACEMENT 0
#else
#define RG_HEAP_DMA_PLACEMENT 1
#endif
#endif
#define RG_HEAP_DMA_LO       0x04000000u   /* lowest start (above PS2 RAM + mirrors) */
#define RG_HEAP_DMA_HI       0x10000000u   /* the heap ends below this (28-bit masks) */

typedef struct rg_ps2_ram {
    uint8_t *heap_start;  /* host address of the heap start (retail RG_PS2_HEAP_START) */
    uint8_t *heap_end;    /* heap_start + RG_PS2_HEAP_SIZE (EndOfHeap) */
    uint8_t *brk;         /* current sbrk break */
} rg_ps2_ram;

int  rg_crt0_init(void);            /* allocate + zero the game heap (RG_INIT_GAME_RAM) */
/* Where rg_crt0_init takes the heap from (before init; NULL = its own allocation).
 * rg-game passes rg_ss_ram_alloc: the save-state region's fixed heap range
 * (docs/TEST-FIXTURES.md).  The provider returns committed memory of at least `size`
 * (= RG_CRT0_HEAP_ALLOC) bytes, or NULL to fall back. */
void rg_crt0_set_ram_provider(void *(*alloc)(size_t size));
void rg_crt0_shutdown(void);
const rg_ps2_ram *rg_crt0_ram(void);
/* The retail-address view, an explicit mapping (trace tools, RG_STATUS_DUMP, audits):
 * retail = host - heap_start + RG_PS2_HEAP_START for host in [heap_start, heap_end).
 * host_to_retail returns 0 outside the heap; retail_to_host returns NULL outside
 * [RG_PS2_HEAP_START, RG_PS2_HEAP_END). */
uint32_t rg_crt0_host_to_retail(const void *host);
void *rg_crt0_retail_to_host(uint32_t retail);
void *rg_crt0_sbrk(intptr_t incr);  /* newlib sbrk: old break, or (void *)-1 (errno ENOMEM) */
void *rg_crt0_end_of_heap(void);    /* EndOfHeap syscall 0x3E */
uint32_t rg_crt0_heap_size(void);   /* heap_end - heap_start (RG_PS2_HEAP_SIZE) */
/* Run a static-constructor table [begin, end) of 32-bit function pointers
 * (RunStaticCtors_100df0's loop; retail then calls EhRegisterFragment, a stub). */
void rg_crt0_run_ctors(const void *begin, const void *end);
/* atexit list run by rg_ps2_exit before the main thread exits (LIFO). */
int  rg_crt0_atexit(void (*fn)(void));

/* Guest thread 1's body: the crt0 sequence above, host-side.  Calls
 * cfg.entry or rg_game_entry(argc, argv), then rg_ps2_exit(ret). */
void rg_ps2_main(void *unused);
void rg_ps2_exit(int code);         /* atexit handlers, then ExitThread */
int  rg_ps2_exit_code(void);
/* Default game entry: a WEAK symbol.  The game build defines a strong
 * rg_game_entry that calls Main_15e700.  The default prints once and returns
 * RG_GAME_NOT_LINKED. */
#define RG_GAME_NOT_LINKED (-0x6E6C)
int rg_game_entry(int argc, char **argv);

#ifdef __cplusplus
}
#endif
#endif

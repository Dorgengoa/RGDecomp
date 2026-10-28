/* SPDX-License-Identifier: CC0-1.0 */
/* The native GS state block and GIF input (docs/NATIVE-RENDER.md "Checkpoint 10"): what an
 * RG_NATIVE_ONLY rg-game keeps of the GS, without a GS model.
 *
 *   nr_gs        the register words in force (render state the native draws read), the
 *                CLUT cells the CPU knows, the privileged registers (PCRTC display set-up,
 *                CSR events, IMR, SIGLBLID) and a transfer's progress.  Plain data, no
 *                pointers: the runtime allocates it in the state heap, a save state carries it.
 *   GIF input    (EE thread) nr_gs_gif: every GIF stream of the native side (frame walker
 *                DIRECT payloads, GIF channel sends, VU1 kicks) as immediate records (nr_im.h)
 *                queued to the worker in order; IMAGE data as worker calls with the bytes;
 *                SIGNAL / FINISH / LABEL raised here (CSR, interrupt), not on the worker.
 *   worker       (nr_q.c) the thread that runs the records and the device: calls in order,
 *                nothing else (no GIF parser, no local memory).
 *   registers    (worker) nr_gs_write_reg: the state block plus the side effects the native
 *                pipeline needs: CLUT loads (TEX0 / TEX2 CLD) and transfers (TRXDIR) by the
 *                device (nr_dev.h), the marker handler (GS_NATIVE_MARK). */
#ifndef RG_NR_GS_H
#define RG_NR_GS_H

#include <stdint.h>
#include <stdio.h>

#include "gs.h"   /* register addresses, PSMs, gs_vertex, gs_mem_rect (types and constants only) */

#ifdef __cplusplus
extern "C" {
#endif

struct gpu_renderer;

typedef struct nr_gs_stats {
    uint64_t clut_loads;        /* CLUT loads made (TEX0 / TEX2 CLD) */
    uint64_t xfers, xfer_bytes; /* host->local transfers completed, their bytes */
    uint64_t l2l, l2h;          /* local->local copies, local->host transfers met in the stream (ignored) */
    uint64_t image_qw, hwreg;   /* IMAGE qwords and HWREG writes received */
    uint64_t resets;            /* CSR.RESET */
    uint64_t unknown_reg_writes;
} nr_gs_stats;

typedef struct nr_gs {
    uint64_t reg[128];          /* general registers by address (0x7E: the last marker) */
    uint64_t preg[32];          /* privileged: [0..15] 0x12000000 + 16 i, [16..31] 0x12001000 + 16 i */
    uint32_t csr_events;        /* CSR bits 0-4 */
    uint32_t csr_field;
    uint16_t clut[512];         /* CLUT cells (CT32: low halves 0-255, high 256-511); the device
                                   owns the cells a GPU-side load wrote (gpu_clut_own) */
    uint32_t cbp0, cbp1;        /* CLD 4 / 5 comparison */
    gs_vertex vq[3];            /* vertex queue of generated primitives (nr_scene.c) */
    int vq_n, strip_n;
    /* the transfer TRXDIR started: 0 host->local (waiting for IMAGE data), -1 none */
    int xfer_dir;
    gs_mem_rect xfer_rc;
    uint32_t xfer_px;           /* pixels received */
    nr_gs_stats stats;
} nr_gs;

/* ---- the state (worker thread, or any thread while the worker is drained) ---- */
void nr_gs_init(nr_gs *gs);     /* power-on: registers, CLUT, privileged registers */
void nr_gs_reset(nr_gs *gs);    /* CSR.RESET: general registers, CLUT, transfer (privileged kept) */
void nr_gs_write_reg(nr_gs *gs, uint32_t addr, uint64_t data);
/* a TEX0 / TEX2 write would change the CLUT cells or reload them on the GPU (the immediate
 * executor flushes its batch first) */
int nr_gs_clut_would_change(nr_gs *gs, uint32_t addr, uint64_t data);
/* IMAGE data of nqw qwords for the transfer in progress */
void nr_gs_image(nr_gs *gs, const void *qw, uint32_t nqw);

/* the device and the native mesh handler the register writes reach */
typedef void (*nr_gs_marker_fn)(void *user, struct gpu_renderer *gr, nr_gs *gs, uint64_t value);
void nr_gs_bind(nr_gs *gs, struct gpu_renderer *gr);
void nr_gs_set_marker(nr_gs_marker_fn fn, void *user);
nr_gs *nr_gs_state(void);
struct gpu_renderer *nr_gs_device(void);

/* ---- GIF input (EE thread) ---- */
void nr_gs_gif(int path, const void *qw, uint32_t nqw);
/* the sink signatures of the walker (nr_fx_sink) and the VU1 consumer */
void nr_gs_gif_path2(void *user, const uint8_t *d, uint32_t bytes);
void nr_gs_gif_path1(void *user, const uint8_t *d, uint32_t bytes);
void nr_gs_gif_path3(const void *qw, uint32_t nqw);
void nr_gs_gif_reset(void);     /* GIF_CTRL.RST: open packets dropped */
int nr_gs_path_idle(int path);  /* no packet open on the path */
void nr_gs_gif_stats(FILE *f);

/* ---- the worker (nr_q.c): calls in order on one thread ---- */
typedef void (*nr_q_fn)(void *user, const void *data);
int nr_q_start(void);
void nr_q_stop(void);
void nr_q_drain(void);
int nr_q_on(void);
/* fn(user, copy of data) after everything queued so far (without the worker: at once) */
void nr_q_call(nr_q_fn fn, void *user, const void *data, uint32_t bytes);
/* the same with the data in two pieces (a header and a payload), copied once */
void nr_q_call2(nr_q_fn fn, void *user, const void *a, uint32_t abytes, const void *b, uint32_t bbytes);
uint64_t nr_q_mark(void);
void nr_q_wait_mark(uint64_t mark);
/* entries, payload bytes, drains that waited, 0 */
void nr_q_stats(uint64_t out[4]);
double nr_q_wait_ms(void);

/* ---- privileged registers (nr_hw.c; EE thread) ---- */
void nr_hw_bind_gs(nr_gs *gs, void (*irq)(void *user, uint32_t csr_bits), void *irq_user);
void nr_hw_gs_event(uint32_t addr, uint64_t data);   /* SIGNAL / FINISH / LABEL from the GIF input */
void nr_hw_vsync(void);                              /* VBlank start: CSR.FIELD, VSINT */
const uint64_t *nr_hw_display_regs(void);            /* the PCRTC registers (preg) */

#ifdef __cplusplus
}
#endif
#endif

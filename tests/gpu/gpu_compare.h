/* SPDX-License-Identifier: CC0-1.0 */
/* SW reference vs GPU renderer: local memory and display comparison with a
 * per-channel tolerance, and the statistics the tests report.  docs/GPU.md
 * "Validation". */
#ifndef RG_GPU_COMPARE_H
#define RG_GPU_COMPARE_H

#include <stdint.h>

#include "gpu.h"
#include "gs.h"

typedef struct cmp_stats {
    int checkpoints;
    uint64_t px;          /* render-target pixels compared (decoded per PSM) */
    uint64_t px_exact;
    uint64_t px_bad;      /* beyond tolerance */
    int max_diff;         /* largest channel difference (8-bit units; Z: raw) */
    uint64_t raw_bad;     /* local-memory bytes outside render targets that differ */
    uint64_t fifo_bytes, fifo_bad;  /* local->host data */
    uint64_t disp_px, disp_exact, disp_bad;
    int disp_max;
    uint64_t px_excused;  /* differences explained by a known reference artifact */
} cmp_stats;

extern cmp_stats g_cmp;
extern int g_cmp_tol;      /* colour tolerance in 8-bit units (0 = exact) */
/* Pixels beyond tolerance allowed per million compared target pixels: 0 for
 * exact scenes, 50 for interpolated ones (docs/GPU.md "Validation"). */
extern int g_cmp_ppm;
extern int g_cmp_disp_ppm;  /* display pixels beyond tol allowed, per million */
/* Optional: returns 1 when a difference at (x,y) is a known artifact of the
 * reference (counted as excused, reported, not failed). */
extern int (*g_cmp_excuse)(int psm, uint32_t x, uint32_t y);

/* Compare sw->vram with hw->vram (call gpu_sync(r) first).  Render-target
 * regions reported by gpu_targets() are decoded and compared per channel /
 * Z value with the tolerance; every other byte must be identical. */
void cmp_vram(const gs_state *sw, const gs_state *hw, gpu_renderer *r, const char *where);
/* Compare two RGBA8 frames. */
void cmp_frame(const uint32_t *a, const uint32_t *b, uint32_t w, uint32_t h, const char *where);
void cmp_fifo(const uint8_t *a, const uint8_t *b, uint32_t n, const char *where);
void cmp_reset(void);
/* Print the summary; returns 0 when everything is within tolerance. */
int cmp_report(const char *name);

#endif

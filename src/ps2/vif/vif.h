/* SPDX-License-Identifier: CC0-1.0 */
/* VIF0/VIF1 command processor (docs/VU.md).
 *
 * vif_write() takes the VIF word stream exactly as the DMA controller would
 * hand it over (the DMAtag's upper 64 bits when TTE is set, then the packet
 * qwords), may be called with any split of that stream, and drives the
 * attached VU: UNPACK/STROW/STCOL/STMASK/STCYCL/STMOD into VU data memory,
 * MPG into VU code memory, MSCAL/MSCALF/MSCNT run the VU program to completion
 * synchronously, DIRECT/DIRECTHL go to the PATH2 GIF sink.  XGKICK output goes
 * to the VU's own PATH1 sink (vu->gif_sink).
 */
#ifndef RG_PS2_VIF_H
#define RG_PS2_VIF_H

#include <stddef.h>
#include <stdint.h>

#include "vu.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    VIF_NOP = 0x00, VIF_STCYCL = 0x01, VIF_OFFSET = 0x02, VIF_BASE = 0x03,
    VIF_ITOP = 0x04, VIF_STMOD = 0x05, VIF_MSKPATH3 = 0x06, VIF_MARK = 0x07,
    VIF_FLUSHE = 0x10, VIF_FLUSH = 0x11, VIF_FLUSHA = 0x13,
    VIF_MSCAL = 0x14, VIF_MSCALF = 0x15, VIF_MSCNT = 0x17,
    VIF_STMASK = 0x20, VIF_STROW = 0x30, VIF_STCOL = 0x31,
    VIF_MPG = 0x4A, VIF_DIRECT = 0x50, VIF_DIRECTHL = 0x51,
    VIF_UNPACK = 0x60 /* 0x60..0x7F */
};

/* GIF output (PATH2: DIRECT/DIRECTHL); bytes is a multiple of 16 */
typedef void (*vif_gif_sink_fn)(void *user, const uint8_t *data, uint32_t bytes);
/* observation hook for MPG uploads (census, tests); code already loaded */
typedef void (*vif_mpg_hook_fn)(void *user, uint32_t vu_addr, const uint8_t *code, uint32_t bytes);
/* the i bit of a VIF code fired (after that command completed) */
typedef void (*vif_irq_fn)(void *user, uint32_t code);

typedef struct vif_stats {
    uint64_t cmds[128];
    uint64_t unpack_qwords;
    uint64_t mscal, mpg_bytes, direct_bytes;
    uint64_t invalid_cmds;
    uint64_t vu_runaways;   /* MSCAL whose program hit the cycle budget */
} vif_stats;

typedef struct vif_state {
    int id;                    /* 0 = VIF0, 1 = VIF1 */
    vu_state *vu;

    /* registers */
    uint32_t cl, wl, mode, mask;
    uint32_t row[4], col[4];
    uint32_t mark, code, num;
    uint32_t base, ofst, tops, itops, top, itop, dbf;
    int mskpath3;
    int irq;                   /* an i-bit command has completed */

    /* command in progress */
    int have_cmd;
    uint32_t need;             /* payload words still to collect */
    uint32_t got;
    uint32_t *buf;             /* payload buffer */
    uint32_t cap;

    /* V3 W lane (docs/VU.md "V3 W lane"): the stream words that follow the
     * command being executed, when this vif_write call already holds them,
     * and the W lanes of the last element still waiting for the next stream
     * word when it did not (written as soon as that word arrives). */
    const uint32_t *ahead;
    size_t ahead_n;
    int wpend;                 /* 1: W lanes below wait for the next word */
    uint32_t wpend_qa, wpend_n, wpend_cyc; /* first qword, count, its cycle */
    uint32_t wpend_vl, wpend_usn, wpend_masked;

    /* configuration */
    uint64_t vu_cycle_budget;  /* per MSCAL; default 1,000,000 */
    int stall_on_irq;          /* return from vif_write after an i-bit command */
    vif_gif_sink_fn gif_sink; void *gif_user;
    vif_mpg_hook_fn mpg_hook;  void *mpg_user;
    vif_irq_fn irq_fn;         void *irq_user;

    vif_stats stats;
    char error[96];
} vif_state;

void vif_init(vif_state *v, int id, vu_state *vu);
void vif_free(vif_state *v);
void vif_reset(vif_state *v);
/* Feed nwords stream words; returns the number consumed (== nwords unless
 * stall_on_irq stopped it; clear v->irq and call again with the rest). */
size_t vif_write(vif_state *v, const uint32_t *words, size_t nwords);
/* 1 if no command is partially received */
int vif_idle(const vif_state *v);
/* microprogram census (measurement, docs/PERF-3D.md): count every MSCAL /
 * MSCNT by program from begin to dump (TSV) */
void vif_census_begin(void);
int vif_census_dump(const char *path);

/* Number of 32-bit payload words that follow VIF code `code`, given the
 * current CL/WL (used by stream walkers); -1 for an invalid command. */
long vif_payload_words(uint32_t code, uint32_t cl, uint32_t wl);

#ifdef __cplusplus
}
#endif
#endif

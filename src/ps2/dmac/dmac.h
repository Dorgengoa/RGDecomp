/* SPDX-License-Identifier: CC0-1.0 */
/* EE DMA controller model (docs/DMAC.md).
 *
 * Written from public descriptions of the EE DMAC (the EE User's Manual's
 * register and DMAtag semantics) and the game's own libdma call sites.  No
 * emulator code was used (PLAN.md D7).
 *
 * TIMING MODEL: a transfer runs to completion (or to a hold, below) inside the
 * call that starts it -- sceDmaSend, a CHCR write with STR=1 through
 * dmac_hw_write32, a FIFO write that releases a held channel.  When that call
 * returns, CHCR.STR already reads 0, every byte has reached the peripheral
 * (VIF -> VU -> GS, GIF -> GS) and D_STAT.CIS is latched in the kernel.  The
 * transfer is then charged to the virtual clock: ps2k_charge(qwords *
 * cycles_per_qword) in thread context, which is also a kernel delivery point,
 * so a DMAC/VIF handler runs at "kick time + cost".  Nothing is asynchronous.
 *
 * A channel is HELD (STR stays 1, nothing moves) only while:
 *   - D_CTRL.DMAE = 0 or D_ENABLEW.CPND = 1 (DMA suspended),
 *   - it is GIF and VIF1 has PATH3 masked (VIF MSKPATH3) -- it resumes the
 *     moment a VIF1 transfer, a VIF1 FIFO write or a VIF1 reset clears it,
 *   - it reads from a peripheral (VIF1 readback, fromIPU, SIF0, SIF2) whose
 *     source callback has no data yet -- dmac_service() resumes it.
 *
 * ADDRESSES (see DMAC.md "Address mapping"): a 32-bit DMA address with bit 31
 * set is a scratchpad address (offset & 0x3FF0).  Otherwise it is resolved by
 * the memory mode:
 *   DMAC_MEM_HOST  (default; the i686 game build) the address IS the host
 *                  pointer.  Mirror bits are NOT stripped: host pointers use
 *                  them.  Addresses below 64 KB are bus errors.
 *   DMAC_MEM_GUEST (tests, replays of PS2 captures) EE physical address into a
 *                  caller-provided RAM block: 0x2000_0000/0x3000_0000 mirrors
 *                  are stripped, 0x7xxx_xxxx is scratchpad.
 */
#ifndef RG_PS2_DMAC_H
#define RG_PS2_DMAC_H

#include <stddef.h>
#include <stdint.h>

#include "gs.h"
#include "vif.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    DMAC_VIF0 = 0, DMAC_VIF1, DMAC_GIF, DMAC_FROM_IPU, DMAC_TO_IPU,
    DMAC_SIF0, DMAC_SIF1, DMAC_SIF2, DMAC_FROM_SPR, DMAC_TO_SPR,
    DMAC_NCH
};

#define DMAC_SPR_BYTES 16384u

/* CHCR bits */
#define DMAC_CHCR_DIR  0x001u
#define DMAC_CHCR_MOD  0x00Cu   /* 0 normal, 1 chain, 2 interleave */
#define DMAC_CHCR_ASP  0x030u
#define DMAC_CHCR_TTE  0x040u
#define DMAC_CHCR_TIE  0x080u
#define DMAC_CHCR_STR  0x100u

/* DMAtag ids (source chain) */
enum {
    DMAC_TAG_REFE = 0, DMAC_TAG_CNT, DMAC_TAG_NEXT, DMAC_TAG_REF,
    DMAC_TAG_REFS, DMAC_TAG_CALL, DMAC_TAG_RET, DMAC_TAG_END
};
/* destination chain ids */
enum { DMAC_DTAG_CNTS = 0, DMAC_DTAG_CNT = 1, DMAC_DTAG_END = 7 };

/* EE register addresses */
#define DMAC_D_CTRL    0x1000E000u
#define DMAC_D_STAT    0x1000E010u
#define DMAC_D_PCR     0x1000E020u
#define DMAC_D_SQWC    0x1000E030u
#define DMAC_D_RBSR    0x1000E040u
#define DMAC_D_RBOR    0x1000E050u
#define DMAC_D_STADR   0x1000E060u
#define DMAC_D_ENABLER 0x1000F520u
#define DMAC_D_ENABLEW 0x1000F590u
#define DMAC_VIF0_FIFO 0x10004000u
#define DMAC_VIF1_FIFO 0x10005000u
#define DMAC_GIF_FIFO  0x10006000u

/* One channel's register block, laid out exactly like the EE's (and the
 * SDK's sceDmaChan): one 32-bit register per 16 bytes.  The game reads and
 * writes these fields through the pointer sceDmaGetChan returns. */
typedef struct dmac_chan_regs {
    uint32_t chcr, _p0[3];
    uint32_t madr, _p1[3];
    uint32_t qwc, _p2[3];
    uint32_t tadr, _p3[3];
    uint32_t asr0, _p4[3];
    uint32_t asr1, _p5[3];
    uint32_t _p6[4], _p7[4];
    uint32_t sadr, _p8[3];
} dmac_chan_regs;

/* Peripheral bindings.
 * out: memory -> peripheral data, in transfer order.  flags & DMAC_OUT_TAG:
 *      the 8 bytes are the upper half of a DMAtag (CHCR.TTE).
 * in:  peripheral -> memory; fill up to `bytes` (a multiple of 16), return
 *      the bytes produced (a multiple of 16).  Returning less holds the
 *      channel until dmac_service(). */
#define DMAC_OUT_TAG 1u
typedef void (*dmac_out_fn)(void *user, int ch, const uint8_t *data, uint32_t bytes, uint32_t flags);
typedef uint32_t (*dmac_in_fn)(void *user, int ch, uint8_t *dst, uint32_t bytes);
/* a to-memory channel was started (SIF0/SIF2/fromIPU): the peripheral may
 * now produce data, synchronously from inside this call or later through
 * dmac_service(). */
typedef void (*dmac_start_fn)(void *user, int ch);

typedef struct dmac_chan_stats {
    uint64_t kicks, completions, qwords, tags, holds, irq_stops;
    uint64_t tte_ignored;     /* TTE set on a channel that does not transfer tags */
    uint64_t unbound_qwords;  /* out data with no peripheral bound (dropped) */
} dmac_chan_stats;

typedef struct dmac_chan_state {   /* internal, per channel */
    int chain_end;     /* the last tag ends the transfer once its data moved */
    int pending;       /* STR=1 and not finished */
    int running;       /* inside run_channel: a peripheral callback that calls
                          dmac_service() must not re-enter this channel */
} dmac_chan_state;

typedef struct dmac_state {
    dmac_chan_regs ch[DMAC_NCH];
    uint32_t ctrl, pcr, sqwc, rbsr, rbor, stadr, enable;
    /* D_STAT bits the kernel does not model: SIS/MEIS/BEIS (13-15), SIM/MEIM (29-30);
     * plus CIS/CIM when not bound to the kernel */
    uint32_t stat_local, mask_local;
    uint8_t spr[DMAC_SPR_BYTES] __attribute__((aligned(16)));

    /* memory */
    int mem_mode;              /* DMAC_MEM_HOST / DMAC_MEM_GUEST */
    uint8_t *ram;              /* guest mode: EE physical 0.. */
    uint32_t ram_size;

    /* peripherals */
    vif_state *vif[2];
    gs_state *gs;
    dmac_out_fn out[DMAC_NCH]; void *out_user[DMAC_NCH];
    dmac_in_fn in[DMAC_NCH];   void *in_user[DMAC_NCH];
    dmac_start_fn start[DMAC_NCH]; void *start_user[DMAC_NCH];

    /* configuration */
    int kernel;                /* 1: CIS/CIM, interrupts and time go through ps2k (default) */
    uint32_t cycles_per_qword; /* virtual cost per qword moved, incl. tags (default 1) */
    uint64_t max_tags;         /* runaway guard per kick (default 1<<24); LOUD when hit */
    int debug_ret_ends_chain;  /* DELIBERATELY WRONG (test control): RET ignores ASP */

    /* state */
    dmac_chan_state cs[DMAC_NCH];
    int depth;                 /* run_pending nesting */
    uint64_t cost;             /* qwords moved by the outermost call, not yet charged */
    dmac_chan_stats stats[DMAC_NCH];
    uint64_t uncharged_cycles; /* cost incurred outside thread context (not charged) */
    uint32_t vif_irq_deferred; /* VIF i-bit INTCs raised during a kick (bit 0 VIF0, 1 VIF1),
                                  posted after the kick (DMAC.md "VIF interrupts") */
    uint64_t bus_errors;
    char error[160];           /* last error, for reports */
} dmac_state;

enum { DMAC_MEM_HOST = 0, DMAC_MEM_GUEST = 1 };

/* ---- lifetime / wiring ---- */
dmac_state *dmac_create(void);           /* host memory mode, bound to the kernel */
void dmac_destroy(dmac_state *d);
void dmac_reset(dmac_state *d);          /* registers + internal state; keeps bindings and SPR */
/* guest memory mode: EE physical addresses index `ram` (size bytes) */
void dmac_map_guest_ram(dmac_state *d, uint8_t *ram, uint32_t size);
/* VIF0/VIF1 (out; VIF1 also its readback in), raises INTC VIF0/VIF1 on the
 * VIF i bit (overwrites vif->irq_fn). */
void dmac_attach_vif(dmac_state *d, int which, vif_state *vif);
/* GIF out (PATH3) and the VIF1 readback source (gs_read_fifo).  If gs->irq
 * is unset it raises INTC GS. */
void dmac_attach_gs(dmac_state *d, gs_state *gs);
void dmac_set_out(dmac_state *d, int ch, dmac_out_fn fn, void *user);
void dmac_set_in(dmac_state *d, int ch, dmac_in_fn fn, void *user);
void dmac_set_start(dmac_state *d, int ch, dmac_start_fn fn, void *user);

/* ---- channels ---- */
dmac_chan_regs *dmac_chan(dmac_state *d, int ch);
int dmac_chan_index(const dmac_state *d, const void *regs); /* -1 if not a channel block */
/* Start channel `ch` with the CHCR value already in its registers (STR must
 * be set).  Returns 1 if it finished, 0 if it is held. */
int dmac_kick(dmac_state *d, int ch);
/* Retry held channels (after a peripheral produced data, or anything else). */
void dmac_service(dmac_state *d);
int dmac_busy(const dmac_state *d, int ch); /* CHCR.STR */
/* A CHCR store as the EE does it: STR 0->1 kicks, STR 1->0 suspends; the
 * TAG bits (31:16) are read-only. */
void dmac_write_chcr(dmac_state *d, int ch, uint32_t value);

/* ---- memory ---- */
/* Host pointer for `bytes` bytes at DMA address `addr` (SPR bit 31), or NULL
 * (bus error).  A scratchpad range that wraps returns NULL. */
uint8_t *dmac_mem(dmac_state *d, uint32_t addr, uint32_t bytes);
/* The DMA address of a host pointer (host mode: the pointer, with SPR
 * pointers turned into 0x8000_0000|offset; guest mode: the RAM offset). */
uint32_t dmac_addr_of(const dmac_state *d, const void *p);
/* libdma's DmaAddrFromSpr on an address argument: guest mode converts
 * 0x7xxx_xxxx to SPR; host mode converts a pointer into d->spr. */
uint32_t dmac_canon_addr(const dmac_state *d, uint32_t addr);

/* ---- registers (the HW_* accessor for 0x10008000..0x1000E06F, D_ENABLER/W) ---- */
int dmac_hw_claims(uint32_t addr);
uint32_t dmac_hw_read32(dmac_state *d, uint32_t addr);
void dmac_hw_write32(dmac_state *d, uint32_t addr, uint32_t value);

/* ---- FIFO windows (the HW_* accessor for 128-bit FIFO stores/loads) ---- */
void dmac_vif_fifo_write(dmac_state *d, int which, const void *qwords, uint32_t nqw);
void dmac_gif_fifo_write(dmac_state *d, const void *qwords, uint32_t nqw);
/* VIF1 FIFO read (GS -> EE readback while VIF1_STAT.FDR is set); bytes read */
uint32_t dmac_vif1_fifo_read(dmac_state *d, void *dst, uint32_t nqw);
/* VIF FBRST.RST: reset the VIF (clears MSKPATH3) and release a held GIF */
void dmac_vif_reset(dmac_state *d, int which);

#ifdef __cplusplus
}
#endif
#endif

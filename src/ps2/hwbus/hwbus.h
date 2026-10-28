/* SPDX-License-Identifier: CC0-1.0 */
/* EE hardware register bus (docs/HWBUS.md, PLAN.md transform 5).
 *
 * Every EE hardware access the game makes by literal address (the
 * address-literal stage rewrites `*(volatile T *)0x1000xxxx` into HW_R32 /
 * HW_W32 ..., include/port/hwaccess.h) lands here and is routed to the model
 * that owns the register, through that model's public API:
 *
 *   0x10000000-0x10001FFF  T0..T3                  ps2k_hw_read32/write32
 *   0x10002000-0x1000203F  IPU_CMD/CTRL/BP/TOP     IPU hook, else a stub
 *   0x10003000-0x100030AF  GIF_CTRL/MODE/STAT/...  local (GIF_STAT synthesised)
 *   0x10003800-0x1000397F  VIF0 registers          vif_state (dmac->vif[0])
 *   0x10003C00-0x10003D7F  VIF1 registers          vif_state; FBRST.RST -> dmac_vif_reset
 *   0x10004000/0x10005000  VIF0/VIF1 FIFO (128)    dmac_vif_fifo_write / dmac_vif1_fifo_read
 *   0x10006000             GIF FIFO (128)          dmac_gif_fifo_write
 *   0x10007000/0x10007010  IPU out/in FIFO (128)   IPU hook, else a stub
 *   0x10008000-0x1000E06F  DMAC channels, D_*      dmac_hw_read32/write32
 *   0x1000F000/0x1000F010  INTC_STAT/INTC_MASK     ps2k_hw_read32/write32
 *   0x1000F200-0x1000F260  SIF MSCOM..BD6          sif_reg_get/sif_reg_set
 *   0x1000F520/0x1000F590  D_ENABLER/D_ENABLEW     dmac_hw_read32/write32
 *   0x12000000-0x120010FF  GS privileged           gs_read_priv/gs_write_priv
 *
 * D_STAT (0x1000E010) is claimed by both the DMAC and the kernel: the DMAC
 * is asked FIRST (it forwards the kernel's CIS/CIM part), as DMAC.md requires.
 *
 * Anything else is UNKNOWN: reads return 0, writes are dropped, and the
 * address is logged once and recorded (hwbus_unknown_*), never silently.
 *
 * SPIN BACKSTOP (docs/SPIN.md "(a) accessor charge"): every READ charges
 * `read_cycles` (default 4) virtual cycles through ps2k_charge, when called
 * from a guest thread outside a handler (otherwise the cycles are counted as
 * uncharged, as the DMAC does).  A hardware poll loop therefore always lets
 * virtual time pass and delivers due interrupts.  Writes charge nothing.
 *
 * Single host thread, like every ps2/ model.  Nothing here locks.
 */
#ifndef RG_PS2_HWBUS_H
#define RG_PS2_HWBUS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct dmac_state;
struct gs_state;

/* ---- owners (claims table) ---- */
enum {
    HWBUS_UNKNOWN = 0,
    HWBUS_KERNEL,   /* timers, INTC (and D_STAT through the DMAC) */
    HWBUS_DMAC,     /* channel registers, D_CTRL..D_STADR, D_ENABLER/W */
    HWBUS_FIFO,     /* VIF0/VIF1/GIF FIFO windows (through the DMAC) */
    HWBUS_VIF,      /* VIF0/VIF1 registers */
    HWBUS_GIF,      /* GIF registers */
    HWBUS_IPU,      /* IPU registers and FIFOs */
    HWBUS_SIF,      /* SIF registers */
    HWBUS_GS,       /* GS privileged registers */
    HWBUS_NOWNERS
};

typedef struct hwbus_region {
    uint32_t lo, hi;      /* inclusive */
    int owner;            /* HWBUS_* */
    const char *name;
} hwbus_region;

/* the static claims table (sorted, non-overlapping), terminated by {0,0,0,0} */
const hwbus_region *hwbus_regions(void);
/* owner of `addr` per the claims table and the owning model's own claim
 * (dmac_hw_claims / ps2k_hw_claims / the register map); HWBUS_UNKNOWN if none */
int hwbus_claims(uint32_t addr);
const char *hwbus_owner_name(int owner);

/* ---- configuration / binding ---- */
typedef void (*hwbus_charge_fn)(void *user, uint64_t cycles);
typedef void (*hwbus_log_fn)(void *user, const char *line);

/* IPU service (the movie layer).  read/write get 32- or 64-bit register
 * accesses (`bits`), fifo gets 128-bit FIFO accesses.  Without a hook the
 * bus keeps a register stub: IPU_CTRL.BUSY / IPU_CMD.BUSY read 0, RST
 * clears the stub, FIFO reads return zero and writes are counted. */
typedef struct hwbus_ipu_hooks {
    uint64_t (*read)(void *user, uint32_t addr, int bits);
    void (*write)(void *user, uint32_t addr, uint64_t value, int bits);
    void (*fifo_write)(void *user, const void *qword);
    void (*fifo_read)(void *user, void *qword);
    void *user;
} hwbus_ipu_hooks;

typedef struct hwbus_stats {
    uint64_t reads[HWBUS_NOWNERS], writes[HWBUS_NOWNERS];
    uint64_t charged_cycles, uncharged_cycles;
    uint64_t ipu_stub_accesses;   /* IPU accesses served by the stub */
    uint64_t ignored_writes;      /* writes to read-only registers of a known owner */
    uint64_t unbound;             /* known owner, model not bound (dropped) */
} hwbus_stats;

/* Reset bindings, stats, unknown records and configuration to defaults. */
void hwbus_init(void);
/* The DMAC instance (its VIFs come from d->vif[], its GS from d->gs unless
 * `gs` is given).  Either may be NULL. */
void hwbus_bind(struct dmac_state *d, struct gs_state *gs);
void hwbus_set_ipu(const hwbus_ipu_hooks *h); /* NULL: back to the stub */
/* cycles charged per read (default HWBUS_DEFAULT_READ_CYCLES; 0 = off) */
#define HWBUS_DEFAULT_READ_CYCLES 4u
void hwbus_set_read_cycles(uint32_t cycles);
uint32_t hwbus_read_cycles(void);
/* Replace the charge (default: ps2k_charge in guest-thread context).  The
 * hook is called for every read with read_cycles != 0, unconditionally. */
void hwbus_set_charge(hwbus_charge_fn fn, void *user);
/* Log sink for the once-per-address unknown reports (default: stderr). */
void hwbus_set_log(hwbus_log_fn fn, void *user);
const hwbus_stats *hwbus_get_stats(void);

/* ---- unknown addresses ---- */
#define HWBUS_MAX_UNKNOWN 256
typedef struct hwbus_unknown_rec {
    uint32_t addr;
    uint32_t reads, writes;
    int bits;            /* width of the first access */
    uint64_t last_write; /* last value written */
} hwbus_unknown_rec;
int hwbus_unknown_count(void);
const hwbus_unknown_rec *hwbus_unknown_get(int i);
uint64_t hwbus_unknown_total(void); /* accesses, including ones past the table */

/* ---- accessors (what HW_R32 / HW_W32 ... call) ---- */
uint8_t  hw_r8(uint32_t addr);
uint16_t hw_r16(uint32_t addr);
uint32_t hw_r32(uint32_t addr);
uint64_t hw_r64(uint32_t addr);
void     hw_r128(uint32_t addr, void *out16);
void hw_w8(uint32_t addr, uint8_t v);
void hw_w16(uint32_t addr, uint16_t v);
void hw_w32(uint32_t addr, uint32_t v);
void hw_w64(uint32_t addr, uint64_t v);
void hw_w128(uint32_t addr, const void *in16);

/* ---- scratchpad (PS2_SPR) ---- */
/* The bound DMAC's 16 KB scratchpad (dmac->spr), so pointers the game makes
 * with PS2_SPR() are what dmac_canon_addr recognises.  Unbound: a private
 * 16 KB block (reported once). */
uint8_t *hw_spr_base(void);

/* ---- overlay data by literal address (RG_OVL_DATA) ---- */
/* Resolver installed by the overlay manager: host address of overlay `ovl`'s
 * symbol `sym` (retail address sym_addr) while that overlay is resident, or
 * NULL when it is not. */
typedef void *(*hwbus_ovl_resolver_fn)(void *user, const char *ovl, const char *sym,
                                       uint32_t sym_addr);
void hwbus_set_ovl_resolver(hwbus_ovl_resolver_fn fn, void *user);
/* What RG_OVL_DATA calls.  Unresolved (no resolver, or the overlay is not
 * resident): a zeroed per-call scratch slot, reported once per symbol;
 * retail would read/write whatever the resident overlay keeps there. */
void *rg_ovl_data_ptr(const char *ovl, const char *sym, uint32_t sym_addr, uint32_t off);
uint64_t hwbus_ovl_unresolved(void);

/* DELIBERATELY WRONG (test control only): ask the kernel before the DMAC
 * for addresses both claim (D_STAT), dropping the DMAC's SIS/MEIS/BEIS and
 * SIM/MEIM bits.  tests/hwbus dstat_order_control must fail with it set. */
extern int hwbus_debug_kernel_first;

#ifdef __cplusplus
}
#endif
#endif

/* SPDX-License-Identifier: CC0-1.0 */
/* EE hardware register bus: routes HW_R* / HW_W* to the owning ps2/ model.
 * See hwbus.h and docs/HWBUS.md.  Register addresses and bit layouts are from
 * the public EE User's Manual register descriptions; no emulator code used
 * (PLAN.md D7). */
#include "hwbus.h"

#include <stdio.h>
#include <string.h>

#include "dmac.h"
#include "gs.h"
#include "ps2k.h"
#include "sif.h"
#include "vif.h"

/* ---------------------------------------------------------------- claims */
static const hwbus_region k_regions[] = {
    {0x10000000u, 0x10001FFFu, HWBUS_KERNEL, "T0..T3"},
    {0x10002000u, 0x1000203Fu, HWBUS_IPU, "IPU regs"},
    {0x10003000u, 0x100030AFu, HWBUS_GIF, "GIF regs"},
    {0x10003800u, 0x1000397Fu, HWBUS_VIF, "VIF0 regs"},
    {0x10003C00u, 0x10003D7Fu, HWBUS_VIF, "VIF1 regs"},
    {0x10004000u, 0x10004FFFu, HWBUS_FIFO, "VIF0 FIFO"},
    {0x10005000u, 0x10005FFFu, HWBUS_FIFO, "VIF1 FIFO"},
    {0x10006000u, 0x10006FFFu, HWBUS_FIFO, "GIF FIFO"},
    {0x10007000u, 0x1000701Fu, HWBUS_IPU, "IPU FIFO"},
    {0x10008000u, 0x1000E06Fu, HWBUS_DMAC, "DMAC"},
    {0x1000F000u, 0x1000F01Fu, HWBUS_KERNEL, "INTC"},
    {0x1000F200u, 0x1000F26Fu, HWBUS_SIF, "SIF regs"},
    {0x1000F520u, 0x1000F52Fu, HWBUS_DMAC, "D_ENABLER"},
    {0x1000F590u, 0x1000F59Fu, HWBUS_DMAC, "D_ENABLEW"},
    {0x12000000u, 0x120010FFu, HWBUS_GS, "GS privileged"},
    {0, 0, 0, 0}};

static const char *const k_owner_names[HWBUS_NOWNERS] = {
    "unknown", "kernel", "dmac", "fifo", "vif", "gif", "ipu", "sif", "gs"};

const hwbus_region *hwbus_regions(void) { return k_regions; }

const char *hwbus_owner_name(int owner)
{
    return owner >= 0 && owner < HWBUS_NOWNERS ? k_owner_names[owner] : "?";
}

static const hwbus_region *region_of(uint32_t a)
{
    const hwbus_region *r;
    for (r = k_regions; r->name; r++)
        if (a >= r->lo && a <= r->hi) return r;
    return NULL;
}

/* register index inside a VIF block, -1 if not a VIF register */
static int vif_reg(uint32_t a, int *which)
{
    uint32_t base, off;
    if (a >= 0x10003C00u && a <= 0x10003D7Fu) { base = 0x10003C00u; *which = 1; }
    else if (a >= 0x10003800u && a <= 0x1000397Fu) { base = 0x10003800u; *which = 0; }
    else return -1;
    off = a - base;
    if (off & 0xFu) return -1;
    off >>= 4;
    if (off > 0x17u) return -1;
    /* VIF0 has no BASE/OFST/TOPS/TOP (0xA, 0xB, 0xC, 0xE) */
    if (*which == 0 && (off == 0xA || off == 0xB || off == 0xC || off == 0xE)) return -1;
    if (off >= 0xF && off < 0x10) return -1;
    return (int)off;
}

static int sif_reg_of(uint32_t a)
{
    switch (a) {
    case 0x1000F200u: return (int)SIF_REG_MSCOM;
    case 0x1000F210u: return (int)SIF_REG_SMCOM;
    case 0x1000F220u: return (int)SIF_REG_MSFLAG;
    case 0x1000F230u: return (int)SIF_REG_SMFLAG;
    case 0x1000F240u: return (int)SIF_REG_CTRL;
    case 0x1000F260u: return 0x100; /* BD6: stored locally */
    default: return -1;
    }
}

static int gs_preg_ok(uint32_t a)
{
    a &= ~7u;
    if ((a & 0xFu) != 0 && (a & 0xFu) != 8u) return 0;
    if (a >= 0x12000000u && a <= 0x120000E0u) return (a & 0xFu) == 0;
    return a == GS_P_CSR || a == GS_P_IMR || a == GS_P_BUSDIR || a == GS_P_SIGLBLID;
}

int hwbus_debug_kernel_first = 0;

int hwbus_claims(uint32_t a)
{
    const hwbus_region *r;
    int w;
    if (hwbus_debug_kernel_first && ps2k_hw_claims(a)) return HWBUS_KERNEL;
    /* DMAC first: it owns D_STAT and forwards the kernel's part (DMAC.md) */
    if (dmac_hw_claims(a)) return HWBUS_DMAC;
    if (ps2k_hw_claims(a)) return HWBUS_KERNEL;
    r = region_of(a);
    if (!r) return HWBUS_UNKNOWN;
    switch (r->owner) {
    case HWBUS_VIF: return vif_reg(a, &w) >= 0 ? HWBUS_VIF : HWBUS_UNKNOWN;
    case HWBUS_FIFO: return (a & 0xFFFu) == 0 ? HWBUS_FIFO : HWBUS_UNKNOWN;
    case HWBUS_GIF: return (a & 0xFu) == 0 ? HWBUS_GIF : HWBUS_UNKNOWN;
    case HWBUS_IPU:
        return ((a & 0xFu) == 0 || ((a & 0xFu) == 4 && a < 0x10002040u)) ? HWBUS_IPU
                                                                          : HWBUS_UNKNOWN;
    case HWBUS_SIF: return sif_reg_of(a) >= 0 ? HWBUS_SIF : HWBUS_UNKNOWN;
    case HWBUS_GS: return gs_preg_ok(a) ? HWBUS_GS : HWBUS_UNKNOWN;
    default: return HWBUS_UNKNOWN; /* kernel/dmac ranges the models did not claim */
    }
}

/* ---------------------------------------------------------------- state */
static struct {
    dmac_state *dmac;
    gs_state *gs;
    hwbus_ipu_hooks ipu;
    int ipu_hooked;
    uint32_t read_cycles;
    hwbus_charge_fn charge; void *charge_user;
    hwbus_log_fn log; void *log_user;
    hwbus_stats stats;
    hwbus_unknown_rec unk[HWBUS_MAX_UNKNOWN];
    int nunk;
    uint64_t unk_total;
    /* local register state */
    uint32_t gif_mode, gif_ctrl;
    uint32_t vif_err[2];
    uint32_t sif_bd6;
    uint64_t ipu_cmd, ipu_top;
    uint32_t ipu_ctrl, ipu_bp;
    int spr_warned;
} B = {.read_cycles = HWBUS_DEFAULT_READ_CYCLES};

static uint8_t g_spr_fallback[DMAC_SPR_BYTES] __attribute__((aligned(16)));

static void logf_line(const char *line)
{
    if (B.log) B.log(B.log_user, line);
    else fprintf(stderr, "%s\n", line);
}

void hwbus_init(void)
{
    memset(&B, 0, sizeof B);
    B.read_cycles = HWBUS_DEFAULT_READ_CYCLES;
}

void hwbus_bind(dmac_state *d, gs_state *gs)
{
    B.dmac = d;
    B.gs = gs ? gs : (d ? d->gs : NULL);
}

void hwbus_set_ipu(const hwbus_ipu_hooks *h)
{
    if (h) { B.ipu = *h; B.ipu_hooked = 1; }
    else { memset(&B.ipu, 0, sizeof B.ipu); B.ipu_hooked = 0; }
}

void hwbus_set_read_cycles(uint32_t c) { B.read_cycles = c; }
uint32_t hwbus_read_cycles(void) { return B.read_cycles; }
void hwbus_set_charge(hwbus_charge_fn fn, void *user) { B.charge = fn; B.charge_user = user; }
void hwbus_set_log(hwbus_log_fn fn, void *user) { B.log = fn; B.log_user = user; }
const hwbus_stats *hwbus_get_stats(void) { return &B.stats; }
int hwbus_unknown_count(void) { return B.nunk; }
const hwbus_unknown_rec *hwbus_unknown_get(int i)
{
    return i >= 0 && i < B.nunk ? &B.unk[i] : NULL;
}
uint64_t hwbus_unknown_total(void) { return B.unk_total; }

static void charge_read(void)
{
    uint64_t c = B.read_cycles;
    if (!c) return;
    if (B.charge) { B.charge(B.charge_user, c); B.stats.charged_cycles += c; return; }
    if (ps2k_get_thread_id() != 0 && !ps2k_in_handler()) {
        B.stats.charged_cycles += c;
        ps2k_charge(c);
    } else {
        B.stats.uncharged_cycles += c;
    }
}

static void unknown(uint32_t a, int bits, int write, uint64_t v)
{
    int i;
    char line[160];
    B.unk_total++;
    B.stats.reads[HWBUS_UNKNOWN] += !write;
    B.stats.writes[HWBUS_UNKNOWN] += write;
    for (i = 0; i < B.nunk; i++)
        if (B.unk[i].addr == a) break;
    if (i == B.nunk) {
        if (B.nunk == HWBUS_MAX_UNKNOWN) return;
        B.nunk++;
        memset(&B.unk[i], 0, sizeof B.unk[i]);
        B.unk[i].addr = a;
        B.unk[i].bits = bits;
        if (write)
            snprintf(line, sizeof line,
                     "hwbus: UNKNOWN hardware address 0x%08X (write%d 0x%llX) -- dropped, "
                     "reported once", a, bits, (unsigned long long)v);
        else
            snprintf(line, sizeof line,
                     "hwbus: UNKNOWN hardware address 0x%08X (read%d) -- reads 0, reported once",
                     a, bits);
        logf_line(line);
    }
    if (write) { B.unk[i].writes++; B.unk[i].last_write = v; }
    else B.unk[i].reads++;
}

static void unbound(int owner, uint32_t a)
{
    char line[120];
    if (B.stats.unbound++ == 0) {
        snprintf(line, sizeof line, "hwbus: %s register 0x%08X accessed with no model bound",
                 hwbus_owner_name(owner), a);
        logf_line(line);
    }
}

/* ---------------------------------------------------------------- VIF */
static vif_state *vif_of(int which)
{
    return B.dmac ? B.dmac->vif[which] : NULL;
}

static uint32_t vif_stat(int which, const vif_state *v)
{
    uint32_t s = 0;
    if (!vif_idle(v)) s |= 1u;                /* VPS: waiting for data */
    if (v->dbf) s |= 1u << 7;                 /* DBF */
    if (v->irq) s |= 1u << 11;                /* INT */
    (void)which; /* VIF1 MSKPATH3 is reported in GIF_STAT.M3P */
    return s;
}

static uint32_t vif_read(uint32_t a, int idx, int which)
{
    vif_state *v = vif_of(which);
    if (!v) { unbound(HWBUS_VIF, a); return 0; }
    switch (idx) {
    case 0x0: return vif_stat(which, v);
    case 0x1: return 0;                                    /* FBRST: write-only */
    case 0x2: return B.vif_err[which];
    case 0x3: return v->mark & 0xFFFFu;
    case 0x4: return (v->cl & 0xFFu) | ((v->wl & 0xFFu) << 8);
    case 0x5: return v->mode & 3u;
    case 0x6: return v->num & 0xFFu;
    case 0x7: return v->mask;
    case 0x8: return v->code;
    case 0x9: return v->itops & 0x3FFu;
    case 0xA: return v->base & 0x3FFu;
    case 0xB: return v->ofst & 0x3FFu;
    case 0xC: return v->tops & 0x3FFu;
    case 0xD: return v->itop & 0x3FFu;
    case 0xE: return v->top & 0x3FFu;
    default:
        if (idx >= 0x10 && idx <= 0x13) return v->row[idx - 0x10];
        if (idx >= 0x14 && idx <= 0x17) return v->col[idx - 0x14];
        return 0;
    }
}

static void vif_write_reg(uint32_t a, int idx, int which, uint32_t val)
{
    vif_state *v = vif_of(which);
    if (!v) { unbound(HWBUS_VIF, a); return; }
    switch (idx) {
    case 0x1: /* FBRST: RST(0) FBK(1) STP(2) STC(3) */
        if (val & 1u) dmac_vif_reset(B.dmac, which);
        if (val & 8u) v->irq = 0; /* STC: stall cancel, clears STAT.INT */
        /* FBK/STP: the model never stalls on a pending transfer (DMAC.md) */
        break;
    case 0x2: B.vif_err[which] = val & 7u; break;
    case 0x3: v->mark = val & 0xFFFFu; break;
    default: B.stats.ignored_writes++; break;   /* read-only from the EE */
    }
}

/* ---------------------------------------------------------------- GIF */
static uint32_t gif_read(uint32_t a)
{
    switch (a & 0xF0u) {
    case 0x10: return B.gif_mode;
    case 0x20: { /* GIF_STAT */
        uint32_t s = 0;
        vif_state *v1 = vif_of(1);
        gs_state *gs = B.gs;
        if (B.gif_mode & 1u) s |= 1u;                     /* M3R */
        if (v1 && v1->mskpath3) s |= 2u;                  /* M3P */
        if (B.gif_mode & 4u) s |= 4u;                     /* IMT */
        if (B.gif_ctrl & 8u) s |= 8u;                     /* PSE */
        if (gs && gs->bus_owner) {
            s |= 1u << 9;                                 /* OPH */
            s |= ((uint32_t)gs->bus_owner & 3u) << 10;    /* APATH */
        }
        return s;
    }
    default: return 0; /* CTRL (write-only), TAG0-3, CNT, P3CNT, P3TAG */
    }
}

static void gif_write(uint32_t a, uint32_t v)
{
    switch (a & 0xF0u) {
    case 0x00:
        /* RST(0): GIF-only reset of the GS model's path state (gs_gif_reset;
         * registers and VRAM untouched).  PSE(3) is stored. */
        if ((v & 1u) && B.gs) gs_gif_reset(B.gs);
        B.gif_ctrl = v & 8u;
        break;
    case 0x10: B.gif_mode = v & 5u; break;
    default: B.stats.ignored_writes++; break;
    }
}

/* ---------------------------------------------------------------- IPU */
static uint64_t ipu_read(uint32_t a, int bits)
{
    if (B.ipu_hooked && B.ipu.read) return B.ipu.read(B.ipu.user, a, bits);
    B.stats.ipu_stub_accesses++;
    switch (a & ~4u) {
    case 0x10002000u: { uint64_t v = B.ipu_cmd & ~(1ull << 63); /* BUSY 0 */
                        return (a & 4u) ? v >> 32 : v; }
    case 0x10002010u: return (a & 4u) ? 0 : (B.ipu_ctrl & ~(1u << 31)); /* BUSY 0 */
    case 0x10002020u: return (a & 4u) ? 0 : B.ipu_bp;
    case 0x10002030u: return (a & 4u) ? B.ipu_top >> 32 : B.ipu_top;
    default: return 0;
    }
}

static void ipu_write(uint32_t a, uint64_t v, int bits)
{
    if (B.ipu_hooked && B.ipu.write) { B.ipu.write(B.ipu.user, a, v, bits); return; }
    B.stats.ipu_stub_accesses++;
    switch (a) {
    case 0x10002000u: B.ipu_cmd = v & 0xFFFFFFFFu; break; /* command: no decoder */
    case 0x10002010u:
        if (v & (1u << 30)) { B.ipu_cmd = 0; B.ipu_bp = 0; B.ipu_top = 0; B.ipu_ctrl = 0; }
        else B.ipu_ctrl = (uint32_t)v & 0x3FFF0000u;
        break;
    default: B.stats.ignored_writes++; break;
    }
}

/* ---------------------------------------------------------------- core */
static uint32_t read32(uint32_t a)
{
    int owner = hwbus_claims(a), idx, which;
    if (owner != HWBUS_UNKNOWN) B.stats.reads[owner]++;
    switch (owner) {
    case HWBUS_DMAC:
        if (!B.dmac) {
            unbound(owner, a);
            return a == DMAC_D_STAT ? ps2k_hw_read32(PS2K_D_STAT) : 0;
        }
        return dmac_hw_read32(B.dmac, a);
    case HWBUS_KERNEL: return ps2k_hw_read32(a);
    case HWBUS_VIF: idx = vif_reg(a, &which); return vif_read(a, idx, which);
    case HWBUS_GIF: return gif_read(a);
    case HWBUS_IPU: return (uint32_t)ipu_read(a, 32);
    case HWBUS_SIF: {
        int r = sif_reg_of(a);
        return r == 0x100 ? B.sif_bd6 : sif_reg_get((uint32_t)r);
    }
    case HWBUS_GS: {
        uint64_t v;
        if (!B.gs) { unbound(owner, a); return 0; }
        v = gs_read_priv(B.gs, a & ~7u);
        return (a & 4u) ? (uint32_t)(v >> 32) : (uint32_t)v;
    }
    case HWBUS_FIFO: return 0; /* a 32-bit access to a 128-bit FIFO moves nothing */
    default: unknown(a, 32, 0, 0); return 0;
    }
}

static void write32(uint32_t a, uint32_t v)
{
    int owner = hwbus_claims(a), idx, which;
    if (owner != HWBUS_UNKNOWN) B.stats.writes[owner]++;
    switch (owner) {
    case HWBUS_DMAC:
        if (!B.dmac) {
            unbound(owner, a);
            if (a == DMAC_D_STAT) ps2k_hw_write32(PS2K_D_STAT, v & 0x03FF03FFu);
            return;
        }
        dmac_hw_write32(B.dmac, a, v);
        return;
    case HWBUS_KERNEL: ps2k_hw_write32(a, v); return;
    case HWBUS_VIF: idx = vif_reg(a, &which); vif_write_reg(a, idx, which, v); return;
    case HWBUS_GIF: gif_write(a, v); return;
    case HWBUS_IPU: ipu_write(a, v, 32); return;
    case HWBUS_SIF: {
        int r = sif_reg_of(a);
        if (r == 0x100) B.sif_bd6 = v;
        else sif_reg_set((uint32_t)r, v);
        return;
    }
    case HWBUS_GS: {
        uint32_t base = a & ~7u;
        uint64_t old, nv;
        if (!B.gs) { unbound(owner, a); return; }
        if (base == GS_P_CSR || base == GS_P_IMR || base == GS_P_SIGLBLID) {
            /* CSR: event bits are write-1-to-clear; never merge stale halves */
            nv = (a & 4u) ? ((uint64_t)v << 32) : v;
        } else {
            old = gs_read_priv(B.gs, base);
            nv = (a & 4u) ? ((old & 0xFFFFFFFFull) | ((uint64_t)v << 32))
                          : ((old & ~0xFFFFFFFFull) | v);
        }
        gs_write_priv(B.gs, base, nv);
        return;
    }
    case HWBUS_FIFO: B.stats.ignored_writes++; return;
    default: unknown(a, 32, 1, v); return;
    }
}

uint32_t hw_r32(uint32_t a)
{
    uint32_t v;
    if (a & 3u) { unknown(a, 32, 0, 0); charge_read(); return 0; }
    v = read32(a);
    charge_read();
    return v;
}

void hw_w32(uint32_t a, uint32_t v)
{
    if (a & 3u) { unknown(a, 32, 1, v); return; }
    write32(a, v);
}

uint64_t hw_r64(uint32_t a)
{
    uint64_t v;
    int owner;
    if (a & 7u) { unknown(a, 64, 0, 0); charge_read(); return 0; }
    owner = hwbus_claims(a);
    if (owner == HWBUS_GS) {
        B.stats.reads[owner]++;
        if (!B.gs) { unbound(owner, a); v = 0; }
        else v = gs_read_priv(B.gs, a);
    } else if (owner == HWBUS_IPU && (a == 0x10002000u || a == 0x10002030u)) {
        B.stats.reads[owner]++;
        v = ipu_read(a, 64);
    } else if (owner == HWBUS_UNKNOWN) {
        unknown(a, 64, 0, 0);
        v = 0;
    } else {
        /* 32-bit registers: the upper word reads as the next register slot
         * would on the EE bus only for 64-bit regs; here it is zero */
        v = read32(a);
    }
    charge_read();
    return v;
}

void hw_w64(uint32_t a, uint64_t v)
{
    int owner;
    if (a & 7u) { unknown(a, 64, 1, v); return; }
    owner = hwbus_claims(a);
    if (owner == HWBUS_GS) {
        B.stats.writes[owner]++;
        if (!B.gs) { unbound(owner, a); return; }
        gs_write_priv(B.gs, a, v);
    } else if (owner == HWBUS_IPU && a == 0x10002000u) {
        B.stats.writes[owner]++;
        ipu_write(a, v, 64);
    } else if (owner == HWBUS_UNKNOWN) {
        unknown(a, 64, 1, v);
    } else {
        write32(a, (uint32_t)v);
    }
}

uint16_t hw_r16(uint32_t a)
{
    uint32_t w = hw_r32(a & ~3u);
    return (uint16_t)(w >> ((a & 2u) * 8));
}

uint8_t hw_r8(uint32_t a)
{
    uint32_t w = hw_r32(a & ~3u);
    return (uint8_t)(w >> ((a & 3u) * 8));
}

/* Sub-word stores: on the EE a byte/halfword store to a 32-bit register
 * writes only those lanes.  Read-modify-write without the read charge. */
static void write_lanes(uint32_t a, uint32_t v, uint32_t mask, int bits)
{
    uint32_t base = a & ~3u, sh = (a & 3u) * 8, old;
    if (hwbus_claims(base) == HWBUS_UNKNOWN) { unknown(a, bits, 1, v); return; }
    old = read32(base);
    write32(base, (old & ~(mask << sh)) | ((v & mask) << sh));
}

void hw_w16(uint32_t a, uint16_t v) { write_lanes(a, v, 0xFFFFu, 16); }
void hw_w8(uint32_t a, uint8_t v) { write_lanes(a, v, 0xFFu, 8); }

void hw_r128(uint32_t a, void *out)
{
    int owner = hwbus_claims(a);
    memset(out, 0, 16);
    if (owner == HWBUS_FIFO) {
        B.stats.reads[owner]++;
        if (a == DMAC_VIF1_FIFO) {
            if (B.dmac) dmac_vif1_fifo_read(B.dmac, out, 1);
            else unbound(owner, a);
        } else {
            B.stats.ignored_writes++; /* VIF0/GIF FIFOs are write-only */
        }
    } else if (owner == HWBUS_IPU && a == 0x10007000u) {
        B.stats.reads[owner]++;
        if (B.ipu_hooked && B.ipu.fifo_read) B.ipu.fifo_read(B.ipu.user, out);
        else B.stats.ipu_stub_accesses++;
    } else if (owner == HWBUS_UNKNOWN || (a & 0xFu)) {
        unknown(a, 128, 0, 0);
    } else {
        uint32_t w = read32(a);
        memcpy(out, &w, 4);
    }
    charge_read();
}

void hw_w128(uint32_t a, const void *in)
{
    int owner = hwbus_claims(a);
    if (owner == HWBUS_FIFO) {
        B.stats.writes[owner]++;
        if (!B.dmac) { unbound(owner, a); return; }
        if (a == DMAC_VIF0_FIFO) dmac_vif_fifo_write(B.dmac, 0, in, 1);
        else if (a == DMAC_VIF1_FIFO) dmac_vif_fifo_write(B.dmac, 1, in, 1);
        else dmac_gif_fifo_write(B.dmac, in, 1);
    } else if (owner == HWBUS_IPU && a == 0x10007010u) {
        B.stats.writes[owner]++;
        if (B.ipu_hooked && B.ipu.fifo_write) B.ipu.fifo_write(B.ipu.user, in);
        else B.stats.ipu_stub_accesses++;
    } else if (owner == HWBUS_UNKNOWN || (a & 0xFu)) {
        uint64_t lo;
        memcpy(&lo, in, 8);
        unknown(a, 128, 1, lo);
    } else {
        uint32_t w;
        memcpy(&w, in, 4);
        write32(a, w);
    }
}

/* ---------------------------------------------------------------- SPR */
uint8_t *hw_spr_base(void)
{
    if (B.dmac) return B.dmac->spr;
    if (!B.spr_warned) {
        B.spr_warned = 1;
        logf_line("hwbus: PS2_SPR used with no DMAC bound -- private scratchpad block "
                  "(DMA from it will not be recognised as SPR)");
    }
    return g_spr_fallback;
}

/* port/hwaccess.h routes the GS privileged and VIF1_FBRST sites to these (docs/NATIVE-RENDER.md
 * "Hardware register sites"): over the bus in builds that link it (the HLE kernel charges the
 * register reads); an RG_NATIVE_ONLY rg-game links src/native/render/nr_hw.c instead */
unsigned long long rg_gs_priv_r64(unsigned int addr) { return hw_r64(addr); }
void rg_gs_priv_w64(unsigned int addr, unsigned long long v) { hw_w64(addr, v); }
void rg_vif1_fbrst_w32(unsigned int v) { hw_w32(0x10003C10u, v); }
/* the game's sites by register id (port/hwaccess.h RG_GS_<REG>, D9): the bus address */
unsigned long long rg_gs_reg_r64(unsigned int reg);
void rg_gs_reg_w64(unsigned int reg, unsigned long long v);
static unsigned int gs_reg_addr(unsigned int reg)
{
    return 0x12000000u + (reg >= 16u ? 0x1000u + ((reg - 16u) << 4) : reg << 4);
}
unsigned long long rg_gs_reg_r64(unsigned int reg) { return hw_r64(gs_reg_addr(reg)); }
void rg_gs_reg_w64(unsigned int reg, unsigned long long v) { hw_w64(gs_reg_addr(reg), v); }

/* SPDX-License-Identifier: CC0-1.0 */
/* The game's last hardware-register sites (docs/NATIVE-RENDER.md "Hardware register
 * sites"): GS privileged registers and VIF1_FBRST, routed here by port/hwaccess.h.
 *
 *   PMODE / DISPFB1 / DISPLAY1   GsDbufPutEnv_144150 (interlaced display), SysInitHardware_15e670
 *   CSR (FIELD bit)              GfxVblankStartHandler_15df20
 *   VIF1_FBRST.STC               Vif1IntcHandler_15e170 (stall cancel after the end-of-frame
 *                                interrupt)
 *
 * Native-only builds: the registers are the renderer's display configuration (the PCRTC
 * block the presenter reads) and the CSR read-out, held in the native state block
 * (nr_gs.h preg / csr_events / csr_field; checkpoint 10: no GS model behind them); SIGNAL /
 * FINISH / LABEL from the GIF input update CSR and SIGLBLID here and raise the GS interrupt
 * when unmasked; the stall cancel has nothing to cancel (no VIF stalls on the native path).
 * Default (oracle) builds keep the bus: the HLE kernel charges register reads, and its
 * timing is part of the oracle. */
#include <stdint.h>

#include "gs.h"
#include "vif.h"

unsigned long long rg_gs_priv_r64(unsigned int addr);
void rg_gs_priv_w64(unsigned int addr, unsigned long long v);
void rg_vif1_fbrst_w32(unsigned int v);
/* by register id (port/hwaccess.h RG_GS_<REG>: the preg[] slot), what the game's sites call
 * since 2026-10-25 (D9: no PS2 address in game code); the address forms stay for libgraph */
unsigned long long rg_gs_reg_r64(unsigned int reg);
void rg_gs_reg_w64(unsigned int reg, unsigned long long v);

#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY && defined(RG_HAVE_GPU)
#include "nr_gs.h"
#include "nr_interp.h"

static nr_gs *g_hgs;
static void (*g_irq)(void *user, uint32_t bits);
static void *g_irq_user;

void nr_hw_bind_gs(nr_gs *gs, void (*irq)(void *user, uint32_t csr_bits), void *irq_user)
{
    g_hgs = gs;
    g_irq = irq;
    g_irq_user = irq_user;
}

const uint64_t *nr_hw_display_regs(void) { return g_hgs ? g_hgs->preg : NULL; }

static int preg_index(uint32_t a)
{
    a &= 0x1FFFu;
    if (a >= 0x1000u) return (a - 0x1000u) >= 0x100u ? -1 : 16 + (int)((a - 0x1000u) >> 4);
    return a >= 0x100u ? -1 : (int)(a >> 4);
}

static void raise_event(uint32_t bit)
{
    uint32_t imr;
    if (!g_hgs) return;
    __atomic_fetch_or(&g_hgs->csr_events, bit, __ATOMIC_SEQ_CST);
    imr = (uint32_t)g_hgs->preg[16 + 1];
    if (!(imr & (bit << 8)) && g_irq) g_irq(g_irq_user, bit);
}

/* CSR.RESET: the general registers / CLUT in stream order on the worker */
static void w_reset(void *user, const void *data)
{
    (void)user; (void)data;
    nr_ip_w_reset();   /* (the retained frames of interpolated presentation are void) */
    if (nr_gs_state()) nr_gs_reset(nr_gs_state());
}

static int reg_index(unsigned int reg) { return reg < 32u ? (int)reg : -1; }

unsigned long long rg_gs_priv_r64(unsigned int addr) { return rg_gs_reg_r64((unsigned int)preg_index(addr)); }
void rg_gs_priv_w64(unsigned int addr, unsigned long long v) { rg_gs_reg_w64((unsigned int)preg_index(addr), v); }

unsigned long long rg_gs_reg_r64(unsigned int reg)
{
    int i = reg_index(reg);
    if (!g_hgs || i < 0) return 0;
    if (i == 16)   /* FIFO empty (bits 14-15 = 01); REV 0x1B, ID 0x55 (as the model) */
        return (uint64_t)g_hgs->csr_events | ((uint64_t)(g_hgs->csr_field & 1u) << 13) | (1ull << 14) | (0x1Bull << 16) |
               (0x55ull << 24);
    return g_hgs->preg[i];
}

void rg_gs_reg_w64(unsigned int reg, unsigned long long v)
{
    int i = reg_index(reg);
    if (!g_hgs || i < 0) return;
    if (i == 16) {   /* CSR */
        g_hgs->csr_events &= ~(uint32_t)(v & 0x1Fu);
        if (v & GS_CSR_RESET) {
            int k;
            for (k = 0; k < 32; k++) g_hgs->preg[k] = 0;
            g_hgs->preg[16 + 1] = 0x7F00;
            g_hgs->csr_events = 0;
            g_hgs->csr_field = 0;
            nr_gs_gif_reset();
            nr_q_call(w_reset, NULL, NULL, 0);
        }
        return;
    }
    if (i == 16 + 1) { g_hgs->preg[i] = v & 0x7F00u; return; }   /* IMR */
    g_hgs->preg[i] = v;
}

void nr_hw_gs_event(uint32_t addr, uint64_t data)
{
    uint32_t id = (uint32_t)data, msk = (uint32_t)(data >> 32);
    uint64_t s;
    if (!g_hgs) return;
    s = g_hgs->preg[16 + 8];
    switch (addr) {
    case GS_SIGNAL: {
        uint32_t sig = ((uint32_t)s & ~msk) | (id & msk);
        g_hgs->preg[16 + 8] = (s & 0xFFFFFFFF00000000ull) | sig;
        raise_event(GS_CSR_SIGNAL);
        break;
    }
    case GS_FINISH:
        raise_event(GS_CSR_FINISH);
        break;
    case GS_LABEL: {
        uint32_t lbl = ((uint32_t)(s >> 32) & ~msk) | (id & msk);
        g_hgs->preg[16 + 8] = (s & 0xFFFFFFFFull) | ((uint64_t)lbl << 32);
        break;
    }
    default: break;
    }
}

void nr_hw_vsync(void)
{
    if (!g_hgs) return;
    if (g_hgs->preg[2] & 1) g_hgs->csr_field ^= 1u;   /* SMODE2.INT */
    else g_hgs->csr_field = 0;
    raise_event(GS_CSR_VSINT);
}

void rg_vif1_fbrst_w32(unsigned int v)
{
    (void)v;   /* STC (bit 3): no VIF stalls natively; RST is never written by the game */
}
#elif defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
/* native-only without the native device (headless Linux, docs/LINUX.md): the software GS model */
void nr_hw_bind(gs_state *gs, vif_state *vif1);
static gs_state *g_gs;
static vif_state *g_vif1;
void nr_hw_bind(gs_state *gs, vif_state *vif1)
{
    g_gs = gs;
    g_vif1 = vif1;
}
unsigned long long rg_gs_priv_r64(unsigned int addr) { return g_gs ? gs_read_priv(g_gs, addr) : 0; }
void rg_gs_priv_w64(unsigned int addr, unsigned long long v)
{
    if (g_gs) gs_write_priv(g_gs, addr, v);
}
/* register id -> the software model's bus address (the model is addressed like the GS) */
static unsigned int reg_addr(unsigned int reg)
{
    return 0x12000000u + (reg >= 16u ? 0x1000u + ((reg - 16u) << 4) : reg << 4);
}
unsigned long long rg_gs_reg_r64(unsigned int reg) { return rg_gs_priv_r64(reg_addr(reg)); }
void rg_gs_reg_w64(unsigned int reg, unsigned long long v) { rg_gs_priv_w64(reg_addr(reg), v); }
void rg_vif1_fbrst_w32(unsigned int v)
{
    if (g_vif1 && (v & 8u)) g_vif1->irq = 0;
}
#else
/* default builds: the bus serves the sites (hwbus.c); the runtime's bind call stays harmless */
void nr_hw_bind(gs_state *gs, vif_state *vif1);
void nr_hw_bind(gs_state *gs, vif_state *vif1) { (void)gs; (void)vif1; }
#endif
/* default (oracle) builds: rg_ps2_hwbus defines them over the bus (hwbus.c), so tests that link
 * the bus without the renderer resolve the port/hwaccess.h routing too */

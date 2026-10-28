/* SPDX-License-Identifier: CC0-1.0 */
/* VU interpreter (docs/VU.md).  Written from public hardware descriptions. */
#include "vu.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "vu_decode.h"
#include "vu_float_inl.h"
#include "vu_internal.h"

enum { C_Z = 1, C_S = 2, C_U = 4, C_O = 8 };

/* the per-pair path is inlined into vu_run (docs/VU.md "Performance") */
#if defined(__GNUC__) || defined(__clang__)
#define VU_ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define VU_ALWAYS_INLINE __inline
#endif

/* ------------------------------------------------------------ decode cache */

/* dc_entry: vu_internal.h (shared with the block translator) */

/* vu_state keeps 96 bytes per pair (tests put two vu_states on the stack) */
typedef char dc_entry_fits[(sizeof(dc_entry) <= sizeof(((vu_state *)0)->dc_store) / 2048) ? 1 : -1];

static void dc_fill(vu_state *vu, uint32_t pc, dc_entry *e)
{
    uint32_t idx = pc >> 3;
    {
        uint32_t lw, uw;
        vu_use us[2];
        unsigned w, k, c, j;
        memcpy(&lw, vu->code + pc, 4);
        memcpy(&uw, vu->code + pc + 4, 4);
        vu_decode_pair(lw, uw, &e->p);
        vu_upper_use(&e->p.up, &us[0]);
        vu_lower_use(&e->p.lo, &us[1]);
        e->writes_q = us[1].writes_q;
        e->writes_p = us[1].writes_p;
        e->is_branch = us[1].is_branch;
        e->vi_w = us[1].vi_w;
        e->n_rd = 0;
        for (w = 0; w < 2; w++)
            for (k = 0; k < us[w].n_vf_r; k++)
                for (c = 0; c < 4; c++) {
                    uint8_t ix = (uint8_t)(us[w].vf_r[k] * 4 + c);
                    if (!us[w].vf_r[k] || !(us[w].vf_r_mask[k] & (8u >> c))) continue;
                    for (j = 0; j < e->n_rd && e->rd[j] != ix; j++) {}
                    if (j == e->n_rd) e->rd[e->n_rd++] = ix;
                }
        e->n_wr = 0;
        for (w = 0; w < 2; w++)
            for (c = 0; c < 4; c++)
                if (us[w].vf_w && (us[w].vf_w_mask & (8u >> c)))
                    e->wr[e->n_wr++] = (uint8_t)(us[w].vf_w * 4 + c);
        vu->dc_valid[idx] = 1;
    }
}

static VU_ALWAYS_INLINE dc_entry *dc_get(vu_state *vu, uint32_t pc)
{
    dc_entry *e = (dc_entry *)vu->dc_store + (pc >> 3);
    if (!vu->dc_valid[pc >> 3]) dc_fill(vu, pc, e);
    return e;
}

static void dc_invalidate(vu_state *vu)
{
    memset(vu->dc_valid, 0, sizeof vu->dc_valid);
}

dc_entry *vu__dc_get(vu_state *vu, uint32_t pc) { return dc_get(vu, pc & (vu->code_bytes - 1) & ~7u); }

/* ------------------------------------------------------------ setup */

void vu_reset_regs(vu_state *vu)
{
    memset(vu->vf, 0, sizeof vu->vf);
    vu->vf[0].f[3] = 1.0f;
    memset(&vu->acc, 0, sizeof vu->acc);
    memset(vu->vi, 0, sizeof vu->vi);
    vu->q = vu->p = vu->i = 0;
    vu->r = 0x3F800000u;
    vu->mac = vu->status = vu->clip = 0;
    vu->pc = vu->tpc = 0;
    vu->running = 0;
    vu->cycle = 0;
    memset(vu->vf_ready, 0, sizeof vu->vf_ready);
    vu->fq_head = vu->fq_n = 0;
    vu->q_busy = vu->p_busy = 0;
    vu->branch_pending = 0;
    vu->ebit_pending = 0;
    memset(vu->vih_reg, -1, sizeof vu->vih_reg);
    memset(vu->vih_old, 0, sizeof vu->vih_old);
    vu->vih_pos = 0;
    vu->prev_vi_write = -1;
}

void vu_init(vu_state *vu, int id)
{
    memset(vu, 0, sizeof *vu);
    vu->id = id;
    vu->mem_bytes = id ? 0x4000 : 0x1000;
    vu->code_bytes = id ? 0x4000 : 0x1000;
    vu->int_branch_quirk = 1;
    vu->blocks = vu__blocks_default();
    vu->blocks_check = vu__blocks_check_default();
    vu->stats_print = vu__stats_default();
    vu_reset_regs(vu);
    dc_invalidate(vu);
}

void vu_load_code(vu_state *vu, uint32_t addr, const void *src, uint32_t bytes)
{
    const uint8_t *s = (const uint8_t *)src;
    uint32_t i, first = 0, last = 0, changed = 0;
    /* Only a change of content matters: the decode cache and the block
     * cache are pure functions of the code bytes, and the game re-uploads
     * resident programs (docs/VU.md "Block translator"). */
    if ((addr & (vu->code_bytes - 1)) + bytes <= vu->code_bytes &&
        !memcmp(vu->code + (addr & (vu->code_bytes - 1)), s, bytes))
        return;
    for (i = 0; i < bytes; i++) {
        uint32_t a = (addr + i) & (vu->code_bytes - 1);
        if (vu->code[a] != s[i]) {
            if (!changed) first = i;
            last = i;
            changed = 1;
            vu->code[a] = s[i];
        }
    }
    if (!changed) return;
    dc_invalidate(vu);
    if (vu->blk) {
        uint32_t a0 = (addr + first) & (vu->code_bytes - 1);
        vu__block_invalidate(vu, a0 >> 3, ((a0 & 7) + (last - first) + 8) >> 3);
    }
}

/* at a program start the VI file "4 pairs ago" is the current one */
static void vi_hist_reset(vu_state *vu)
{
    memset(vu->vih_reg, -1, sizeof vu->vih_reg);
    vu->prev_vi_write = -1;
}

void vu_start(vu_state *vu, uint32_t pc)
{
    vu->pc = pc & (vu->code_bytes - 1);
    vu->running = 1;
    vu->branch_pending = 0;
    vu->ebit_pending = 0;
    vi_hist_reset(vu);
    vu->stats.runs++;
}

void vu_continue(vu_state *vu) { vu_start(vu, vu->tpc); }

/* ------------------------------------------------------------ pipeline */

static VU_ALWAYS_INLINE void commit_mac(vu_state *vu, uint32_t mac)
{
    uint32_t agg = 0;
    vu->mac = mac;
    if (mac & 0x000F) agg |= VU_ST_Z;
    if (mac & 0x00F0) agg |= VU_ST_S;
    if (mac & 0x0F00) agg |= VU_ST_U;
    if (mac & 0xF000) agg |= VU_ST_O;
    vu->status = (vu->status & ~0xFu) | agg | (agg << 6);
}

static VU_ALWAYS_INLINE void commit_events(vu_state *vu, uint64_t now);
void vu__commit_events(vu_state *vu, uint64_t now) { commit_events(vu, now); }

static VU_ALWAYS_INLINE void commit_events(vu_state *vu, uint64_t now)
{
    while (vu->fq_n && vu->fq[vu->fq_head].t <= now) {
        vu_flag_event *ev = &vu->fq[vu->fq_head];
        if (ev->kind == 1) commit_mac(vu, ev->value);
        else vu->clip = ((vu->clip << 6) | ev->value) & 0xFFFFFFu;
        vu->fq_head = (vu->fq_head + 1) & 15;
        vu->fq_n--;
    }
    if (vu->q_busy && vu->q_done <= now) {
        vu->q = vu->q_next;
        vu->status = (vu->status & ~0x30u) | vu->q_next_flags | (vu->q_next_flags << 6);
        vu->q_busy = 0;
    }
    if (vu->p_busy && vu->p_done <= now) {
        vu->p = vu->p_next;
        vu->p_busy = 0;
    }
}

static VU_ALWAYS_INLINE void push_event(vu_state *vu, uint64_t t, int kind, uint32_t value)
{
    vu_flag_event *ev;
    if (vu->fq_n == 16) commit_events(vu, vu->fq[vu->fq_head].t); /* cannot happen in order */
    ev = &vu->fq[(vu->fq_head + vu->fq_n) & 15];
    ev->t = t;
    ev->kind = (uint8_t)kind;
    ev->value = value;
    vu->fq_n++;
}

void vu_drain(vu_state *vu)
{
    uint64_t end = vu->cycle;
    unsigned k;
    for (k = 0; k < vu->fq_n; k++) {
        uint64_t t = vu->fq[(vu->fq_head + k) & 15].t;
        if (t > end) end = t;
    }
    if (vu->q_busy && vu->q_done > end) end = vu->q_done;
    if (vu->p_busy && vu->p_done > end) end = vu->p_done;
    commit_events(vu, end);
    vu->cycle = end;
}

/* ------------------------------------------------------------ memory */

static uint32_t *vu0_window(vu_state *vu, uint32_t qa, uint32_t *scratch)
{
    /* VU0 addresses 0x4000.. (qword 0x400..) map VU1 registers */
    vu_state *v1 = vu->vu1;
    uint32_t r = qa & 0x3F;
    if (!v1) return NULL;
    if (r < 0x20) return v1->vf[r].u;
    if (r < 0x30) {
        scratch[0] = v1->vi[r & 15];
        scratch[1] = scratch[2] = scratch[3] = 0;
        return scratch;
    }
    return NULL;
}

static void mem_read(vu_state *vu, uint32_t qa, uint32_t out[4])
{
    if (vu->id == 0 && (qa & 0x400)) {
        uint32_t s[4];
        uint32_t *p = vu0_window(vu, qa, s);
        if (p) memcpy(out, p, 16);
        else memset(out, 0, 16);
        return;
    }
    memcpy(out, vu->mem + (qa & (vu->mem_bytes / 16 - 1)) * 16, 16);
}

static void mem_write(vu_state *vu, uint32_t qa, const uint32_t in[4], unsigned dest)
{
    uint32_t *p, s[4], c;
    if (vu->id == 0 && (qa & 0x400)) {
        uint32_t r = qa & 0x3F;
        p = vu0_window(vu, qa, s);
        if (!p) return;
        if (r < 0x20) {
            if (r == 0) return;
            for (c = 0; c < 4; c++) if (dest & (8u >> c)) p[c] = in[c];
        } else if (dest & 8) {
            if (r & 15) vu->vu1->vi[r & 15] = (uint16_t)in[0];
        }
        return;
    }
    p = (uint32_t *)(vu->mem + (qa & (vu->mem_bytes / 16 - 1)) * 16);
    for (c = 0; c < 4; c++)
        if (dest & (8u >> c)) memcpy(&p[c], &in[c], 4);
}

uint32_t vu_gif_packet_bytes(const vu_state *vu, uint32_t addr)
{
    uint32_t total = 0, qmask = vu->mem_bytes - 1;
    for (;;) {
        uint32_t lo, hi, nloop, eop, flg, nreg, q;
        const uint8_t *t = vu->mem + ((addr + total) & qmask & ~15u);
        memcpy(&lo, t, 4);
        memcpy(&hi, t + 4, 4);
        nloop = lo & 0x7FFF;
        eop = (lo >> 15) & 1;
        flg = (hi >> 26) & 3;
        nreg = (hi >> 28) & 0xF;
        if (!nreg) nreg = 16;
        if (flg == 0) q = nloop * nreg;
        else if (flg == 1) q = (nloop * nreg + 1) / 2;
        else q = nloop;
        total += 16 * (1 + q);
        if (total > vu->mem_bytes) return 0;
        if (eop) return total;
    }
}

static void xgkick(vu_state *vu, uint32_t vi);
void vu__xgkick(vu_state *vu, uint32_t vi) { xgkick(vu, vi); }

static void xgkick(vu_state *vu, uint32_t vi)
{
    uint32_t addr = (vi * 16) & (vu->mem_bytes - 1);
    uint32_t bytes = vu_gif_packet_bytes(vu, addr);
    static uint8_t buf[0x4000];
    uint32_t k;
    vu->stats.xgkicks++;
    if (!bytes) {
        snprintf(vu->error, sizeof vu->error, "XGKICK at 0x%x: no EOP within VU memory", addr);
        return;
    }
    if (addr + bytes <= vu->mem_bytes) memcpy(buf, vu->mem + addr, bytes);
    else for (k = 0; k < bytes; k++) buf[k] = vu->mem[(addr + k) & (vu->mem_bytes - 1)];
    vu->stats.xgkick_bytes += bytes;
    if (vu->gif_sink) vu->gif_sink(vu->gif_user, buf, bytes, addr);
}

/* ------------------------------------------------------------ upper */

typedef struct up_out {
    uint8_t reg, mask, to_acc;
    vu_vec v;
} up_out;

static uint32_t operand_t(const vu_state *vu, const vu_upper *u, const vu_vec *ft, int c)
{
    switch (u->src) {
    case VU_SRC_BC: return ft->u[u->bc];
    case VU_SRC_Q: return vu->q;
    case VU_SRC_I: return vu->i;
    default: return ft->u[c];
    }
}

/* MAC layout: O 15..12 | U 11..8 | S 7..4 | Z 3..0, x in the high bit of each
 * nibble: lane c's Z/S/U/O condition bits, spread for x, then >> c */
static const uint16_t mac_spread[16] = {
#define MS(v) (((v) & C_Z ? 0x0008u : 0) | ((v) & C_S ? 0x0080u : 0) | \
               ((v) & C_U ? 0x0800u : 0) | ((v) & C_O ? 0x8000u : 0))
    MS(0), MS(1), MS(2), MS(3), MS(4), MS(5), MS(6), MS(7),
    MS(8), MS(9), MS(10), MS(11), MS(12), MS(13), MS(14), MS(15)
#undef MS
};

static VU_ALWAYS_INLINE void exec_upper(vu_state *vu, const vu_upper *u, uint64_t issue, up_out *o)
{
    /* nothing writes VF before the upper's results land: read in place */
    const vu_vec *fs = &vu->vf[u->fs], *ft = &vu->vf[u->ft];
    /* results straight into o->v (no 16-byte copy of four 4-byte stores) */
    uint32_t *r = o->v.u;
    uint32_t mac = 0;
    int c, fmac = 0;
    o->reg = 0;
    o->mask = 0;
    o->to_acc = 0;
    r[0] = r[1] = r[2] = r[3] = 0;
    if (u->src == VU_SRC_Q && vu->q_busy) vu->stats.q_early_reads++;

    switch (u->kind) {
    case VU_U_ADD: case VU_U_SUB: case VU_U_MUL: case VU_U_MADD: case VU_U_MSUB: {
        /* one loop per kind; operand t per lane from src (operand_t) */
        uint32_t tb = u->src == VU_SRC_BC ? ft->u[u->bc] : u->src == VU_SRC_Q ? vu->q : vu->i;
        double dtb = vuf_to_d(tb);
        int vec = u->src == VU_SRC_VF;
        unsigned dest = u->dest;
        fmac = 1;
        /* EXPR sees a = fs lane as a double (da) and the operand (dt) */
#define FMAC_LANES(EXPR)                                \
        for (c = 0; c < 4; c++) {                       \
            unsigned cond, pc;                          \
            double da, dt;                              \
            if (!(dest & (8u >> c))) continue;          \
            da = vuf_to_d(fs->u[c]);                    \
            dt = vec ? vuf_to_d(ft->u[c]) : dtb;        \
            EXPR;                                       \
            (void)pc;                                   \
            mac |= mac_spread[cond & 15] >> c;          \
        }
        switch (u->kind) {
        case VU_U_ADD: FMAC_LANES(r[c] = vuf_from_d(da + dt, &cond)) break;
        case VU_U_SUB: FMAC_LANES(r[c] = vuf_from_d(da - dt, &cond)) break;
        case VU_U_MUL: FMAC_LANES(r[c] = vuf_from_d(da * dt, &cond)) break;
        case VU_U_MADD:
            FMAC_LANES(r[c] = vuf_add(vu->acc.u[c], vuf_from_d(da * dt, &pc), &cond); cond |= pc & C_O)
            break;
        default:
            FMAC_LANES(r[c] = vuf_sub(vu->acc.u[c], vuf_from_d(da * dt, &pc), &cond); cond |= pc & C_O)
            break;
        }
#undef FMAC_LANES
        o->to_acc = u->to_acc;
        o->reg = u->to_acc ? 0 : u->fd;
        o->mask = u->dest;
        break;
    }
    case VU_U_OPMULA: case VU_U_OPMSUB: {
        static const int a1[3] = {1, 2, 0}, b1[3] = {2, 0, 1};
        fmac = 1;
        for (c = 0; c < 3; c++) {
            unsigned cond = 0, pc = 0;
            uint32_t pr;
            if (!(u->dest & (8u >> c))) continue;
            pr = vuf_mul(fs->u[a1[c]], ft->u[b1[c]], &pc);
            if (u->kind == VU_U_OPMULA) r[c] = pr, cond = pc;
            else r[c] = vuf_sub(vu->acc.u[c], pr, &cond), cond |= pc & C_O;
            mac |= mac_spread[cond & 15] >> c;
        }
        o->to_acc = u->kind == VU_U_OPMULA;
        o->reg = o->to_acc ? 0 : u->fd;
        o->mask = u->dest & 0xE;
        break;
    }
    case VU_U_MAX: case VU_U_MINI:
        for (c = 0; c < 4; c++) {
            uint32_t a = fs->u[c], t = operand_t(vu, u, ft, c);
            int cmp = vuf_cmp(a, t);
            if (u->kind == VU_U_MAX) r[c] = cmp >= 0 ? a : t;
            else r[c] = cmp <= 0 ? a : t;
        }
        o->reg = u->fd;
        o->mask = u->dest;
        break;
    case VU_U_ITOF: case VU_U_FTOI: case VU_U_ABS:
        for (c = 0; c < 4; c++) {
            uint32_t a = fs->u[c];
            if (u->kind == VU_U_ITOF) r[c] = vuf_itof(a, u->frac);
            else if (u->kind == VU_U_FTOI) r[c] = vuf_ftoi(a, u->frac);
            else r[c] = a & 0x7FFFFFFFu;
        }
        o->reg = u->ft;
        o->mask = u->dest;
        break;
    case VU_U_CLIP:
        push_event(vu, issue + VU_LAT_FMAC, 2, vuf_clip(fs->u, ft->u[3]));
        break;
    default: break;
    }
    if (fmac) push_event(vu, issue + VU_LAT_FMAC, 1, mac);
}

/* ------------------------------------------------------------ lower */

static void set_vi(vu_state *vu, int r, uint32_t v)
{
    if (r > 0 && r < 16) vu->vi[r] = (uint16_t)v;
}

static void write_vf(vu_state *vu, unsigned reg, unsigned dest, const uint32_t v[4])
{
    int c;
    if (!reg) return;
    for (c = 0; c < 4; c++)
        if (dest & (8u >> c)) vu->vf[reg].u[c] = v[c];
}

static uint32_t efu_latency(int op);
uint32_t vu__efu_latency(int op) { return efu_latency(op); }

static uint32_t efu_latency(int op)
{
    switch (op) {
    case VU_L_ESADD: return 11;
    case VU_L_ERSADD: return 18;
    case VU_L_ELENG: return 18;
    case VU_L_ERLENG: return 24;
    case VU_L_EATANxy: case VU_L_EATANxz: case VU_L_EATAN: return 54;
    case VU_L_ESUM: return 12;
    case VU_L_ESQRT: return 12;
    case VU_L_ERSQRT: return 18;
    case VU_L_ERCPR: return 12;
    case VU_L_ESIN: return 29;
    case VU_L_EEXP: return 44;
    default: return 1;
    }
}

static uint32_t efu_value(const vu_state *vu, const vu_lower *l)
{
    return vu_efu(l->op, vu->vf[l->fs].u, l->fsf);
}

static int branch_vi(vu_state *vu, int r, int quirk)
{
    if (quirk && r == vu->prev_vi_write) {
        /* r as it was at the start of the pair 4 before this one: the
         * oldest logged write to r in the last 4 pairs undone */
        int k;
        vu->stats.int_branch_quirks++;
        for (k = 3; k >= 0; k--)
            if (vu->vih_reg[(vu->vih_pos + k) & 3] == r) return (int16_t)vu->vih_old[(vu->vih_pos + k) & 3];
        return (int16_t)vu->vi[r];
    }
    return (int16_t)vu->vi[r];
}

/* returns 1 if a branch is taken; target in *tgt */
static VU_ALWAYS_INLINE int exec_lower(vu_state *vu, const vu_lower *l, uint32_t pc, uint64_t issue,
                      int quirk_ok, uint32_t *tgt)
{
    uint32_t v[4], fl;
    uint32_t cmask = vu->code_bytes - 1;
    int c;
    switch (l->op) {
    case VU_L_NOP: case VU_L_INVALID: break;
    case VU_L_LOI: vu->i = (uint32_t)l->imm; break;
    case VU_L_LQ:
        mem_read(vu, (uint32_t)(vu->vi[l->fs] + l->imm), v);
        write_vf(vu, l->ft, l->dest, v);
        break;
    case VU_L_SQ:
        mem_write(vu, (uint32_t)(vu->vi[l->ft] + l->imm), vu->vf[l->fs].u, l->dest);
        break;
    case VU_L_LQI:
        mem_read(vu, vu->vi[l->fs], v);
        write_vf(vu, l->ft, l->dest, v);
        set_vi(vu, l->fs, vu->vi[l->fs] + 1u);
        break;
    case VU_L_LQD:
        set_vi(vu, l->fs, vu->vi[l->fs] - 1u);
        mem_read(vu, vu->vi[l->fs], v);
        write_vf(vu, l->ft, l->dest, v);
        break;
    case VU_L_SQI:
        mem_write(vu, vu->vi[l->ft], vu->vf[l->fs].u, l->dest);
        set_vi(vu, l->ft, vu->vi[l->ft] + 1u);
        break;
    case VU_L_SQD:
        set_vi(vu, l->ft, vu->vi[l->ft] - 1u);
        mem_write(vu, vu->vi[l->ft], vu->vf[l->fs].u, l->dest);
        break;
    case VU_L_ILW: case VU_L_ILWR: {
        uint32_t qa = vu->vi[l->fs] + (l->op == VU_L_ILW ? (uint32_t)l->imm : 0);
        mem_read(vu, qa, v);
        for (c = 0; c < 4; c++)
            if (l->dest & (8u >> c)) break;
        set_vi(vu, l->ft, c < 4 ? v[c] : 0);
        break;
    }
    case VU_L_ISW: case VU_L_ISWR: {
        uint32_t qa = vu->vi[l->fs] + (l->op == VU_L_ISW ? (uint32_t)l->imm : 0);
        v[0] = v[1] = v[2] = v[3] = vu->vi[l->ft];
        mem_write(vu, qa, v, l->dest);
        break;
    }
    case VU_L_IADDIU: set_vi(vu, l->ft, vu->vi[l->fs] + (uint32_t)l->imm); break;
    case VU_L_ISUBIU: set_vi(vu, l->ft, vu->vi[l->fs] - (uint32_t)l->imm); break;
    case VU_L_IADDI: set_vi(vu, l->ft, vu->vi[l->fs] + (uint32_t)l->imm); break;
    case VU_L_IADD: set_vi(vu, l->fd, (uint32_t)vu->vi[l->fs] + vu->vi[l->ft]); break;
    case VU_L_ISUB: set_vi(vu, l->fd, (uint32_t)vu->vi[l->fs] - vu->vi[l->ft]); break;
    case VU_L_IAND: set_vi(vu, l->fd, (uint32_t)vu->vi[l->fs] & vu->vi[l->ft]); break;
    case VU_L_IOR: set_vi(vu, l->fd, (uint32_t)vu->vi[l->fs] | vu->vi[l->ft]); break;
    case VU_L_FCEQ: set_vi(vu, 1, vu->clip == (uint32_t)l->imm); break;
    case VU_L_FCSET: vu->clip = (uint32_t)l->imm & 0xFFFFFFu; break;
    case VU_L_FCAND: set_vi(vu, 1, (vu->clip & (uint32_t)l->imm) != 0); break;
    case VU_L_FCOR: set_vi(vu, 1, ((vu->clip | (uint32_t)l->imm) & 0xFFFFFFu) == 0xFFFFFFu); break;
    case VU_L_FCGET: set_vi(vu, l->ft, vu->clip & 0xFFF); break;
    case VU_L_FSEQ: set_vi(vu, l->ft, (vu->status & 0xFFF) == (uint32_t)l->imm); break;
    case VU_L_FSSET: vu->status = (vu->status & 0x3Fu) | ((uint32_t)l->imm & 0xFC0u); break;
    case VU_L_FSAND: set_vi(vu, l->ft, vu->status & (uint32_t)l->imm & 0xFFF); break;
    case VU_L_FSOR: set_vi(vu, l->ft, (vu->status | (uint32_t)l->imm) & 0xFFF); break;
    case VU_L_FMEQ: set_vi(vu, l->ft, vu->mac == vu->vi[l->fs]); break;
    case VU_L_FMAND: set_vi(vu, l->ft, vu->mac & vu->vi[l->fs]); break;
    case VU_L_FMOR: set_vi(vu, l->ft, vu->mac | vu->vi[l->fs]); break;
    case VU_L_B:
        *tgt = (pc + 8 + (uint32_t)l->imm * 8) & cmask;
        return 1;
    case VU_L_BAL:
        *tgt = (pc + 8 + (uint32_t)l->imm * 8) & cmask;
        set_vi(vu, l->ft, (pc + 16) / 8);
        return 1;
    case VU_L_JR:
        *tgt = ((uint32_t)vu->vi[l->fs] * 8) & cmask;
        return 1;
    case VU_L_JALR:
        *tgt = ((uint32_t)vu->vi[l->fs] * 8) & cmask;
        set_vi(vu, l->ft, (pc + 16) / 8);
        return 1;
    case VU_L_IBEQ: case VU_L_IBNE: case VU_L_IBLTZ: case VU_L_IBGTZ:
    case VU_L_IBLEZ: case VU_L_IBGEZ: {
        int s = branch_vi(vu, l->fs, quirk_ok), t = 0, take = 0;
        if (l->op == VU_L_IBEQ || l->op == VU_L_IBNE) t = branch_vi(vu, l->ft, quirk_ok);
        switch (l->op) {
        case VU_L_IBEQ: take = (uint16_t)s == (uint16_t)t; break;
        case VU_L_IBNE: take = (uint16_t)s != (uint16_t)t; break;
        case VU_L_IBLTZ: take = s < 0; break;
        case VU_L_IBGTZ: take = s > 0; break;
        case VU_L_IBLEZ: take = s <= 0; break;
        default: take = s >= 0; break;
        }
        *tgt = (pc + 8 + (uint32_t)l->imm * 8) & cmask;
        return take;
    }
    case VU_L_MOVE: write_vf(vu, l->ft, l->dest, vu->vf[l->fs].u); break;
    case VU_L_MR32: {
        const uint32_t *s = vu->vf[l->fs].u;
        v[0] = s[1]; v[1] = s[2]; v[2] = s[3]; v[3] = s[0];
        write_vf(vu, l->ft, l->dest, v);
        break;
    }
    case VU_L_DIV: case VU_L_SQRT: case VU_L_RSQRT:
        vu->q_next = vu_fdiv(l->op, vu->vf[l->fs].u[l->fsf], vu->vf[l->ft].u[l->ftf], &fl);
        vu->q_next_flags = fl;
        vu->q_done = issue + (l->op == VU_L_RSQRT ? VU_LAT_RSQRT : VU_LAT_DIV);
        vu->q_busy = 1;
        break;
    case VU_L_WAITQ: break; /* the stall already happened at issue */
    case VU_L_MTIR: set_vi(vu, l->ft, vu->vf[l->fs].u[l->fsf] & 0xFFFF); break;
    case VU_L_MFIR:
        v[0] = v[1] = v[2] = v[3] = (uint32_t)(int32_t)(int16_t)vu->vi[l->fs];
        write_vf(vu, l->ft, l->dest, v);
        break;
    case VU_L_RNEXT: {
        uint32_t r = vu->r, bit = ((r >> 4) ^ (r >> 22)) & 1;
        vu->r = 0x3F800000u | (((r << 1) | bit) & 0x7FFFFFu);
    }   /* fall through */
    case VU_L_RGET:
        v[0] = v[1] = v[2] = v[3] = vu->r;
        write_vf(vu, l->ft, l->dest, v);
        break;
    case VU_L_RINIT: vu->r = 0x3F800000u | (vu->vf[l->fs].u[l->fsf] & 0x7FFFFFu); break;
    case VU_L_RXOR: vu->r = 0x3F800000u | ((vu->r ^ vu->vf[l->fs].u[l->fsf]) & 0x7FFFFFu); break;
    case VU_L_MFP:
        v[0] = v[1] = v[2] = v[3] = vu->p;
        write_vf(vu, l->ft, l->dest, v);
        break;
    case VU_L_XTOP: set_vi(vu, l->ft, vu->top & 0x3FF); break;
    case VU_L_XITOP: set_vi(vu, l->ft, vu->itop & (vu->id ? 0x3FF : 0xFF)); break;
    case VU_L_XGKICK: xgkick(vu, vu->vi[l->fs]); break;
    case VU_L_WAITP: break;
    default: /* EFU */
        vu->p_next = efu_value(vu, l);
        vu->p_done = issue + efu_latency(l->op);
        vu->p_busy = 1;
        break;
    }
    return 0;
}

/* ------------------------------------------------------------ step / run */


static VU_ALWAYS_INLINE vu_stop step_pair(vu_state *vu)
{
    uint32_t pc, next, tgt = 0;
    dc_entry *e;
    const vu_pair *p;
    uint64_t issue;
    up_out uo;
    int taken, k, quirk_ok;
    int cur_vi_write, vi_w;
    uint16_t vi_old;

    if (!vu->running) return VU_STOP_IDLE;
    pc = vu->pc & (vu->code_bytes - 1) & ~7u;
    e = dc_get(vu, pc);
    p = &e->p;

    /* ---- issue cycle: interlocks on VF, FDIV, EFU ---- */
    issue = vu->cycle;
    {   /* stall_on for the upper and the lower reads */
        const uint64_t *rdy = &vu->vf_ready[0][0];
        unsigned k;
        for (k = 0; k < e->n_rd; k++)
            if (rdy[e->rd[k]] > issue) issue = rdy[e->rd[k]];
    }
    if (e->writes_q && vu->q_busy && vu->q_done > issue) issue = vu->q_done;
    if (e->writes_p && vu->p_busy && vu->p_done > issue) issue = vu->p_done;
    vu->stats.stall_cycles += issue - vu->cycle;
    if (vu->fq_n || vu->q_busy || vu->p_busy) commit_events(vu, issue);

    quirk_ok = vu->int_branch_quirk && issue == vu->cycle && vu->prev_vi_write > 0;

    /* ---- execute: upper reads first, lower runs, upper writes land last ---- */
    exec_upper(vu, &p->up, issue, &uo);
    vi_w = e->vi_w > 0 && e->vi_w < 16 ? e->vi_w : -1;
    vi_old = vi_w > 0 ? vu->vi[vi_w] : 0;
    taken = exec_lower(vu, &p->lo, pc, issue, quirk_ok, &tgt);
    /* VI history: this pair's write, logged after the lower read the
     * history (it covers the 4 pairs before this one) */
    vu->vih_pos = (vu->vih_pos - 1) & 3;
    vu->vih_reg[vu->vih_pos] = (int8_t)vi_w;
    vu->vih_old[vu->vih_pos] = vi_old;
    if (uo.to_acc) {
        for (k = 0; k < 4; k++)
            if (uo.mask & (8u >> k)) vu->acc.u[k] = uo.v.u[k];
    } else if (uo.reg) {
        write_vf(vu, uo.reg, uo.mask, uo.v.u);
    }
    {   /* mark_ready for the upper's and the lower's VF writes */
        uint64_t *rdy = &vu->vf_ready[0][0], t = issue + VU_LAT_FMAC;
        unsigned k;
        for (k = 0; k < e->n_wr; k++) rdy[e->wr[k]] = t;
    }

    /* Only integer ALU / load results feed the branch quirk.  Flag reads
     * (FC*, FS*, FM*) do not: the retail microcode branches on them in the
     * very next pair 67 times, while it always leaves a gap after IADD &co. */
    cur_vi_write = (e->is_branch || (p->lo.op >= VU_L_FCEQ && p->lo.op <= VU_L_FCGET)) ? -1 : e->vi_w;
    vu->prev_vi_write = cur_vi_write;
    vu->cycle = issue + 1;
    vu->stats.cycles = vu->cycle;
    vu->stats.pairs++;

    /* ---- sequencing ---- */
    next = (pc + 8) & (vu->code_bytes - 1);
    if (vu->branch_pending) {
        next = vu->branch_target;
        vu->branch_pending = 0;
    }
    if (taken) {
        vu->branch_pending = 1;
        vu->branch_target = tgt;
    }
    vu->pc = next;

    if (vu->ebit_pending) {
        vu->ebit_pending = 0;
        vu->running = 0;
        vu->tpc = next;
        vu->branch_pending = 0;
        vu_drain(vu);
        return VU_STOP_EBIT;
    }
    if (p->up.bits & VU_B_E) vu->ebit_pending = 1;
    if ((p->up.bits & (VU_B_D | VU_B_T)) && vu->break_on_dt) return VU_STOP_DBIT;
    return VU_STOP_CYCLES;
}

vu_stop vu_step(vu_state *vu) { return step_pair(vu); }
vu_stop vu__step(vu_state *vu) { return step_pair(vu); }

vu_stop vu_run(vu_state *vu, uint64_t max_cycles)
{
    uint64_t start = vu->cycle;
    if (!vu->running) return VU_STOP_IDLE;
    if (vu->stats_print) vu__stats_tick(vu);
    /* VU1: translated blocks (vu_block.c), which fall back to step_pair
     * whenever a static assumption does not hold */
    if (vu->blocks && vu->id == 1) return vu__block_run(vu, max_cycles);
    for (;;) {
        vu_stop s = step_pair(vu);
        if (s != VU_STOP_CYCLES) return s;
        if (max_cycles && vu->cycle - start >= max_cycles) return VU_STOP_CYCLES;
    }
}

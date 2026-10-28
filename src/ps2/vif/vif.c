/* SPDX-License-Identifier: CC0-1.0 */
/* VIF0/VIF1 command processor.  Written from the public EE/VIF descriptions;
 * no emulator code was copied.  docs/VU.md lists the rules and the places
 * where hardware behaviour is undocumented and a choice was made. */
#include "vif.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#else
#include <time.h>
#endif

/* ---- microprogram census (measurement; docs/PERF-3D.md "VU1 microprograms") ----
 * Between vif_census_begin and vif_census_dump every MSCAL / MSCNT is counted
 * by (VU, start address, hash of the 16 pairs there: the program as loaded)
 * with its pairs, VU cycles and host time. */
typedef struct vcen {
    uint32_t vu, pc, hash;
    uint64_t calls, pairs, cycles;
    double ms;
} vcen;
enum { VCEN_MAX = 1024 };
static vcen *g_vcen;
static int g_nvcen, g_vcen_on;

static double vcen_now_ms(void)
{
#ifdef _WIN32
    static LARGE_INTEGER f;
    LARGE_INTEGER c;
    if (!f.QuadPart) QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart * 1000.0 / (double)f.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1.0e6;
#endif
}

void vif_census_begin(void)
{
    if (!g_vcen) g_vcen = (vcen *)calloc(VCEN_MAX, sizeof *g_vcen);
    g_nvcen = 0;
    g_vcen_on = g_vcen != NULL;
}

int vif_census_dump(const char *path)
{
    FILE *f = fopen(path, "w");
    g_vcen_on = 0;
    if (!f) return -1;
    fprintf(f, "# vu\tpc\thash\tcalls\tpairs\tvu_cycles\thost_ms\n");
    for (int i = 0; i < g_nvcen; i++)
        fprintf(f, "%u\t0x%04X\t%08X\t%llu\t%llu\t%llu\t%.3f\n", g_vcen[i].vu, g_vcen[i].pc, g_vcen[i].hash,
                (unsigned long long)g_vcen[i].calls, (unsigned long long)g_vcen[i].pairs,
                (unsigned long long)g_vcen[i].cycles, g_vcen[i].ms);
    fclose(f);
    return 0;
}

static void vcen_add(const vu_state *vu, uint32_t pc, uint64_t pairs, uint64_t cycles, double ms)
{
    uint32_t h = 2166136261u, k;
    for (k = 0; k < 128; k++) h = (h ^ vu->code[(pc + k) & (vu->code_bytes - 1)]) * 16777619u;
    for (k = 0; k < (uint32_t)g_nvcen; k++)
        if (g_vcen[k].vu == (uint32_t)vu->id && g_vcen[k].pc == pc && g_vcen[k].hash == h) break;
    if (k == (uint32_t)g_nvcen) {
        if (g_nvcen == VCEN_MAX) return;
        g_vcen[k].vu = (uint32_t)vu->id;
        g_vcen[k].pc = pc;
        g_vcen[k].hash = h;
        g_nvcen++;
    }
    g_vcen[k].calls++;
    g_vcen[k].pairs += pairs;
    g_vcen[k].cycles += cycles;
    g_vcen[k].ms += ms;
}

void vif_init(vif_state *v, int id, vu_state *vu)
{
    memset(v, 0, sizeof *v);
    v->id = id;
    v->vu = vu;
    v->vu_cycle_budget = 1000000;
    vif_reset(v);
}

void vif_free(vif_state *v)
{
    free(v->buf);
    v->buf = NULL;
    v->cap = 0;
}

void vif_reset(vif_state *v)
{
    v->cl = v->wl = 1;
    v->mode = v->mask = 0;
    memset(v->row, 0, sizeof v->row);
    memset(v->col, 0, sizeof v->col);
    v->mark = v->code = v->num = 0;
    v->base = v->ofst = v->tops = v->itops = v->top = v->itop = v->dbf = 0;
    v->mskpath3 = 0;
    v->irq = 0;
    v->have_cmd = 0;
    v->need = v->got = 0;
    v->ahead = NULL;
    v->ahead_n = 0;
    v->wpend = 0;
}

int vif_idle(const vif_state *v) { return !v->have_cmd; }

/* ---- UNPACK geometry ---- */

static uint32_t unpack_bits(uint32_t cmd)
{
    uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3;
    if (vl == 3) return vn == 3 ? 16 : 0; /* only V4-5 exists */
    return (32u >> vl) * (vn + 1);
}

static uint32_t unpack_elems(uint32_t num, uint32_t cl, uint32_t wl)
{
    if (wl == 0) wl = 1; /* undefined on hardware; avoid dividing by zero */
    if (cl >= wl) return num;
    return (num / wl) * cl + ((num % wl) < cl ? (num % wl) : cl);
}

long vif_payload_words(uint32_t code, uint32_t cl, uint32_t wl)
{
    uint32_t cmd = (code >> 24) & 0x7F;
    uint32_t num = (code >> 16) & 0xFF;
    uint32_t imm = code & 0xFFFF;
    if (cmd >= 0x60) {
        uint32_t bits = unpack_bits(cmd);
        if (!bits) return -1;
        if (!num) num = 256;
        return (long)((unpack_elems(num, cl, wl) * bits + 31) / 32);
    }
    switch (cmd) {
    case VIF_NOP: case VIF_STCYCL: case VIF_OFFSET: case VIF_BASE: case VIF_ITOP:
    case VIF_STMOD: case VIF_MSKPATH3: case VIF_MARK: case VIF_FLUSHE: case VIF_FLUSH:
    case VIF_FLUSHA: case VIF_MSCAL: case VIF_MSCALF: case VIF_MSCNT:
        return 0;
    case VIF_STMASK: return 1;
    case VIF_STROW: case VIF_STCOL: return 4;
    case VIF_MPG: return (long)((num ? num : 256) * 2);
    case VIF_DIRECT: case VIF_DIRECTHL: return (long)((imm ? imm : 65536) * 4);
    default: return -1;
    }
}

static uint32_t extend(uint32_t raw, uint32_t vl, int usn)
{
    if (vl == 1 && !usn && (raw & 0x8000)) raw |= 0xFFFF0000u;
    if (vl == 2 && !usn && (raw & 0x80)) raw |= 0xFFFFFF00u;
    return raw;
}

/* W lane of V3 element e (docs/VU.md "V3 W lane", measured against PCSX2
 * captures, docs/VALIDATION.md section 5):
 *   V3-32  the next 32-bit word of the stream (extrapolated, not measured);
 *   V3-16  the next 16-bit value of the stream: the following element's X,
 *          the padding halfword, or (past the payload) the low half of the
 *          next stream word, normally the next VIF code; except elements
 *          with e % 16 == 7 or 9, whose W is 0;
 *   V3-8   element 0: the next byte (the padding byte when NUM = 1); every
 *          other element: 0.
 * Returns 1 when the value lies past the payload and the next stream word has
 * not arrived yet (the caller defers the W lane), else 0 with *w set. */
static int v3_w(const vif_state *v, const uint8_t *b, uint32_t paybytes, uint32_t vl, int usn,
                uint32_t e, uint32_t *w)
{
    uint32_t sz = 4u >> vl, off = (e * 3 + 3) * sz, raw = 0, k;
    if ((vl == 1 && (e % 16 == 7 || e % 16 == 9)) || (vl == 2 && e != 0)) {
        *w = 0;
        return 0;
    }
    for (k = 0; k < sz; k++) {
        uint32_t o = off + k, byte;
        if (o < paybytes) {
            byte = b[o];
        } else {
            /* the payload ends on a word boundary, so W never straddles it */
            uint32_t a = o - paybytes;
            if (a / 4 >= v->ahead_n) return 1;
            byte = (v->ahead[a / 4] >> ((a & 3) * 8)) & 0xFF;
        }
        raw |= byte << (k * 8);
    }
    *w = extend(raw, vl, usn);
    return 0;
}

/* fetch element e (0-based) of the payload as up to 4 32-bit components;
 * returns 1 if a V3 W lane must wait for the next stream word */
static int unpack_elem(const vif_state *v, const uint32_t *pay, uint32_t paybytes, uint32_t cmd, int usn,
                       uint32_t e, uint32_t out[4])
{
    uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3;
    uint32_t n = vn + 1, c;
    const uint8_t *b = (const uint8_t *)pay;
    if (vl == 3) { /* V4-5: RGBA 5:5:5:1 in one halfword */
        uint32_t h = (uint32_t)b[e * 2] | ((uint32_t)b[e * 2 + 1] << 8);
        out[0] = (h & 0x1F) << 3;
        out[1] = ((h >> 5) & 0x1F) << 3;
        out[2] = ((h >> 10) & 0x1F) << 3;
        out[3] = ((h >> 15) & 1) << 7;
        return 0;
    }
    for (c = 0; c < n; c++) {
        uint32_t idx = e * n + c, val;
        if (vl == 0) {
            memcpy(&val, b + idx * 4, 4);
        } else if (vl == 1) {
            val = extend((uint32_t)b[idx * 2] | ((uint32_t)b[idx * 2 + 1] << 8), vl, usn);
        } else {
            val = extend(b[idx], vl, usn);
        }
        out[c] = val;
    }
    /* components the format does not supply (see docs/VU.md) */
    switch (vn) {
    case 0: out[1] = out[2] = out[3] = out[0]; break;  /* S: broadcast */
    case 1: out[2] = out[0]; out[3] = out[1]; break;   /* V2: x y x y */
    case 2: return v3_w(v, b, paybytes, vl, usn, e, &out[3]);
    default: break;
    }
    return 0;
}

static uint32_t mask_field(const vif_state *v, int masked, uint32_t cyc, uint32_t c)
{
    return masked ? (v->mask >> (((cyc > 3 ? 3 : cyc) * 8) + c * 2)) & 3 : 0;
}

/* a data value for lane c after STMOD (offset / difference) */
static uint32_t mode_value(vif_state *v, uint32_t c, uint32_t val)
{
    if (v->mode == 1) val += v->row[c];
    else if (v->mode == 2) { v->row[c] += val; val = v->row[c]; }
    return val;
}

/* the next stream word arrived: write the deferred V3 W lanes */
static void v3w_resolve(vif_state *v, uint32_t next)
{
    uint32_t qmask = (v->vu->mem_bytes / 16) - 1, j;
    uint32_t raw = v->wpend_vl == 0 ? next : v->wpend_vl == 1 ? (next & 0xFFFF) : (next & 0xFF);
    uint32_t w = extend(raw, v->wpend_vl, (int)v->wpend_usn);
    v->wpend = 0;
    for (j = 0; j < v->wpend_n; j++) {
        uint32_t val;
        if (mask_field(v, (int)v->wpend_masked, v->wpend_cyc + j, 3) != 0) continue; /* not a data lane */
        val = mode_value(v, 3, w);
        memcpy(v->vu->mem + ((v->wpend_qa + j) & qmask) * 16 + 12, &val, 4);
    }
}

static void do_unpack(vif_state *v, uint32_t code, const uint32_t *pay)
{
    uint32_t cmd = (code >> 24) & 0x7F;
    uint32_t num = (code >> 16) & 0xFF;
    uint32_t imm = code & 0xFFFF;
    int masked = (cmd >> 4) & 1;
    int usn = (imm >> 14) & 1;
    uint32_t qmask = (v->vu->mem_bytes / 16) - 1;
    uint32_t addr = imm & (v->id ? 0x3FF : 0xFF);
    uint32_t cl = v->cl, wl = v->wl ? v->wl : 1, i, e = 0;
    uint32_t data[4] = {0, 0, 0, 0};
    uint32_t paybytes = (uint32_t)vif_payload_words(code, v->cl, v->wl) * 4u;
    int pend = 0;
    if (v->id && (imm & 0x8000)) addr += v->tops;
    if (!num) num = 256;

    for (i = 0; i < num; i++) {
        uint32_t cyc, qa, c;
        int fill;
        uint8_t *dst;
        if (cl >= wl) {
            cyc = i % wl;
            qa = addr + (i / wl) * cl + cyc;
            fill = 0;
        } else {
            cyc = i % wl;
            qa = addr + i;
            fill = cyc >= cl;
        }
        if (!fill) pend = unpack_elem(v, pay, paybytes, cmd, usn, e++, data);
        /* a filling cycle re-writes the last element read (undocumented) */
        dst = v->vu->mem + (qa & qmask) * 16;
        for (c = 0; c < 4; c++) {
            uint32_t m = mask_field(v, masked, cyc, c);
            uint32_t val;
            switch (m) {
            case 0:
                if (c == 3 && pend) {
                    /* V3 W past the payload: wait for the next stream word.
                     * Only the last element can be pending, so its qwords
                     * (fill cycles included) are consecutive. */
                    if (!v->wpend) {
                        v->wpend = 1;
                        v->wpend_qa = qa & qmask;
                        v->wpend_cyc = cyc;
                        v->wpend_vl = cmd & 3;
                        v->wpend_usn = (uint32_t)usn;
                        v->wpend_masked = (uint32_t)masked;
                    }
                    v->wpend_n = (((qa & qmask) - v->wpend_qa) & qmask) + 1;
                    continue;
                }
                val = mode_value(v, c, data[c]);
                break;
            case 1: val = v->row[c]; break;
            case 2: val = v->col[cyc > 3 ? 3 : cyc]; break;
            default: continue; /* write-protected */
            }
            memcpy(dst + c * 4, &val, 4);
        }
        v->stats.unpack_qwords++;
    }
    v->num = 0;
}

static void start_vu(vif_state *v, uint32_t cmd, uint32_t imm)
{
    vu_state *vu = v->vu;
    vu_stop st;
    if (vu->running) {
        /* previous program never finished (runaway): hardware would stall forever */
        v->stats.vu_runaways++;
        vu->running = 0;
    }
    v->itop = v->itops;
    vu->itop = (uint16_t)v->itop;
    if (v->id) {
        v->top = v->tops;
        vu->top = (uint16_t)v->top;
        v->dbf ^= 1;
        v->tops = v->base + (v->dbf ? v->ofst : 0);
    }
    uint32_t cen_pc = cmd == VIF_MSCNT ? vu->tpc : imm * 8;
    uint64_t cen_pairs = vu->stats.pairs, cen_cyc = vu->stats.cycles;
    double cen_t = g_vcen_on ? vcen_now_ms() : 0.0;
    if (cmd == VIF_MSCNT) vu_continue(vu);
    else vu_start(vu, imm * 8);
    v->stats.mscal++;
    st = vu_run(vu, v->vu_cycle_budget);
    if (g_vcen_on)
        vcen_add(vu, cen_pc & (vu->code_bytes - 1), vu->stats.pairs - cen_pairs, vu->stats.cycles - cen_cyc,
                 vcen_now_ms() - cen_t);
    if (st == VU_STOP_CYCLES) {
        v->stats.vu_runaways++;
        snprintf(v->error, sizeof v->error, "VU%d program at 0x%x exceeded %llu cycles",
                 vu->id, imm * 8, (unsigned long long)v->vu_cycle_budget);
        vu->running = 0;
    }
}

static void exec_cmd(vif_state *v, uint32_t code, const uint32_t *pay)
{
    uint32_t cmd = (code >> 24) & 0x7F;
    uint32_t imm = code & 0xFFFF;
    uint32_t num = (code >> 16) & 0xFF;
    v->code = code;
    v->stats.cmds[cmd]++;
    if (cmd >= 0x60) {
        do_unpack(v, code, pay);
        goto done;
    }
    switch (cmd) {
    case VIF_NOP: break;
    case VIF_STCYCL: v->cl = imm & 0xFF; v->wl = (imm >> 8) & 0xFF; break;
    case VIF_OFFSET:
        if (!v->id) goto invalid;
        v->ofst = imm & 0x3FF; v->dbf = 0; v->tops = v->base; break;
    case VIF_BASE:
        if (!v->id) goto invalid;
        v->base = imm & 0x3FF; break;
    case VIF_ITOP: v->itops = imm & 0x3FF; break;
    case VIF_STMOD: v->mode = imm & 3; break;
    case VIF_MSKPATH3:
        if (!v->id) goto invalid;
        v->mskpath3 = (imm >> 15) & 1; break;
    case VIF_MARK: v->mark = imm; break;
    case VIF_FLUSHE: break;               /* VU always idle here (synchronous model) */
    case VIF_FLUSH: case VIF_FLUSHA:
        if (!v->id) goto invalid;
        break;
    case VIF_MSCAL: case VIF_MSCALF: case VIF_MSCNT:
        start_vu(v, cmd, imm); break;
    case VIF_STMASK: v->mask = pay[0]; break;
    case VIF_STROW: memcpy(v->row, pay, 16); break;
    case VIF_STCOL: memcpy(v->col, pay, 16); break;
    case VIF_MPG: {
        uint32_t bytes = (num ? num : 256) * 8;
        uint32_t addr = (imm * 8) & (v->vu->code_bytes - 1);
        vu_load_code(v->vu, addr, pay, bytes);
        v->stats.mpg_bytes += bytes;
        if (v->mpg_hook) v->mpg_hook(v->mpg_user, addr, (const uint8_t *)pay, bytes);
        break;
    }
    case VIF_DIRECT: case VIF_DIRECTHL: {
        uint32_t bytes = (imm ? imm : 65536) * 16;
        if (!v->id) goto invalid;
        v->stats.direct_bytes += bytes;
        if (v->gif_sink) v->gif_sink(v->gif_user, (const uint8_t *)pay, bytes);
        break;
    }
    default:
    invalid:
        v->stats.invalid_cmds++;
        snprintf(v->error, sizeof v->error, "VIF%d invalid command 0x%08x", v->id, code);
        break;
    }
done:
    if (code & 0x80000000u) {
        v->irq = 1;
        if (v->irq_fn) v->irq_fn(v->irq_user, code);
    }
}

size_t vif_write(vif_state *v, const uint32_t *w, size_t n)
{
    size_t i = 0;
    if (v->wpend && n) v3w_resolve(v, w[0]);
    while (i < n) {
        if (!v->have_cmd) {
            uint32_t code = w[i++];
            long need = vif_payload_words(code, v->cl, v->wl);
            if (need < 0) need = 0; /* invalid: treated as a one-word NOP */
            v->code = code;
            v->have_cmd = 1;
            v->need = (uint32_t)need;
            v->got = 0;
            if (v->need > v->cap) {
                uint32_t c = v->need < 1024 ? 1024 : v->need;
                uint32_t *nb = (uint32_t *)realloc(v->buf, c * 4u);
                if (!nb) { snprintf(v->error, sizeof v->error, "out of memory"); return i; }
                v->buf = nb;
                v->cap = c;
            }
        } else {
            size_t take = v->need - v->got;
            if (take > n - i) take = n - i;
            memcpy(v->buf + v->got, w + i, take * 4);
            v->got += (uint32_t)take;
            i += take;
        }
        if (v->have_cmd && v->got == v->need) {
            v->have_cmd = 0;
            v->ahead = w + i;
            v->ahead_n = n - i;
            exec_cmd(v, v->code, v->buf);
            v->ahead = NULL;
            v->ahead_n = 0;
            if (v->irq && v->stall_on_irq) return i;
        }
    }
    /* a zero-payload command at the very end is executed in the loop above */
    return i;
}

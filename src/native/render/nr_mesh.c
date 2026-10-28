/* SPDX-License-Identifier: CC0-1.0 */
/* Native mesh cache: decode a model mesh's static VIF packet once
 * (nr_mesh.h, docs/NATIVE-RENDER.md "Mesh cache").
 *
 * The packet is what ModelEmitDrawPacketsMaybe CALLs after MSCAL 0x320: a DMA
 * chain (host-mode addresses = host pointers, i686) whose VIF stream is, per
 * batch, STCYCL 1,1 + UNPACKs with FLG (header V4-32 at TOP+0, then positions,
 * normals, UVs, colours, skin records) + MSCNT.  The UNPACK formats are
 * decoded like the VIF does (sign / zero extension to 32-bit lanes) into one
 * batch image, then converted to nr_vtx.  Anything else in the stream (other
 * commands, masks, cycle modes, MSCAL, MPG, DIRECT) marks the mesh `bad`: it
 * stays on the emulated path. */
#include "nr_mem.h"
#include "nr_mesh.h"
#include "nr_vu1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

static nr_mesh_stats g_st;
const nr_mesh_stats *nr_mesh_get_stats(void) { return &g_st; }

/* scratchpad / null / not readable memory / a poisoned (dead) packet: not a static packet (nr_mem.h) */
static const uint8_t *host(uint32_t a, uint32_t bytes)
{
    const uint8_t *p = nr_game_ptr(a, bytes ? bytes : 16);
    if (p && nr_poison_check(p, "nr_mesh", a)) return NULL;
    return p;
}

/* ---- DMA chain walk: calls blk(user, vifcodes, data, qwc) per tag ------- */
typedef int (*blk_fn)(void *user, const uint32_t *codes2, const uint8_t *data, uint32_t qwc);

static int walk(uint32_t pkt, blk_fn fn, void *user, uint32_t *bytes_out)
{
    uint32_t tadr = pkt, stack[2], sp = 0, tags = 0, bytes = 0;
    for (;;) {
        const uint8_t *t = host(tadr, 16);
        uint32_t lo, hi, qwc, id, codes[2];
        const uint8_t *data = NULL;
        if (!t || ++tags > 4096) return -1;
        lo = rd32(t); hi = rd32(t + 4); codes[0] = rd32(t + 8); codes[1] = rd32(t + 12);
        qwc = lo & 0xFFFF; id = (lo >> 28) & 7;
        bytes += 16 + qwc * 16;
        if (qwc && id != 0 && id != 3 && id != 4 && !nr_game_ptr(tadr, 16 + qwc * 16)) return -1;   /* inline payload */
        switch (id) {
        case 1: /* CNT */ data = t + 16; if (fn(user, codes, data, qwc)) return -1; tadr += 16 + qwc * 16; break;
        case 2: /* NEXT */ data = t + 16; if (fn(user, codes, data, qwc)) return -1; tadr = hi; break;
        case 3: case 4: /* REF / REFS */
            data = qwc ? host(hi, qwc * 16) : t;
            if (!data || fn(user, codes, qwc ? data : NULL, qwc)) return -1;
            tadr += 16; break;
        case 0: /* REFE */
            data = qwc ? host(hi, qwc * 16) : t;
            if (!data || fn(user, codes, qwc ? data : NULL, qwc)) return -1;
            if (bytes_out) *bytes_out = bytes;
            return 0;
        case 5: /* CALL */
            data = t + 16; if (fn(user, codes, data, qwc)) return -1;
            if (sp >= 2) return -1;
            stack[sp++] = tadr + 16 + qwc * 16; tadr = hi; break;
        case 6: /* RET */
            data = t + 16; if (fn(user, codes, data, qwc)) return -1;
            if (sp == 0) { if (bytes_out) *bytes_out = bytes; return 0; }
            tadr = stack[--sp]; break;
        default: /* END */
            data = t + 16; if (fn(user, codes, data, qwc)) return -1;
            if (bytes_out) *bytes_out = bytes;
            return 0;
        }
    }
}

/* ---- hashing (cache validation) ------------------------------------------ */
typedef struct hctx { uint32_t h; uint64_t n; } hctx;
static int hash_blk(void *user, const uint32_t *codes, const uint8_t *data, uint32_t qwc)
{
    hctx *c = (hctx *)user;
    uint32_t h = c->h, i;
    const uint8_t *cb = (const uint8_t *)codes;
    for (i = 0; i < 8; i++) h = (h ^ cb[i]) * 16777619u;
    if (data)
        for (i = 0; i < qwc * 16; i += 4) h = (h ^ rd32(data + i)) * 16777619u;
    c->h = h;
    c->n += 8 + qwc * 16;
    return 0;
}

/* sparse revalidation hash (docs "Mesh cache"): every DMA tag's VIF words
 * and size, the first qword of each block and one qword in 32 (the DMA tags
 * and batch headers change with any other mesh); the full hash is taken
 * only at decode */
static int shash_blk(void *user, const uint32_t *codes, const uint8_t *data, uint32_t qwc)
{
    hctx *c = (hctx *)user;
    uint32_t h = c->h, i;
    h = (h ^ codes[0]) * 16777619u;
    h = (h ^ codes[1]) * 16777619u;
    h = (h ^ qwc) * 16777619u;
    c->n += 8;
    if (data) {
        for (i = 0; i < qwc; i += (i == 0 ? 1 : 32)) {
            const uint8_t *q = data + i * 16;
            h = (h ^ rd32(q)) * 16777619u;
            h = (h ^ rd32(q + 4)) * 16777619u;
            h = (h ^ rd32(q + 8)) * 16777619u;
            h = (h ^ rd32(q + 12)) * 16777619u;
            c->n += 16;
        }
    }
    c->h = h;
    return 0;
}

/* ---- VIF stream decode ---------------------------------------------------- */
typedef struct dec {
    int skinned_variant;
    nr_mesh *m;
    /* VIF stream state: a command may straddle tag blocks */
    uint32_t cl, wl;
    uint32_t pend_cmd;        /* UNPACK/STMASK/STROW/... waiting for payload words */
    uint32_t pend_words, pend_got;
    uint32_t pay[1024 * 4 + 8];
    nr_qw img[1024];          /* the batch image (TOP-relative) */
    uint8_t wr[1024];         /* lanes (bit 0 x .. bit 3 w) the batch's UNPACKs wrote per qword */
    uint32_t cap_vtx, cap_idx;
    const char *err;
    nr_batch_cb on_batch;     /* tests: each batch image at its MSCNT */
    void *on_batch_user;
} dec;

static void fail(dec *d, const char *why) { if (!d->err) d->err = why; }

static long payload_words(uint32_t code, uint32_t cl, uint32_t wl)
{
    uint32_t cmd = (code >> 24) & 0x7F, num = (code >> 16) & 0xFF, imm = code & 0xFFFF;
    if (cmd == 0x20) return 1;
    if (cmd == 0x30 || cmd == 0x31) return 4;
    if (cmd == 0x4A) return (long)(num ? num : 256) * 2;
    if (cmd == 0x50 || cmd == 0x51) return (long)(imm ? imm : 65536) * 4;
    if (cmd >= 0x60) {
        uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3, n = num ? num : 256, bits, elems;
        bits = (32u >> vl) * (vn + 1);
        elems = wl <= cl ? n : cl * (n / wl) + (n % wl < cl ? n % wl : cl);
        return (long)((elems * bits + 31) / 32);
    }
    return 0;
}

static void push_vtx(dec *d, const nr_vtx *v)
{
    nr_mesh *m = d->m;
    if (m->nvtx == d->cap_vtx) {
        d->cap_vtx = d->cap_vtx ? d->cap_vtx * 2 : 256;
        m->vtx = (nr_vtx *)realloc(m->vtx, d->cap_vtx * sizeof(nr_vtx));
    }
    m->vtx[m->nvtx++] = *v;
}
static void push_tri(dec *d, uint32_t a, uint32_t b, uint32_t c)
{
    nr_mesh *m = d->m;
    if (m->nidx + 3 > d->cap_idx) {
        d->cap_idx = d->cap_idx ? d->cap_idx * 2 : 768;
        m->idx = (uint32_t *)realloc(m->idx, d->cap_idx * sizeof(uint32_t));
    }
    m->idx[m->nidx++] = a; m->idx[m->nidx++] = b; m->idx[m->nidx++] = c;
}

static int written(const dec *d, uint32_t a, uint32_t n)
{
    uint32_t i;
    for (i = 0; i < n; i++) if (!d->wr[a + i]) return 0;
    return 1;
}

static int fits16(int32_t v) { return v >= -32768 && v <= 32767; }
static int fits8s(int32_t v) { return v >= -128 && v <= 127; }
static int fits8u(int32_t v) { return v >= 0 && v <= 255; }
static int fits16s(int32_t v) { return v >= -32768 && v <= 32767; }

/* MSCNT: one batch in d->img -> vertices + triangles */
static void end_batch(dec *d)
{
    nr_mesh *m = d->m;
    const nr_qw *h0 = &d->img[0], *h1 = &d->img[1];
    uint32_t prim = h0->u[0], n = h0->u[1] & 0x7FFF, i, base = m->nvtx;
    uint32_t a_nrm = 2 + h0->u[3], a_uv = 2 + h1->u[0], a_col = 2 + h1->u[1], a_skin = 2 + h1->u[2];
    uint32_t j = h1->u[3], nb = 0;
    if (d->err) return;
    if (n == 0) return;
    /* header .x: the GS PRIM for the model program (3 list, 4 strip, 5 fan);
     * the line-strand program uses its own layout codes (0x11, 0x13); other
     * values stay emulated */
    if (prim != 3 && prim != 4 && prim != 5 && prim != 0x11 && prim != 0x13) { fail(d, "batch PRIM not a triangle list/strip/fan or line layout"); return; }
    if (2 + n > 1024 || !written(d, 2, n)) { fail(d, "positions not unpacked in the batch"); return; }
    /* arrays the batch did not unpack are left zero and recorded: a variant
     * that reads them stays emulated (nr_model_record) */
    {
        int have_nrm = a_nrm + n <= 1024 && written(d, a_nrm, n);
        int have_uv = a_uv + n <= 1024 && written(d, a_uv, n);
        int have_col = a_col + n <= 1024 && written(d, a_col, n);
        if (!have_nrm) m->missing |= NR_MISS_NRM;
        if (!have_uv) m->missing |= NR_MISS_UV;
        if (!have_col) m->missing |= NR_MISS_COL;
        if (!have_nrm) a_nrm = 0;
        if (!have_uv) a_uv = 0;
        if (!have_col) a_col = 0;
    }
    if (d->skinned_variant) {
        if (a_skin + 2 * n > 1024 || !written(d, a_skin, 2 * n)) { fail(d, "skin records not unpacked in the batch"); return; }
        nb = j == 0 ? 1 : j == 2 ? 2 : (j == 4 || j == 6) ? 4 : 0;
        if (!nb) { fail(d, "skin jump without a decode path"); return; }
        m->skinned = 1;
    }
    for (i = 0; i < n; i++) {
        nr_vtx v;
        static const nr_qw zero;
        const nr_qw *p = &d->img[2 + i];
        const nr_qw *nq = a_nrm ? &d->img[a_nrm + i] : &zero, *uq = a_uv ? &d->img[a_uv + i] : &zero;
        const nr_qw *cq = a_col ? &d->img[a_col + i] : &zero;
        uint32_t k;
        memset(&v, 0, sizeof v);
        if (!fits16(p->i[0]) || !fits16(p->i[1]) || !fits16(p->i[2])) { fail(d, "position not 16-bit"); return; }
        v.px = (int16_t)p->i[0]; v.py = (int16_t)p->i[1]; v.pz = (int16_t)p->i[2];
        if (fits8s(nq->i[0]) && fits8s(nq->i[1]) && fits8s(nq->i[2])) {
            v.nx = (int8_t)nq->i[0]; v.ny = (int8_t)nq->i[1]; v.nz = (int8_t)nq->i[2];
        } else {
            m->missing |= NR_MISS_NRM;
        }
        if (!fits16s(uq->i[0]) || !fits16s(uq->i[1])) { fail(d, "UV not 16-bit signed"); return; }
        v.u = (int16_t)uq->i[0]; v.v = (int16_t)uq->i[1];
        for (k = 0; k < 4; k++) {
            if (!fits8u(cq->i[k])) { fail(d, "colour not 8-bit unsigned"); return; }
        }
        v.r = (uint8_t)cq->i[0]; v.g = (uint8_t)cq->i[1]; v.b = (uint8_t)cq->i[2]; v.a = (uint8_t)cq->i[3];
        if (nb) {
            const nr_qw *si = &d->img[a_skin + 2 * i], *sw = &d->img[a_skin + 2 * i + 1];
            for (k = 0; k < nb; k++) {
                uint32_t row = (900u + 2u * (si->u[k] & 0xFFFFu)) & 1023u;
                if (!fits8u(sw->i[k])) { fail(d, "skin weight not 8-bit"); return; }
                if (sw->i[k] == 0) continue;     /* a bone with weight 0 adds 0 (its index may be junk) */
                if (row < 768 || row > 1020) {
                    static char why[96];
                    snprintf(why, sizeof why, "bone matrix outside rows 768..1023 (row %u, index %u)", row, si->u[k] & 0xFFFFu);
                    fail(d, why);
                    return;
                }
                v.bone[k] = (uint8_t)(row - 768);
                v.wgt[k] = (uint8_t)sw->i[k];
            }
        }
        {
            float f[3] = { (float)v.px, (float)v.py, (float)v.pz };
            if (m->nvtx == 0) { for (k = 0; k < 3; k++) { m->bbox[k] = f[k]; m->bbox[3 + k] = f[k]; } }
            for (k = 0; k < 3; k++) {
                if (f[k] < m->bbox[k]) m->bbox[k] = f[k];
                if (f[k] > m->bbox[3 + k]) m->bbox[3 + k] = f[k];
            }
        }
        push_vtx(d, &v);
    }
    if (prim == 3) {
        for (i = 0; i + 2 < n; i += 3) push_tri(d, base + i, base + i + 1, base + i + 2);
    } else if (prim == 4) {
        /* strip: odd triangles flipped, so every triangle has the winding of
         * the even ones (the culling rule, docs "Native pipeline rules") */
        for (i = 0; i + 2 < n; i++) {
            if (i & 1) push_tri(d, base + i + 1, base + i, base + i + 2);
            else push_tri(d, base + i, base + i + 1, base + i + 2);
        }
    } else if (prim == 5) {
        for (i = 1; i + 1 < n; i++) push_tri(d, base, base + i, base + i + 1);
    }   /* line layouts: vertices only (nr_vu1ln.c reads them per batch) */
    if (m->nbatch >= NR_MESH_MAXB) m->batch_overflow = 1;
    if (m->nbatch < NR_MESH_MAXB) {
        m->batch[m->nbatch].first = base;
        m->batch[m->nbatch].count = n;
        m->batch[m->nbatch].prim = prim;
    }
    m->nbatch++;
    m->last_prim = prim;
    m->prim_mask |= 1u << prim;
}

static void do_unpack(dec *d, uint32_t code, const uint32_t *pay)
{
    uint32_t cmd = (code >> 24) & 0x7F, num = (code >> 16) & 0xFF, imm = code & 0xFFFF;
    uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3, n = num ? num : 256, addr = imm & 0x3FF;
    int usn = (imm >> 14) & 1, flg = (imm >> 15) & 1;
    uint32_t e, bitpos = 0, comps = vn + 1, bits = 32u >> vl;
    if (cmd & 0x10) { fail(d, "masked UNPACK"); return; }
    if (!flg) { fail(d, "UNPACK without FLG (absolute address)"); return; }
    if (d->cl < d->wl) { fail(d, "STCYCL filling write (CL < WL)"); return; }
    if (d->wl == 0) { fail(d, "STCYCL WL 0"); return; }
    if (vl == 3) { fail(d, "V4-5 UNPACK"); return; }
    for (e = 0; e < n; e++) {
        /* skipping write (CL >= WL): of every CL qwords the first WL get data */
        uint32_t qa = addr + (e / d->wl) * d->cl + (e % d->wl), c;
        nr_qw q;
        if (qa >= 1024) { fail(d, "UNPACK past the batch buffer"); return; }
        memset(&q, 0, sizeof q);
        for (c = 0; c < comps; c++) {
            uint32_t word = pay[bitpos >> 5], v;
            if (bits == 32) v = word;
            else {
                v = (word >> (bitpos & 31)) & ((1u << bits) - 1u);
                if (!usn && (v >> (bits - 1))) v |= ~((1u << bits) - 1u);
            }
            q.u[c] = v;
            bitpos += bits;
        }
        if (comps == 1) { q.u[1] = q.u[2] = q.u[3] = q.u[0]; }   /* S: broadcast */
        if (comps == 3) q.u[3] = d->img[qa].u[3];               /* V3: W lane untouched (unused here) */
        if (comps == 2) { q.u[2] = d->img[qa].u[2]; q.u[3] = d->img[qa].u[3]; }
        d->img[qa] = q;
        d->wr[qa] |= (uint8_t)(comps == 1 || comps == 4 ? 15u : comps == 3 ? 7u : 3u);
    }
}

static void exec(dec *d, uint32_t code, const uint32_t *pay)
{
    uint32_t cmd = (code >> 24) & 0x7F;
    if (cmd >= 0x60) { do_unpack(d, code, pay); return; }
    switch (cmd) {
    case 0x00: case 0x02: case 0x03: case 0x04: case 0x06: case 0x07:
    case 0x10: case 0x11: case 0x13:
        return;                                        /* NOP OFFSET BASE ITOP MSKPATH3 MARK FLUSH* */
    case 0x01: d->cl = code & 0xFF; d->wl = (code >> 8) & 0xFF; if (d->cl != d->wl) d->m->skipwrite = 1; return;   /* STCYCL */
    case 0x05: if (code & 3) fail(d, "STMOD != 0"); return;
    case 0x20: case 0x30: case 0x31: return;           /* STMASK / STROW / STCOL (masks unsupported anyway) */
    case 0x17: if (d->on_batch) d->on_batch(d->on_batch_user, d->img, d->wr); end_batch(d); memset(d->img, 0, sizeof d->img); memset(d->wr, 0, sizeof d->wr); return;  /* MSCNT */
    default: fail(d, "unexpected VIF command in a mesh packet"); return;  /* MSCAL MPG DIRECT ... */
    }
}

static void feed(dec *d, uint32_t w)
{
    if (d->pend_words) {
        d->pay[d->pend_got++] = w;
        if (d->pend_got == d->pend_words) {
            d->pend_words = 0;
            exec(d, d->pend_cmd, d->pay);
        }
        return;
    }
    {
        long n = payload_words(w, d->cl, d->wl);
        if (n < 0 || n > (long)(sizeof d->pay / 4)) { fail(d, "VIF payload too large"); return; }
        if (n == 0) { exec(d, w, NULL); return; }
        d->pend_cmd = w; d->pend_words = (uint32_t)n; d->pend_got = 0;
    }
}

static int dec_blk(void *user, const uint32_t *codes, const uint8_t *data, uint32_t qwc)
{
    dec *d = (dec *)user;
    uint32_t i;
    feed(d, codes[0]);
    feed(d, codes[1]);
    if (data)
        for (i = 0; i < qwc * 4; i++) feed(d, rd32(data + 4 * i));
    return d->err ? 1 : 0;
}

static uint32_t g_next_id = 1;

/* RG_NR_DUMP=DIR (debugging): every decoded packet's VIF word stream to
 * DIR/m<id>_<pkt>.vif (tools/native/render_meshdump.c reads them) */
static int dump_blk(void *user, const uint32_t *codes, const uint8_t *data, uint32_t qwc)
{
    FILE *f = (FILE *)user;
    fwrite(codes, 4, 2, f);
    if (data) fwrite(data, 16, qwc, f);
    return 0;
}
static void dump_packet(uint32_t pkt, uint32_t id, int sk)
{
    const char *dir = getenv("RG_NR_DUMP");
    char path[512];
    FILE *f;
    if (!dir) return;
    snprintf(path, sizeof path, "%s/m%05u_%08X_%d.vif", dir, id, pkt, sk);
    f = fopen(path, "wb");
    if (!f) return;
    walk(pkt, dump_blk, f, NULL);
    fclose(f);
}

nr_mesh *nr_mesh_decode(uint32_t pkt, int skinned_variant)
{
    dec *d = (dec *)calloc(1, sizeof(dec));
    nr_mesh *m = (nr_mesh *)calloc(1, sizeof(nr_mesh));
    hctx hc = { 2166136261u, 0 };
    uint32_t bytes = 0;
    m->id = g_next_id++;
    m->pkt = pkt;
    dump_packet(pkt, m->id, skinned_variant);
    d->m = m;
    d->skinned_variant = skinned_variant;
    d->cl = d->wl = 1;
    if (walk(pkt, hash_blk, &hc, &bytes) != 0) {
        m->bad = 1; m->why = "DMA chain not walkable";
    } else {
        hctx sc = { 2166136261u, 0 };
        walk(pkt, shash_blk, &sc, NULL);
        m->shash = sc.h;
        m->hash = hc.h;
        m->pkt_bytes = bytes;
        if (walk(pkt, dec_blk, d, NULL) != 0 || d->err) {
            m->bad = 1; m->why = d->err ? d->err : "DMA chain not walkable";
        } else if (d->pend_words) {
            m->bad = 1; m->why = "VIF command cut off at the end of the packet";
        } else if (!m->nvtx) {
            m->bad = 1; m->why = "no vertices";
        }
    }
    free(d);
    g_st.decodes++;
    if (m->bad) g_st.bad++;
    if (m->bad && getenv("RG_NR_DEBUG"))
        fprintf(stderr, "nr_mesh: packet %08X (%u bytes) stays emulated: %s\n", pkt, m->pkt_bytes, m->why);
    return m;
}

nr_mesh *nr_mesh_decode_words(const uint32_t *w, uint32_t n, int skinned_variant, nr_batch_cb cb, void *user)
{
    dec *d = (dec *)calloc(1, sizeof(dec));
    nr_mesh *m = (nr_mesh *)calloc(1, sizeof(nr_mesh));
    uint32_t i;
    m->id = g_next_id++;
    d->m = m;
    d->skinned_variant = skinned_variant;
    d->cl = d->wl = 1;
    d->on_batch = cb;
    d->on_batch_user = user;
    for (i = 0; i < n && !d->err; i++) feed(d, w[i]);
    if (d->err) { m->bad = 1; m->why = d->err; }
    else if (d->pend_words) { m->bad = 1; m->why = "VIF command cut off at the end of the stream"; }
    free(d);
    return m;
}

void nr_mesh_free(nr_mesh *m)
{
    if (!m) return;
    free(m->vtx);
    free(m->idx);
    free(m);
}

/* ---- cache: open addressing on the packet address ------------------------ */
#define NR_MESH_SLOTS 16384
static struct { uint32_t pkt; int sk; nr_mesh *m; } g_tab[NR_MESH_SLOTS];

static int g_full = -1;   /* RG_NR_FULLHASH=1: revalidate with the full packet hash (check) */

const nr_mesh *nr_mesh_get(uint32_t pkt, int skinned_variant)
{
    uint32_t h = (pkt >> 4) * 2654435761u, i, k;
    hctx hc = { 2166136261u, 0 };
    g_st.lookups++;
    if (g_full < 0) { const char *e = getenv("RG_NR_FULLHASH"); g_full = e && atoi(e) != 0; }
    for (i = 0; i < NR_MESH_SLOTS; i++) {
        k = (h + i) & (NR_MESH_SLOTS - 1);
        if (g_tab[k].m == NULL) break;
        if (g_tab[k].pkt == pkt && g_tab[k].sk == skinned_variant) {
            nr_mesh *m = g_tab[k].m;
            uint32_t bytes = 0;
            if (walk(pkt, g_full ? hash_blk : shash_blk, &hc, &bytes) == 0 && hc.h == (g_full ? m->hash : m->shash) &&
                bytes == m->pkt_bytes) {
                g_st.bytes_hashed += hc.n;
                return m;
            }
            g_st.rehash++;
            /* the memory now holds another mesh: decode it into this slot
             * (the old object stays allocated for records in flight) */
            g_tab[k].m = nr_mesh_decode(pkt, skinned_variant);
            return g_tab[k].m;
        }
    }
    if (i == NR_MESH_SLOTS) {
        /* full: decode uncached (never expected; meshes are a few thousand) */
        return nr_mesh_decode(pkt, skinned_variant);
    }
    g_tab[k].pkt = pkt;
    g_tab[k].sk = skinned_variant;
    g_tab[k].m = nr_mesh_decode(pkt, skinned_variant);
    return g_tab[k].m;
}

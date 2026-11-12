/* SPDX-License-Identifier: CC0-1.0 */
/* Leftover normals natively (nr_lnrm.h; docs/NATIVE-RENDER.md "Leftover normals natively").
 *
 * The log: one op per model batch in draw order (walker markers), or a range some other
 * writer may have changed.  A model batch at TOP writes (TOP-relative, n = header .y):
 *   - its UNPACKs (nr_mesh lay runs; values from the mesh packet, nr_mesh_images);
 *   - the decode piece, per vertex i in order: position 2 + i (x y z), normal 2 + nofs + i
 *     (x y z, when nofs), UV 2 + uvofs + i (x y): rigid (0x4392C0) itof15 x qw77 / 78 / 79;
 *     skinned (0x4393B0, 1 / 2 / 4 bones by header 1.w when qw76.z) the weighted bone rows
 *     900 + 2 idx .. +3 times (p, 1) / n, accumulated bone by bone, row by row;
 *   - the environment-map kind (0x43EA30): UV i = ((E0 n.x + E1 n.y + E2 n.z) + 1) x 0.5 from
 *     the stored normal, E_k = view rows 24..26 .xy x qw64+k;
 *   - one store past the batch: rigid position n; skinned UV n, and with four bones normal n;
 *   - the output pieces and the clipper: [qw76.x, + 4 + 3 n + 2) (+ 640 with the clipper,
 *     qw81.x bit 1): unknown here.
 * Checked bit for bit against the oracle's VU memory (tools/native/lnrm_model.py on
 * tools/native/vudump.py dumps): every stored qword of every model batch of a battle frame, and
 * every normal slot the frame's leftover-normal meshes read (1,224 / 1,224).
 *
 * Arithmetic as the VU (nr_comp.c, src/ps2/vu/vu_float_inl.h): exponent 0 reads as zero,
 * results are the double result chopped to 24 bits, MADD = acc + chop(a x b). */
#include "nr_lnrm.h"
#include "nr.h"
#include "nr_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nr_lnrm_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_MISSNRM"); on = !e || !e[0] || e[0] == '3'; }
    return on;
}

/* ---- VU arithmetic --------------------------------------------------------------------- */
static double to_d(uint32_t a)
{
    uint32_t hi = a & 0x80000000u, lo = 0;
    uint64_t b;
    double d;
    if (a & 0x7F800000u) {
        hi |= ((a & 0x7FFFFFFFu) >> 3) + ((uint32_t)(1023 - 127) << 20);
        lo = a << 29;
    }
    b = ((uint64_t)hi << 32) | lo;
    memcpy(&d, &b, 8);
    return d;
}
static uint32_t from_d(double v)
{
    uint64_t b;
    uint32_t hi, s;
    int e;
    memcpy(&b, &v, 8);
    hi = (uint32_t)(b >> 32);
    s = hi & 0x80000000u;
    if (!(b << 1)) return s;
    e = (int)((hi >> 20) & 0x7FF) - 896;
    if (e >= 256) return s | 0x7FFFFFFFu;
    if (e <= 0) return s;
    return s | ((uint32_t)e << 23) | ((hi << 3) & 0x7FFFF8u) | (uint32_t)((uint32_t)b >> 29);
}
static uint32_t vmul(uint32_t a, uint32_t b) { return from_d(to_d(a) * to_d(b)); }
static uint32_t vadd(uint32_t a, uint32_t b) { return from_d(to_d(a) + to_d(b)); }
static uint32_t itof15(uint32_t a) { return from_d((double)(int32_t)a * (1.0 / 32768.0)); }
static uint32_t itof0(uint32_t a) { return from_d((double)(int32_t)a); }
float nr_lnrm_itof15(int32_t v)
{
    uint32_t u = itof15((uint32_t)v);
    float f;
    if (!(u & 0x7F800000u)) u &= 0x80000000u;
    else if ((u & 0x7F800000u) == 0x7F800000u) u = (u & 0x80000000u) | 0x7F7FFFFFu;   /* VU exponent 255: past FLT_MAX */
    memcpy(&f, &u, 4);
    return f;
}
#define F_ONE 0x3F800000u
#define F_HALF 0x3F000000u
#define W255 0x3B808081u     /* the decode pieces' LOI */

/* ---- the log ------------------------------------------------------------------------------ */
enum { K24, K25, K26, K64, K65, K66, K76, K77, K78, K79, K81, KN };
static const uint8_t k_rows[KN] = { 24, 25, 26, 64, 65, 66, 76, 77, 78, 79, 81 };
#define LN_DRAWS 4096u
#define LN_OPS 32768u
/* the VIF1 double buffer as the frame's chain drives it (OFFSET resets, every program start
 * flips): kept from the walker's VIF commands, the item packets a native draw stands for, the
 * native draws' own starts (MSCAL 0x320 + one MSCNT per batch) and the composite's sprites */
static struct { uint32_t base, ofs, dbf, tops; int known; int vux; } g_vs = { 140, 0, 0, 140, 0, 0 };
static void vs_offset(uint32_t o) { g_vs.ofs = o & 0x3FF; g_vs.dbf = 0; g_vs.tops = g_vs.base; g_vs.known = 1; }
static uint32_t vs_start(void)
{
    uint32_t top = g_vs.tops;
    g_vs.dbf ^= 1;
    g_vs.tops = (g_vs.dbf ? g_vs.base + g_vs.ofs : g_vs.base) & 1023;
    return top;
}
typedef struct ln_draw {
    const nr_mesh *mesh;
    nr_qw k[KN];
    const nr_qw *bones;
    const uint32_t *live;
    uint32_t live_id;
    uint8_t skinned, env, shadow;
} ln_draw;
typedef struct ln_op {
    uint32_t draw;            /* draw seq, or ~0u: an unknown range */
    uint16_t top, batch;      /* model; unknown: top = lo, batch = n */
} ln_op;
static ln_draw g_dr[LN_DRAWS];
static ln_op g_op[LN_OPS];
static uint32_t g_ndr, g_nop;   /* sequence numbers (ring index = seq % size) */

static struct {
    uint64_t draws, ops, unknown_ops, consumers, cvtx, cvtx_unknown, steps, img_decodes, img_fail, memo_hits;
} g_st;

void nr_lnrm_unknown(uint32_t lo, uint32_t n)
{
    ln_op *o;
    if (!nr_lnrm_on() || !n) return;
    lo &= 1023;
    if (lo + n <= 128) return;   /* constants: never a batch's slot (TOP >= 140) */
    o = &g_op[g_nop % LN_OPS];
    o->draw = ~0u;
    o->top = (uint16_t)(lo & 1023);
    o->batch = (uint16_t)(n > 1024 ? 1024 : n);
    g_nop++;
    g_st.unknown_ops++;
}

/* ---- per-op layout -------------------------------------------------------------------- */
typedef struct lay {
    const ln_draw *d;
    const struct nr_mesh_lay *l;
    uint32_t top, n, nofs, uvofs, skofs, nb, outo, outn;
    int skinned;
    /* the decode's stores: positions [0, n) (+ n: pos_n1), normals (nrm_on; + n: nrm_n1; skinned or
     * itof15 x qw78: nrm_skin), UVs (uv_on; + n: uv_n1) */
    int pos_n1, nrm_on, nrm_n1, nrm_skin, uv_on, uv_n1;
} lay;
static int op_lay(uint32_t j, lay *L)
{
    const ln_op *o = &g_op[j % LN_OPS];
    const ln_draw *d;
    uint32_t jmp;
    if (o->draw == ~0u) return 0;
    if (g_ndr - o->draw > LN_DRAWS) return -1;
    d = &g_dr[o->draw % LN_DRAWS];
    L->d = d;
    L->l = &d->mesh->lay[o->batch];
    L->top = o->top;
    L->n = L->l->h[1] & 0x7FFF;
    L->nofs = L->l->h[3];
    L->uvofs = L->l->h[4];
    L->skofs = L->l->h[6];
    L->skinned = d->skinned;
    jmp = d->k[K76].u[2] ? L->l->h[7] : 0;
    L->nb = !d->skinned ? 1 : jmp == 0 ? 1 : jmp == 2 ? 2 : (jmp == 4 || jmp == 6) ? 4 : 0;
    L->outo = d->k[K76].u[0] & 1023;
    L->outn = 4 + 3 * L->n + 2 + ((d->k[K81].u[0] & 2) ? 640 : 0);
    if (!d->shadow) {
        /* the model program: 0x4392C0 / 0x4393B0 */
        L->pos_n1 = !d->skinned;
        L->nrm_on = L->nofs != 0;
        L->nrm_n1 = d->skinned && L->nb == 4;
        L->nrm_skin = d->skinned;
        L->uv_on = 1;
        L->uv_n1 = d->skinned;
    } else {
        /* the shadow-volume program (head 0x4425F0): rigid 0x439F90 stores positions (+ n);
         * skinned 0x43A020 positions, and on its 2 / 4-bone paths normals itof15 x qw78
         * (not skinned) and UVs, each + n (oracle dump, every store bit for bit) */
        L->pos_n1 = !d->skinned;
        L->nrm_on = d->skinned && L->nb > 1 && L->nofs != 0;
        L->nrm_n1 = L->nrm_on;
        L->nrm_skin = 0;
        L->uv_on = d->skinned && L->nb > 1;
        L->uv_n1 = L->uv_on;
    }
    return 1;
}
static int in_rng(uint32_t rel, uint32_t a, uint32_t n) { return ((rel - a) & 1023) < n; }

/* lanes op j's UNPACKs wrote at rel (0: none); *val = the run's value index */
static uint32_t unp_lanes(const lay *L, uint32_t rel, uint32_t *vidx)
{
    const nr_mesh *m = L->d->mesh;
    uint32_t r, acc = L->l->vbase;   /* value index: runs of earlier batches first */
    for (r = 0; r < L->l->nrun; r++) {
        uint32_t w = m->runs[L->l->run0 + r], s = w & 0x3FF, n = (w >> 10) & 0x7FF;
        if (rel >= s && rel < s + n) { *vidx = acc + rel - s; return (w >> 21) & 15; }
        acc += n;
    }
    return 0;
}
/* does op j write qword A (any way)? */
static int op_writes(uint32_t j, uint32_t A)
{
    const ln_op *o = &g_op[j % LN_OPS];
    lay L;
    uint32_t rel, v;
    int k = op_lay(j, &L);
    if (k == 0) return in_rng(A & 1023, o->top, o->batch);
    if (k < 0) return 1;
    rel = (A - L.top) & 1023;
    if (in_rng(rel, L.outo, L.outn)) return 1;
    if (L.nb) {
        if (in_rng(rel, 2, L.n + (uint32_t)L.pos_n1)) return 1;
        if (L.nrm_on && in_rng(rel, 2 + L.nofs, L.n + (uint32_t)L.nrm_n1)) return 1;
        if (L.uv_on && in_rng(rel, 2 + L.uvofs, L.n + (uint32_t)L.uv_n1)) return 1;
    }
    return unp_lanes(&L, rel, &v) != 0;
}

/* ---- mesh images (UNPACKed values), cached per mesh ----------------------------------- */
#define LN_IMG 24
static struct { const nr_mesh *m; nr_qw *v; uint64_t used; } g_img[LN_IMG];
static uint64_t g_img_clock;
typedef struct img_ctx { const nr_mesh *m; nr_qw *v; uint32_t b, at; } img_ctx;
static void img_cb(void *user, const nr_qw *img, const uint8_t *wr)
{
    img_ctx *c = (img_ctx *)user;
    uint32_t r;
    (void)wr;
    if (c->b >= c->m->nlay) return;
    {
        const struct nr_mesh_lay *l = &c->m->lay[c->b];
        for (r = 0; r < l->nrun; r++) {
            uint32_t w = c->m->runs[l->run0 + r], s = w & 0x3FF, n = (w >> 10) & 0x7FF;
            memcpy(&c->v[c->at], &img[s], n * sizeof(nr_qw));
            c->at += n;
        }
    }
    c->b++;
}
static const nr_qw *mesh_vals(const nr_mesh *m, int skinned)
{
    int i, lru = 0;
    uint32_t tot = 0, k;
    img_ctx c;
    for (i = 0; i < LN_IMG; i++) {
        if (g_img[i].m == m) { g_img[i].used = ++g_img_clock; return g_img[i].v; }
        if (g_img[i].used < g_img[lru].used) lru = i;
    }
    for (k = 0; k < m->lay[m->nlay - 1].run0 + m->lay[m->nlay - 1].nrun; k++) tot += (m->runs[k] >> 10) & 0x7FF;
    free(g_img[lru].v);
    g_img[lru].m = NULL;
    g_img[lru].v = NULL;
    c.m = m;
    c.v = (nr_qw *)malloc((tot ? tot : 1) * sizeof(nr_qw));
    c.b = 0;
    c.at = 0;
    if (!c.v) return NULL;
    g_st.img_decodes++;
    if (nr_mesh_images(m, skinned, img_cb, &c) != 0 || c.at != tot) {
        g_st.img_fail++;
        free(c.v);
        return NULL;
    }
    g_img[lru].m = m;
    g_img[lru].v = c.v;
    g_img[lru].used = ++g_img_clock;
    return c.v;
}

/* ---- values -------------------------------------------------------------------------- */
typedef struct qv { uint32_t u[4]; uint32_t known; } qv;   /* known: lane mask bit 0 = x .. bit 3 = w */
#define LN_MEMO 65536u
static struct { uint32_t j, a; qv v; } g_memo[LN_MEMO];   /* value after op j at qword a (j + 1 stored; 0 empty) */
static int g_depth;

static void val_after(uint32_t j, uint32_t A, qv *out);
/* value at A before op k (after every earlier op) */
static void resolve(uint32_t A, uint32_t k, qv *out)
{
    uint32_t j = k, lim = g_nop > LN_OPS ? g_nop - LN_OPS : 0;
    A &= 1023;
    while (j > lim) {
        j--;
        g_st.steps++;
        if (op_writes(j, A)) { val_after(j, A, out); return; }
    }
    memset(out, 0, sizeof *out);   /* before the log: unknown */
}

/* value at A after op j's UNPACKs (the decode's input) */
static void pre_decode(uint32_t j, const lay *L, uint32_t A, qv *out)
{
    uint32_t vi = 0, lanes = unp_lanes(L, (A - L->top) & 1023, &vi), c;
    /* the VIF writes every lane (src/ps2/vif/vif.c unpack_elem): V2 as x y x y, V3's W from the
     * next stream word (unknown here; the stores never read it); the mesh decoder records the
     * lanes the format supplies (3 = V2, 7 = V3) */
    if (lanes == 3 || lanes == 7) {
        const nr_qw *v = mesh_vals(L->d->mesh, L->d->skinned);
        memset(out, 0, sizeof *out);
        if (!v) return;
        out->u[0] = v[vi].u[0];
        out->u[1] = v[vi].u[1];
        out->u[2] = lanes == 3 ? v[vi].u[0] : v[vi].u[2];
        out->u[3] = lanes == 3 ? v[vi].u[1] : 0;
        out->known = lanes == 3 ? 15u : 7u;
        return;
    }
    if (lanes != 15) resolve(A, j, out);
    else memset(out, 0, sizeof *out);
    if (lanes) {
        const nr_qw *v = mesh_vals(L->d->mesh, L->d->skinned);
        for (c = 0; c < 4; c++) {
            if (!(lanes & (1u << c))) continue;
            if (v) { out->u[c] = v[vi].u[c]; out->known |= 1u << c; }
            else out->known &= ~(1u << c);
        }
    }
}

/* the decode's stores for vertex i: position (want 1), normal (want 2) */
static void decode_vtx(uint32_t j, const lay *L, uint32_t i, int want, qv *P, qv *N)
{
    const ln_draw *d = L->d;
    uint32_t pa = L->top + 2 + i, na = L->top + 2 + L->nofs + i, c;
    qv pin, nin;
    uint32_t p[4], nv[3];
    int kp = 1, kn = 1;
    if (want & 1) {
        pre_decode(j, L, pa, &pin);
        *P = pin;
        kp = (pin.known & 7) == 7;
        for (c = 0; c < 3; c++) p[c] = vmul(itof15(pin.u[c]), d->k[K77].u[c]);
        p[3] = F_ONE;
    }
    if (want & 2) {
        pre_decode(j, L, na, &nin);
        *N = nin;
        kn = (nin.known & 7) == 7;
        for (c = 0; c < 3; c++) nv[c] = vmul(itof15(nin.u[c]), d->k[K78].u[c]);
    }
    if (L->skinned && ((want & 1) || L->nrm_skin)) {
        qv si, sw;
        uint32_t w[4], b, k, accp[3] = { 0, 0, 0 }, accn[3] = { 0, 0, 0 };
        int first = 1, ks, alive = !d->live || *d->live == d->live_id;
        pre_decode(j, L, L->top + 2 + L->skofs + 2 * i, &si);
        pre_decode(j, L, L->top + 2 + L->skofs + 2 * i + 1, &sw);
        ks = alive && ((si.known & sw.known) & ((1u << L->nb) - 1)) == ((1u << L->nb) - 1);
        for (b = 0; b < 4; b++) w[b] = vmul(itof0(sw.u[b]), W255);
        for (c = 0; c < 3; c++) {
            first = 1;
            for (b = 0; b < L->nb; b++) {
                uint32_t row = 900 + 2 * (si.u[b] & 0xFFFF);
                const nr_qw *R[4];
                for (k = 0; k < 4; k++) {
                    uint32_t r = (row + k) & 1023;
                    R[k] = r >= 768 ? &d->bones[r - 768] : NULL;
                    if (!R[k]) ks = 0;
                }
                if (want & 1) {
                    for (k = 0; k < 4; k++) {
                        uint32_t t = vmul(R[k] ? R[k]->u[c] : 0, vmul(p[k], w[b]));
                        accp[c] = first ? t : vadd(accp[c], t);
                        first = 0;
                    }
                }
            }
            first = 1;
            for (b = 0; b < L->nb && (want & 2) && L->nrm_skin; b++) {
                uint32_t row = 900 + 2 * (si.u[b] & 0xFFFF);
                for (k = 0; k < 3; k++) {
                    uint32_t r = (row + k) & 1023;
                    uint32_t t = vmul(r >= 768 ? d->bones[r - 768].u[c] : 0, vmul(nv[k], w[b]));
                    accn[c] = first ? t : vadd(accn[c], t);
                    first = 0;
                }
            }
        }
        if (want & 1) { for (c = 0; c < 3; c++) P->u[c] = accp[c]; if (!(kp && ks)) P->known &= ~7u; }
        if ((want & 2) && L->nrm_skin) { for (c = 0; c < 3; c++) N->u[c] = accn[c]; if (!(kn && ks)) N->known &= ~7u; }
        if ((want & 2) && !L->nrm_skin) { for (c = 0; c < 3; c++) N->u[c] = nv[c]; if (!kn) N->known &= ~7u; }
    } else {
        if (want & 1) { for (c = 0; c < 3; c++) P->u[c] = p[c]; if (!kp) P->known &= ~7u; }
        if (want & 2) { for (c = 0; c < 3; c++) N->u[c] = nv[c]; if (!kn) N->known &= ~7u; }
    }
}

/* value at A after op j's decode stores (no kind piece / overrun / output) */
static void after_decode(uint32_t j, const lay *L, uint32_t A, qv *v)
{
    uint32_t rel = (A - L->top) & 1023;
    /* the stores covering A in program order: (vertex, kind) ascending */
    int32_t ip = -1, in_ = -1, iu = -1;
    pre_decode(j, L, A, v);
    if (!L->nb) return;
    if (in_rng(rel, 2, L->n)) ip = (int32_t)((rel - 2) & 1023);
    if (L->nrm_on && in_rng(rel, 2 + L->nofs, L->n)) in_ = (int32_t)((rel - 2 - L->nofs) & 1023);
    if (L->uv_on && in_rng(rel, 2 + L->uvofs, L->n)) iu = (int32_t)((rel - 2 - L->uvofs) & 1023);
    {
        int32_t key[3] = { ip >= 0 ? ip * 3 : -1, in_ >= 0 ? in_ * 3 + 1 : -1, iu >= 0 ? iu * 3 + 2 : -1 };
        int s, t;
        for (s = 0; s < 3; s++) {
            int best = -1;
            for (t = 0; t < 3; t++)
                if (key[t] >= 0 && (best < 0 || key[t] < key[best])) best = t;
            if (best < 0) break;
            if (best == 0) {
                qv P, N;
                decode_vtx(j, L, (uint32_t)ip, 1, &P, &N);
                memcpy(v->u, P.u, 12);
                v->known = (v->known & 8u) | (P.known & 7u);
            } else if (best == 1) {
                qv P, N;
                decode_vtx(j, L, (uint32_t)in_, 2, &P, &N);
                memcpy(v->u, N.u, 12);
                v->known = (v->known & 8u) | (N.known & 7u);
            } else {
                qv u;
                pre_decode(j, L, L->top + 2 + L->uvofs + (uint32_t)iu, &u);
                v->u[0] = vmul(itof15(u.u[0]), L->d->k[K79].u[0]);
                v->u[1] = vmul(itof15(u.u[1]), L->d->k[K79].u[1]);
                v->known = (v->known & 12u) | (((u.known & 3u) == 3u) ? 3u : 0u);
            }
            key[best] = -1;
        }
    }
}

static uint32_t mac3(const uint32_t a[3], const uint32_t b[3])
{
    uint32_t acc = vmul(a[0], b[0]);
    acc = vadd(acc, vmul(a[1], b[1]));
    return vadd(acc, vmul(a[2], b[2]));
}

static void val_after_calc(uint32_t j, uint32_t A, qv *v)
{
    lay L;
    uint32_t rel;
    int k = op_lay(j, &L);
    memset(v, 0, sizeof *v);
    if (k <= 0) return;                          /* unknown range / draw gone */
    rel = (A - L.top) & 1023;
    if (in_rng(rel, L.outo, L.outn)) return;     /* output packet / clipper */
    after_decode(j, &L, A, v);
    if (!L.nb) return;
    /* the environment-map kind's UVs */
    if (L.d->env && in_rng(rel, 2 + L.uvofs, L.n)) {
        uint32_t i = (rel - 2 - L.uvofs) & 1023, c, kk, e[3][2], n[3];
        qv nq;
        if (!L.nofs) { v->known &= ~3u; return; }
        after_decode(j, &L, L.top + 2 + L.nofs + i, &nq);
        for (kk = 0; kk < 3; kk++)
            for (c = 0; c < 2; c++) {
                uint32_t a3[3] = { L.d->k[K24].u[c], L.d->k[K25].u[c], L.d->k[K26].u[c] };
                uint32_t b3[3] = { L.d->k[K64 + kk].u[0], L.d->k[K64 + kk].u[1], L.d->k[K64 + kk].u[2] };
                e[kk][c] = mac3(a3, b3);
            }
        memcpy(n, nq.u, 12);
        for (c = 0; c < 2; c++) {
            uint32_t a3[3] = { e[0][c], e[1][c], e[2][c] };
            v->u[c] = vmul(vadd(mac3(a3, n), F_ONE), F_HALF);
        }
        v->known = (v->known & 12u) | (((nq.known & 7u) == 7u) ? 3u : 0u);
    }
    /* one store past the batch */
    if (L.pos_n1 && rel == ((2 + L.n) & 1023)) {
        qv in;
        uint32_t c;
        pre_decode(j, &L, A, &in);
        for (c = 0; c < 3; c++) v->u[c] = vmul(itof15(in.u[c]), L.d->k[K77].u[c]);
        v->known = (v->known & 8u) | ((in.known & 7u) == 7u ? 7u : 0u);
    }
    if (L.uv_n1 && rel == ((2 + L.uvofs + L.n) & 1023)) {
        qv in;
        pre_decode(j, &L, A, &in);
        v->u[0] = vmul(itof15(in.u[0]), L.d->k[K79].u[0]);
        v->u[1] = vmul(itof15(in.u[1]), L.d->k[K79].u[1]);
        v->known = (v->known & 12u) | ((in.known & 3u) == 3u ? 3u : 0u);
    }
    if (L.nrm_n1 && rel == ((2 + L.nofs + L.n) & 1023)) {
        qv P, N;
        decode_vtx(j, &L, L.n, 2, &P, &N);
        memcpy(v->u, N.u, 12);
        v->known = (v->known & 8u) | (N.known & 7u);
    }
}

static void val_after(uint32_t j, uint32_t A, qv *out)
{
    uint32_t h = ((j * 2654435761u) ^ (A * 40503u)) & (LN_MEMO - 1);
    if (g_memo[h].j == j + 1 && g_memo[h].a == A) { *out = g_memo[h].v; g_st.memo_hits++; return; }
    if (++g_depth > 3000) { memset(out, 0, sizeof *out); g_depth--; return; }
    val_after_calc(j, A, out);
    g_depth--;
    g_memo[h].j = j + 1;
    g_memo[h].a = A;
    g_memo[h].v = *out;
}

/* ---- VIF commands (walker; item packets of native draws) ------------------------------- */
void nr_lnrm_vif(uint32_t c, uint32_t cl, uint32_t wl)
{
    uint32_t cmd = (c >> 24) & 0x7F, imm = c & 0xFFFF, num = (c >> 16) & 0xFF;
    if (!nr_lnrm_on()) return;
    if (cmd >= 0x60) {   /* UNPACK: not a model batch's data */
        uint32_t n = num ? num : 256, a = imm & 0x3FF, span;
        if (imm & 0x8000) a += g_vs.tops;
        if (!wl) wl = 1;
        span = cl >= wl ? ((n - 1) / wl) * cl + (n - 1) % wl + 1 : n;
        nr_lnrm_unknown(a, span);
        return;
    }
    switch (cmd) {
    case 0x02: vs_offset(imm); break;
    case 0x03: g_vs.base = imm & 0x3FF; break;
    case 0x14: case 0x15: case 0x17:
        vs_start();
        /* the program's own writes: nr_vux.c reports them (particles; untranslated starts); without
         * it (oracle builds) anything but the object-constant program at 0 is unknown */
        if (!g_vs.vux && !(cmd != 0x17 && imm == 0)) nr_lnrm_unknown(140, 760);
        break;
    default: break;
    }
}
void nr_lnrm_vux_present(void) { g_vs.vux = 1; }
/* a draw whose VU work is not modelled (shadow volumes, line strands, ...): anything may change */
void nr_lnrm_opaque_draw(void)
{
    if (!nr_lnrm_on()) return;
    nr_lnrm_unknown(140, 760);
    g_vs.known = 0;
}
void nr_lnrm_sprite(void) { if (nr_lnrm_on()) { vs_start(); nr_lnrm_unknown(140, 30); } }

/* an item packet (CALL target: DMA tags to RET) the PS2 chain would have here: its VIF codes */
static void scan_items(uint32_t addr)
{
    uint32_t tadr = addr, tags = 0, cl = 1, wl = 1, need = 0;
    for (;;) {
        const uint8_t *t = nr_game_ptr(tadr, 16), *data = NULL;
        uint32_t lo, qwc, id, hi, i, words[2], nw;
        if (!t || ++tags > 256) { g_vs.known = 0; return; }
        memcpy(&lo, t, 4); memcpy(&hi, t + 4, 4); memcpy(words, t + 8, 8);
        qwc = lo & 0xFFFF; id = (lo >> 28) & 7;
        if (id == 3 || id == 4 || id == 0) data = qwc ? nr_game_ptr(hi, qwc * 16) : NULL;
        else data = qwc ? nr_game_ptr(tadr + 16, qwc * 16) : NULL;
        if (qwc && !data) { g_vs.known = 0; return; }
        nw = qwc * 4;
        for (i = 0; i < 2 + nw; i++) {
            uint32_t c;
            if (i < 2) c = words[i]; else memcpy(&c, data + (i - 2) * 4, 4);
            if (need) { need--; continue; }
            {
                uint32_t cmd = (c >> 24) & 0x7F, imm = c & 0xFFFF, num = (c >> 16) & 0xFF;
                nr_lnrm_vif(c, cl, wl);
                if (cmd >= 0x60) {
                    uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3, n = num ? num : 256, el, bits;
                    bits = vl == 3 ? 16 : (32u >> vl) * (vn + 1);
                    el = wl <= cl || !cl ? n : cl * (n / wl) + (n % wl < cl ? n % wl : cl);
                    need = (el * bits + 31) / 32;
                } else if (cmd == 0x01) { cl = imm & 0xFF; wl = (imm >> 8) & 0xFF; }
                else if (cmd == 0x20) need = 1;
                else if (cmd == 0x30 || cmd == 0x31) need = 4;
                else if (cmd == 0x4A) need = (num ? num : 256u) * 2u;
                else if (cmd == 0x50 || cmd == 0x51) need = (imm ? imm : 65536u) * 4u;
            }
        }
        switch (id) {
        case 1: tadr += 16 + qwc * 16; break;            /* CNT */
        case 2: tadr = hi; break;                        /* NEXT */
        case 3: case 4: tadr += 16; break;               /* REF / REFS */
        default: return;                                 /* REFE / CALL / RET / END: the packet's end */
        }
    }
}

/* ---- the walker's model draws ----------------------------------------------------------- */
static FILE *g_dump;
uint32_t nr_lnrm_draw_pass(const nr_lnrm_draw *d, int32_t (*out)[3], uint8_t *known)
{
    ln_draw *D;
    uint32_t b, first_op, unk = 0, k;
    const nr_mesh *m = d->mesh;
    if (!nr_lnrm_on() || !m || m->bad || !m->nlay) return 0;
    D = &g_dr[g_ndr % LN_DRAWS];
    D->mesh = m;
    for (k = 0; k < KN; k++) D->k[k] = d->c[k_rows[k]];
    D->bones = d->bones;
    D->live = d->live;
    D->live_id = d->live_id;
    D->skinned = (uint8_t)(d->skinned != 0);
    D->env = (uint8_t)(d->env != 0);
    D->shadow = (uint8_t)(d->shadow != 0);
    for (k = 0; k < (uint32_t)d->nitems; k++) scan_items(d->items[k]);
    vs_start();                                  /* MSCAL 0x320 (sets TPC only) */
    first_op = g_nop;
    for (b = 0; b < m->nlay; b++) {
        ln_op *o = &g_op[g_nop % LN_OPS];
        uint32_t top = vs_start();               /* MSCNT */
        if (!g_vs.known) {   /* the double buffer's phase is not known: anything may change */
            o->draw = ~0u;
            o->top = 140;
            o->batch = 760;
        } else {
            o->draw = g_ndr;
            o->top = (uint16_t)top;
            o->batch = (uint16_t)b;
        }
        g_nop++;
    }
    g_ndr++;
    g_st.draws++;
    g_st.ops += m->nlay;
    if (!out) return 0;
    g_st.consumers++;
    {
        static int dd = -1;
        if (dd < 0) {
            const char *e = getenv("RG_NR_LNRM_DUMP");
            dd = e && e[0] && (g_dump = fopen(e, "w")) != NULL;
        }
    }
    if (g_dump) {
        uint32_t q, from = first_op > 120 ? first_op - 120 : 0;
        fprintf(g_dump, "C %u %08X %u\n", nr_frame_no(), m->pkt, m->nlay);
        for (q = from; q < first_op; q++) {   /* the log before it (comparisons with oracle dumps) */
            const ln_op *o = &g_op[q % LN_OPS];
            if (o->draw == ~0u) fprintf(g_dump, "U %u %u\n", o->top, o->batch);
            else {
                const ln_draw *dd = &g_dr[o->draw % LN_DRAWS];
                fprintf(g_dump, "O %08X %u %u %u %u %u\n", dd->mesh->pkt, o->batch, o->top, dd->mesh->lay[o->batch].h[1] & 0x7FFF,
                        dd->skinned, dd->env);
            }
        }
    }
    for (b = 0; b < m->nlay; b++) {
        lay L;
        uint32_t i, j = first_op + b;
        if (op_lay(j, &L) <= 0) continue;
        if (g_dump) fprintf(g_dump, "B %u %u\n", L.top, L.n);
        for (i = 0; i < L.n; i++) {
            qv v;
            uint32_t vi = L.l->vfirst + i;
            pre_decode(j, &L, L.top + 2 + L.nofs + i, &v);
            if (vi < m->nvtx) {
                out[vi][0] = (int32_t)v.u[0];
                out[vi][1] = (int32_t)v.u[1];
                out[vi][2] = (int32_t)v.u[2];
                known[vi] = (v.known & 7u) == 7u;
                if (!known[vi]) unk++;
            }
            if (g_dump) fprintf(g_dump, "%08x %08x %08x %u\n", v.u[0], v.u[1], v.u[2], v.known & 7u);
        }
    }
    g_st.cvtx += m->nvtx;
    g_st.cvtx_unknown += unk;
    if (g_dump) fflush(g_dump);
    return unk;
}

void nr_lnrm_stats(void *file)
{
    FILE *f = (FILE *)file;
    if (!nr_lnrm_on() || !f) return;
    fprintf(f, "native render leftover normals (RG_NR_MISSNRM=3): %llu draws logged (%llu batches, %llu unknown ranges); "
            "%llu draws read leftovers: %llu vertices, %llu unknown; %llu log steps, %llu memo hits, %llu packet re-decodes (%llu failed)\n",
            (unsigned long long)g_st.draws, (unsigned long long)g_st.ops, (unsigned long long)g_st.unknown_ops,
            (unsigned long long)g_st.consumers, (unsigned long long)g_st.cvtx, (unsigned long long)g_st.cvtx_unknown,
            (unsigned long long)g_st.steps, (unsigned long long)g_st.memo_hits, (unsigned long long)g_st.img_decodes,
            (unsigned long long)g_st.img_fail);
}

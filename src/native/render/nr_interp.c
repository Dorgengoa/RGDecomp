/* SPDX-License-Identifier: CC0-1.0 */
/* Interpolated presentation (nr_interp.h, docs/NATIVE-RENDER.md "Interpolated presentation"). */
#include "nr_interp.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY && defined(RG_HAVE_GPU)

#include "nr_const.h"
#include "nr_gs.h"
#include "nr_im.h"
#include "nr_mesh.h"
#include "nr_vu1.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
static double now_ms(void)
{
    static LARGE_INTEGER f;
    LARGE_INTEGER c;
    if (!f.QuadPart) QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart * 1000.0 / (double)f.QuadPart;
}
#else
#include <time.h>
static double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1.0e6;
}
#endif

/* ---- logs and items (worker) --------------------------------------------------- */

/* how an item is drawn in a pass */
enum { IM_EXACT = 0,   /* as recorded (snaps to the latest frame) */
       IM_CAM = 1,     /* the recorded object, the camera interpolated (new / teleported items) */
       IM_FULL = 2 };  /* object, camera and bones interpolated from the matched previous item */

typedef struct ip_item {
    uint32_t id;
    const nr_mesh *mesh;
    int variant;
    uint32_t ctx;            /* the draw context (src[0]) */
    uint32_t fbp;            /* FRAME.FBP of the draw */
    int has_box;
    float box[4];
    uint32_t bones_hi;
    size_t qoff;             /* c (112 qw) then bones (bones_hi qw) in the log's arena */
    int match;               /* index of the previous log's item, -1 */
    int how;                 /* IM_* */
    int derivable;           /* rows 64-75 are nr_const_prog0 of the item's sources (else lerped) */
} ip_item;

typedef struct ip_log {
    int valid;               /* a log (not voided by a reset / overflow) */
    uint32_t seq;            /* logs begun (unique) */
    uint32_t frame;          /* EE frame number (nr_frame_begin) */
    uint64_t T;              /* phases taken when the frame began */
    uint64_t T1;             /* ... when the device first got work from it (its first record) */
    int have_T1;
    uint32_t nrec;           /* immediate records the GS input ran */
    ip_item *it;
    uint32_t nit;
    size_t cap;
    nr_qw *qw;
    size_t qw_n, qw_cap;
    /* matching with the log before it */
    uint32_t matched_seq, matched_nit;
    int cut;                 /* a camera cut / teleport of the whole view: no interpolation */
    /* immediate record signatures (census) */
    uint64_t *sig;
    uint32_t nsig;
    size_t sigcap;
} ip_log;

#define NLOG NR_IP_SLOTS
static ip_log g_log[NLOG];
static int g_newest = -1;
static uint32_t g_seq;
static int w_on;
static uint64_t g_wticks;    /* the phase the worker's input belongs to (w_tick) */
static int g_dirty;          /* the device holds an in-between image (a pass ran since the last restore) */
static int g_pass;           /* 0, 1 interpolated, 2 exact */
static ip_log *g_pl, *g_pp;  /* the pass's log and the one before it */
static float g_alpha;

/* the census and the pass statistics */
static struct {
    uint64_t logs, voided, overflow;
    uint64_t items, full, cam, exact, unmatched, zscale, skin, lines, shadow, overlap, cut_logs, jumped;
    uint64_t ims, ims_static;
    uint64_t passes, pass_skip_nolog, pass_skip_noprev, pass_skip_cut, pass_skip_alpha1, pass_stale;
    uint64_t restores, exacts, gs_mismatch, notfound;
    uint64_t drawn_full, drawn_cam, drawn_exact;
    double pass_ms, restore_ms, exact_ms;
    uint64_t cmds, cmds_max, pre, born, bad_logs, items_max, underivable;
} g_st;
static FILE *g_census;       /* $RG_INTERP_CENSUS=path: one TSV row per log */

static int grow(void **p, size_t *cap, size_t want, size_t elem)
{
    size_t nc;
    void *np;
    if (want <= *cap) return 0;
    nc = *cap ? *cap : 1024;
    while (nc < want) nc *= 2;
    np = realloc(*p, nc * elem);
    if (!np) return -1;
    *p = np;
    *cap = nc;
    return 0;
}

static ip_log *log_at(int back)
{
    int i;
    if (g_newest < 0 || back >= NLOG) return NULL;
    i = (g_newest - back + NLOG) % NLOG;
    return g_log[i].valid ? &g_log[i] : NULL;
}

static void log_void(ip_log *L)
{
    L->valid = 0;
    L->have_T1 = 0;
    L->nit = 0;
    L->qw_n = 0;
    L->nrec = 0;
    L->nsig = 0;
}

static nr_qw *item_c(const ip_log *L, const ip_item *t) { return L->qw + t->qoff; }
static nr_qw *item_bones(const ip_log *L, const ip_item *t) { return L->qw + t->qoff + NRQ_CONST_N; }

/* ---- bone matrix starts of a mesh (the rows its vertices reference) --------------- */
typedef struct bmask { uint8_t done, overlap; uint32_t m[8]; } bmask;
static bmask *g_bm;
static size_t g_bm_cap;
static const bmask *bones_of(const nr_mesh *m)
{
    bmask *b;
    uint32_t i;
    int k, s;
    if (grow((void **)&g_bm, &g_bm_cap, (size_t)m->id + 1, sizeof *g_bm)) return NULL;
    b = &g_bm[m->id];
    if (b->done == 1) return b;
    memset(b, 0, sizeof *b);
    for (i = 0; i < m->nvtx; i++)
        for (k = 0; k < 4; k++)
            if (m->vtx[i].wgt[k]) b->m[m->vtx[i].bone[k] >> 5] |= 1u << (m->vtx[i].bone[k] & 31);
    /* matrices of 4 rows: two starts closer than 4 rows share rows (no decomposition) */
    for (s = 0; s < 256; s++) {
        int n;
        if (!(b->m[s >> 5] & (1u << (s & 31)))) continue;
        for (n = 1; n < 4 && s + n < 256; n++)
            if (b->m[(s + n) >> 5] & (1u << ((s + n) & 31))) b->overlap = 1;
    }
    b->done = 1;
    return b;
}

/* ---- the GS input of the newest log (worker) ------------------------------------- */
static void restore_if_dirty(void)
{
    /* a replay left in-between images in the targets: back as they were before anything else
     * draws or reads */
    double t0;
    if (!g_dirty) return;
    g_dirty = 0;
    t0 = now_ms();
    gpu_ip_restore(nr_gs_device());
    g_st.restore_ms += now_ms() - t0;
    g_st.restores++;
}

void nr_ip_w_rec(uint32_t id)
{
    ip_log *L;
    if (!w_on) return;
    restore_if_dirty();
    L = log_at(0);
    if (!L) return;
    if (!L->have_T1) { L->T1 = g_wticks; L->have_T1 = 1; }
    L->nrec++;
    if (!grow((void **)&L->sig, &L->sigcap, (size_t)L->nsig + 1, sizeof *L->sig)) {
        uint64_t sg = 0, vh = 0;
        uint32_t nv = 0;
        nr_im_rec_info(id, &sg, &nv, &vh);
        (void)nv;
        L->sig[L->nsig++] = sg ^ (vh * 0x9E3779B97F4A7C15ull);   /* (state and vertex data folded: census only) */
    }
}

void nr_ip_w_image(const void *qw, uint32_t nqw)
{
    (void)qw;
    (void)nqw;
    if (!w_on) return;
    restore_if_dirty();
}

void nr_ip_w_reset(void)
{
    int i;
    if (!w_on) return;
    restore_if_dirty();
    for (i = 0; i < NLOG; i++) if (g_log[i].valid) { log_void(&g_log[i]); g_st.voided++; }
}

int nr_ip_pass(void) { return g_pass; }

static nr_cblock g_dvb;
/* the item's derived rows (64-66, 68-75) come from its camera / projection / object rows
 * through the VU program at 0 (nr_const_prog0), bit for bit: interpolating the sources and
 * deriving again is valid; else the rows were uploaded otherwise and are interpolated directly */
static int derivable_c(const nr_qw *c)
{
    memcpy(g_dvb.c, c, sizeof g_dvb.c);
    nr_const_prog0(&g_dvb);
    return !memcmp(&g_dvb.c[64], &c[64], 3 * sizeof(nr_qw)) && !memcmp(&g_dvb.c[68], &c[68], 8 * sizeof(nr_qw));
}

void nr_ip_note(uint32_t id, const void *mesh, int variant, uint32_t ctx, uint64_t frame_reg, int has_box,
                const float box[4], const void *c, const void *bones, uint32_t bones_hi)
{
    ip_log *L;
    ip_item *t;
    size_t nq;
    if (!w_on || g_pass) return;
    L = log_at(0);
    if (!L) return;
    if (!(variant & NRV_SKIN)) bones_hi = 0;
    if (bones_hi > NR_BONE_ROWS) bones_hi = NR_BONE_ROWS;
    nq = NRQ_CONST_N + bones_hi;
    if (grow((void **)&L->it, &L->cap, (size_t)L->nit + 1, sizeof *L->it) ||
        grow((void **)&L->qw, &L->qw_cap, L->qw_n + nq, sizeof *L->qw)) {
        log_void(L);
        return;
    }
    t = &L->it[L->nit++];
    t->id = id;
    t->mesh = (const nr_mesh *)mesh;
    t->variant = variant;
    t->ctx = ctx;
    t->fbp = (uint32_t)(frame_reg & 0x1FF);
    t->has_box = has_box;
    memcpy(t->box, box, sizeof t->box);
    t->bones_hi = bones_hi;
    t->qoff = L->qw_n;
    t->match = -1;
    t->how = IM_EXACT;
    t->derivable = derivable_c((const nr_qw *)c);
    memcpy(L->qw + L->qw_n, c, NRQ_CONST_N * sizeof(nr_qw));
    if (bones_hi) memcpy(L->qw + L->qw_n + NRQ_CONST_N, bones, bones_hi * sizeof(nr_qw));
    L->qw_n += nq;
}

/* ---- identity: items of a log matched with the previous log's ----------------------
 * key (decoded mesh, draw context, program variant); several instances of one key are
 * paired greedily by the nearest object position (object matrix translation + the first bone
 * row's translation).  A pair whose screen position jumps (teleport, cut, re-used instance)
 * draws with the recorded object and the interpolated camera; a draw context where most
 * pairs jump is a cut: nothing in it is interpolated. */
static const ip_log *g_sortlog;
static int key_cmp3(const ip_item *a, const ip_item *b)
{
    if (a->mesh != b->mesh) return (uintptr_t)a->mesh < (uintptr_t)b->mesh ? -1 : 1;
    if (a->ctx != b->ctx) return a->ctx < b->ctx ? -1 : 1;
    if (a->variant != b->variant) return a->variant < b->variant ? -1 : 1;
    return 0;
}
static int idx_cmp(const void *x, const void *y)
{
    const ip_item *a = &g_sortlog->it[*(const uint32_t *)x], *b = &g_sortlog->it[*(const uint32_t *)y];
    int k = key_cmp3(a, b);
    if (k) return k;
    return *(const uint32_t *)x < *(const uint32_t *)y ? -1 : 1;
}

static void item_pos(const ip_log *L, const ip_item *t, float p[3])
{
    const nr_qw *c = item_c(L, t);
    p[0] = c[63].f[0];
    p[1] = c[63].f[1];
    p[2] = c[63].f[2];
    if (t->bones_hi >= 4) {
        const nr_qw *b = item_bones(L, t);
        p[0] += b[3].f[0];
        p[1] += b[3].f[1];
        p[2] += b[3].f[2];
    }
}
/* the item's origin (or first bone) on screen, GS window pixels; 0 behind the camera */
static int item_screen(const ip_log *L, const ip_item *t, float s[2])
{
    const nr_qw *c = item_c(L, t);
    float p[3] = { 0, 0, 0 }, h[4];
    int k;
    if (t->bones_hi >= 4) {
        const nr_qw *b = item_bones(L, t);
        p[0] = b[3].f[0]; p[1] = b[3].f[1]; p[2] = b[3].f[2];
    }
    for (k = 0; k < 4; k++)
        h[k] = p[0] * c[NRQ_SCREEN].f[k] + p[1] * c[NRQ_SCREEN + 1].f[k] + p[2] * c[NRQ_SCREEN + 2].f[k] + c[NRQ_SCREEN + 3].f[k];
    if (!(h[3] > 1e-6f) || !isfinite(h[0]) || !isfinite(h[1])) return 0;
    s[0] = h[0] / h[3];
    s[1] = h[1] / h[3];
    return isfinite(s[0]) && isfinite(s[1]);
}

/* A pair whose object moves more than g_jump_ang (world displacement / view depth, radians) in
 * one game frame does not interpolate its object (teleport, re-used instance): camera only.
 * Camera motion is not object motion: a pan moves everything on screen and interpolates.
 * A draw context is a cut when its camera turns more than g_cut_deg in one frame, or most of its
 * pairs move more than g_cut_px on screen. */
static int g_2d = 1;               /* $RG_INTERP_2D=0: immediate draws (2D, effects) as recorded */
/* Z-scale composites (character parts drawn into a work target, then copied into the frame by
 * 32-pixel sprite strips cut on the EE for the recorded screen box): $RG_INTERP_ZSCALE=
 *   0  exact (snap; checkpoint 11),
 *   1  the parts' meshes interpolated (control: their constants also place the part in the
 *      work buffer, so the part leaves the recorded box and the strips cut it),
 *   2  (default) placement: the parts drawn exact, the strips that copy them into the frame
 *      moved along the strip group's own screen motion (nr_iprec.cpp "composite placement"),
 *   3  placement and the parts' bones interpolated (their camera / object / projection rows as
 *      recorded: the part stays in its slot of the work buffer, the pose moves; a limb that
 *      leaves the recorded box is cut by the strips),
 *   4  (default) the pose: the parts' bones interpolated as in 3 (camera / object rows as recorded:
 *      the part stays where the frame drew it in the work buffer), the copy moved as in 2 by the
 *      composite call's own pair, and the work buffer's clear and the copy strips widened to cover
 *      the pose between the two frames (nr_iprec.cpp "composite poses"), so nothing is cut; a call
 *      whose copy cannot be widened (not paired, no clear found, parts not all composites) has its
 *      parts drawn as recorded and is placed as in 2.  (The parts' camera / object rows are not
 *      interpolated: mode 1 loses parts, e.g. the hero's cape on the Salgin walk, at low weights.) */
static int g_zs_mode = 4;
static int g_zs_allow;             /* (mode 4, set by the replay per mesh draw) its strip group was widened */
/* $RG_INTERP_LEAD=x (0..1, default 0): show the frame x game frames earlier by extrapolating past it
 * (docs "Interpolated presentation", the display delay) */
static float g_lead;
static float g_jump_ang = 0.12f;   /* $RG_INTERP_FAR_ANG */
static float g_cut_deg = 30.0f;    /* $RG_INTERP_CUT_DEG */
static float g_cut_px = 200.0f;    /* $RG_INTERP_CUT_PX */

/* the view rotation's turn between two constant blocks, degrees (rows normalised) */
static float view_turn_deg(const nr_qw *ca, const nr_qw *cb)
{
    float ra[3][3], rb[3][3], tr = 0;
    int i, k;
    for (i = 0; i < 3; i++) {
        float na = 0, nb = 0;
        for (k = 0; k < 3; k++) {
            na += ca[NRQ_VIEW + i].f[k] * ca[NRQ_VIEW + i].f[k];
            nb += cb[NRQ_VIEW + i].f[k] * cb[NRQ_VIEW + i].f[k];
        }
        na = na > 1e-30f ? 1.0f / sqrtf(na) : 0.0f;
        nb = nb > 1e-30f ? 1.0f / sqrtf(nb) : 0.0f;
        for (k = 0; k < 3; k++) { ra[i][k] = ca[NRQ_VIEW + i].f[k] * na; rb[i][k] = cb[NRQ_VIEW + i].f[k] * nb; }
    }
    for (i = 0; i < 3; i++)
        for (k = 0; k < 3; k++) tr += ra[i][k] * rb[i][k];
    tr = (tr - 1.0f) * 0.5f;
    if (!isfinite(tr)) return 180.0f;
    if (tr > 1.0f) tr = 1.0f;
    if (tr < -1.0f) tr = -1.0f;
    return acosf(tr) * (180.0f / 3.14159265f);
}

static void match_logs(ip_log *L, ip_log *P)
{
    static uint32_t *ord;
    static size_t ocap;
    static uint8_t *taken;
    static size_t tcap;
    uint32_t i;
    if (L->matched_seq == P->seq && L->matched_nit == L->nit) return;
    L->matched_seq = P->seq;
    L->matched_nit = L->nit;
    L->cut = 0;
    for (i = 0; i < L->nit; i++) { L->it[i].match = -1; L->it[i].how = IM_EXACT; }
    if (!P->nit || !L->nit) return;
    if (grow((void **)&ord, &ocap, P->nit, sizeof *ord) || grow((void **)&taken, &tcap, P->nit, 1)) return;
    for (i = 0; i < P->nit; i++) ord[i] = i;
    g_sortlog = P;
    qsort(ord, P->nit, sizeof *ord, idx_cmp);
    memset(taken, 0, P->nit);
    for (i = 0; i < L->nit; i++) {
        ip_item *b = &L->it[i];
        uint32_t lo = 0, hi = P->nit, j, best = UINT32_MAX;
        float pb[3], bd = 0;
        /* lower bound of the key */
        while (lo < hi) {
            uint32_t mid = (lo + hi) / 2;
            if (key_cmp3(&P->it[ord[mid]], b) < 0) lo = mid + 1; else hi = mid;
        }
        item_pos(L, b, pb);
        for (j = lo; j < P->nit && key_cmp3(&P->it[ord[j]], b) == 0; j++) {
            float pa[3], d;
            if (taken[ord[j]]) continue;
            item_pos(P, &P->it[ord[j]], pa);
            d = (pa[0] - pb[0]) * (pa[0] - pb[0]) + (pa[1] - pb[1]) * (pa[1] - pb[1]) + (pa[2] - pb[2]) * (pa[2] - pb[2]);
            if (!isfinite(d)) d = 1e30f;
            if (best == UINT32_MAX || d < bd) { best = ord[j]; bd = d; }
        }
        if (best != UINT32_MAX) { taken[best] = 1; b->match = (int)best; }
    }
    /* how: composites (Z-scale output: the draw-back strips were cut on the EE for the
     * recorded position) stay exact; pairs that jump on screen take the camera only */
    {
        /* per draw context: pairs, jumped pairs (cut detection) */
        enum { NCTX = 16 };
        uint32_t cx[NCTX], np[NCTX], nf[NCTX];
        float tu[NCTX];
        int ncx = 0, k;
        for (i = 0; i < L->nit; i++) {
            ip_item *b = &L->it[i];
            float sa[2], sb[2];
            if ((b->variant & NRV_ZSCALE) && g_zs_mode != 1 && g_zs_mode != 3 && g_zs_mode != 4) { b->how = IM_EXACT; continue; }
            if (b->match < 0) { b->how = IM_CAM; continue; }
            b->how = IM_FULL;
            /* (composite parts take no part in the context's camera / cut tests: their
             * constants place them in the work buffer) */
            if (!(b->variant & NRV_ZSCALE)) {
            for (k = 0; k < ncx && cx[k] != b->ctx; k++) {}
            if (k == ncx && ncx < NCTX) { cx[ncx] = b->ctx; np[ncx] = nf[ncx] = 0; tu[ncx] = 0; ncx++; }
            if (k == ncx) continue;   /* (more contexts than tracked: no cut test) */
            if (!np[k]) tu[k] = view_turn_deg(item_c(P, &P->it[b->match]), item_c(L, b));
            np[k]++;
            if (item_screen(L, b, sb) && item_screen(P, &P->it[b->match], sa)) {
                float dx = sb[0] - sa[0], dy = sb[1] - sa[1];
                if (dx * dx + dy * dy > g_cut_px * g_cut_px) nf[k]++;
            }
            }
            {
                /* the object's own motion: world displacement over the view depth */
                float pa[3], pb[3], d2 = 0, w = 0;
                const nr_qw *cl = item_c(L, b);
                int j;
                item_pos(P, &P->it[b->match], pa);
                item_pos(L, b, pb);
                for (j = 0; j < 3; j++) d2 += (pb[j] - pa[j]) * (pb[j] - pa[j]);
                /* view depth of the item: w of its origin (object space 0) through the screen matrix */
                w = cl[NRQ_SCREEN + 3].f[3];
                if (b->bones_hi >= 4) {
                    const nr_qw *bo = item_bones(L, b);
                    w += bo[3].f[0] * cl[NRQ_SCREEN].f[3] + bo[3].f[1] * cl[NRQ_SCREEN + 1].f[3] + bo[3].f[2] * cl[NRQ_SCREEN + 2].f[3];
                }
                if (!isfinite(d2) || (w > 1e-3f && d2 > g_jump_ang * g_jump_ang * w * w)) b->how = IM_CAM;
            }
        }
        for (k = 0; k < ncx; k++) {
            if (tu[k] > g_cut_deg || (np[k] >= 4 && nf[k] * 10 > np[k] * 6)) {
                /* most of the context jumps: a camera cut */
                for (i = 0; i < L->nit; i++)
                    if (L->it[i].ctx == cx[k] && L->it[i].how != IM_EXACT) L->it[i].how = IM_EXACT;
                L->cut = 1;
            }
        }
    }
}

/* ---- the census (one row per completed log) -------------------------------------- */
static int u64_cmp(const void *x, const void *y)
{
    uint64_t a = *(const uint64_t *)x, b = *(const uint64_t *)y;
    return a < b ? -1 : a > b;
}
static void census_log(ip_log *L, ip_log *P)
{
    uint32_t i, full = 0, cam = 0, ex = 0, unm = 0, zs = 0, sk = 0, ov = 0, jumped = 0, sh = 0, ln = 0;
    uint32_t ims = 0;
    if (P) match_logs(L, P);
    for (i = 0; i < L->nit; i++) {
        const ip_item *t = &L->it[i];
        if (t->how == IM_FULL) full++;
        else if (t->how == IM_CAM) { cam++; if (t->match >= 0) jumped++; }
        else ex++;
        if (t->match < 0) unm++;
        if (!t->derivable) g_st.underivable++;
        if (t->variant & NRV_ZSCALE) zs++;
        if (t->variant & NRV_SHADOW) sh++;
        if (t->variant & NRV_LINES) ln++;
        if (t->variant & NRV_SKIN) {
            const bmask *b = bones_of(t->mesh);
            sk++;
            if (b && b->overlap) ov++;
        }
    }
    if (P && L->nsig && P->nsig) {
        /* immediate records: the multiset intersection of the signatures with the previous
         * log's (a signature folds the state writes and the vertex data: a common one is a
         * record drawn exactly as before, i.e. static 2D) */
        static uint64_t *x, *y;
        static size_t xc, yc;
        if (!grow((void **)&x, &xc, L->nsig, sizeof *x) && !grow((void **)&y, &yc, P->nsig, sizeof *y)) {
            uint32_t a = 0, b = 0;
            memcpy(x, L->sig, L->nsig * sizeof *x);
            memcpy(y, P->sig, P->nsig * sizeof *y);
            qsort(x, L->nsig, sizeof *x, u64_cmp);
            qsort(y, P->nsig, sizeof *y, u64_cmp);
            while (a < L->nsig && b < P->nsig) {
                if (x[a] == y[b]) { ims++; a++; b++; }
                else if (x[a] < y[b]) a++;
                else b++;
            }
        }
    }
    g_st.logs++;
    g_st.items += L->nit;
    g_st.full += full;
    g_st.cam += cam;
    g_st.exact += ex;
    g_st.unmatched += unm;
    g_st.zscale += zs;
    g_st.skin += sk;
    g_st.overlap += ov;
    g_st.shadow += sh;
    g_st.lines += ln;
    g_st.jumped += jumped;
    g_st.cut_logs += L->cut ? 1 : 0;
    g_st.ims += L->nsig;
    g_st.ims_static += ims;
    {
        static long dump = -2;
        uint32_t si[4];
        if (dump == -2) { const char *e = getenv("RG_INTERP_CMDDUMP"); dump = e ? atol(e) : -1; }
        if (dump >= 0 && L->frame >= (uint32_t)dump && L->frame < (uint32_t)dump + 3) gpu_ip_dump(nr_gs_device(), (int)(L - g_log), stderr);
        gpu_ip_slot_info(nr_gs_device(), (int)(L - g_log), si);
        if (si[0] > g_st.cmds_max) g_st.cmds_max = si[0];
        g_st.cmds += si[0];
        g_st.pre += si[1];
        g_st.born += si[2];
        g_st.bad_logs += si[3] ? 1 : 0;
    }
    if (L->nit > g_st.items_max) g_st.items_max = L->nit;
    if (g_census)
        fprintf(g_census, "%u\t%llu\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%zu\n", L->frame, (unsigned long long)L->T,
                L->nit, full, cam, ex, unm, jumped, zs, sk, ov, L->cut, L->nsig, ims, L->nrec, (size_t)0);
}

/* ---- interpolation of the constant block ---------------------------------------- */
static float lerpf(float a, float b, float t) { return a + (b - a) * t; }

static void quat_from(const float m[3][3], float q[4])
{
    float tr = m[0][0] + m[1][1] + m[2][2], s;
    if (tr > 0.0f) {
        s = sqrtf(tr + 1.0f) * 2.0f;
        q[3] = 0.25f * s;
        q[0] = (m[2][1] - m[1][2]) / s;
        q[1] = (m[0][2] - m[2][0]) / s;
        q[2] = (m[1][0] - m[0][1]) / s;
    } else if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) {
        s = sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2.0f;
        q[3] = (m[2][1] - m[1][2]) / s;
        q[0] = 0.25f * s;
        q[1] = (m[0][1] + m[1][0]) / s;
        q[2] = (m[0][2] + m[2][0]) / s;
    } else if (m[1][1] > m[2][2]) {
        s = sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2.0f;
        q[3] = (m[0][2] - m[2][0]) / s;
        q[0] = (m[0][1] + m[1][0]) / s;
        q[1] = 0.25f * s;
        q[2] = (m[1][2] + m[2][1]) / s;
    } else {
        s = sqrtf(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2.0f;
        q[3] = (m[1][0] - m[0][1]) / s;
        q[0] = (m[0][2] + m[2][0]) / s;
        q[1] = (m[1][2] + m[2][1]) / s;
        q[2] = 0.25f * s;
    }
}
static void quat_to(const float q[4], float m[3][3])
{
    float x = q[0], y = q[1], z = q[2], w = q[3];
    m[0][0] = 1 - 2 * (y * y + z * z); m[0][1] = 2 * (x * y - z * w);     m[0][2] = 2 * (x * z + y * w);
    m[1][0] = 2 * (x * y + z * w);     m[1][1] = 1 - 2 * (x * x + z * z); m[1][2] = 2 * (y * z - x * w);
    m[2][0] = 2 * (x * z - y * w);     m[2][1] = 2 * (y * z + x * w);     m[2][2] = 1 - 2 * (x * x + y * y);
}
static void slerp(const float a[4], const float b0[4], float t, float o[4])
{
    float b[4], d = a[0] * b0[0] + a[1] * b0[1] + a[2] * b0[2] + a[3] * b0[3], wa, wb, n;
    int k;
    for (k = 0; k < 4; k++) b[k] = d < 0 ? -b0[k] : b0[k];
    d = fabsf(d);
    if (d > 0.9995f) {
        wa = 1 - t;
        wb = t;
    } else {
        float th = acosf(d), s = sinf(th);
        wa = sinf((1 - t) * th) / s;
        wb = sinf(t * th) / s;
    }
    n = 0;
    for (k = 0; k < 4; k++) { o[k] = wa * a[k] + wb * b[k]; n += o[k] * o[k]; }
    n = n > 0 ? 1.0f / sqrtf(n) : 0;
    for (k = 0; k < 4; k++) o[k] *= n;
}

static uint64_t g_aff_lerp, g_aff_slerp;
/* 4 rows: rows 0..2 the basis (xyz; w lerped), row 3 the translation.  Rotation slerp, per-row
 * scale and translation lerp; a basis that is not (nearly) orthogonal, or whose handedness
 * changes, is lerped component by component. */
static void aff_interp(const nr_qw *A, const nr_qw *B, float t, nr_qw *O)
{
    float ra[3][3], rb[3][3], sa[3], sb[3], qa[4], qb[4], q[4], r[3][3];
    int i, k, ok = 1;
    if (!memcmp(A, B, 4 * sizeof(nr_qw))) { memcpy(O, B, 4 * sizeof(nr_qw)); return; }
    for (i = 0; i < 3 && ok; i++) {
        sa[i] = sqrtf(A[i].f[0] * A[i].f[0] + A[i].f[1] * A[i].f[1] + A[i].f[2] * A[i].f[2]);
        sb[i] = sqrtf(B[i].f[0] * B[i].f[0] + B[i].f[1] * B[i].f[1] + B[i].f[2] * B[i].f[2]);
        if (!(sa[i] > 1e-20f) || !(sb[i] > 1e-20f) || !isfinite(sa[i]) || !isfinite(sb[i])) { ok = 0; break; }
        for (k = 0; k < 3; k++) { ra[i][k] = A[i].f[k] / sa[i]; rb[i][k] = B[i].f[k] / sb[i]; }
    }
    if (ok) {
        float da, db;
        for (i = 0; i < 3 && ok; i++)
            for (k = i + 1; k < 3; k++) {
                float dA = ra[i][0] * ra[k][0] + ra[i][1] * ra[k][1] + ra[i][2] * ra[k][2];
                float dB = rb[i][0] * rb[k][0] + rb[i][1] * rb[k][1] + rb[i][2] * rb[k][2];
                if (fabsf(dA) > 0.02f || fabsf(dB) > 0.02f) { ok = 0; break; }
            }
        if (ok) {
            da = ra[0][0] * (ra[1][1] * ra[2][2] - ra[1][2] * ra[2][1]) - ra[0][1] * (ra[1][0] * ra[2][2] - ra[1][2] * ra[2][0]) +
                 ra[0][2] * (ra[1][0] * ra[2][1] - ra[1][1] * ra[2][0]);
            db = rb[0][0] * (rb[1][1] * rb[2][2] - rb[1][2] * rb[2][1]) - rb[0][1] * (rb[1][0] * rb[2][2] - rb[1][2] * rb[2][0]) +
                 rb[0][2] * (rb[1][0] * rb[2][1] - rb[1][1] * rb[2][0]);
            if ((da < 0) != (db < 0)) ok = 0;
            else if (da < 0) {
                /* a mirror: flip the third row into a rotation, its scale carries the sign */
                for (k = 0; k < 3; k++) { ra[2][k] = -ra[2][k]; rb[2][k] = -rb[2][k]; }
                sa[2] = -sa[2];
                sb[2] = -sb[2];
            }
        }
    }
    if (!ok) {
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++) O[i].f[k] = lerpf(A[i].f[k], B[i].f[k], t);
        g_aff_lerp++;
        return;
    }
    quat_from(ra, qa);
    quat_from(rb, qb);
    slerp(qa, qb, t, q);
    quat_to(q, r);
    for (i = 0; i < 3; i++) {
        float s = lerpf(sa[i], sb[i], t);
        for (k = 0; k < 3; k++) O[i].f[k] = r[i][k] * s;
        O[i].f[3] = lerpf(A[i].f[3], B[i].f[3], t);
    }
    for (k = 0; k < 4; k++) O[3].f[k] = lerpf(A[3].f[k], B[3].f[k], t);
    g_aff_slerp++;
}

static nr_cblock g_tmpb;
/* camera (view 24..27, position 28, projection 4..11) of a toward b into o */
static void cam_interp(const nr_qw *ca, const nr_qw *cb, float t, nr_qw *o)
{
    int i, k;
    aff_interp(&ca[NRQ_VIEW], &cb[NRQ_VIEW], t, &o[NRQ_VIEW]);
    for (k = 0; k < 3; k++) o[NRQ_CAMPOS].f[k] = lerpf(ca[NRQ_CAMPOS].f[k], cb[NRQ_CAMPOS].f[k], t);
    for (i = 4; i < 12; i++)
        if (memcmp(&ca[i], &cb[i], sizeof(nr_qw)))
            for (k = 0; k < 4; k++) o[i].f[k] = lerpf(ca[i].f[k], cb[i].f[k], t);
}
static void derive(nr_qw *c)
{
    memcpy(g_tmpb.c, c, sizeof g_tmpb.c);
    nr_const_prog0(&g_tmpb);
    memcpy(&c[64], &g_tmpb.c[64], 12 * sizeof(nr_qw));
    memcpy(&c[100], &g_tmpb.c[100], 3 * sizeof(nr_qw));
    memcpy(&c[111], &g_tmpb.c[111], sizeof(nr_qw));
}

/* per draw context: the camera pair of the pass (from the first interpolated pair) */
enum { NCAM = 16 };
static struct { uint32_t ctx; int ok; nr_qw a[NRQ_CONST_N], b[NRQ_CONST_N]; } g_cam[NCAM];
static int g_ncam;

static void pass_cams(ip_log *L, ip_log *P)
{
    uint32_t i;
    int k;
    g_ncam = 0;
    for (i = 0; i < L->nit; i++) {
        const ip_item *b = &L->it[i];
        if (b->how != IM_FULL || (b->variant & NRV_ZSCALE)) continue;   /* (composite parts: work-buffer constants) */
        for (k = 0; k < g_ncam && g_cam[k].ctx != b->ctx; k++) {}
        if (k < g_ncam || g_ncam == NCAM) continue;
        g_cam[k].ctx = b->ctx;
        g_cam[k].ok = 1;
        memcpy(g_cam[k].a, item_c(P, &P->it[b->match]), sizeof g_cam[k].a);
        memcpy(g_cam[k].b, item_c(L, b), sizeof g_cam[k].b);
        g_ncam++;
    }
}

/* the id -> item table of the pass */
static uint32_t *g_ht;
static size_t g_htcap;
static uint32_t g_htmask;
static void pass_table(const ip_log *L)
{
    size_t n = 64;
    uint32_t i;
    while (n < (size_t)L->nit * 2) n *= 2;
    if (grow((void **)&g_ht, &g_htcap, n, sizeof *g_ht)) { g_htmask = 0; return; }
    g_htmask = (uint32_t)n - 1;
    memset(g_ht, 0xFF, n * sizeof *g_ht);
    for (i = 0; i < L->nit; i++) {
        uint32_t h = (L->it[i].id * 2654435761u) & g_htmask;
        while (g_ht[h] != UINT32_MAX) h = (h + 1) & g_htmask;
        g_ht[h] = i;
    }
}

static nr_qw g_ic[NRQ_CONST_N], g_ib[NR_BONE_ROWS];
static nr_ip_draw g_draw;

/* the bone rows of b interpolated from a's into g_ib */
static void bones_interp(const ip_log *P, const ip_item *a, const ip_log *L, const ip_item *b)
{
    uint32_t rows = a->bones_hi < b->bones_hi ? a->bones_hi : b->bones_hi, r;
    const nr_qw *ba = item_bones(P, a), *bb = item_bones(L, b);
    const bmask *bm = bones_of(b->mesh);
    uint8_t done[NR_BONE_ROWS];
    memset(done, 0, sizeof done);
    if (bm && !bm->overlap)
        for (r = 0; r + 3 < rows; r++)
            if (bm->m[r >> 5] & (1u << (r & 31))) {
                aff_interp(&ba[r], &bb[r], g_alpha, &g_ib[r]);
                done[r] = done[r + 1] = done[r + 2] = done[r + 3] = 1;
            }
    for (r = 0; r < rows; r++)
        if (!done[r]) {
            int k;
            for (k = 0; k < 4; k++) g_ib[r].f[k] = lerpf(ba[r].f[k], bb[r].f[k], g_alpha);
        }
}

const nr_ip_draw *nr_ip_draw_for(uint32_t id)
{
    const ip_log *L = g_pl;
    const ip_item *b = NULL;
    uint32_t h;
    if (!g_pass || !L || !g_htmask) return NULL;
    h = (id * 2654435761u) & g_htmask;
    while (g_ht[h] != UINT32_MAX) {
        if (L->it[g_ht[h]].id == id) { b = &L->it[g_ht[h]]; break; }
        h = (h + 1) & g_htmask;
    }
    if (!b) { g_st.notfound++; return NULL; }
    g_draw.mesh = b->mesh;
    g_draw.variant = b->variant;
    g_draw.has_box = b->has_box;
    memcpy(g_draw.box, b->box, sizeof g_draw.box);
    g_draw.bones_hi = b->bones_hi;
    memcpy(g_ic, item_c(L, b), sizeof g_ic);
    memset(g_ib, 0, sizeof g_ib);
    if (b->bones_hi) memcpy(g_ib, item_bones(L, b), b->bones_hi * sizeof(nr_qw));
    g_draw.c = g_ic;
    g_draw.bones = g_ib;
    g_draw.interp = 0;
    if (g_pass != 1 || b->how == IM_EXACT) { g_st.drawn_exact++; return &g_draw; }
    if ((b->variant & NRV_ZSCALE) && g_zs_mode == 4 && !g_zs_allow) { g_st.drawn_exact++; return &g_draw; }
    if ((b->variant & NRV_ZSCALE) && (g_zs_mode == 3 || g_zs_mode == 4)) {
        /* the pose only (mode 3) */
        const ip_log *P = g_pp;
        const ip_item *a = b->match >= 0 ? &P->it[b->match] : NULL;
        if (b->how != IM_FULL || !a || !b->bones_hi || !a->bones_hi) { g_st.drawn_exact++; return &g_draw; }
        bones_interp(P, a, L, b);
        g_draw.interp = 1;
        g_st.drawn_full++;
        return &g_draw;
    }
    g_draw.interp = 1;
    if (b->how == IM_FULL) {
        const ip_log *P = g_pp;
        const ip_item *a = &P->it[b->match];
        const nr_qw *ca = item_c(P, a);
        cam_interp(ca, item_c(L, b), g_alpha, g_ic);
        if (b->derivable && a->derivable) {
            aff_interp(&ca[NRQ_OBJMTX], &item_c(L, b)[NRQ_OBJMTX], g_alpha, &g_ic[NRQ_OBJMTX]);
            derive(g_ic);
        } else {
            /* rows the game uploaded already combined: lerped as they are */
            const nr_qw *cb = item_c(L, b);
            int r, k;
            for (r = 60; r <= 75; r++)
                for (k = 0; k < 4; k++) g_ic[r].f[k] = lerpf(ca[r].f[k], cb[r].f[k], g_alpha);
            for (r = 100; r <= 102; r++)
                for (k = 0; k < 4; k++) g_ic[r].f[k] = lerpf(ca[r].f[k], cb[r].f[k], g_alpha);
        }
        if (b->bones_hi && a->bones_hi) bones_interp(P, a, L, b);
        g_draw.has_box = 0;   /* (the box was cut for the recorded position) */
        g_st.drawn_full++;
        return &g_draw;
    }
    /* IM_CAM: the context's camera pair */
    {
        int k;
        for (k = 0; k < g_ncam && g_cam[k].ctx != b->ctx; k++) {}
        if (k == g_ncam || !b->derivable) { g_st.drawn_exact++; g_draw.interp = 0; return &g_draw; }
        cam_interp(g_cam[k].a, g_cam[k].b, g_alpha, g_ic);
        derive(g_ic);
        g_draw.has_box = 0;
        g_st.drawn_cam++;
        return &g_draw;
    }
}

int nr_ip_zs_mode(void) { return g_zs_mode; }
void nr_ip_zs_allow(int ok) { g_zs_allow = ok; }
int nr_ip_zs_item(uint32_t id)
{
    const ip_log *L = g_pl;
    uint32_t h;
    if (!g_pass || !L || !g_htmask) return 0;
    h = (id * 2654435761u) & g_htmask;
    while (g_ht[h] != UINT32_MAX) {
        if (L->it[g_ht[h]].id == id) return (L->it[g_ht[h]].variant & NRV_ZSCALE) ? 1 : 0;
        h = (h + 1) & g_htmask;
    }
    return 0;
}

/* the log's device commands run again (mode 1 interpolated, 2 exact) */
static int run_pass(ip_log *L, ip_log *P, float alpha, int mode, int back)
{
    int rc, sl[NLOG], n = 0, i;
    /* L and every later log (what the device did since L began: e.g. the copy of L's image into
     * the display buffer at the next frame's start) */
    for (i = back; i >= 0; i--) {
        ip_log *x = log_at(i);
        if (!x) return -1;
        sl[n++] = (int)(x - g_log);
    }
    g_pl = L;
    g_pp = P;
    g_alpha = alpha;
    pass_table(L);
    if (mode == 1) pass_cams(L, P);
    g_pass = mode;
    rc = gpu_ip_replay(nr_gs_device(), sl, n, mode == 1 ? 0 : -1, mode == 1 && P && g_2d ? (int)(P - g_log) : -1, alpha);
    g_pass = 0;
    g_zs_allow = 0;
    g_pl = g_pp = NULL;
    if (rc == 0 || gpu_ip_dirty(nr_gs_device())) g_dirty = 1;
    if (rc != 0) g_st.pass_stale++;
    return rc;
}

/* ---- worker calls queued by the EE --------------------------------------------- */
typedef struct w_cfg { int on; } w_cfg;
static void w_config(void *user, const void *data)
{
    const w_cfg *c = (const w_cfg *)data;
    int i;
    (void)user;
    if (c->on == w_on) return;
    restore_if_dirty();
    w_on = c->on;
    for (i = 0; i < NLOG; i++) {
        log_void(&g_log[i]);
        gpu_ip_slot_free(nr_gs_device(), i);
    }
    g_newest = -1;
    if (w_on) gpu_ip_install(nr_gs_device());
    else gpu_ip_rec_slot(nr_gs_device(), -1);
}

typedef struct w_bnd { uint32_t frame; uint32_t pad; uint64_t T; } w_bnd;
static void w_boundary(void *user, const void *data)
{
    const w_bnd *b = (const w_bnd *)data;
    ip_log *L;
    (void)user;
    if (!w_on || !nr_gs_device()) return;
    restore_if_dirty();
    L = log_at(0);
    if (L) census_log(L, log_at(1));
    g_newest = (g_newest + 1) % NLOG;
    L = &g_log[g_newest];
    log_void(L);
    L->valid = 1;
    L->seq = ++g_seq;
    L->frame = b->frame;
    L->T = b->T;
    gpu_ip_rec_slot(nr_gs_device(), g_newest);   /* the device records this frame's commands */
    L->matched_seq = 0;
    L->matched_nit = 0;
    L->cut = 0;
}

typedef struct w_req { double tau; uint64_t dispfb[2]; uint64_t pmode; int mode; int pad; } w_req;
/* $RG_INTERP_DEBUG=n: the first n pass requests on stderr (skips with their reason) */
static int dbg_want(void)
{
    static int dbg = -1, nd;
    if (dbg < 0) { const char *e = getenv("RG_INTERP_DEBUG"); dbg = e ? atoi(e) : 0; }
    if (nd >= dbg) return 0;
    nd++;
    return 1;
}
static void dbg_skip(const char *why, double tau)
{
    int i;
    if (!dbg_want()) return;
    fprintf(stderr, "interp skip %s: tau %.3f;", why, tau);
    for (i = 0; i < NLOG; i++) {
        ip_log *c = log_at(i);
        if (c) fprintf(stderr, " [%d] frame %u T %llu T1 %llu items %u recs %u", i, c->frame, (unsigned long long)c->T,
                       (unsigned long long)(c->have_T1 ? c->T1 : 0), c->nit, c->nrec);
    }
    fprintf(stderr, "\n");
}
/* $RG_INTERP_TRACE=path (measurement, tools/native/interp_trace.py): one row per pass request on
 * the worker: wall ms, tau, outcome (0 pass, 1 no log, 2 no previous, 3 cut, 4 alpha 1), the
 * shown log's frame / the previous log's frame, alpha, vis, iv, the displayed camera position
 * (the first interpolated context's CAMPOS lerped at alpha; the shown log's for 3 / 4), that
 * context's camera in the previous and the shown log, and, for up
 * to 16 interpolated (IM_FULL, not composite) items whose key (mesh, variant, context) is unique
 * in the log, key:x,y,z of the displayed object position (item_pos lerped) */
static FILE *g_trace;
static uint32_t trace_key(const ip_item *t)
{
    uint32_t h = (uint32_t)(uintptr_t)t->mesh * 2654435761u;
    h ^= ((uint32_t)t->variant + 0x9E3779B9u + (h << 6) + (h >> 2));
    h ^= (t->ctx + 0x9E3779B9u + (h << 6) + (h >> 2));
    return h;
}
static void trace_row(int code, double tau, const ip_log *L, const ip_log *P, double a, double vis, double iv)
{
    uint32_t i, cand[64], ci[64], nc = 0, j, out = 0;
    float cam[3] = { NAN, NAN, NAN }, cp[3] = { NAN, NAN, NAN }, cl[3] = { NAN, NAN, NAN };
    if (!g_trace) return;
    fprintf(g_trace, "%.3f\t%.4f\t%d\t%u\t%u\t%.4f\t%.2f\t%.2f", now_ms(), tau, code, L ? L->frame : 0u, P ? P->frame : 0u, a, vis, iv);
    if (L && P && (code == 0 || code == 3 || code == 4)) {
        float t = code == 0 ? (float)a : 1.0f;
        for (i = 0; i < L->nit; i++) {
            const ip_item *b = &L->it[i];
            if (b->how != IM_FULL || (b->variant & NRV_ZSCALE) || b->match < 0) continue;
            {
                const nr_qw *ca = item_c(P, &P->it[b->match]), *cb = item_c(L, b);
                int k;
                for (k = 0; k < 3; k++) {
                    cam[k] = lerpf(ca[NRQ_CAMPOS].f[k], cb[NRQ_CAMPOS].f[k], t);
                    cp[k] = ca[NRQ_CAMPOS].f[k];
                    cl[k] = cb[NRQ_CAMPOS].f[k];
                }
            }
            break;
        }
        fprintf(g_trace, "\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f", cam[0], cam[1], cam[2], cp[0], cp[1], cp[2], cl[0], cl[1], cl[2]);
        for (i = 0; i < L->nit && nc < 64; i++) {
            const ip_item *b = &L->it[i];
            if ((code == 0 && b->how != IM_FULL) || (b->variant & NRV_ZSCALE) || b->match < 0) continue;
            cand[nc] = trace_key(b);
            ci[nc++] = i;
        }
        for (j = 0; j < nc && out < 16; j++) {
            uint32_t n = 0;
            float pa[3], pb[3];
            const ip_item *b = &L->it[ci[j]];
            for (i = 0; i < L->nit && n < 2; i++)
                if (L->it[i].mesh == b->mesh && L->it[i].variant == b->variant && L->it[i].ctx == b->ctx) n++;
            if (n != 1) continue;
            item_pos(P, &P->it[b->match], pa);
            item_pos(L, b, pb);
            fprintf(g_trace, "\t%08x:%.4f,%.4f,%.4f", cand[j], lerpf(pa[0], pb[0], t), lerpf(pa[1], pb[1], t), lerpf(pa[2], pb[2], t));
            out++;
        }
    }
    fputc('\n', g_trace);
}

static void w_pass(void *user, const void *data)
{
    const w_req *q = (const w_req *)data;
    ip_log *L = NULL, *P, *N;
    int back = 0, i;
    double vis, iv, a;
    (void)user;
    if (!w_on) return;
    /* the frame the display shows: the newest log with mesh items whose drawing reaches the
     * displayed target by now (data flow over the device commands: this game draws frame N into a
     * work buffer and copies it into the display buffer when frame N + 1's chain starts, so the
     * display shows the log before the newest one that ran) */
    for (i = 0; i + 1 < NLOG && !L; i++) {
        ip_log *c = log_at(i);
        int sl[NLOG], n = 0, k, f;
        if (!c || !c->nit) continue;
        for (k = i; k >= 0; k--) {
            ip_log *x = log_at(k);
            if (x) sl[n++] = (int)(x - g_log);
        }
        f = gpu_ip_flows(nr_gs_device(), sl, n);
        if (f != 0) { L = c; back = i; }
    }
    if (!L) { g_st.pass_skip_nolog++; if (q->mode == 1) { dbg_skip("no log", q->tau); trace_row(1, q->tau, NULL, NULL, 0, 0, 0); } restore_if_dirty(); return; }
    if (q->mode == 2) {
        /* the exact replay of the shown frame (check): an equal display = the retained frame
         * reproduces the original */
        double t0 = now_ms();
        run_pass(L, NULL, 1.0f, 2, back);
        g_st.exact_ms += now_ms() - t0;
        g_st.exacts++;
        return;
    }
    P = log_at(back + 1);
    if (!P || !P->nit) { g_st.pass_skip_noprev++; dbg_skip("no previous", q->tau); trace_row(2, q->tau, L, NULL, 0, 0, 0); restore_if_dirty(); return; }
    /* alpha: the display has shown L since the device last changed it from P's image to L's: the
     * first work of the log after L when L's image reached the display at the next frame's start
     * (back > 0), else L's own; one game-frame interval (the same step one log earlier) */
    N = back ? log_at(back - 1) : NULL;
    if (N && N->have_T1 && L->have_T1) { vis = (double)N->T1; iv = (double)N->T1 - (double)L->T1; }
    else if (L->have_T1 && P->have_T1) { vis = (double)L->T1; iv = (double)L->T1 - (double)P->T1; }
    else { vis = (double)L->T; iv = (double)L->T - (double)P->T; }
    if (iv < 1.0) iv = 1.0;
    if (iv > 4.0) iv = 4.0;
    a = (q->tau - vis) / iv;
    if (!(a > 0.0)) a = 0.0;
    if (g_lead > 0.0f) {
        /* lead: x game frames ahead (extrapolated past L up to 1 + x); a frame that comes late
         * (a > 1) takes the overshoot back over the next interval instead of holding it */
        double x = (double)g_lead;
        if (a <= 1.0)
            a += x;
        else {
            a = 1.0 + x - (a - 1.0);
            if (a < 1.0) a = 1.0;
        }
    } else if (a > 1.0)
        a = 1.0;
    {
        static double force = -2.0;   /* $RG_INTERP_ALPHA=x: every pass at weight x (controls) */
        if (force < -1.5) { const char *e = getenv("RG_INTERP_ALPHA"); force = e && *e ? atof(e) : -1.0; }
        if (force >= 0.0) a = force > 0.998 && g_lead <= 0.0f ? 0.998 : force;
    }
    match_logs(L, P);
    if (L->cut) { g_st.pass_skip_cut++; dbg_skip("cut", q->tau); trace_row(3, q->tau, L, P, a, vis, iv); restore_if_dirty(); return; }
    if (a >= 0.999 && a <= 1.001) { g_st.pass_skip_alpha1++; dbg_skip("alpha 1", q->tau); trace_row(4, q->tau, L, P, a, vis, iv); restore_if_dirty(); return; }
    {
        double t0 = now_ms();
        int rc = run_pass(L, P, (float)a, 1, back);
        g_st.pass_ms += now_ms() - t0;
        g_st.passes++;
        trace_row(0, q->tau, L, P, a, vis, iv);
        {
            if (dbg_want()) {
                fprintf(stderr, "interp pass: tau %.3f alpha %.3f vis %.1f iv %.1f back %d rc %d;", q->tau, a, vis, iv, back, rc);
                for (i = 0; i < NLOG; i++) {
                    ip_log *c = log_at(i);
                    if (c) fprintf(stderr, " [%d] frame %u T %llu T1 %llu items %u recs %u", i, c->frame, (unsigned long long)c->T, (unsigned long long)(c->have_T1 ? c->T1 : 0), c->nit, c->nrec);
                }
                fprintf(stderr, " -> %d\n", L ? back : -1);
            }
        }
    }
}

static void w_tick(void *user, const void *data)
{
    (void)user;
    memcpy(&g_wticks, data, sizeof g_wticks);
}

static void w_restore(void *user, const void *data)
{
    (void)user;
    (void)data;
    restore_if_dirty();
}

/* ---- EE ------------------------------------------------------------------------ */
static int g_on_ee = -1;
static uint64_t g_ticks;
static uint64_t g_frames_ee;
static int g_dirty_ee;

static int env_on(void)
{
    const char *e = getenv("RG_INTERP");
    return e && *e ? (e[0] == '1' ? 1 : 0) : -1;
}

void nr_ip_configure(int on)
{
    int e = env_on();
    w_cfg c;
    if (e >= 0) on = e;
    on = on ? 1 : 0;
    if (on == g_on_ee) return;
    if (g_on_ee < 0 && !on) { g_on_ee = 0; return; }
    g_on_ee = on;
    if (on) {
        const char *p = getenv("RG_INTERP_CENSUS"), *f = NULL;
        if (p && *p && !g_census) {
            g_census = fopen(p, "w");
            if (g_census)
                fprintf(g_census, "#frame\tT\titems\tfull\tcam\texact\tunmatched\tfar\tzscale\tskin\toverlap\tcut\tims\tims_static\trecs\tbytes\n");
        }
        (void)f;
        f = getenv("RG_INTERP_TRACE");
        if (f && *f && !g_trace) {
            g_trace = fopen(f, "w");
            if (g_trace) fprintf(g_trace, "#wall_ms\ttau\tcode\tframe\tprev\talpha\tvis\tiv\tcamx\tcamy\tcamz\tprev cam xyz\tshown cam xyz\tkey:x,y,z...\n");
        }
        f = getenv("RG_INTERP_2D");
        g_2d = !(f && f[0] == '0');
        f = getenv("RG_INTERP_ZSCALE");
        if (f && *f) g_zs_mode = atoi(f);
        f = getenv("RG_INTERP_LEAD");
        if (f && *f) {
            g_lead = (float)atof(f);
            if (!(g_lead >= 0.0f)) g_lead = 0.0f;
            if (g_lead > 1.0f) g_lead = 1.0f;
        }
        f = getenv("RG_INTERP_FAR_ANG");
        if (f && *f) g_jump_ang = (float)atof(f);
        f = getenv("RG_INTERP_CUT_DEG");
        if (f && *f) g_cut_deg = (float)atof(f);
        f = getenv("RG_INTERP_CUT_PX");
        if (f && *f) g_cut_px = (float)atof(f);
    }
    c.on = on;
    g_frames_ee = 0;
    g_dirty_ee = 0;
    nr_q_call(w_config, NULL, &c, sizeof c);
}

int nr_ip_on(void) { return g_on_ee > 0; }

void nr_ip_tick(uint64_t ticks)
{
    g_ticks = ticks;
    if (g_on_ee > 0) nr_q_call(w_tick, NULL, &ticks, sizeof ticks);   /* (the phase the next GS input is from) */
}

void nr_ip_frame_begin(uint32_t frame_no)
{
    w_bnd b;
    if (g_on_ee <= 0) return;
    b.frame = frame_no;
    b.pad = 0;
    b.T = g_ticks;
    g_frames_ee++;
    nr_q_call(w_boundary, NULL, &b, sizeof b);
}

int nr_ip_queue_present(double tau, const uint64_t *preg)
{
    w_req q;
    if (g_on_ee <= 0 || g_frames_ee < 3) return 0;
    memset(&q, 0, sizeof q);
    q.tau = tau;
    if (preg) {
        q.pmode = preg[0];
        q.dispfb[0] = preg[7];
        q.dispfb[1] = preg[9];
    }
    q.mode = 1;
    nr_q_call(w_pass, NULL, &q, sizeof q);
    g_dirty_ee = 1;
    return 1;
}

int nr_ip_queue_exact(void)
{
    w_req q;
    if (g_on_ee <= 0 || g_frames_ee < 2) return 0;
    memset(&q, 0, sizeof q);
    q.mode = 2;
    nr_q_call(w_pass, NULL, &q, sizeof q);
    return 1;
}

void nr_ip_settle(void)
{
    if (g_on_ee <= 0 || !g_dirty_ee) return;
    g_dirty_ee = 0;
    nr_q_call(w_restore, NULL, NULL, 0);
}

void nr_ip_stats(FILE *f)
{
    double it;
    if (!f || g_on_ee <= 0) return;
    it = g_st.items ? 100.0 / (double)g_st.items : 0.0;
    fprintf(f, "interp: logs %llu (voided %llu, %llu not replayable), device commands %.1f per log (most %llu), pre-images %.2f "
               "and targets created %.2f per log; mesh items %llu (most %llu per log): interpolated %.1f %%, camera only %.1f %% "
               "(of them jumped %llu), exact %.1f %% (Z-scale composite %llu, cut logs %llu), unmatched %.1f %%; skinned %llu "
               "(bone rows shared %llu), shadow %llu, lines %llu, not derivable %llu; immediate records %llu, repeated exactly %.1f %%\n",
            (unsigned long long)g_st.logs, (unsigned long long)g_st.voided, (unsigned long long)g_st.bad_logs,
            g_st.logs ? (double)g_st.cmds / (double)g_st.logs : 0.0, (unsigned long long)g_st.cmds_max,
            g_st.logs ? (double)g_st.pre / (double)g_st.logs : 0.0, g_st.logs ? (double)g_st.born / (double)g_st.logs : 0.0,
            (unsigned long long)g_st.items, (unsigned long long)g_st.items_max, g_st.full * it,
            g_st.cam * it, (unsigned long long)g_st.jumped, g_st.exact * it, (unsigned long long)g_st.zscale,
            (unsigned long long)g_st.cut_logs, g_st.unmatched * it, (unsigned long long)g_st.skin,
            (unsigned long long)g_st.overlap, (unsigned long long)g_st.shadow, (unsigned long long)g_st.lines,
            (unsigned long long)g_st.underivable, (unsigned long long)g_st.ims, g_st.ims ? 100.0 * (double)g_st.ims_static / (double)g_st.ims : 0.0);
    fprintf(f, "interp: passes %llu (%.2f ms each), restores %llu (%.2f ms), exact checks %llu (%.2f ms); skipped: no log %llu, "
               "no previous %llu, cut %llu, alpha 1 %llu, refused %llu; drawn interpolated %llu, camera only %llu, exact %llu, "
               "not found %llu; matrices slerped %llu, lerped %llu\n",
            (unsigned long long)g_st.passes, g_st.passes ? g_st.pass_ms / (double)g_st.passes : 0.0,
            (unsigned long long)g_st.restores, g_st.restores ? g_st.restore_ms / (double)g_st.restores : 0.0,
            (unsigned long long)g_st.exacts, g_st.exacts ? g_st.exact_ms / (double)g_st.exacts : 0.0,
            (unsigned long long)g_st.pass_skip_nolog, (unsigned long long)g_st.pass_skip_noprev,
            (unsigned long long)g_st.pass_skip_cut, (unsigned long long)g_st.pass_skip_alpha1,
            (unsigned long long)g_st.pass_stale, (unsigned long long)g_st.drawn_full, (unsigned long long)g_st.drawn_cam,
            (unsigned long long)g_st.drawn_exact, (unsigned long long)g_st.notfound,
            (unsigned long long)g_aff_slerp, (unsigned long long)g_aff_lerp);
    gpu_ip_stats(nr_gs_device(), f);
    if (g_census) fflush(g_census);
    if (g_trace) fflush(g_trace);
}

#else /* no native-only device: stubs */

void nr_ip_configure(int on) { (void)on; }
int nr_ip_on(void) { return 0; }
void nr_ip_tick(uint64_t ticks) { (void)ticks; }
void nr_ip_frame_begin(uint32_t frame_no) { (void)frame_no; }
int nr_ip_queue_present(double tau, const uint64_t *display_regs) { (void)tau; (void)display_regs; return 0; }
int nr_ip_queue_exact(void) { return 0; }
void nr_ip_settle(void) {}
void nr_ip_stats(FILE *f) { (void)f; }
void nr_ip_w_rec(uint32_t id) { (void)id; }
void nr_ip_w_image(const void *qw, uint32_t nqw) { (void)qw; (void)nqw; }
void nr_ip_w_reset(void) {}
int nr_ip_pass(void) { return 0; }
void nr_ip_note(uint32_t id, const void *mesh, int variant, uint32_t ctx, uint64_t frame_reg, int has_box,
                const float box[4], const void *c, const void *bones, uint32_t bones_hi)
{
    (void)id; (void)mesh; (void)variant; (void)ctx; (void)frame_reg; (void)has_box; (void)box; (void)c; (void)bones;
    (void)bones_hi;
}
const nr_ip_draw *nr_ip_draw_for(uint32_t id) { (void)id; return NULL; }
int nr_ip_zs_mode(void) { return 0; }
void nr_ip_zs_allow(int ok) { (void)ok; }
int nr_ip_zs_item(uint32_t id) { (void)id; return 0; }

#endif

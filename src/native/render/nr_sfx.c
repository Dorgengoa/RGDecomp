/* SPDX-License-Identifier: CC0-1.0 */
/* Screen effects in the native renderer (nr_sfx.h, docs/NATIVE-RENDER.md "Screen effects").
 *
 * Every immediate record carries the name of the game task that built it (the task table's
 * own names: "Draw Glare", "Draw DOF", ...; TaskTableRun_1f5340 override -> nr_im_task).  The
 * game's full-screen passes are each built by one task (census: tools/p6/fxcensus.py over
 * $RG_NR_FXLOG), so a batch's class is its task plus, where a task draws other things too,
 * the batch's state (render target, texture, coverage).  Per class the settings decide:
 *
 *   original  the batch as it is (every class: Original is pixel-identical)
 *   off       the pass's batches into the scene's frame buffer are left out (its work
 *             buffers are still drawn, so nothing later reads different texels); a batch that
 *             writes depth is drawn with its colour masked instead (the depth target, which
 *             the lens-flare probe reads, stays exactly the same)
 *   enhanced  see nr_sfx_batch (per class)
 *
 * Reduced flashing (accessibility.flashing): flash-class batches (fades to a colour, effect
 * flashes: full-screen quads) have their colour / alpha limited, and a large frame-to-frame
 * rise of the flash's intensity is spread over several frames.
 *
 * $RG_NR_FXLOG=path: one TSV line per immediate batch (task, render target, texture, blend,
 * coverage, colours; frames $RG_NR_FXLOG_FROM..$RG_NR_FXLOG_TO); tools/p6/fxcensus.py groups
 * it into the census.  $RG_NR_SFX=0: no classification at all (control). */
#include "nr_sfx.h"

#include <stdlib.h>
#include <string.h>

#include "nr.h"
#ifdef RG_HAVE_GPU
#include "gpu.h"
#endif
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY && defined(RG_HAVE_GPU)
#include "nr_gs.h"
#define SFX_ON 1
#define BITS(v, lo, n) ((uint32_t)(((uint64_t)(v) >> (lo)) & ((1ull << (n)) - 1ull)))
#else
#define SFX_ON 0
#endif

#ifndef NR_SFX_BLOOM_GAIN
#define NR_SFX_BLOOM_GAIN 0.91f
#endif

static const char *const k_names[NR_SFX_COUNT] = {
    "none", "glare", "tbox_bloom", "dof", "focus", "cblur", "tint", "fade", "pause", "flash", "particles", "shadow",
};
const char *nr_sfx_name(int cls) { return cls >= 0 && cls < NR_SFX_COUNT ? k_names[cls] : "?"; }

static struct {
    uint64_t batches[NR_SFX_COUNT], prims[NR_SFX_COUNT], skipped[NR_SFX_COUNT], zonly[NR_SFX_COUNT];
    uint64_t flash_clamped, flash_ramped, light_limited, enhanced[NR_SFX_COUNT];
} g_st;

#if SFX_ON
static int task_class(const char *t)
{
    static const struct { const char *name; int cls; } tab[] = {
        { "Draw Glare", NR_SFX_GLARE },          { "Draw TBox", NR_SFX_TBOX_BLOOM },
        { "Draw DOF", NR_SFX_DOF },              { "Draw Focus", NR_SFX_FOCUS },
        { "Draw Chara Blur", NR_SFX_CBLUR },     { "Draw Gray Scale Filter", NR_SFX_TINT },
        { "Draw Fade", NR_SFX_FADE },            { "Draw Pause Filter", NR_SFX_PAUSE },
        { "Draw Effect", NR_SFX_FLASH },         { "Draw Prog Effect", NR_SFX_FLASH },
        { "Draw Status Effect", NR_SFX_FLASH },  { "Draw Shadow", NR_SFX_SHADOW },
    };
    size_t i;
    if (!t) return NR_SFX_NONE;
    for (i = 0; i < sizeof tab / sizeof tab[0]; i++)
        if (!strcmp(t, tab[i].name)) return tab[i].cls;
    return NR_SFX_NONE;
}

/* ---- census log ---------------------------------------------------------------------- */
static FILE *g_log;
static uint32_t g_mask_tbp;   /* the motion blur's mask texture (TBP0; 0 = not seen yet) */
static uint32_t g_log_from, g_log_to = 0xFFFFFFFFu;
static int log_open(void)
{
    static int st = -1;
    if (st < 0) {
        const char *p = getenv("RG_NR_FXLOG"), *a = getenv("RG_NR_FXLOG_FROM"), *b = getenv("RG_NR_FXLOG_TO");
        st = 0;
        if (a) g_log_from = (uint32_t)strtoul(a, NULL, 10);
        if (b) g_log_to = (uint32_t)strtoul(b, NULL, 10);
        if (p && p[0] && (g_log = fopen(p, "w")) != NULL) {
            st = 1;
            fprintf(g_log, "frame\ttask\tcls\tctx\tfbp\tfbw\tfpsm\tfbmsk\tzbp\tzmsk\tzte\tztst\tabe\talpha\ttme\ttbp\ttbw\ttpsm"
                           "\ttw\tth\ttfx\ttcc\tlin\tprim\tn\tx0\ty0\tx1\ty1\tarea\tcmin\tcmax\tfst\tumin\tvmin\tumax\tvmax\tsc\n");
        }
    }
    return st;
}

typedef struct bstat {
    float x0, y0, x1, y1, area, u0, v0, u1, v1;
    uint8_t cmin[4], cmax[4];
} bstat;

static void batch_stats(const gpu_gs *gs, const gs_vertex *v, int n, int type, uint64_t attr, bstat *b)
{
    int c = (int)BITS(attr, 9, 1), i, j, k;
    uint64_t xy = gs->reg[GS_XYOFFSET_1 + c], t0 = gs->reg[GS_TEX0_1 + c];
    float ox = (float)BITS(xy, 0, 16) / 16.0f, oy = (float)BITS(xy, 32, 16) / 16.0f;
    float tw = (float)(1u << BITS(t0, 26, 4)), th = (float)(1u << BITS(t0, 30, 4));
    int nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_SPRITE || type == GS_PRIM_LINE ? 2 : 1;
    int fst = (int)BITS(attr, 8, 1);
    b->x0 = b->y0 = b->u0 = b->v0 = 1e30f;
    b->x1 = b->y1 = b->u1 = b->v1 = -1e30f;
    b->area = 0.0f;
    for (k = 0; k < 4; k++) { b->cmin[k] = 255; b->cmax[k] = 0; }
    for (i = 0; i < n; i++) {
        float px[3], py[3];
        for (j = 0; j < nv; j++) {
            const gs_vertex *p = &v[i * 3 + j];
            uint8_t cc[4] = { p->r, p->g, p->b, p->a };
            float U, V;
            px[j] = (float)p->x / 16.0f - ox;
            py[j] = (float)p->y / 16.0f - oy;
            if (px[j] < b->x0) b->x0 = px[j];
            if (px[j] > b->x1) b->x1 = px[j];
            if (py[j] < b->y0) b->y0 = py[j];
            if (py[j] > b->y1) b->y1 = py[j];
            if (fst) { U = (float)p->u / 16.0f; V = (float)p->v / 16.0f; }
            else { float iq = p->q != 0.0f ? 1.0f / p->q : 0.0f; U = p->s * iq * tw; V = p->t * iq * th; }
            if (U < b->u0) b->u0 = U;
            if (U > b->u1) b->u1 = U;
            if (V < b->v0) b->v0 = V;
            if (V > b->v1) b->v1 = V;
            for (k = 0; k < 4; k++) {
                if (cc[k] < b->cmin[k]) b->cmin[k] = cc[k];
                if (cc[k] > b->cmax[k]) b->cmax[k] = cc[k];
            }
        }
        if (nv == 2 && type == GS_PRIM_SPRITE) {
            float a = (px[1] - px[0]) * (py[1] - py[0]);
            b->area += a < 0 ? -a : a;
        } else if (nv == 3) {
            float a = 0.5f * ((px[1] - px[0]) * (py[2] - py[0]) - (px[2] - px[0]) * (py[1] - py[0]));
            b->area += a < 0 ? -a : a;
        }
    }
}

static void log_batch(const gpu_gs *gs, int cls, const gs_vertex *v, int n, int type, uint64_t attr, const char *task,
                      uint32_t frame)
{
    int c = (int)BITS(attr, 9, 1);
    uint64_t fr = gs->reg[GS_FRAME_1 + c], zb = gs->reg[GS_ZBUF_1 + c], te = gs->reg[GS_TEST_1 + c];
    uint64_t al = gs->reg[GS_ALPHA_1 + c], t0 = gs->reg[GS_TEX0_1 + c], t1 = gs->reg[GS_TEX1_1 + c];
    uint64_t sc = gs->reg[GS_SCISSOR_1 + c];
    int tme = (int)BITS(attr, 4, 1);
    bstat b;
    static int all = -1;
    if (all < 0) { const char *e = getenv("RG_NR_FXLOG_ALL"); all = e && e[0] == '1'; }
    int mask;
    if (frame < g_log_from || frame > g_log_to) return;
    /* the motion blur's mask (CBlurDrawMaybe_1784e0 copies it into the afterimage buffer's alpha,
     * FBMSK 00FFFFFF): its texture is learned from that copy; any other batch into it is a write of
     * the mask (ModelDrawOffscreenCompositeMaybe_16aac0: a model with a blur texture marks its
     * screen box with alpha 128 x its blur alpha), logged with class "mask" (tools/p6/cblurscan.py) */
    if (cls == NR_SFX_CBLUR && tme && BITS(fr, 32, 32) == 0x00FFFFFFu) g_mask_tbp = (uint32_t)BITS(t0, 0, 14);
    mask = cls != NR_SFX_CBLUR && g_mask_tbp && (uint32_t)BITS(fr, 0, 9) * 32u == g_mask_tbp;
    batch_stats(gs, v, n, type, attr, &b);
    /* default: classified batches, screen-sized ones and mask writes ($RG_NR_FXLOG_ALL=1: every batch) */
    if (!all && !mask && cls == NR_SFX_NONE && b.area < 0.5f * 512.0f * 448.0f &&
        !(b.x1 - b.x0 >= 500.0f && b.y1 - b.y0 >= 400.0f))
        return;
    fprintf(g_log, "%u\t%s\t%s\t%d\t%u\t%u\t%u\t%08X\t%u\t%u\t%u\t%u\t%u\t%016llX\t%d\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%d\t%d"
                   "\t%.1f\t%.1f\t%.1f\t%.1f\t%.0f\t%02X%02X%02X%02X\t%02X%02X%02X%02X\t%u\t%.1f\t%.1f\t%.1f\t%.1f"
                   "\t%u,%u,%u,%u\n",
            frame, task ? task : "-", mask ? "mask" : nr_sfx_name(cls), c, (unsigned)BITS(fr, 0, 9) * 32u, (unsigned)BITS(fr, 16, 6),
            (unsigned)BITS(fr, 24, 6), (unsigned)BITS(fr, 32, 32), (unsigned)BITS(zb, 0, 9) * 32u, (unsigned)BITS(zb, 32, 1),
            (unsigned)BITS(te, 16, 1), (unsigned)BITS(te, 17, 2), (unsigned)BITS(attr, 6, 1), (unsigned long long)al, tme,
            tme ? (unsigned)BITS(t0, 0, 14) : 0u, tme ? (unsigned)BITS(t0, 14, 6) : 0u, tme ? (unsigned)BITS(t0, 20, 6) : 0u,
            tme ? 1u << BITS(t0, 26, 4) : 0u, tme ? 1u << BITS(t0, 30, 4) : 0u, (unsigned)BITS(t0, 35, 2),
            (unsigned)BITS(t0, 34, 1), (unsigned)BITS(t1, 5, 1), type, n, b.x0, b.y0, b.x1, b.y1, b.area,
            b.cmin[0], b.cmin[1], b.cmin[2], b.cmin[3], b.cmax[0], b.cmax[1], b.cmax[2], b.cmax[3],
            (unsigned)BITS(attr, 8, 1), tme ? b.u0 : 0.0f, tme ? b.v0 : 0.0f, tme ? b.u1 : 0.0f, tme ? b.v1 : 0.0f,
            (unsigned)BITS(sc, 0, 11), (unsigned)BITS(sc, 32, 11), (unsigned)BITS(sc, 16, 11), (unsigned)BITS(sc, 48, 11));
    {
        static uint32_t last;
        if (frame != last) { last = frame; fflush(g_log); }
    }
}
#endif

#if SFX_ON
/* bloom "enhanced" at the internal resolution ($RG_NR_SFX_HIRES=0: the 192x192 buffers filled
 * by a box filter instead, PF_BOX, the 11-01 p6fx version) */
static int hires_on(void)
{
    static int on = -1;
    if (on < 0) { const char *x = getenv("RG_NR_SFX_HIRES"); on = !(x && x[0] == '0'); }
    return on;
}
/* the colour factor of the bloom's draw over the frame at the internal resolution: the PS2's
 * mean added light (docs/NATIVE-RENDER.md "Screen effects": measured, tools/p6/bloomgain.py);
 * $RG_NR_SFX_BLOOM_GAIN=k overrides (1 = the full-resolution chain as the game weights it) */
static float bloom_gain(void)
{
    static float k = -1.0f;
    if (k < 0.0f) {
        const char *x = getenv("RG_NR_SFX_BLOOM_GAIN");
        k = x && x[0] ? (float)atof(x) : NR_SFX_BLOOM_GAIN;
        if (!(k >= 0.0f && k <= 4.0f)) k = 1.0f;
    }
    return k;
}

/* the footprint (in work-buffer pixels) the twin's copy of the frame averages per pixel, colour
 * and alpha apart as the GS's taps do (the PS2's bright-pass strength at every pixel: steady);
 * $RG_NR_SFX_BLOOM_BOX=k overrides (0: plain bilinear, the full-resolution bright pass) */
static float bloom_box(void)
{
    static float k = -1.0f;
    if (k < 0.0f) {
        const char *x = getenv("RG_NR_SFX_BLOOM_BOX");
        k = x && x[0] ? (float)atof(x) : 1.0f;
        if (!(k >= 0.0f && k <= 4.0f)) k = 1.0f;
    }
    return k;
}

/* the setting for a class (GPU_FXMODE_*); -1: no toggle */
static int class_mode(const gpu_enhance *e, int cls)
{
    switch (cls) {
    case NR_SFX_GLARE: case NR_SFX_TBOX_BLOOM: return e->fx[GPU_FX_BLOOM];
    case NR_SFX_DOF: case NR_SFX_FOCUS: return e->fx[GPU_FX_DOF];
    case NR_SFX_CBLUR: return e->fx[GPU_FX_MOTION_BLUR];
    case NR_SFX_SHADOW: return e->shadow_res == 1 ? GPU_FXMODE_ENHANCED : GPU_FXMODE_ORIGINAL;
    default: return -1;
    }
}

/* reduced flashing: per class the intensity let through on the last EE frame that had one
 * (0..128 = white at full strength); a rise is limited per frame (frames, not presents: an
 * interpolated present replays the recorded draws and never comes here) */
static struct { uint32_t frame; float level; } g_fl[NR_SFX_COUNT];

static int flash_limit(const gpu_gs *gs, int cls, gs_vertex *v, int n, int type, uint64_t attr, uint32_t frame,
                       int mode)
{
    static const float cap_of[3] = { 128.0f, 36.0f, 20.0f }, step_of[3] = { 128.0f, 6.0f, 4.0f };
    int c = (int)BITS(attr, 9, 1), nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_SPRITE || type == GS_PRIM_LINE ? 2 : 1;
    uint64_t al = gs->reg[GS_ALPHA_1 + c];
    int A = (int)BITS(al, 0, 2), B = (int)BITS(al, 2, 2), C = (int)BITS(al, 4, 2), D = (int)BITS(al, 6, 2);
    float fix = (float)BITS(al, 32, 8), want = 0.0f, allow, k;
    int i, j;
    /* only a blend that adds the source over the frame: (Cs - Cd) * F + Cd or Cs * F + Cd */
    if (!BITS(attr, 6, 1) || A != 0 || (B != 1 && B != 2) || D != 1 || C == 1) return 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < nv; j++) {
            const gs_vertex *p = &v[i * 3 + j];
            float m = (float)(p->r > p->g ? (p->r > p->b ? p->r : p->b) : (p->g > p->b ? p->g : p->b));
            float f = C == 2 ? fix : (float)p->a;
            float it;
            if (m < 64.0f && B == 1) continue;   /* a fade toward a dark colour: no flash */
            it = m / 255.0f * (f > 128.0f ? 128.0f : f);   /* white at full strength = 128 */
            if (it > want) want = it;
        }
    if (want <= 0.0f) return 0;
    if (frame != g_fl[cls].frame) {
        /* the level a frame ago (none since: 0), plus one step */
        float lim = (frame - g_fl[cls].frame == 1u ? g_fl[cls].level : 0.0f) + step_of[mode];
        allow = want < lim ? want : lim;
        if (allow > cap_of[mode]) allow = cap_of[mode];
        g_fl[cls].frame = frame;
        g_fl[cls].level = allow;
    } else {
        allow = g_fl[cls].level;   /* (another batch of the same frame: the same limit) */
        if (want < allow) allow = want;
    }
    if (allow >= want) return 0;
    k = allow / want;
    if (want > cap_of[mode]) g_st.flash_clamped++;
    else g_st.flash_ramped++;
    for (i = 0; i < n; i++)
        for (j = 0; j < nv; j++) {
            gs_vertex *p = &v[i * 3 + j];
            if (C == 2) {
                p->r = (uint8_t)((float)p->r * k); p->g = (uint8_t)((float)p->g * k); p->b = (uint8_t)((float)p->b * k);
            } else {
                p->a = (uint8_t)((float)p->a * k);
            }
        }
    return 1;
}

/* the blend adds the source over the frame (as flash_limit): 0 = no, 1 = (Cs - Cd) * F + Cd, 2 = Cs * F + Cd */
static int adds_light(const gpu_gs *gs, uint64_t attr)
{
    uint64_t al = gs->reg[GS_ALPHA_1 + (int)BITS(attr, 9, 1)];
    int A = (int)BITS(al, 0, 2), B = (int)BITS(al, 2, 2), C = (int)BITS(al, 4, 2), D = (int)BITS(al, 6, 2);
    if (!BITS(attr, 6, 1) || A != 0 || (B != 1 && B != 2) || D != 1 || C == 1) return 0;
    return B == 2 ? 2 : 1;
}

/* the area of a polygon clipped to the rectangle x0..x1, y0..y1 (Sutherland-Hodgman) */
static float clip_area(const float *px, const float *py, int nv, float x0, float y0, float x1, float y1)
{
    float ax[12], ay[12], bx[12], by[12], a = 0.0f;
    int n = nv, e, i, m;
    for (i = 0; i < nv; i++) { ax[i] = px[i]; ay[i] = py[i]; }
    for (e = 0; e < 4 && n > 0; e++) {
        m = 0;
        for (i = 0; i < n; i++) {
            float sx = ax[i], sy = ay[i], tx = ax[(i + 1) % n], ty = ay[(i + 1) % n];
            float ds = e == 0 ? sx - x0 : e == 1 ? x1 - sx : e == 2 ? sy - y0 : y1 - sy;
            float dt = e == 0 ? tx - x0 : e == 1 ? x1 - tx : e == 2 ? ty - y0 : y1 - ty;
            if (ds >= 0.0f && m < 12) { bx[m] = sx; by[m] = sy; m++; }
            if ((ds >= 0.0f) != (dt >= 0.0f) && m < 12) {
                float k = ds / (ds - dt);
                bx[m] = sx + (tx - sx) * k; by[m] = sy + (ty - sy) * k; m++;
            }
        }
        n = m;
        for (i = 0; i < n; i++) { ax[i] = bx[i]; ay[i] = by[i]; }
    }
    for (i = 0; i < n; i++) a += ax[i] * ay[(i + 1) % n] - ax[(i + 1) % n] * ay[i];
    return a < 0.0f ? -0.5f * a : 0.5f * a;
}

/* the light a batch adds, in flash levels (a full-screen white flash at full strength = 128):
 * per primitive its area inside the scissor x its strength (brightest vertex colour; for a
 * textured one the colour's scale of the texel times NR_SFX_TEXW, a typical particle texture's
 * mean coverage: the texels are not known here) x its blend factor (As: vertex alpha, 128 = 1; or FIX) */
#ifndef NR_SFX_TEXW
#define NR_SFX_TEXW 0.5f
#endif
static float batch_light(const gpu_gs *gs, const gs_vertex *v, int n, int type, uint64_t attr)
{
    int c = (int)BITS(attr, 9, 1), tme = (int)BITS(attr, 4, 1), i, j;
    int nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_SPRITE ? 2 : 0;
    uint64_t xy = gs->reg[GS_XYOFFSET_1 + c], sc = gs->reg[GS_SCISSOR_1 + c], al = gs->reg[GS_ALPHA_1 + c];
    uint64_t t0 = gs->reg[GS_TEX0_1 + c];
    float ox = (float)BITS(xy, 0, 16) / 16.0f, oy = (float)BITS(xy, 32, 16) / 16.0f;
    float sx0 = (float)BITS(sc, 0, 11), sx1 = (float)BITS(sc, 16, 11) + 1.0f;
    float sy0 = (float)BITS(sc, 32, 11), sy1 = (float)BITS(sc, 48, 11) + 1.0f;
    int C = (int)BITS(al, 4, 2), tfx = (int)BITS(t0, 35, 2);
    float fix = (float)BITS(al, 32, 8) / 128.0f, sum = 0.0f;
    if (!nv) return 0.0f;
    if (fix > 1.0f) fix = 1.0f;
    for (i = 0; i < n; i++) {
        float px[3], py[3], m = 0.0f, f = 0.0f, k, area;
        for (j = 0; j < nv; j++) {
            const gs_vertex *p = &v[i * 3 + j];
            float mc = (float)(p->r > p->g ? (p->r > p->b ? p->r : p->b) : (p->g > p->b ? p->g : p->b));
            float fa = C == 2 ? fix : ((float)p->a / 128.0f > 1.0f ? 1.0f : (float)p->a / 128.0f);
            /* the colour's strength: untextured 255 = white; textured (modulate) 128 = the texel */
            mc = !tme ? mc / 255.0f : tfx == 1 ? 1.0f : (mc / 128.0f > 1.0f ? 1.0f : mc / 128.0f);
            if (mc > m) m = mc;
            if (fa > f) f = fa;
            px[j] = (float)p->x / 16.0f - ox;
            py[j] = (float)p->y / 16.0f - oy;
        }
        k = m * f * (tme ? NR_SFX_TEXW : 1.0f);
        if (k <= 0.0f) continue;
        if (nv == 2) {
            float x0 = px[0] < px[1] ? px[0] : px[1], x1 = px[0] < px[1] ? px[1] : px[0];
            float y0 = py[0] < py[1] ? py[0] : py[1], y1 = py[0] < py[1] ? py[1] : py[0];
            if (x0 < sx0) x0 = sx0;
            if (y0 < sy0) y0 = sy0;
            if (x1 > sx1) x1 = sx1;
            if (y1 > sy1) y1 = sy1;
            area = x1 > x0 && y1 > y0 ? (x1 - x0) * (y1 - y0) : 0.0f;
        } else {
            area = clip_area(px, py, 3, sx0, sy0, sx1, sy1);
        }
        sum += area * k;
    }
    return sum / (512.0f * 448.0f) * 128.0f;
}

/* reduced flashing over the frame's whole added light: the effects' bright additive batches
 * (flash and particle classes) of one EE frame share one budget, flash_limit's caps applied to
 * their sum (an effect's many smaller particles light as much of the screen as one full-screen
 * flash), and the sum may rise only one step per EE frame.  A batch is scaled by the factor that
 * held the previous frame's demand to its budget (a steady burst dims evenly) and, past the
 * budget left in this frame, by what remains (the first frame of a burst). */
static struct { uint32_t frame; float used, demand, allow, kf; } g_lt;

static void light_limit(const gpu_gs *gs, gs_vertex *v, int n, int type, uint64_t attr, uint32_t frame, int mode)
{
    static const float cap_of[3] = { 128.0f, 36.0f, 20.0f }, step_of[3] = { 128.0f, 6.0f, 4.0f };
    int c = (int)BITS(attr, 9, 1), nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_SPRITE ? 2 : 1, i, j, C;
    float e = batch_light(gs, v, n, type, attr), k;
    if (e <= 0.0f) return;
    if (frame != g_lt.frame) {
        int next = frame - g_lt.frame == 1u;
        float lev = next ? g_lt.used : 0.0f, dem = next ? g_lt.demand : 0.0f;
        g_lt.allow = lev + step_of[mode];
        if (g_lt.allow > cap_of[mode]) g_lt.allow = cap_of[mode];
        g_lt.kf = dem > g_lt.allow ? g_lt.allow / dem : 1.0f;
        g_lt.frame = frame;
        g_lt.used = g_lt.demand = 0.0f;
    }
    g_lt.demand += e;
    k = g_lt.kf;
    if (g_lt.used + e * k > g_lt.allow) k = g_lt.allow > g_lt.used ? (g_lt.allow - g_lt.used) / e : 0.0f;
    g_lt.used += e * k;
    if (k >= 1.0f) return;
    g_st.light_limited++;
    C = (int)BITS(gs->reg[GS_ALPHA_1 + c], 4, 2);
    for (i = 0; i < n; i++)
        for (j = 0; j < nv; j++) {
            gs_vertex *p = &v[i * 3 + j];
            if (C == 2) {
                p->r = (uint8_t)((float)p->r * k); p->g = (uint8_t)((float)p->g * k); p->b = (uint8_t)((float)p->b * k);
            } else {
                p->a = (uint8_t)((float)p->a * k);
            }
        }
}
#endif

/* (ptbugs3) the focus pre-filter's box in native pixels x 100 ($RG_NR_SFX_FOCUSK=k, default 1: one
 * PS2 pixel; nr_dev.cpp focus_prefilter) */
int nr_sfx_focus_k(void)
{
    static int k = -1;
    if (k < 0) {
        const char *x = getenv("RG_NR_SFX_FOCUSK");
        double f = x && x[0] ? atof(x) : 1.0;
        k = f >= 0.25 && f <= 8.0 ? (int)(f * 100.0 + 0.5) : 100;
    }
    return k;
}

int nr_sfx_batch(struct gpu_renderer *gr, gpu_gs *gs, gs_vertex *v, int n, int type, uint64_t attr, const char *task,
                 uint32_t frame)
{
#if SFX_ON
    static int on = -1;
    int cls, c, mode, tme, abe;
    uint64_t fr;
    bstat b;
    gpu_enhance e;
    if (on < 0) { const char *x = getenv("RG_NR_SFX"); on = !(x && x[0] == '0'); }
    if (!on) return NR_SFX_DRAW;
    cls = task_class(task);
    tme = (int)BITS(attr, 4, 1);
    abe = (int)BITS(attr, 6, 1);
    batch_stats(gs, v, n, type, attr, &b);
    if ((cls == NR_SFX_NONE || cls == NR_SFX_FLASH) && !tme && abe && type == GS_PRIM_SPRITE && n >= 100 &&
        b.x0 <= 0.5f && b.y0 <= 0.5f && b.x1 >= 511.5f && b.y1 >= 447.5f)
        cls = NR_SFX_FADE;   /* ScreenFadeBlockDraw_177540's tiled full-screen sprites, whoever draws them */
    if (cls == NR_SFX_NONE && !task && adds_light(gs, attr) == 2 &&
        !(tme && BITS(gs->reg[GS_TEX0_1 + BITS(attr, 9, 1)], 14, 6) >= 8))
        cls = NR_SFX_PARTICLES;   /* untagged (outside any task: packets the frame walker decodes) pure
                                   * additive batches, not a copy of the picture (frame-wide texture) */
    if (cls == NR_SFX_FLASH || cls == NR_SFX_PARTICLES) {
        if (abe && b.area >= 0.5f * 512.0f * 448.0f)
            cls = NR_SFX_FLASH;   /* full-screen: an effect flash, or an untagged one */
        else
            cls = adds_light(gs, attr) ? NR_SFX_PARTICLES : NR_SFX_NONE;   /* an effect's particles */
    }
    if (log_open()) log_batch(gs, cls, v, n, type, attr, task, frame);
    if (cls == NR_SFX_NONE) return NR_SFX_DRAW;
    g_st.batches[cls]++;
    g_st.prims[cls] += (uint64_t)n;
    gpu_get_enhance(gr, &e);
    if (cls == NR_SFX_FADE || cls == NR_SFX_FLASH) {
        static int ft = -1;
        if (ft < 0) { const char *x = getenv("RG_NR_SFX_FLASHTEST"); ft = x && x[0] == '1'; }
        if (ft && cls == NR_SFX_FADE && !tme) {
            /* TEST ONLY ($RG_NR_SFX_FLASHTEST=1): the game's fades drawn white, a flash to exercise
             * accessibility.flashing on real fades (presentation only, like any fade colour) */
            int i, j;
            for (i = 0; i < n; i++)
                for (j = 0; j < 3; j++) { v[i * 3 + j].r = 0xFF; v[i * 3 + j].g = 0xFF; v[i * 3 + j].b = 0xFF; }
        }
        if (e.flash > 0 && e.flash <= 2) {
            flash_limit(gs, cls, v, n, type, attr, frame, e.flash);
            if (cls == NR_SFX_FLASH) light_limit(gs, v, n, type, attr, frame, e.flash);
        }
        return NR_SFX_DRAW;
    }
    if (cls == NR_SFX_PARTICLES) {
        if (e.flash > 0 && e.flash <= 2) light_limit(gs, v, n, type, attr, frame, e.flash);
        return NR_SFX_DRAW;
    }
    mode = class_mode(&e, cls);
    c = (int)BITS(attr, 9, 1);
    fr = gs->reg[GS_FRAME_1 + c];
    if (cls == NR_SFX_FOCUS && mode != GPU_FXMODE_OFF && tme && abe && BITS(fr, 16, 6) >= 8 &&
        BITS(fr, 32, 32) == 0xFF000000u && b.x1 - b.x0 >= 400.0f && b.y1 - b.y0 >= 300.0f) {
        /* (ptbugs3) the focus blur's composite (FocusFilterDrawMaybe_17c000's last sprite: the
         * 192x192 buffer over the frame, RGB only, by its soft depth mask): the frame under it is
         * softened to the PS2's resolution at an internal scale > 1 (nr_dev.cpp focus_prefilter).
         * $RG_NR_SFX_FOCUSLP: 2 (default) Original and Enhanced, 1 Enhanced only, 0 the old path */
        static int lp = -1;
        if (lp < 0) { const char *x = getenv("RG_NR_SFX_FOCUSLP"); lp = x && x[0] >= '0' && x[0] <= '2' ? x[0] - '0' : 2; }
        if (lp == 2 || (lp == 1 && mode == GPU_FXMODE_ENHANCED)) {
            g_st.enhanced[cls]++;
            /* the read's texels per pixel (192 / 512): focus_blur_read's footprint */
            gpu_set_im_focus_ratio(gr, b.x1 > b.x0 ? (b.u1 - b.u0) / (b.x1 - b.x0) : 0.0f);
            return NR_SFX_FOCUSLP;
        }
    }
    if (mode <= GPU_FXMODE_ORIGINAL) return NR_SFX_DRAW;
    if (mode == GPU_FXMODE_OFF) {
        /* the pass's blend over the frame (a frame-wide target, screen-sized) */
        if (abe && BITS(fr, 16, 6) >= 8 && b.x1 - b.x0 >= 400.0f && b.y1 - b.y0 >= 300.0f) {
            uint64_t zb = gs->reg[GS_ZBUF_1 + c];
            /* the chara-blur pass in its additive mode (battle, GameSceneCBlurResetMode2Maybe_2f1da0:
             * ALPHA 0x48, a grey glow through the mask) is the charged-weapon aura ("sword is
             * radiating lightning", TaskCharaAction_1fa5c0), game state rather than an afterimage:
             * kept; only the afterimage (the previous picture lerped in, ALPHA 0x44) is left out */
            if (cls == NR_SFX_CBLUR && adds_light(gs, attr) == 2) return NR_SFX_DRAW;
            if (!BITS(zb, 32, 1)) { g_st.zonly[cls]++; return NR_SFX_ZONLY; }
            g_st.skipped[cls]++;
            return NR_SFX_SKIP;
        }
        return NR_SFX_DRAW;
    }
    if (mode == GPU_FXMODE_ENHANCED && (cls == NR_SFX_GLARE || cls == NR_SFX_TBOX_BLOOM || cls == NR_SFX_SHADOW) && hires_on()) {
        /* bloom at the internal resolution: every batch of the pass, its work buffers twinned at
         * the frame's internal resolution (nr_dev.cpp "twins"); the draw over the frame reads the
         * twin, its colour scaled to the PS2's strength (bloom_gain) */
        static float hs[NR_SFX_COUNT][2];
        uint64_t sc = gs->reg[GS_SCISSOR_1 + c];
        float sx = hs[cls][0] > 0.0f ? hs[cls][0] : 512.0f / 192.0f, sy = hs[cls][1] > 0.0f ? hs[cls][1] : 448.0f / 192.0f;
        if (BITS(fr, 16, 6) < 8) {
            /* a work buffer: (its scissor) -> the frame (512 x 448) */
            float w = (float)BITS(sc, 16, 11) + 1.0f - (float)BITS(sc, 0, 11);
            float h = (float)BITS(sc, 48, 11) + 1.0f - (float)BITS(sc, 32, 11);
            int psm = (int)BITS(fr, 24, 6);   /* (p6left: not the shadow buffer's CT16 view, 192 x 384) */
            if (w >= 16.0f && h >= 16.0f && w < 512.0f && h <= 448.0f && (psm == 0x00 || psm == 0x01)) {
                sx = hs[cls][0] = 512.0f / w;
                sy = hs[cls][1] = 448.0f / h;
            }
        } else if (tme && abe && cls != NR_SFX_SHADOW) {
            float k = bloom_gain();
            int i, j, nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_SPRITE ? 2 : 1;
            if (k != 1.0f)
                for (i = 0; i < n; i++)
                    for (j = 0; j < nv; j++) {
                        gs_vertex *p = &v[i * 3 + j];
                        float r_ = (float)p->r * k + 0.5f, g_ = (float)p->g * k + 0.5f, b_ = (float)p->b * k + 0.5f;
                        p->r = (uint8_t)(r_ > 255.0f ? 255.0f : r_);
                        p->g = (uint8_t)(g_ > 255.0f ? 255.0f : g_);
                        p->b = (uint8_t)(b_ > 255.0f ? 255.0f : b_);
                    }
        }
        /* (the shadow pass: the GS's own filter on its copy of the frame mask, no box) */
        gpu_set_im_hires(gr, cls == NR_SFX_SHADOW ? 2 : 1, sx, sy, cls == NR_SFX_SHADOW ? 0.0f : bloom_box(), frame);
        g_st.enhanced[cls]++;
        return NR_SFX_HIRES;
    }
    if (mode == GPU_FXMODE_ENHANCED && tme) {
        /* a minifying read (the frame into the pass's reduced work buffer): box-filtered over
         * the footprint at the internal resolution when the texture is a live target */
        float dx = b.x1 - b.x0, dy = b.y1 - b.y0;
        if (dx > 0.0f && dy > 0.0f && ((b.u1 - b.u0) > 1.25f * dx || (b.v1 - b.v0) > 1.25f * dy)) {
            g_st.enhanced[cls]++;
            /* (p6left) depth of field: the footprint widened to the PS2's blur in screen units
             * (nr_dev.cpp gpu_set_im_box mode 2; $RG_NR_SFX_DOFK=0: p6fx2's plain box) */
            if (cls == NR_SFX_DOF || cls == NR_SFX_FOCUS) {
                static int k2 = -1;
                if (k2 < 0) { const char *x = getenv("RG_NR_SFX_DOFK"); k2 = !(x && x[0] == '0' && !x[1]); }
                if (k2) return NR_SFX_BOX2;
            }
            return NR_SFX_BOX;
        }
    }
    return NR_SFX_DRAW;
#else
    (void)gr; (void)gs; (void)v; (void)n; (void)type; (void)attr; (void)task; (void)frame;
    return NR_SFX_DRAW;
#endif
}

void nr_sfx_stats(FILE *f)
{
    int i, any = 0;
    if (!f) return;
    for (i = 1; i < NR_SFX_COUNT; i++) any |= g_st.batches[i] != 0;
    if (!any) return;
    fprintf(f, "native render screen effects (batches / primitives / left out / depth-only / enhanced):");
    for (i = 1; i < NR_SFX_COUNT; i++)
        if (g_st.batches[i])
            fprintf(f, " %s %llu/%llu/%llu/%llu/%llu", k_names[i], (unsigned long long)g_st.batches[i],
                    (unsigned long long)g_st.prims[i], (unsigned long long)g_st.skipped[i],
                    (unsigned long long)g_st.zonly[i], (unsigned long long)g_st.enhanced[i]);
    if (g_st.flash_clamped || g_st.flash_ramped || g_st.light_limited)
        fprintf(f, "; reduced flashing: batches limited %llu, rises spread %llu, frame light limited %llu",
                (unsigned long long)g_st.flash_clamped, (unsigned long long)g_st.flash_ramped,
                (unsigned long long)g_st.light_limited);
    fprintf(f, "\n");
}

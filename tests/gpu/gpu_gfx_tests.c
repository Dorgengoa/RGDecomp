/* SPDX-License-Identifier: CC0-1.0 */
/* Graphics settings of the GPU renderer (docs/GPU.md "Graphics settings"):
 * every option's effect on a synthetic scene, and the Original preset ==
 * the software reference.  ctest -L settings / -L gpu, tests gpu.gfx.*.
 *
 *   gfx.original         Original preset through the settings registry ->
 *                        gpu_gfx -> renderer + post chain: bit-exact
 *   gfx.settings_map     graphics.* -> gpu_gfx mapping, scale math
 *   gfx.internal_res     live scale changes mid-stream (1 -> 2 -> 3 -> 1)
 *   gfx.texture_filter   force bilinear / nearest; sprites and render-target
 *                        reads keep the GS filter
 *   gfx.anisotropic      a receding plane: far rows smoother, near rows and
 *                        1:1 mapping unchanged
 *   gfx.ssaa             scale 2/4 + box (and the other filters) down to native
 *   gfx.fxaa, gfx.sharpen, gfx.color, gfx.output_filter, gfx.resample
 *   gfx.replay-all DIR   the game recordings with the Original preset applied
 *                        through gpu_gfx and gpu_read_output: exact
 *   gfxbench DIR         per-field cost of every option (not a ctest)
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gpu_compare.h"
#include "gpu_tests.h"
#include "rg_settings.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#define FW 256
#define FH 224
#define TEXBP (64u * 32u)    /* page 64: the 64x64 CT32 texture */
#define RTBP (100u * 32u)    /* page 100: an offscreen 64x64 CT32 render target */

static int g_bad;
#define EXPECT(c, ...)                                                    \
    do {                                                                  \
        if (!(c)) {                                                       \
            fprintf(stderr, "  FAIL %s:%d: ", __func__, __LINE__);        \
            fprintf(stderr, __VA_ARGS__);                                 \
            fprintf(stderr, "\n");                                        \
            g_bad++;                                                      \
        }                                                                 \
    } while (0)

typedef struct pair {
    gs_state *sw, *hw;
    gpu_renderer *r;
} pair;

static void W(pair *p, uint32_t reg, uint64_t v)
{
    gs_write_reg(p->sw, reg, v);
    gs_write_reg(p->hw, reg, v);
}
static void PRIV(pair *p, uint32_t a, uint64_t v)
{
    gs_write_priv(p->sw, a, v);
    gs_write_priv(p->hw, a, v);
}
static uint64_t xyz(float x, float y) { return (uint64_t)(int)(x * 16.0f) | ((uint64_t)(int)(y * 16.0f) << 16); }
static uint64_t rgbaq(uint32_t c, float q)
{
    uint32_t qu;
    memcpy(&qu, &q, 4);
    return c | ((uint64_t)qu << 32);
}
static uint64_t st(float s, float t)
{
    uint32_t a, b;
    memcpy(&a, &s, 4);
    memcpy(&b, &t, 4);
    return a | ((uint64_t)b << 32);
}
static uint64_t uv(float u, float v) { return (uint64_t)((int)(u * 16) & 0x3FFF) | ((uint64_t)((int)(v * 16) & 0x3FFF) << 16); }
static uint64_t tex0(uint32_t tbp, uint32_t tbw, int tw, int th)
{
    /* CT32, TCC 1, TFX DECAL */
    return tbp | ((uint64_t)tbw << 14) | ((uint64_t)tw << 26) | ((uint64_t)th << 30) | (1ull << 34) |
           (1ull << 35);
}
static uint64_t tex1(int mmag, int mmin) { return ((uint64_t)mmag << 5) | ((uint64_t)mmin << 6); }

#define PRIM_TRI 3u
#define PRIM_SPRITE 6u
#define P_IIP (1u << 3)
#define P_TME (1u << 4)
#define P_FST (1u << 8)

static void p_open(pair *p, gpu_renderer *r)
{
    p->sw = gs_create();
    p->hw = gs_create();
    p->r = r;
    gpu_attach(r, p->hw);
    W(p, GS_PRMODECONT, 1);
    W(p, GS_FRAME_1, 0 | (4ull << 16));                          /* FBP 0, 256 wide, CT32 */
    W(p, GS_ZBUF_1, 300 | (1ull << 32));                         /* ZMSK */
    W(p, GS_TEST_1, 0);
    W(p, GS_SCISSOR_1, (uint64_t)(FW - 1) << 16 | ((uint64_t)(FH - 1) << 48));
    W(p, GS_XYOFFSET_1, 0);
    W(p, GS_COLCLAMP, 1);
    W(p, GS_CLAMP_1, 1 | (1u << 2));                             /* CLAMP */
    PRIV(p, GS_P_SMODE2, 0);
    PRIV(p, GS_P_DISPFB1, 0 | (4ull << 9));
    PRIV(p, GS_P_DISPLAY1, ((uint64_t)(FW - 1) << 32) | ((uint64_t)(FH - 1) << 44));
    PRIV(p, GS_P_PMODE, 1 | (1u << 5) | (0xFFu << 8));
}
static void p_close(pair *p)
{
    gpu_detach(p->r);
    gs_destroy(p->sw);
    gs_destroy(p->hw);
}

static void sprite(pair *p, float x0, float y0, float x1, float y1, uint32_t c)
{
    W(p, GS_PRIM, PRIM_SPRITE);
    W(p, GS_RGBAQ, rgbaq(c, 1.0f));
    W(p, GS_XYZ2, xyz(x0, y0));
    W(p, GS_XYZ2, xyz(x1, y1));
}
/* textured triangle, UV in texels (FST) */
static void tri_uv(pair *p, const float v[3][4], uint32_t c)
{
    W(p, GS_PRIM, PRIM_TRI | P_TME | P_FST);
    for (int i = 0; i < 3; i++) {
        W(p, GS_RGBAQ, rgbaq(c, 1.0f));
        W(p, GS_UV, uv(v[i][2], v[i][3]));
        W(p, GS_XYZ2, xyz(v[i][0], v[i][1]));
    }
}
/* textured triangle, S/T/Q (perspective) */
static void tri_stq(pair *p, const float v[3][5], uint32_t c)
{
    W(p, GS_PRIM, PRIM_TRI | P_TME);
    for (int i = 0; i < 3; i++) {
        W(p, GS_ST, st(v[i][2] * v[i][4], v[i][3] * v[i][4]));
        W(p, GS_RGBAQ, rgbaq(c, v[i][4]));
        W(p, GS_XYZ2, xyz(v[i][0], v[i][1]));
    }
}
static void tri_flat(pair *p, float x0, float y0, float x1, float y1, float x2, float y2, uint32_t c)
{
    W(p, GS_PRIM, PRIM_TRI);
    W(p, GS_RGBAQ, rgbaq(c, 1.0f));
    W(p, GS_XYZ2, xyz(x0, y0));
    W(p, GS_XYZ2, xyz(x1, y1));
    W(p, GS_XYZ2, xyz(x2, y2));
}

/* 64x64 CT32 texture: kind 0 = 8x8 checker (two colours), 1 = 1-texel
 * vertical stripes (black/white), 2 = a smooth gradient */
static void texture(pair *p, int kind)
{
    for (uint32_t y = 0; y < 64; y++)
        for (uint32_t x = 0; x < 64; x++) {
            uint32_t c;
            if (kind == 0) c = ((x >> 3) ^ (y >> 3)) & 1 ? 0xFF2040E0u : 0xFFF0D020u;
            else if (kind == 1) c = (x & 1) ? 0xFFFFFFFFu : 0xFF000000u;
            else c = 0xFF000000u | (x * 4) | ((y * 4) << 8) | (((x + y) * 2) << 16);
            gs_write_pixel(p->sw, GS_PSMCT32, TEXBP, 1, x, y, c);
            gs_write_pixel(p->hw, GS_PSMCT32, TEXBP, 1, x, y, c);
        }
    gs_mem_rect rc = { TEXBP, 1, GS_PSMCT32, 0, 0, 64, 64 };
    gpu_mem_written(p->r, &rc);
}
static void use_texture(pair *p, uint32_t tbp, int mmag, int mmin)
{
    W(p, GS_TEXFLUSH, 0);
    W(p, GS_TEX0_1, tex0(tbp, 1, 6, 6));
    W(p, GS_TEX1_1, tex1(mmag, mmin));
}

/* ------------------------------------------------------------ running */
static uint32_t *g_ref, *g_out, *g_out2;
#define CAP (4096u * 4096u)

/* A scene through the reference and the renderer (with e and scale), the
 * reference display into g_ref (FW x FH), the renderer's output through
 * post into out.  Returns 0 if both produced a frame. */
static int run(gpu_renderer *r, void (*scene)(pair *), const gpu_enhance *e, int scale,
               const gpu_post *post, uint32_t *out, uint32_t *w, uint32_t *h, int check_vram)
{
    gpu_enhance none;
    gpu_enhance_default(&none);
    gpu_set_scale(r, scale);
    gpu_set_enhance(r, e ? e : &none);
    pair p;
    p_open(&p, r);
    scene(&p);
    uint32_t rw = 0, rh = 0;
    int rc = gs_read_display(p.sw, GS_READ_FRAME, g_ref, CAP, &rw, &rh);
    int rc2 = gpu_read_output(r, GS_READ_FRAME, post, out, CAP, w, h);
    if (check_vram) {
        gpu_sync(r);
        cmp_vram(p.sw, p.hw, r, "vram");
    }
    p_close(&p);
    gpu_set_enhance(r, &none);
    EXPECT(rc == 0 && rw == FW && rh == FH, "reference display %d %ux%u", rc, rw, rh);
    EXPECT(rc2 == 0, "gpu output %d (%ux%u)", rc2, *w, *h);
    return rc == 0 && rc2 == 0 ? 0 : -1;
}

static int ch(uint32_t c, int k) { return (int)((c >> (8 * k)) & 255); }
static int maxdiff(uint32_t a, uint32_t b)
{
    int m = 0;
    for (int k = 0; k < 3; k++) {
        int d = abs(ch(a, k) - ch(b, k));
        if (d > m) m = d;
    }
    return m;
}
/* pixels of two FW x FH frames that differ by more than tol */
static int ndiff(const uint32_t *a, const uint32_t *b, int tol, int y0, int y1)
{
    int n = 0;
    for (int y = y0; y < y1; y++)
        for (int x = 0; x < FW; x++)
            if (maxdiff(a[y * FW + x], b[y * FW + x]) > tol) n++;
    return n;
}
/* the reference pixel is next to (within d of) a different reference colour */
static int near_edge(const uint32_t *ref, int x, int y, int d)
{
    uint32_t c = ref[y * FW + x];
    for (int j = -d; j <= d; j++)
        for (int i = -d; i <= d; i++) {
            int xx = x + i, yy = y + j;
            if (xx < 0 || yy < 0 || xx >= FW || yy >= FH) continue;
            if ((ref[yy * FW + xx] & 0xFFFFFF) != (c & 0xFFFFFF)) return 1;
        }
    return 0;
}

/* ------------------------------------------------------------ scenes */
static void scene_mixed(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF302010u);
    texture(p, 0);
    use_texture(p, TEXBP, 0, 0);
    const float a[3][4] = { { 10, 10, 0, 0 }, { 120, 20, 64, 0 }, { 30, 110, 0, 64 } };
    tri_uv(p, a, 0x80808080u);
    use_texture(p, TEXBP, 1, 1);
    const float b[3][4] = { { 130, 12, 2, 3 }, { 250, 40, 60, 5 }, { 140, 120, 8, 61 } };
    tri_uv(p, b, 0x80808080u);
    const float c[3][5] = { { 20, 220, 0, 1, 1.0f }, { 240, 220, 1, 1, 1.0f }, { 128, 130, 0.5f, 0, 0.2f } };
    tri_stq(p, c, 0x80808080u);
    tri_flat(p, 150, 130, 250, 150, 170, 210, 0xFF20C040u);
    W(p, GS_PRIM, PRIM_SPRITE | P_TME | P_FST);
    W(p, GS_RGBAQ, rgbaq(0x80808080u, 1.0f));
    W(p, GS_UV, uv(0, 0));
    W(p, GS_XYZ2, xyz(190, 160));
    W(p, GS_UV, uv(64, 64));
    W(p, GS_XYZ2, xyz(254, 222));
}

/* ------------------------------------------------------------ tests */
static void t_original(gpu_renderer *r)
{
    rg_settings *s = rg_settings_create();
    rg_settings_register_core(s);
    rg_settings_apply_preset(s, "original");
    gpu_gfx g;
    gpu_gfx_from_settings(&g, s);
    EXPECT(gpu_gfx_original(&g), "the Original preset maps to non-Original renderer settings");
    int ssaa = 0;
    int sc = gpu_gfx_scale(&g, 960, FH, &ssaa);
    EXPECT(sc == 1 && ssaa == 1, "Original scale %d ssaa %d", sc, ssaa);
    gpu_post post = g.post;
    post.ssaa = ssaa;
    EXPECT(gpu_post_identity(&post), "Original post chain is not the identity");
    uint32_t w = 0, h = 0;
    g_cmp_tol = 0;
    if (run(r, scene_mixed, &g.enh, sc, &post, g_out, &w, &h, 1) == 0) {
        EXPECT(w == FW && h == FH, "size %ux%u", w, h);
        cmp_frame(g_ref, g_out, FW, FH, "original display");
    }
    /* every preset value round trip: the default preset is not Original */
    rg_settings_apply_preset(s, "default");
    gpu_gfx_from_settings(&g, s);
    EXPECT(!gpu_gfx_original(&g), "default preset reported as Original");
    rg_settings_destroy(s);
}

static void t_settings_map(gpu_renderer *r)
{
    (void)r;
    rg_settings *s = rg_settings_create();
    rg_settings_register_core(s);
    gpu_gfx g;
    struct { const char *id, *val; } cases[] = {
        { "graphics.internal_res", "4x" }, { "graphics.antialiasing", "ssaa2" },
        { "graphics.antialiasing", "fxaa" },
        { "graphics.texture_filter", "nearest" }, { "graphics.anisotropic", "8x" },
        { "graphics.gamma", "1.2" }, { "graphics.brightness", "0.9" }, { "graphics.sharpen", "0.5" },
        { "graphics.output_filter", "crt" }, { "graphics.bloom", "off" },
    };
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; i++) {
        rg_settings_apply_preset(s, "original");
        int k = rg_settings_find(s, cases[i].id);
        EXPECT(k >= 0, "%s missing", cases[i].id);
        if (k < 0) continue;
        EXPECT(rg_settings_set_text(s, k, cases[i].val, RG_SRC_API, NULL, 0) >= 0, "%s=%s", cases[i].id,
               cases[i].val);
        gpu_gfx_from_settings(&g, s);
        EXPECT(!gpu_gfx_original(&g), "%s=%s still Original", cases[i].id, cases[i].val);
    }
    /* the downsampling filter alone changes nothing (no SSAA, no minification) */
    rg_settings_apply_preset(s, "original");
    rg_settings_set_text(s, rg_settings_find(s, "graphics.downsample"), "lanczos", RG_SRC_API, NULL, 0);
    gpu_gfx_from_settings(&g, s);
    EXPECT(g.post.downsample == GPU_RS_LANCZOS && gpu_gfx_original(&g), "downsample alone");
    rg_settings_apply_preset(s, "original");
    rg_settings_set_text(s, rg_settings_find(s, "graphics.internal_res"), "4x", RG_SRC_API, NULL, 0);
    gpu_gfx_from_settings(&g, s);
    EXPECT(g.internal_res == 4, "4x -> %d", g.internal_res);
    rg_settings_set_text(s, rg_settings_find(s, "graphics.antialiasing"), "ssaa4", RG_SRC_API, NULL, 0);
    gpu_gfx_from_settings(&g, s);
    int ss = 0;
    EXPECT(gpu_gfx_scale(&g, 960, 448, &ss) == 8 && ss == 2, "4x * ssaa4 capped: ssaa %d", ss);
    rg_settings_set_text(s, rg_settings_find(s, "graphics.internal_res"), "window", RG_SRC_API, NULL, 0);
    rg_settings_set_text(s, rg_settings_find(s, "graphics.antialiasing"), "off", RG_SRC_API, NULL, 0);
    gpu_gfx_from_settings(&g, s);
    EXPECT(gpu_gfx_scale(&g, 960, 448, &ss) == 3 && ss == 1, "match window 960/448 -> 3");
    EXPECT(gpu_gfx_scale(&g, 896, 448, &ss) == 2, "match window 896/448 -> 2");
    EXPECT(gpu_gfx_scale(&g, 0, 448, &ss) == 1, "match window headless -> 1");
    rg_settings_set_text(s, rg_settings_find(s, "graphics.anisotropic"), "16x", RG_SRC_API, NULL, 0);
    rg_settings_set_text(s, rg_settings_find(s, "graphics.texture_filter"), "bilinear", RG_SRC_API, NULL, 0);
    gpu_gfx_from_settings(&g, s);
    EXPECT(g.enh.aniso == 16 && g.enh.tex_filter == GPU_TEXF_BILINEAR, "aniso %d filter %d", g.enh.aniso,
           g.enh.tex_filter);
    /* the menu marks no renderer setting as planned any more, except the
     * screen effects and the game-side ones */
    const char *real[] = { "graphics.internal_res", "graphics.antialiasing", "graphics.downsample",
                           "graphics.anisotropic", "graphics.texture_filter", "graphics.gamma",
                           "graphics.brightness", "graphics.sharpen", "graphics.output_filter",
                           "display.frame_rate", "display.monitor" };
    for (size_t i = 0; i < sizeof real / sizeof real[0]; i++) {
        int k = rg_settings_find(s, real[i]);
        EXPECT(k >= 0 && !(rg_settings_def(s, k)->flags & RG_SETF_PLACEHOLDER), "%s still planned", real[i]);
    }
    rg_settings_destroy(s);
}

static void scene_flat_sprites(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF102030u);
    for (int i = 0; i < 20; i++)
        sprite(p, (float)(i * 11), (float)(i * 9), (float)(i * 11 + 40), (float)(i * 9 + 30),
               0xFF000000u | (uint32_t)(i * 0x0B1D27));
}

static void t_internal_res(gpu_renderer *r)
{
    g_cmp_tol = 0;
    gpu_set_scale(r, 1);
    pair p;
    p_open(&p, r);
    uint32_t w, h;
    sprite(&p, 0, 0, FW, FH, 0xFF102030u);
    for (int i = 0; i < 6; i++) sprite(&p, (float)(i * 20), 10, (float)(i * 20 + 15), 60, 0xFF0000F0u + (uint32_t)i * 0x2000);
    uint64_t drops0 = gpu_get_stats(r)->rt_drops;
    int sc[] = { 2, 3, 1, 4 };
    for (int k = 0; k < 4; k++) {
        EXPECT(gpu_set_scale(r, sc[k]) == sc[k], "set scale %d", sc[k]);
        EXPECT(gpu_get_scale(r) == sc[k], "scale now %d", gpu_get_scale(r));
        for (int i = 0; i < 6; i++)
            sprite(&p, (float)(i * 20 + k * 3), (float)(70 + 30 * k), (float)(i * 20 + 15 + k * 3),
                   (float)(95 + 30 * k), 0xFF00A000u + (uint32_t)(i * 31 + k * 7));
        int rc = gpu_read_display(r, GS_READ_FRAME, g_out, CAP, &w, &h);
        EXPECT(rc == 0 && w == (uint32_t)(FW * sc[k]) && h == (uint32_t)(FH * sc[k]), "scale %d: %ux%u", sc[k], w, h);
        uint32_t rw, rh;
        gs_read_display(p.sw, GS_READ_FRAME, g_ref, CAP, &rw, &rh);
        /* whole-pixel sprites: every s x s block equals the reference pixel */
        int bad = 0;
        for (uint32_t y = 0; y < (uint32_t)FH && rc == 0; y++)
            for (uint32_t x = 0; x < (uint32_t)FW; x++)
                for (int j = 0; j < sc[k]; j++)
                    for (int i = 0; i < sc[k]; i++)
                        if ((g_out[(y * sc[k] + j) * w + x * sc[k] + i] & 0xFFFFFF) != (g_ref[y * FW + x] & 0xFFFFFF)) bad++;
        EXPECT(bad == 0, "scale %d: %d sub-samples differ from the reference", sc[k], bad);
    }
    EXPECT(gpu_get_stats(r)->rt_drops > drops0, "targets were not dropped on scale changes");
    gpu_sync(r);
    cmp_vram(p.sw, p.hw, r, "after scale changes");
    p_close(&p);
    gpu_set_scale(r, 1);
}

/* the checker texture magnified on a triangle, GS filter nearest */
static void scene_tf_nearest(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF000000u);
    texture(p, 0);
    use_texture(p, TEXBP, 0, 0);
    const float a[3][4] = { { 4, 4, 0, 0 }, { 250, 10, 32, 0 }, { 8, 220, 0, 32 } };
    tri_uv(p, a, 0x80808080u);
}
static void scene_tf_bilinear(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF000000u);
    texture(p, 0);
    use_texture(p, TEXBP, 1, 1);
    const float a[3][4] = { { 4, 4, 0, 0 }, { 250, 10, 32, 0 }, { 8, 220, 0, 32 } };
    tri_uv(p, a, 0x80808080u);
}
static void scene_tf_sprite(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF000000u);
    texture(p, 0);
    use_texture(p, TEXBP, 0, 0);
    W(p, GS_PRIM, PRIM_SPRITE | P_TME | P_FST);
    W(p, GS_RGBAQ, rgbaq(0x80808080u, 1.0f));
    W(p, GS_UV, uv(0, 0));
    W(p, GS_XYZ2, xyz(10, 10));
    W(p, GS_UV, uv(32, 32));
    W(p, GS_XYZ2, xyz(250, 210));
}
/* a render target (drawn on the GPU) as the texture of a triangle */
static void scene_tf_rtt(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF000000u);
    W(p, GS_FRAME_1, (RTBP / 32) | (1ull << 16));
    for (int i = 0; i < 8; i++) sprite(p, (float)(i * 8), 0, (float)(i * 8 + 4), 64, 0xFFFFFFFFu);
    W(p, GS_FRAME_1, 0 | (4ull << 16));
    use_texture(p, RTBP, 0, 0);
    const float a[3][4] = { { 4, 4, 0, 0 }, { 250, 10, 32, 0 }, { 8, 220, 0, 32 } };
    tri_uv(p, a, 0x80808080u);
}

static int distinct_colours(const uint32_t *f, int n)
{
    /* small set: count up to 64 distinct values */
    uint32_t seen[64];
    int k = 0;
    for (int i = 0; i < n && k < 64; i++) {
        uint32_t c = f[i] & 0xFFFFFF;
        int j = 0;
        while (j < k && seen[j] != c) j++;
        if (j == k) seen[k++] = c;
    }
    return k;
}

static void t_texture_filter(gpu_renderer *r)
{
    gpu_enhance e;
    gpu_enhance_default(&e);
    uint32_t w, h;
    gpu_post id;
    gpu_post_default(&id);
    /* nearest state, override bilinear: smooth (many colours), differs */
    e.tex_filter = GPU_TEXF_BILINEAR;
    if (run(r, scene_tf_nearest, &e, 1, &id, g_out, &w, &h, 0) == 0) {
        int nd = ndiff(g_ref, g_out, 0, 0, FH);
        EXPECT(nd > 2000, "force bilinear on a nearest texture changed only %d px", nd);
        EXPECT(distinct_colours(g_ref, FW * FH) <= 3, "reference has %d colours", distinct_colours(g_ref, FW * FH));
        EXPECT(distinct_colours(g_out, FW * FH) > 10, "bilinear output has %d colours", distinct_colours(g_out, FW * FH));
        printf("  force bilinear (nearest state): %d px changed\n", nd);
    }
    e.tex_filter = GPU_TEXF_NEAREST;
    if (run(r, scene_tf_nearest, &e, 1, &id, g_out, &w, &h, 0) == 0)
        EXPECT(ndiff(g_ref, g_out, 0, 0, FH) == 0, "force nearest on a nearest texture changed pixels");
    /* bilinear state, override nearest: only texture colours remain */
    if (run(r, scene_tf_bilinear, &e, 1, &id, g_out, &w, &h, 0) == 0) {
        int nd = ndiff(g_ref, g_out, 0, 0, FH);
        EXPECT(nd > 2000, "force nearest on a bilinear texture changed only %d px", nd);
        EXPECT(distinct_colours(g_out, FW * FH) <= 3, "nearest output has %d colours", distinct_colours(g_out, FW * FH));
        printf("  force nearest (bilinear state): %d px changed\n", nd);
    }
    e.tex_filter = GPU_TEXF_BILINEAR;
    if (run(r, scene_tf_bilinear, &e, 1, &id, g_out, &w, &h, 0) == 0)
        EXPECT(ndiff(g_ref, g_out, 0, 0, FH) == 0, "force bilinear on a bilinear texture changed pixels");
    /* 2D sprites and render-target reads keep the GS filter */
    g_cmp_tol = 0;
    if (run(r, scene_tf_sprite, &e, 1, &id, g_out, &w, &h, 1) == 0)
        EXPECT(ndiff(g_ref, g_out, 0, 0, FH) == 0, "a sprite was filtered");
    if (run(r, scene_tf_rtt, &e, 1, &id, g_out, &w, &h, 1) == 0)
        EXPECT(ndiff(g_ref, g_out, 0, 0, FH) == 0, "a render-target read was filtered");
}

/* a plane receding to the top: stripes, bilinear, no mipmaps */
static void scene_plane(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF000000u);
    texture(p, 1);
    use_texture(p, TEXBP, 1, 1);
    W(p, GS_CLAMP_1, 0);   /* REPEAT */
    /* near edge (bottom): q = 1, 64 texels over 256 px (magnified); far
     * edge (top): q = 0.05, ~5 texels per pixel */
    const float A[3][5] = { { 0, 223, 0, 1, 1.0f }, { 256, 223, 1, 1, 1.0f }, { 0, 20, 0, 0, 0.05f } };
    const float B[3][5] = { { 256, 223, 1, 1, 1.0f }, { 256, 20, 1, 0, 0.05f }, { 0, 20, 0, 0, 0.05f } };
    tri_stq(p, A, 0x80808080u);
    tri_stq(p, B, 0x80808080u);
}
/* the texture 1:1 on an axis-aligned triangle pair */
static void scene_onetoone(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF000000u);
    texture(p, 0);
    use_texture(p, TEXBP, 1, 1);
    const float A[3][4] = { { 50, 50, 0, 0 }, { 114, 50, 64, 0 }, { 50, 114, 0, 64 } };
    const float B[3][4] = { { 114, 50, 64, 0 }, { 114, 114, 64, 64 }, { 50, 114, 0, 64 } };
    tri_uv(p, A, 0x80808080u);
    tri_uv(p, B, 0x80808080u);
}
static double hf_energy(const uint32_t *f, int y0, int y1)
{
    double e = 0;
    for (int y = y0; y < y1; y++)
        for (int x = 0; x + 1 < FW; x++) e += abs(ch(f[y * FW + x], 1) - ch(f[y * FW + x + 1], 1));
    return e / ((double)(y1 - y0) * (FW - 1));
}
static void t_anisotropic(gpu_renderer *r)
{
    gpu_enhance e;
    gpu_enhance_default(&e);
    e.aniso = 16;
    uint32_t w, h;
    gpu_post id;
    gpu_post_default(&id);
    if (run(r, scene_plane, &e, 1, &id, g_out, &w, &h, 0) == 0) {
        if (!gpu_exact_triangles(r)) {
            printf("  float-triangle device: no footprint gradients, anisotropy inactive\n");
            EXPECT(ndiff(g_ref, g_out, 0, 0, FH) == 0, "aniso changed pixels without gradients");
        } else {
            /* near rows (bottom, magnified: footprint < 1 texel) unchanged */
            int nnear = ndiff(g_ref, g_out, 0, 200, 223);
            int nfar = ndiff(g_ref, g_out, 4, 20, 120);
            double er = hf_energy(g_ref, 22, 50), ea = hf_energy(g_out, 22, 50);
            printf("  aniso 16x: near rows %d px changed, far rows %d px changed, far HF energy %.1f -> %.1f\n",
                   nnear, nfar, er, ea);
            EXPECT(nnear == 0, "near (magnified) rows changed: %d px", nnear);
            EXPECT(nfar > 500, "far rows barely changed: %d px", nfar);
            EXPECT(ea < er * 0.7, "far rows not smoother (%.1f -> %.1f)", er, ea);
        }
    }
    if (run(r, scene_onetoone, &e, 1, &id, g_out, &w, &h, 0) == 0)
        EXPECT(ndiff(g_ref, g_out, 0, 0, FH) == 0, "aniso changed a 1:1 mapping");
}

static void scene_edges(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF201810u);
    sprite(p, 20, 20, 80, 60, 0xFF0080FFu);
    tri_flat(p, 100.3f, 10.1f, 250.7f, 60.4f, 130.2f, 200.9f, 0xFF40E060u);
    tri_flat(p, 10.5f, 120.2f, 90.1f, 215.6f, 30.9f, 210.3f, 0xFFE0E0E0u);
}
/* every difference from the reference lies within d px of a reference edge */
static void only_edges(const uint32_t *out, int d, int tol, const char *what, int *changed)
{
    int off = 0, n = 0;
    for (int y = 0; y < FH; y++)
        for (int x = 0; x < FW; x++)
            if (maxdiff(g_ref[y * FW + x], out[y * FW + x]) > tol) {
                n++;
                if (!near_edge(g_ref, x, y, d)) off++;
            }
    EXPECT(off == 0, "%s: %d px changed away from edges", what, off);
    *changed = n;
}

static void t_ssaa(gpu_renderer *r)
{
    static const char *fn[] = { "box", "bilinear", "bicubic", "lanczos" };
    for (int s = 2; s <= 4; s += 2)
        for (int f = 0; f < 4; f++) {
            if (s == 4 && f) continue;
            gpu_post post;
            gpu_post_default(&post);
            post.ssaa = s;
            post.downsample = f;
            uint32_t w, h;
            if (run(r, scene_edges, NULL, s, &post, g_out, &w, &h, 0) != 0) continue;
            EXPECT(w == FW && h == FH, "ssaa %d: %ux%u", s, w, h);
            int n = 0;
            /* box: flat areas exact; the wider kernels ring up to 2 px out */
            only_edges(g_out, f == 0 ? 2 : 3, f == 0 ? 0 : 1, fn[f], &n);
            EXPECT(n > 100, "ssaa %d %s: only %d edge px anti-aliased", s, fn[f], n);
            printf("  ssaa %d %s: %d edge px smoothed\n", s, fn[f], n);
        }
}

static void t_fxaa(gpu_renderer *r)
{
    gpu_post post;
    gpu_post_default(&post);
    post.fxaa = 1;
    uint32_t w, h;
    if (run(r, scene_edges, NULL, 1, &post, g_out, &w, &h, 0) == 0) {
        int n = 0;
        only_edges(g_out, 1, 0, "fxaa", &n);
        EXPECT(n > 50, "fxaa changed only %d px", n);
        printf("  fxaa: %d edge px blended\n", n);
    }
}

/* a bilinear-magnified gradient + hard edges (something to sharpen) */
static void scene_soft(pair *p)
{
    sprite(p, 0, 0, FW, FH, 0xFF404040u);
    texture(p, 0);
    use_texture(p, TEXBP, 1, 1);
    const float a[3][4] = { { 4, 4, 0, 0 }, { 250, 4, 16, 0 }, { 4, 220, 0, 16 } };
    tri_uv(p, a, 0x80808080u);
}
static void t_sharpen(gpu_renderer *r)
{
    gpu_post post;
    gpu_post_default(&post);
    post.sharpen = 1.0f;
    uint32_t w, h;
    if (run(r, scene_soft, NULL, 1, &post, g_out, &w, &h, 0) == 0) {
        int changed = 0, outside = 0;
        for (int y = 1; y < FH - 1; y++)
            for (int x = 1; x < FW - 1; x++) {
                uint32_t o = g_out[y * FW + x];
                if (maxdiff(o, g_ref[y * FW + x]) > 1) changed++;
                for (int k = 0; k < 3; k++) {
                    int mn = 255, mx = 0;
                    const int dx[5] = { 0, 1, -1, 0, 0 }, dy[5] = { 0, 0, 0, 1, -1 };
                    for (int q = 0; q < 5; q++) {
                        int v = ch(g_ref[(y + dy[q]) * FW + x + dx[q]], k);
                        if (v < mn) mn = v;
                        if (v > mx) mx = v;
                    }
                    if (ch(o, k) < mn - 1 || ch(o, k) > mx + 1) outside++;
                }
            }
        printf("  sharpen 1.0: %d px changed\n", changed);
        EXPECT(changed > 300, "sharpen changed only %d px", changed);
        EXPECT(outside == 0, "sharpen overshot the neighbourhood at %d channels", outside);
        /* flat background rows (a solid colour) stay */
        EXPECT(ndiff(g_ref, g_out, 1, 222, 224) == 0, "flat rows changed");
    }
}

static void t_color(gpu_renderer *r)
{
    float gam[] = { 2.0f, 0.6f, 1.0f }, bri[] = { 1.0f, 1.0f, 1.3f };
    for (int c = 0; c < 3; c++) {
        gpu_post post;
        gpu_post_default(&post);
        post.gamma = gam[c];
        post.brightness = bri[c];
        uint32_t w, h;
        if (run(r, scene_flat_sprites, NULL, 1, &post, g_out, &w, &h, 0) != 0) continue;
        int bad = 0;
        for (int i = 0; i < FW * FH; i++)
            for (int k = 0; k < 3; k++) {
                double v = ch(g_ref[i], k) / 255.0 * bri[c];
                if (v > 1) v = 1;
                int want = (int)floor(pow(v, 1.0 / gam[c]) * 255.0 + 0.5);
                if (abs(ch(g_out[i], k) - want) > 1) bad++;
            }
        EXPECT(bad == 0, "gamma %.1f brightness %.1f: %d channels off", gam[c], bri[c], bad);
    }
}

static void scene_grey(pair *p) { sprite(p, 0, 0, FW, FH, 0xFF808080u); }

static void t_output_filter(gpu_renderer *r)
{
    for (int of = 1; of <= 2; of++) {
        gpu_post post;
        gpu_post_default(&post);
        post.output_filter = of;
        post.out_w = FW * 3;
        post.out_h = FH * 3;
        post.upscale = GPU_RS_NEAREST;
        uint32_t w, h;
        if (run(r, scene_grey, NULL, 1, &post, g_out, &w, &h, 0) != 0) continue;
        EXPECT(w == FW * 3 && h == FH * 3, "output filter %d: %ux%u", of, w, h);
        /* rows at a source line's centre (y % 3 == 1) are brighter than the
         * rows between lines */
        double centre = 0, edge = 0;
        for (uint32_t x = 0; x < w; x++) {
            centre += ch(g_out[(3 * 50 + 1) * w + x], 1);
            edge += ch(g_out[(3 * 50) * w + x], 1);
        }
        EXPECT(centre > edge * 1.15, "filter %d: line centre %.0f vs edge %.0f", of, centre / w, edge / w);
        if (of == 2) {
            /* the aperture grille: green peaks every third column */
            int g0 = ch(g_out[(3 * 50 + 1) * w + 30], 1), g1 = ch(g_out[(3 * 50 + 1) * w + 31], 1);
            EXPECT(g1 > g0, "crt mask: column 31 green %d not above column 30 %d", g1, g0);
        }
        printf("  output filter %d: line centre %.1f, between lines %.1f\n", of, centre / w, edge / w);
    }
    /* no output filter, a window larger than the frame: the presenter scales */
    gpu_post post;
    gpu_post_default(&post);
    post.gamma = 1.1f;
    post.out_w = FW * 3;
    post.out_h = FH * 3;
    uint32_t w, h;
    if (run(r, scene_grey, NULL, 1, &post, g_out, &w, &h, 0) == 0)
        EXPECT(w == FW && h == FH, "no output filter: resampled to %ux%u", w, h);
}

static void t_resample(gpu_renderer *r)
{
    /* a 4x frame into a 2x window rectangle: minified on the GPU */
    for (int f = 0; f < 4; f++) {
        gpu_post post;
        gpu_post_default(&post);
        post.downsample = f;
        post.out_w = FW * 2;
        post.out_h = FH * 2;
        uint32_t w, h;
        if (run(r, scene_flat_sprites, NULL, 4, &post, g_out, &w, &h, 0) != 0) continue;
        EXPECT(w == FW * 2 && h == FH * 2, "filter %d: %ux%u", f, w, h);
        /* inside the flat background (top-right corner block) colours match */
        int bad = 0;
        for (uint32_t y = 2; y < 16; y++)
            for (uint32_t x = w - 40; x < w - 2; x++)
                if (maxdiff(g_out[y * w + x], g_ref[(y / 2) * FW + x / 2]) > 1) bad++;
        EXPECT(bad == 0, "filter %d: %d flat px off", f, bad);
    }
    /* nearest magnification with an output filter: whole blocks */
    gpu_post post;
    gpu_post_default(&post);
    post.output_filter = GPU_OUTF_SCANLINES;
    post.out_w = FW * 2;
    post.out_h = FH * 2;
    post.upscale = GPU_RS_NEAREST;
    uint32_t w, h;
    if (run(r, scene_flat_sprites, NULL, 1, &post, g_out, &w, &h, 0) == 0) {
        int bad = 0;
        for (uint32_t y = 0; y < h; y++)
            for (uint32_t x = 0; x + 1 < w; x += 2)
                if (g_out[y * w + x] != g_out[y * w + x + 1]) bad++;
        EXPECT(bad == 0, "nearest x2: %d column pairs differ", bad);
    }
}

/* ------------------------------------------------------------ replays */
extern const gpu_post *g_replay_post;   /* gpu_replay.c */

int run_gfx_replay_dir(const char *dir, gpu_renderer *r)
{
    rg_settings *s = rg_settings_create();
    rg_settings_register_core(s);
    rg_settings_apply_preset(s, "original");
    gpu_gfx g;
    gpu_gfx_from_settings(&g, s);
    rg_settings_destroy(s);
    int ss = 1;
    gpu_set_scale(r, gpu_gfx_scale(&g, 960, 448, &ss));
    gpu_set_enhance(r, &g.enh);
    static gpu_post post;
    post = g.post;
    post.ssaa = ss;
    g_replay_post = &post;
    int n = run_replay_dir(dir, r);
    g_replay_post = NULL;
    return n;
}

/* ------------------------------------------------------------ bench */
static double now_ms(void)
{
#ifdef _WIN32
    LARGE_INTEGER f, c;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart * 1000.0 / (double)f.QuadPart;
#else
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec * 1e3 + ts.tv_nsec / 1e6;
#endif
}

typedef struct bench_cfg {
    const char *name;
    int scale;
    gpu_enhance e;
    gpu_post p;
} bench_cfg;

/* one recording through the renderer alone, every field presented through
 * post for a 1280x960 window; returns ms per field (or -1) */
static double bench_one(const char *path, gpu_renderer *r, const bench_cfg *c, int *fields_out)
{
    gs_rec_file rf;
    if (gs_rec_open(&rf, path) != 0) return -1;
    gs_state *hw = gs_create();
    if (gs_rec_load(&rf, hw) != 0) { gs_rec_close(&rf); gs_destroy(hw); return -1; }
    gpu_set_scale(r, c->scale);
    gpu_set_enhance(r, &c->e);
    gpu_attach(r, hw);
    static uint8_t fifo[1 << 20];
    gs_rec_ev ev;
    int fields = 0;
    double t0 = now_ms(), tfirst = 0;
    while (gs_rec_next(&rf, &ev) == 1) {
        if (ev.kind == GS_REC_FIFO_READ && ev.a > sizeof fifo) ev.a = sizeof fifo;
        gs_rec_apply(hw, &ev, fifo);
        if (ev.kind == GS_REC_VSYNC) {
            uint32_t w, h;
            gpu_read_output(r, GS_READ_FRAME, &c->p, g_out2, CAP, &w, &h);
            if (++fields == 1) tfirst = now_ms();
        }
    }
    double t1 = now_ms();
    gpu_detach(r);
    gs_destroy(hw);
    gs_rec_close(&rf);
    *fields_out = fields - 1;
    (void)t0;
    return fields > 1 ? (t1 - tfirst) / (fields - 1) : -1;
}

/* gfxbench DIR perf [MATCH] (docs/GPU.md "Performance"): every recording
 * whose file name contains MATCH replayed through the renderer alone at the
 * Original preset (x1) and at x3 (the windowed default), best of
 * RG_BENCH_REPS (3).  Per field: wall ms (GS replay + batches + display
 * read-back), the part spent in the display read-back (which waits for the
 * GPU), and the renderer's counters. */
typedef struct perf_res {
    double ms, disp_ms;
    int fields;
    gpu_stats d;
} perf_res;

static int perf_one(const char *path, gpu_renderer *r, int scale, perf_res *o)
{
    gs_rec_file rf;
    if (gs_rec_open(&rf, path) != 0) return -1;
    gs_state *hw = gs_create();
    if (gs_rec_load(&rf, hw) != 0) { gs_rec_close(&rf); gs_destroy(hw); return -1; }
    if (scale) gpu_set_scale(r, scale);
    gpu_enhance none;
    gpu_enhance_default(&none);
    gpu_set_enhance(r, &none);
    gpu_post p;
    gpu_post_default(&p);
    /* scale 0: the GS model alone (GIF, registers, transfers; no drawing),
     * what the replay costs before any renderer */
    if (scale) gpu_attach(r, hw);
    else hw->sw_raster = 0;
    static uint8_t fifo[1 << 20];
    gs_rec_ev ev;
    int fields = 0;
    double tfirst = 0, disp = 0;
    gpu_stats s0;
    memset(&s0, 0, sizeof s0);
    while (gs_rec_next(&rf, &ev) == 1) {
        if (ev.kind == GS_REC_FIFO_READ && ev.a > sizeof fifo) ev.a = sizeof fifo;
        gs_rec_apply(hw, &ev, fifo);
        if (ev.kind == GS_REC_VSYNC) {
            uint32_t w, h;
            double a = now_ms();
            if (scale) gpu_read_output(r, GS_READ_FRAME, &p, g_out2, CAP, &w, &h);
            if (fields > 0) disp += now_ms() - a;
            if (++fields == 1) { tfirst = now_ms(); s0 = *gpu_get_stats(r); }
        }
    }
    double t1 = now_ms();
    gpu_stats s1 = *gpu_get_stats(r);
    if (scale) gpu_detach(r);
    else s1 = s0;
    gs_destroy(hw);
    gs_rec_close(&rf);
    if (fields < 2) return -1;
    o->fields = fields - 1;
    o->ms = (t1 - tfirst) / o->fields;
    o->disp_ms = disp / o->fields;
    const uint64_t *a = (const uint64_t *)&s0, *b = (const uint64_t *)&s1;
    uint64_t *d = (uint64_t *)&o->d;
    for (size_t i = 0; i < sizeof(gpu_stats) / 8; i++) d[i] = b[i] - a[i];
    return 0;
}

int run_gfx_perf(const char *dir, const char *match, gpu_renderer *r)
{
    char paths[32][600];
    int np = 0;
#ifdef _WIN32
    WIN32_FIND_DATAA fd;
    char pat[700];
    snprintf(pat, sizeof pat, "%s\\*.rggs", dir);
    HANDLE hf = FindFirstFileA(pat, &fd);
    if (hf == INVALID_HANDLE_VALUE) return 0;
    do {
        if (np < 32 && strstr(fd.cFileName, match))
            snprintf(paths[np++], sizeof paths[0], "%s/%s", dir, fd.cFileName);
    } while (FindNextFileA(hf, &fd));
    FindClose(hf);
#endif
    if (!np) return 0;
    if (!g_out2) g_out2 = (uint32_t *)malloc((size_t)CAP * 4);
    int reps = getenv("RG_BENCH_REPS") ? atoi(getenv("RG_BENCH_REPS")) : 3;
    printf("gfxbench perf: %s%s, %d recordings, best of %d; per field\n", gpu_device_name(r),
           gpu_ordered_blend(r) ? " (ordered blending)" : "", np, reps);
    printf("| recording | scale | ms | display+wait ms | prims | batches | ordered | dst copies | "
           "write-backs | upload KB | decodes | decode hits |\n"
           "| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |\n");
    perf_res warm;
    perf_one(paths[0], r, 1, &warm);
    static const int scales[3] = { 0, 1, 3 };
    for (int si = 0; si < 3; si++)
        for (int i = 0; i < np; i++) {
            perf_res best;
            memset(&best, 0, sizeof best);
            best.ms = 1e30;
            for (int rep = 0; rep < reps; rep++) {
                perf_res x;
                if (perf_one(paths[i], r, scales[si], &x) == 0 && x.ms < best.ms) best = x;
            }
            if (best.ms > 1e29) continue;
            double f = (double)best.fields;
            const char *nm = strrchr(paths[i], '/');
            char sc[16];
            if (scales[si]) snprintf(sc, sizeof sc, "x%d", scales[si]);
            else snprintf(sc, sizeof sc, "GS model only");
            printf("| %s | %s | %.3f | %.3f | %.0f | %.1f | %.1f | %.1f | %.1f | %.0f | %.1f | %.1f |\n",
                   nm ? nm + 1 : paths[i], sc, best.ms, best.disp_ms, best.d.prims / f, best.d.batches / f,
                   best.d.rov_batches / f, best.d.dst_copies / f, best.d.rt_writebacks / f,
                   best.d.upload_bytes / 1024.0 / f, best.d.tex_decodes / f, best.d.tex_decode_hits / f);
            fflush(stdout);
        }
    gpu_set_scale(r, 1);
    return np;
}

int run_gfx_bench(const char *dir, gpu_renderer *r)
{
    char paths[16][600];
    int np = 0;
#ifdef _WIN32
    WIN32_FIND_DATAA fd;
    char pat[700];
    snprintf(pat, sizeof pat, "%s\\*.rggs", dir);
    HANDLE hf = FindFirstFileA(pat, &fd);
    if (hf == INVALID_HANDLE_VALUE) return 0;
    do {
        if (np < 16) snprintf(paths[np++], sizeof paths[0], "%s/%s", dir, fd.cFileName);
    } while (FindNextFileA(hf, &fd));
    FindClose(hf);
#endif
    if (!np) return 0;
    if (!g_out2) g_out2 = (uint32_t *)malloc((size_t)CAP * 4);
    bench_cfg cfgs[24];
    int nc = 0;
#define CFG(nm, sc) (memset(&cfgs[nc], 0, sizeof cfgs[nc]), cfgs[nc].name = nm, cfgs[nc].scale = sc, \
                     gpu_enhance_default(&cfgs[nc].e), gpu_post_default(&cfgs[nc].p), &cfgs[nc++])
    bench_cfg *c;
    CFG("original (x1)", 1);
    CFG("internal x2", 2);
    CFG("internal x3 (match 1280x960)", 3);
    CFG("internal x4", 4);
    CFG("internal x6", 6);
    CFG("internal x8", 8);
    c = CFG("ssaa 2 (x2 -> native, box)", 2); c->p.ssaa = 2;
    c = CFG("ssaa 4 (x4 -> native, box)", 4); c->p.ssaa = 4;
    c = CFG("x3 + ssaa 2 (x6 -> 1280x960, bicubic)", 6); c->p.ssaa = 2; c->p.downsample = GPU_RS_BICUBIC;
    c->p.out_w = 1280; c->p.out_h = 960;
    c = CFG("x4 -> window 1280x960 (box)", 4); c->p.out_w = 1280; c->p.out_h = 960;
    c = CFG("x4 -> window 1280x960 (lanczos)", 4); c->p.out_w = 1280; c->p.out_h = 960;
    c->p.downsample = GPU_RS_LANCZOS;
    c = CFG("fxaa", 1); c->p.fxaa = 1;
    c = CFG("fxaa at x3", 3); c->p.fxaa = 1;
    c = CFG("sharpen 0.5", 1); c->p.sharpen = 0.5f;
    c = CFG("gamma 1.2 + brightness 1.1", 1); c->p.gamma = 1.2f; c->p.brightness = 1.1f;
    c = CFG("scanlines (1280x960 window)", 1); c->p.output_filter = GPU_OUTF_SCANLINES;
    c->p.out_w = 1280; c->p.out_h = 960; c->p.upscale = GPU_RS_SHARP;
    c = CFG("crt (1280x960 window)", 1); c->p.output_filter = GPU_OUTF_CRT;
    c->p.out_w = 1280; c->p.out_h = 960; c->p.upscale = GPU_RS_SHARP;
    c = CFG("texture filter bilinear", 1); c->e.tex_filter = GPU_TEXF_BILINEAR;
    c = CFG("texture filter nearest", 1); c->e.tex_filter = GPU_TEXF_NEAREST;
    c = CFG("anisotropic 16x", 1); c->e.aniso = 16;
    c = CFG("everything (x3 ssaa2 fxaa sharpen aniso crt)", 6); c->p.ssaa = 2; c->p.fxaa = 1;
    c->p.sharpen = 0.5f; c->e.aniso = 16; c->e.tex_filter = GPU_TEXF_BILINEAR;
    c->p.output_filter = GPU_OUTF_CRT; c->p.out_w = 1280; c->p.out_h = 960; c->p.upscale = GPU_RS_SHARP;
    CFG("original (x1), again", 1);
#undef CFG
    int reps = getenv("RG_BENCH_REPS") ? atoi(getenv("RG_BENCH_REPS")) : 3;
    printf("gfxbench: %s, %d recordings, %d reps; ms per field (GS replay + display/post + read-back)\n",
           gpu_device_name(r), np, reps);
    double base = 0;
    {
        /* warm-up: device, shaders, driver caches */
        int fl = 0;
        for (int k = 0; k < nc; k++) bench_one(paths[0], r, &cfgs[k], &fl);
    }
    for (int k = 0; k < nc; k++) {
        double best[16];
        int fl = 0, tot = 0;
        for (int i = 0; i < np; i++) best[i] = 1e30;
        for (int rep = 0; rep < reps; rep++)
            for (int i = 0; i < np; i++) {
                double ms = bench_one(paths[i], r, &cfgs[k], &fl);
                if (ms >= 0 && ms < best[i]) best[i] = ms;
            }
        double sum = 0;
        for (int i = 0; i < np; i++) { sum += best[i]; tot++; }
        double mean = sum / tot;
        if (k == 0) base = mean;
        printf("| %-46s | %7.3f | %+7.3f |", cfgs[k].name, mean, mean - base);
        for (int i = 0; i < np; i++) printf(" %6.3f", best[i]);
        printf("\n");
    }
    gpu_set_scale(r, 1);
    gpu_enhance none;
    gpu_enhance_default(&none);
    gpu_set_enhance(r, &none);
    return np;
}

/* ------------------------------------------------------------ entry */
int run_gfx_test(const char *name, gpu_renderer *r)
{
    static const struct { const char *n; void (*f)(gpu_renderer *); } T[] = {
        { "original", t_original }, { "settings_map", t_settings_map },
        { "internal_res", t_internal_res }, { "texture_filter", t_texture_filter },
        { "anisotropic", t_anisotropic }, { "ssaa", t_ssaa }, { "fxaa", t_fxaa },
        { "sharpen", t_sharpen }, { "color", t_color }, { "output_filter", t_output_filter },
        { "resample", t_resample },
    };
    if (!g_ref) {
        g_ref = (uint32_t *)malloc((size_t)CAP * 4);
        g_out = (uint32_t *)malloc((size_t)CAP * 4);
        g_out2 = (uint32_t *)malloc((size_t)CAP * 4);
    }
    for (size_t i = 0; i < sizeof T / sizeof T[0]; i++)
        if (!strcmp(name, T[i].n)) {
            g_bad = 0;
            T[i].f(r);
            return g_bad ? -1 : 1;
        }
    return 0;
}

/* Pipelined read-back (gpu_config.readback_lag, docs/GPU.md "Performance"):
 * replay a recording through `ref` (lag off) and `lag`, hashing every
 * field's gpu_read_display; the lagged read k must return frame k-1 (frame 0
 * for the first read), bit for bit.  At scale 1 and 3. */
static uint64_t frame_hash(const uint32_t *px, uint32_t w, uint32_t h)
{
    uint64_t x = 1469598103934665603ull ^ ((uint64_t)w << 32 | h);
    for (size_t i = 0; i < (size_t)w * h; i++) { x ^= px[i]; x *= 1099511628211ull; }
    return x;
}

static int lag_hashes(const char *path, gpu_renderer *r, int scale, uint64_t *out, int cap)
{
    gs_rec_file rf;
    if (gs_rec_open(&rf, path) != 0) return -1;
    gs_state *hw = gs_create();
    if (gs_rec_load(&rf, hw) != 0) { gs_rec_close(&rf); gs_destroy(hw); return -1; }
    gpu_set_scale(r, scale);
    gpu_attach(r, hw);
    static uint8_t fifo[1 << 20];
    gs_rec_ev ev;
    int n = 0;
    while (gs_rec_next(&rf, &ev) == 1) {
        if (ev.kind == GS_REC_FIFO_READ && ev.a > sizeof fifo) ev.a = sizeof fifo;
        gs_rec_apply(hw, &ev, fifo);
        if (ev.kind == GS_REC_VSYNC && n < cap) {
            uint32_t w = 0, h = 0;
            if (gpu_read_display(r, GS_READ_FRAME, g_out2, CAP, &w, &h) != 0) w = h = 0;
            out[n++] = frame_hash(g_out2, w, h);
        }
    }
    gpu_detach(r);
    gs_destroy(hw);
    gs_rec_close(&rf);
    return n;
}

int run_lag_test(const char *path, gpu_renderer *ref, gpu_renderer *lag)
{
    static uint64_t a[4096], b[4096];
    if (!g_out2) g_out2 = (uint32_t *)malloc((size_t)CAP * 4);
    int bad = 0;
    static const int scales[2] = { 1, 3 };
    for (int si = 0; si < 2; si++) {
        int na = lag_hashes(path, ref, scales[si], a, 4096);
        int nb = lag_hashes(path, lag, scales[si], b, 4096);
        if (na < 2 || na != nb) {
            printf("lag: %s x%d: %d / %d fields\n", path, scales[si], na, nb);
            return -1;
        }
        int distinct = 0;
        for (int i = 0; i < na; i++) {
            uint64_t want = a[i > 0 ? i - 1 : 0];
            if (b[i] != want) {
                if (bad < 8) printf("lag: x%d read %d: not frame %d\n", scales[si], i, i > 0 ? i - 1 : 0);
                bad++;
            }
            if (i > 0 && a[i] != a[i - 1]) distinct++;
        }
        printf("lag: %s x%d: %d reads, %d frames differ from their predecessor, %d wrong\n", path,
               scales[si], na, distinct, bad);
        if (!distinct) {
            printf("lag: the recording shows one frame only: not a test\n");
            return -1;
        }
    }
    gpu_set_scale(ref, 1);
    gpu_set_scale(lag, 1);
    return bad ? -1 : 1;
}

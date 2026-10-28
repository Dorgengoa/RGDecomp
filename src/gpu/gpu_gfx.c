/* SPDX-License-Identifier: CC0-1.0 */
/* The graphics settings (src/settings, PLAN.md P6 "Graphics settings") as
 * renderer parameters: what the presenter (src/runtime) hands to the GPU
 * renderer.  docs/GPU.md "Graphics settings". */
#include <string.h>

#include "gpu.h"
#include "rg_settings.h"

void gpu_gfx_default(gpu_gfx *g)
{
    memset(g, 0, sizeof *g);
    g->internal_res = 1;
    g->ssaa = 1;
    gpu_enhance_default(&g->enh);
    gpu_post_default(&g->post);
}

static int has(const rg_settings *s, const char *id) { return rg_settings_find(s, id) >= 0; }

void gpu_gfx_from_settings(gpu_gfx *g, const struct rg_settings *s)
{
    gpu_gfx_default(g);
    if (!s) return;
    if (has(s, "graphics.internal_res")) {
        /* native, 2x..8x, window */
        int v = rg_settings_get_enum(s, "graphics.internal_res");
        g->internal_res = v <= 0 ? 1 : (v >= 8 ? 0 : v + 1);
    }
    if (has(s, "graphics.antialiasing")) {
        /* off, fxaa, ssaa2, ssaa3, ssaa4 */
        int v = rg_settings_get_enum(s, "graphics.antialiasing");
        g->post.fxaa = v == 1;
        g->ssaa = v >= 2 ? v : 1;
    }
    if (has(s, "graphics.downsample")) {
        static const int m[] = { GPU_RS_BOX, GPU_RS_BILINEAR, GPU_RS_BICUBIC, GPU_RS_LANCZOS };
        int v = rg_settings_get_enum(s, "graphics.downsample");
        g->post.downsample = v >= 0 && v < 4 ? m[v] : GPU_RS_BOX;
    }
    if (has(s, "graphics.texture_filter")) {
        int v = rg_settings_get_enum(s, "graphics.texture_filter");
        g->enh.tex_filter = v == 1 ? GPU_TEXF_BILINEAR : (v == 2 ? GPU_TEXF_NEAREST : GPU_TEXF_ORIGINAL);
    }
    if (has(s, "graphics.anisotropic")) {
        int v = rg_settings_get_enum(s, "graphics.anisotropic");   /* off, 2x .. 16x */
        g->enh.aniso = v <= 0 ? 0 : 1 << v;
    }
    static const char *const fx[GPU_FX_COUNT] = { "graphics.bloom", "graphics.depth_of_field",
                                                  "graphics.motion_blur" };
    for (int i = 0; i < GPU_FX_COUNT; i++)
        if (has(s, fx[i])) g->enh.fx[i] = rg_settings_get_enum(s, fx[i]);
    if (has(s, "graphics.gamma")) g->post.gamma = (float)rg_settings_get_float(s, "graphics.gamma");
    if (has(s, "graphics.brightness"))
        g->post.brightness = (float)rg_settings_get_float(s, "graphics.brightness");
    if (has(s, "graphics.sharpen")) g->post.sharpen = (float)rg_settings_get_float(s, "graphics.sharpen");
    if (has(s, "graphics.output_filter")) {
        int v = rg_settings_get_enum(s, "graphics.output_filter");
        g->post.output_filter = v == 1 ? GPU_OUTF_SCANLINES : (v == 2 ? GPU_OUTF_CRT : GPU_OUTF_OFF);
    }
}

int gpu_gfx_scale(const gpu_gfx *g, int dst_h, int native_h, int *ssaa_eff)
{
    int base = g->internal_res;
    if (base <= 0) {
        /* match the window: the smallest factor that reaches its height */
        base = native_h > 0 && dst_h > 0 ? (dst_h + native_h - 1) / native_h : 1;
    }
    if (base < 1) base = 1;
    if (base > 8) base = 8;
    int ss = g->ssaa < 1 ? 1 : g->ssaa;
    while (ss > 1 && base * ss > 8) ss--;   /* the renderer stops at 8x */
    if (ssaa_eff) *ssaa_eff = ss;
    return base * ss;
}

int gpu_gfx_original(const gpu_gfx *g)
{
    gpu_gfx o;
    gpu_gfx_default(&o);
    return g->internal_res == 1 && g->ssaa == 1 && memcmp(&g->enh, &o.enh, sizeof o.enh) == 0 &&
           gpu_post_identity(&g->post);
}

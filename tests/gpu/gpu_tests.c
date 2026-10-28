/* SPDX-License-Identifier: CC0-1.0 */
/* rg-gpu-tests <test>: runs GS streams through the software reference
 * rasterizer and the GPU renderer (D3D11 WARP unless RG_GPU_HW=1) and
 * compares local memory / display output.  docs/GPU.md "Validation".
 *
 *   golden.<name>   a tests/gs golden scene, through the tee (gpu_tee.h)
 *   scene.<name>    a scene of gpu_scenes.c
 *   control         scene.blend_flat with a deliberately wrong GPU blend
 *                   (must FAIL: proves the comparison is armed)
 *   control_feedback  scene.rtt_feedback without feedback splitting (must FAIL)
 *   info            prints the device and exits 0 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpu_compare.h"
#include "gpu_tests.h"

int g_fail;   /* the golden tests' own CHECK counter (gs_test_util.h) */
static int g_warp;
static int g_lag;   /* make_renderer: gpu_config.readback_lag */

extern int g_rtt_native;   /* gpu_scenes.c */

static gpu_renderer *make_renderer(int fault, int scale, int native)
{
    gpu_config c;
    gpu_config_default(&c);
    c.scale = scale;
    const char *hw = getenv("RG_GPU_HW");
    c.warp = !(hw && hw[0] == '1');
    g_warp = c.warp;
    c.fault = fault;
    if (getenv("RG_GPU_FAULT")) c.fault = atoi(getenv("RG_GPU_FAULT"));   /* debugging */
    c.rtt_native = native;
    c.readback_lag = g_lag;
    g_rtt_native = native;
    char err[256] = "";
    gpu_renderer *r = gpu_create(&c, err, sizeof err);
    if (!r) {
        fprintf(stderr, "gpu_create: %s\n", err);
        exit(2);
    }
    return r;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: rg-gpu-tests golden.<name> | scene.<name> | control | info\n");
        return 2;
    }
    const char *n = argv[1];
    int fault = !strcmp(n, "control") ? 1 : (!strcmp(n, "control_feedback") ? 2 :
                (!strcmp(n, "control_alias") ? 3 : (!strcmp(n, "control_exact") ? 4 :
                (!strcmp(n, "control_cover") ? 5 : (!strcmp(n, "control_ordered") ? 6 :
                (!strcmp(n, "control_decode") ? 7 : (!strcmp(n, "control_shared") ? 10 :
                (!strcmp(n, "control_selfread") ? 11 : (!strcmp(n, "control_floatpath") ? 12 :
                (!strcmp(n, "control_readcurrent") ? 14 :
                (!strcmp(n, "control_early") ? 16 : 0)))))))))));
    /* scaleN.<scene>: internal resolution xN (N = 2..8); scaleNn.<scene>: the
     * same with render targets always sampled through the native mirror
     * (gpu_config.rtt_native, the bit-exact path) */
    int scale = 1, native = 0, skip = 0;
    if (!strncmp(n, "scale", 5) && n[5] >= '2' && n[5] <= '8') {
        if (n[6] == '.') { scale = n[5] - '0'; skip = 7; }
        else if (n[6] == 'n' && n[7] == '.') { scale = n[5] - '0'; native = 1; skip = 8; }
    }
    /* control_direct: rtt_upscaled at x2 with direct sampling off */
    int control_direct = !strcmp(n, "control_direct");
    if (control_direct) { scale = 2; native = 1; }
    /* replay FILE / scaleN.replay FILE / replay-all DIR: GS recordings of the
     * real game (gpu_replay.c); replay-all skips without RG_DATA or files.
     * gfx.replay-all DIR: the same with the Original preset applied through
     * the graphics settings (gpu_gfx_tests.c); gfxbench DIR: per-field cost
     * of every graphics option (renderer only, no reference) */
    int gfx_replay = !strcmp(n, "gfx.replay-all"), gfx_bench = !strcmp(n, "gfxbench");
    if (gfx_replay) skip = 4;
    int replay = !strcmp(n + skip, "replay"), replay_all = !strcmp(n + skip, "replay-all");
    if (gfx_bench) {
        if (argc < 3) { fprintf(stderr, "usage: rg-gpu-tests gfxbench DIR [perf [MATCH]]\n"); return 2; }
        gpu_renderer *rb = make_renderer(0, 1, 0);
        /* gfxbench DIR perf [MATCH]: the renderer's own cost per field on
         * the recordings whose name contains MATCH (docs/GPU.md "Performance") */
        int k = argc >= 4 && !strcmp(argv[3], "perf")
                    ? run_gfx_perf(argv[2], argc >= 5 ? argv[4] : "", rb)
                    : run_gfx_bench(argv[2], rb);
        gpu_destroy(rb);
        return k > 0 ? 0 : 77;
    }
    if (!strcmp(n, "lag")) {
        /* lag FILE: the pipelined read-back returns each previous frame
         * (docs/GPU.md "Performance"); FILE is a recording (game data) */
        FILE *f = argc >= 3 ? fopen(argv[2], "rb") : NULL;
        if (!f || !getenv("RG_DATA")) {
            if (f) fclose(f);
            printf("lag: needs a recording and RG_DATA: skipped\n");
            return 77;
        }
        fclose(f);
        gpu_renderer *ra = make_renderer(0, 1, 0);
        g_lag = 1;
        gpu_renderer *rb = make_renderer(0, 1, 0);
        g_lag = 0;
        int k = run_lag_test(argv[2], ra, rb);
        gpu_destroy(ra);
        gpu_destroy(rb);
        printf("lag: %s\n", k > 0 ? "PASS" : "FAIL");
        return k > 0 ? 0 : 1;
    }
    if ((replay || replay_all) && argc < 3) {
        fprintf(stderr, "usage: rg-gpu-tests [scaleN.]replay FILE | replay-all DIR\n");
        return 2;
    }
    if (replay_all && !getenv("RG_DATA")) {
        printf("%s: needs game data (RG_DATA unset): skipped\n", n);
        return 77;
    }
    gpu_renderer *r = make_renderer(fault, scale, native);
    if (!strcmp(n, "info")) {
        printf("device: %s%s\n", gpu_device_name(r), gpu_ordered_blend(r) ? " (ordered blending)" : "");
        gpu_destroy(r);
        return 0;
    }
    cmp_reset();
    int found = 0;
    if (replay || replay_all) {
        /* real game frames: exact at scale 1 (RG_REPLAY_TOL overrides).
         * Upscaled: local memory holds the sub-sample (s/2, s/2) and the
         * display is box-filtered to native; magnified bilinear stars and
         * the internal-resolution anti-flicker merge differ from the
         * reference by design (measured max 62), so only gross errors
         * (a wrong texture, a missing primitive: > 64) fail */
        const char *tol = getenv("RG_REPLAY_TOL");
        g_cmp_tol = tol ? atoi(tol) : (scale > 1 ? 64 : 0);
        /* upscaled: isolated pixels may go beyond 64 where a star smaller
         * than a native pixel lands between sub-samples, or shifts a
         * quarter pixel through the internal-resolution anti-flicker merge
         * (normal_2150_warp: 88 target / 28 display pixels, max 114 / 72,
         * 32 and 2 ppm); a wrong texture or a missing primitive is
         * thousands */
        if (scale > 1) g_cmp_ppm = g_cmp_disp_ppm = 200;
        if (replay) {
            found = run_replay(argv[2], r) == 0;
        } else {
            int k = gfx_replay ? run_gfx_replay_dir(argv[2], r) : run_replay_dir(argv[2], r);
            if (k == 0) {
                printf("%s: no recordings (*.rggs) in %s: skipped\n", n, argv[2]);
                gpu_destroy(r);
                return 77;
            }
            found = k > 0;
        }
        if (!found) {
            gpu_destroy(r);
            return 1;
        }
    } else if (!strncmp(n, "gfx.", 4)) {
        /* graphics settings: every option on a synthetic scene, Original exact */
        g_cmp_tol = 0;
        int k = run_gfx_test(n + 4, r);
        found = k != 0;
        if (k < 0) g_cmp.raw_bad++;   /* the test's own checks failed */
    } else if (!strncmp(n, "golden.", 7)) {
        const char *t = n + 7;
        tee_set_renderer(r);
        g_tee_name = t;
        /* exact triangles (docs/GPU.md "Exact triangles"): every golden
         * scene matches the reference bit for bit; float interpolation
         * (a device without double-precision shader ops) gets +-2 */
        g_cmp_tol = gpu_exact_triangles(r) ? 0 : 2;
        if (getenv("RG_SCENE_TOL")) g_cmp_tol = atoi(getenv("RG_SCENE_TOL"));   /* debugging */
        found = test_prim(t) || test_pixel(t) || test_clut(t) || test_display(t);
    } else if (!strncmp(n, "scene.", 6)) {
        found = run_scene(n + 6, r);
        /* interpolated scenes: discrete decisions taken on interpolated
         * values (mip level, 1/16 bilinear weight, depth-test winner, and on
         * WARP edge pixels) can flip at their boundaries */
        if (g_cmp_tol > 0) g_cmp_ppm = 50;
    } else if (control_direct) {
        found = run_scene("rtt_upscaled", r);
    } else if (fault == 5) {
        /* control_cover: offscreen with the rasterizer deciding triangle
         * coverage (no bounding box); fails where the device clips large
         * triangles into fans (WARP), skipped where it does not */
        found = run_scene("offscreen", r);
        if (found && g_cmp.px_bad == 0 && g_cmp.raw_bad == 0) {
            printf("control_cover: %s covers the clipped triangles exactly: skipped\n",
                   gpu_device_name(r));
            gpu_destroy(r);
            return 77;
        }
    } else if (fault == 7) {
        /* control_decode: every decoded texel's red channel off by one;
         * tex_point (every texture format and CLUT mode) must see it */
        found = run_scene("tex_point", r);
    } else if (fault == 6) {
        /* control_ordered: the ordered states drawn with one destination
         * snapshot per batch and no overlap split */
        found = run_scene("ordered", r);
    } else if (fault == 4) {
        /* control_exact: frame640 (a Gouraud triangle) through float
         * interpolation, held to the exact-triangle tolerance 0 */
        g_scene_tol_force = 0;
        found = run_scene("frame640", r);
    } else if (fault == 3) {
        found = run_scene("rtt_alias", r);
    } else if (fault == 10) {
        /* control_shared: colour and depth targets sharing pages are not
         * written back around their draws (docs/GPU.md "Checkpoint 4") */
        found = run_scene("alias_pages", r);
    } else if (fault == 16) {
        /* control_early: early copies kept although the pages were drawn
         * after them */
        found = run_scene("rtt_depth", r);
    } else if (fault == 14) {
        /* control_readcurrent: split pages taken as current for CPU reads */
        found = run_scene("alias_pages", r);
    } else if (fault == 12) {
        /* control_floatpath: float values taken without their bound */
        found = run_scene("exact_float", r);
    } else if (fault == 11) {
        /* control_selfread: the reference samples memory as the primitive
         * writes it (no texture snapshot); the GPU cannot, and must differ */
        gs_tex_snapshot_off = 1;
        found = run_scene("alias_pages", r);
    } else if (scale > 1) {
        /* upscaled internal resolution: flat 2D scenes only (sprites on
         * whole pixels keep every s x s block uniform); compared through
         * the write-back (centre sample) and the display (top-left sample) */
        found = run_scene(n + skip, r);
        /* upscaled passes sampled directly set their own tolerance */
    } else if (fault == 2) {
        found = run_scene("rtt_feedback", r);
    } else if (fault) {
        found = run_scene("blend_flat", r);
    }
    if (!found) {
        fprintf(stderr, "unknown test %s\n", n);
        gpu_destroy(r);
        return 2;
    }
    printf("%s: device %s (%s)\n", n, gpu_device_name(r), g_warp ? "WARP" : "hardware");
    int bad = cmp_report(n);
    const gpu_stats *s = gpu_get_stats(r);
    printf("%s: gpu: %llu ordered batches%s, %llu textures decoded, %llu decoded-texture hits, %llu grown triangles, %llu shared-target batches, %llu reads current, %llu early copies, %llu early reads\n", n,
           (unsigned long long)s->rov_batches, gpu_ordered_blend(r) ? "" : " (ordered blending off)",
           (unsigned long long)s->tex_decodes, (unsigned long long)s->tex_decode_hits,
           (unsigned long long)s->grown_tris, (unsigned long long)s->shared_rt_batches,
           (unsigned long long)s->reads_current, (unsigned long long)s->early_copies, (unsigned long long)s->early_reads);
    printf("%s: gpu: %llu exact triangles, %llu of them large (double coverage), %llu px\n", n,
           (unsigned long long)s->exact_tris, (unsigned long long)s->big_tris, (unsigned long long)s->big_px);
    printf("%s: gpu: %llu prims, %llu batches, %llu passes, %llu dst copies, %llu targets created,"
           " %llu loads, %llu write-backs, %llu drops, %llu feedback splits, up %llu KB, down %llu KB,"
           " %llu direct samples, %llu write-backs avoided, %llu target copies, %llu cpu prims\n",
           n, (unsigned long long)s->prims, (unsigned long long)s->batches,
           (unsigned long long)s->passes, (unsigned long long)s->dst_copies,
           (unsigned long long)s->rt_creates, (unsigned long long)s->rt_loads,
           (unsigned long long)s->rt_writebacks, (unsigned long long)s->rt_drops,
           (unsigned long long)s->feedback_splits,
           (unsigned long long)(s->upload_bytes >> 10), (unsigned long long)(s->download_bytes >> 10),
           (unsigned long long)s->direct_samples, (unsigned long long)s->writebacks_avoided,
           (unsigned long long)s->tex_copies, (unsigned long long)s->cpu_prims);
    gpu_destroy(r);
    if (g_fail) fprintf(stderr, "%s: %d reference CHECKs failed\n", n, g_fail);
    if (bad || g_fail) {
        printf("%s: FAIL\n", n);
        return 1;
    }
    printf("%s: PASS\n", n);
    return 0;
}

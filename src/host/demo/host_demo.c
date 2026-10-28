/* SPDX-License-Identifier: CC0-1.0 */
/* rg-host-demo: the host shell end to end without the game.
 *
 * Each 59.94 Hz field it sends GIF packets (PATH3) to the GS model's software
 * rasterizer -- a background sprite, a rotating Gouraud triangle, a bouncing
 * alpha-blended sprite and a panel showing the live DS2 pad state -- reads the
 * PCRTC display out (640x448 interlaced FRAME mode) and presents it.  It plays
 * a test tone (440 Hz, 660 Hz while CROSS is held).
 *
 *   rg-host-demo [--headless] [--frames N] [--screenshot out.png]
 *                [--input script.txt] [--config map.cfg] [--write-config f]
 *                [--scale linear|nearest|integer|stretch] [--fullscreen]
 *                [--unthrottled] [--mute] [--vsync]
 *                [--gpu [--warp] [--gpu-scale N]]
 *
 * --gpu draws with the Direct3D 11 GS renderer (src/gpu, docs/GPU.md) instead
 * of the software rasterizer and builds the display on the GPU; the frame is
 * read back and presented through the same rg_host_present path.  --warp
 * uses the WARP software device; --gpu-scale renders at N x resolution.
 *
 * --headless implies --unthrottled and no audio device; it prints the FNV-1a
 * hash of the last frame so CTest can compare runs.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "gs.h"
#include "host.h"
#include "rg_input.h"
#include "rg_settings.h"
#ifdef RG_HAVE_GPU
#include "gpu.h"
#endif

/* ------------------------------------------------------------ GIF packets */
typedef struct pkt { uint64_t q[2 * 512]; uint32_t n, tag; } pkt;

static void pk_begin(pkt *p) { p->n = 0; }
static void pk_qw(pkt *p, uint64_t lo, uint64_t hi)
{
    p->q[2 * p->n] = lo;
    p->q[2 * p->n + 1] = hi;
    p->n++;
}
/* one A+D packet: tag (NLOOP filled in at pk_send), then reg/value pairs */
static void pk_ad_begin(pkt *p) { p->tag = p->n; pk_qw(p, 0, 0); }
static void pk_ad(pkt *p, uint32_t reg, uint64_t v) { pk_qw(p, v, reg); }
static void pk_ad_end(pkt *p)
{
    uint32_t nloop = p->n - p->tag - 1;
    /* NLOOP, EOP=1, FLG=PACKED, NREG=1, REGS[0]=0xE (A+D) */
    p->q[2 * p->tag] = (uint64_t)nloop | (1ull << 15) | (1ull << 60);
    p->q[2 * p->tag + 1] = 0xE;
}
static void pk_send(gs_state *gs, pkt *p) { gs_gif_write(gs, GS_PATH3, p->q, p->n); }

static uint64_t rgbaq(int r, int g, int b, int a)
{
    return (uint64_t)(r & 255) | ((uint64_t)(g & 255) << 8) | ((uint64_t)(b & 255) << 16) |
           ((uint64_t)(a & 255) << 24) | (0x3F800000ull << 32);
}
static uint64_t xyz(int x16, int y16) { return (uint64_t)(x16 & 0xFFFF) | ((uint64_t)(y16 & 0xFFFF) << 16); }

#define PRIM(type, iip, abe) ((uint64_t)(type) | ((uint64_t)(iip) << 3) | ((uint64_t)(abe) << 6))

static void sprite(pkt *p, int x0, int y0, int x1, int y1, int r, int g, int b, int a, int abe)
{
    pk_ad(p, GS_PRIM, PRIM(GS_PRIM_SPRITE, 0, abe));
    pk_ad(p, GS_RGBAQ, rgbaq(r, g, b, a));
    pk_ad(p, GS_XYZ2, xyz(x0 * 16, y0 * 16));
    pk_ad(p, GS_XYZ2, xyz(x1 * 16, y1 * 16));
}

static void gs_setup(gs_state *gs)
{
    pkt p;
    pk_begin(&p);
    pk_ad_begin(&p);
    pk_ad(&p, GS_FRAME_1, 0 | (10ull << 16) | ((uint64_t)GS_PSMCT32 << 24));
    pk_ad(&p, GS_ZBUF_1, 140 | (1ull << 32));                 /* Z32 at page 140, ZMSK */
    pk_ad(&p, GS_TEST_1, (1ull << 16) | (1ull << 17));        /* ZTE, ZTST ALWAYS */
    pk_ad(&p, GS_XYOFFSET_1, 0);
    pk_ad(&p, GS_SCISSOR_1, 0 | (639ull << 16) | (0ull << 32) | (447ull << 48));
    pk_ad(&p, GS_PRMODECONT, 1);
    pk_ad(&p, GS_COLCLAMP, 1);
    pk_ad(&p, GS_DTHE, 0);
    pk_ad(&p, GS_ALPHA_1, 0x44);                              /* (Cs-Cd)*As>>7 + Cd */
    pk_ad_end(&p);
    pk_send(gs, &p);
    /* PCRTC: circuit 1, interlaced FRAME mode, 640x448 (libgraph DH = 2h-1) */
    gs_write_priv(gs, GS_P_SMODE2, 3);
    gs_write_priv(gs, GS_P_DISPFB1, 0 | (10ull << 9) | ((uint64_t)GS_PSMCT32 << 15));
    gs_write_priv(gs, GS_P_DISPLAY1, 636 | (50ull << 12) | (3ull << 23) | (0ull << 27) |
                                     (2559ull << 32) | (895ull << 44));
    gs_write_priv(gs, GS_P_BGCOLOR, 0);
    gs_write_priv(gs, GS_P_PMODE, 1 | (1u << 2) | (1u << 5) | (0xFFu << 8));
}

static int tri_wave(int t, int span)
{
    int m = t % (2 * span);
    return m < span ? m : 2 * span - m;
}

static void draw_frame(gs_state *gs, uint32_t k, const rg_pad *pad)
{
    pkt p;
    pk_begin(&p);
    pk_ad_begin(&p);
    /* background */
    sprite(&p, 0, 0, 640, 448, 16, 18, 40, 0x80, 0);
    /* rotating Gouraud triangle */
    float ang = (float)(k % 600) * (6.2831853f / 600.0f);
    static const int col[3][3] = { { 255, 40, 40 }, { 40, 255, 40 }, { 40, 80, 255 } };
    pk_ad(&p, GS_PRIM, PRIM(GS_PRIM_TRIANGLE, 1, 0));
    for (int i = 0; i < 3; i++) {
        float a = ang + (float)i * 2.0943951f;
        int x = (int)lroundf((320.0f + 170.0f * cosf(a)) * 16.0f);
        int y = (int)lroundf((200.0f + 150.0f * sinf(a)) * 16.0f);
        pk_ad(&p, GS_RGBAQ, rgbaq(col[i][0], col[i][1], col[i][2], 0x80));
        pk_ad(&p, GS_XYZ2, xyz(x, y));
    }
    /* bouncing half-transparent sprite (blended over the triangle) */
    int bx = 20 + tri_wave((int)k * 5, 640 - 40 - 64);
    int by = 20 + tri_wave((int)k * 3, 360 - 40 - 64);
    sprite(&p, bx, by, bx + 64, by + 64, 255, 170, 0, 0x40, 1);
    pk_ad_end(&p);
    pk_send(gs, &p);

    /* pad panel: 16 buttons in report bit order, then the two sticks */
    pk_begin(&p);
    pk_ad_begin(&p);
    sprite(&p, 0, 372, 640, 448, 8, 8, 16, 0x80, 0);
    for (int i = 0; i < 16; i++) {
        int on = (pad->buttons >> i) & 1;
        int x = 16 + i * 26;
        sprite(&p, x, 392, x + 20, 412, on ? 80 : 50, on ? 255 : 50, on ? 120 : 60, 0x80, 0);
    }
    const uint8_t st[2][2] = { { pad->lx, pad->ly }, { pad->rx, pad->ry } };
    for (int s = 0; s < 2; s++) {
        int x0 = 448 + s * 84, y0 = 378;
        sprite(&p, x0, y0, x0 + 64, y0 + 64, 40, 40, 70, 0x80, 0);
        int dx = x0 + st[s][0] / 4, dy = y0 + st[s][1] / 4;
        sprite(&p, dx - 3, dy - 3, dx + 4, dy + 4, 255, 255, 255, 0x80, 0);
    }
    pk_ad_end(&p);
    pk_send(gs, &p);
}

static uint64_t fnv1a(const void *d, size_t n)
{
    const uint8_t *p = (const uint8_t *)d;
    uint64_t h = 0xCBF29CE484222325ull;
    while (n--) { h ^= *p++; h *= 0x100000001B3ull; }
    return h;
}

/* audio samples due by the start of field k: floor(k * 48000 * 1001 / 60000) */
static uint64_t samples_at(uint64_t k) { return k * 4004 / 5; }

static void usage(void)
{
    fprintf(stderr,
            "usage: rg-host-demo [--headless] [--frames N] [--screenshot out.png]\n"
            "       [--input script.txt] [--config map.cfg] [--write-config map.cfg]\n"
            "       [--scale linear|nearest|integer|stretch] [--fullscreen]\n"
            "       [--unthrottled] [--mute] [--vsync] [--gpu [--warp] [--gpu-scale N]]\n"
            "       [--settings FILE] [--set id=value] [--preset original|default]\n"
            "       [--write-settings FILE] [--overlay] [--window-shot out.png]\n"
            "       [--menu up,down,accept,...,text:abc,press:key:F,motion:DX:DY]\n"
            "       (F1 / gamepad Guide: settings overlay)\n");
}

int main(int argc, char **argv)
{
    rg_host_config hc;
    rg_host_config_default(&hc);
    /* settings first (docs/SETTINGS.md): --settings / --set / --preset are
     * consumed from argv; the flags below still override them */
    rg_settings *settings = rg_settings_create();
    rg_settings_register_core(settings);
    rg_actions_register_settings(settings);
    const char *settings_path = NULL, *write_settings = NULL;
    int open_overlay = 0;
    const char *window_shot = NULL, *menu_script = NULL;
    int set_errors = 0;
    argc = rg_settings_apply_args(settings, argc, argv, &set_errors, &settings_path);
    if (set_errors) { usage(); return 2; }
    rg_host_config_from_settings(&hc, settings);
    hc.title = "rg-host-demo";
    long frames = -1;
    const char *shot = NULL, *script_path = NULL, *cfg_path = NULL, *write_cfg = NULL;
    int unthrottled = 0, mute = 0;
    int use_gpu = 0, gpu_warp = 0, gpu_scale = 1, gpu_scale_set = 0;
    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
        const char *v = i + 1 < argc ? argv[i + 1] : NULL;
        if (!strcmp(a, "--headless")) hc.headless = 1;
        else if (!strcmp(a, "--frames") && v) { frames = strtol(v, NULL, 0); i++; }
        else if (!strcmp(a, "--screenshot") && v) { shot = v; i++; }
        else if (!strcmp(a, "--input") && v) { script_path = v; i++; }
        else if (!strcmp(a, "--config") && v) { cfg_path = v; i++; }
        else if (!strcmp(a, "--write-config") && v) { write_cfg = v; i++; }
        else if (!strcmp(a, "--write-settings") && v) { write_settings = v; i++; }
        else if (!strcmp(a, "--overlay")) open_overlay = 1;
        else if (!strcmp(a, "--window-shot") && v) { window_shot = v; i++; }
        else if (!strcmp(a, "--menu") && v) { menu_script = v; open_overlay = 1; i++; }
        else if (!strcmp(a, "--scale") && v) {
            int m = rg_scale_from_name(v);
            if (m < 0) { usage(); return 2; }
            hc.scale = (rg_scale_mode)m;
            i++;
        } else if (!strcmp(a, "--fullscreen")) hc.fullscreen = 1;
        else if (!strcmp(a, "--unthrottled")) unthrottled = 1;
        else if (!strcmp(a, "--mute")) mute = 1;
        else if (!strcmp(a, "--vsync")) hc.vsync = 1;
        else if (!strcmp(a, "--gpu")) use_gpu = 1;
        else if (!strcmp(a, "--warp")) gpu_warp = 1;
        else if (!strcmp(a, "--gpu-scale") && v) { gpu_scale = (int)strtol(v, NULL, 0); gpu_scale_set = 1; i++; }
        else { usage(); return 2; }
    }
    if (hc.headless) {
        unthrottled = 1;
        if (frames < 0) frames = 60;
    }
    hc.audio = !mute;

    rg_input_script script = { 0 };
    char err[512];
    if (script_path && rg_input_script_load(&script, script_path, err, sizeof err)) {
        fprintf(stderr, "rg-host-demo: %s\n", err);
        return 1;
    }
    rg_host *h = rg_host_create(&hc);
    if (!h) {
        fprintf(stderr, "rg-host-demo: %s\n", rg_host_last_error());
        return 1;
    }
    rg_host_settings_from_config(settings, &hc);   /* --scale etc. win over the file */
    rg_host_attach_settings(h, settings, settings_path);
    rg_settings_mark_applied(settings);
    if (open_overlay) rg_host_set_overlay(h, true);
    if (menu_script && rg_host_menu_script(h, menu_script) < 0) {
        fprintf(stderr, "rg-host-demo: bad --menu item in '%s'\n", menu_script);
        rg_host_destroy(h);
        return 2;
    }
    if (write_settings && rg_settings_save(settings, write_settings, 0))
        fprintf(stderr, "rg-host-demo: cannot write %s\n", write_settings);
    if (cfg_path && rg_input_map_load(rg_host_input_map(h), cfg_path, err, sizeof err)) {
        fprintf(stderr, "rg-host-demo: %s\n", err);
        rg_host_destroy(h);
        return 1;
    }
    if (cfg_path)   /* the legacy per-PS2-input map replaces the action bindings */
        rg_host_apply_input_map(h);
    if (write_cfg) {
        static char text[16384];
        rg_input_map_format(rg_host_input_map(h), text, sizeof text);
        FILE *f = fopen(write_cfg, "wb");
        if (!f || fputs(text, f) < 0) { fprintf(stderr, "rg-host-demo: cannot write %s\n", write_cfg); }
        if (f) fclose(f);
    }
    if (script.words) rg_host_set_input_script(h, &script);

    gs_state *gs = gs_create();
#ifdef RG_HAVE_GPU
    gpu_renderer *gpu = NULL;
    if (use_gpu) {
        gpu_config gc;
        gpu_config_default(&gc);
        gc.warp = gpu_warp;
        gc.scale = gpu_scale;
        gpu = gpu_create(&gc, err, sizeof err);
        if (!gpu) {
            fprintf(stderr, "rg-host-demo: --gpu: %s\n", err);
            gs_destroy(gs);
            rg_host_destroy(h);
            return 1;
        }
        gpu_attach(gpu, gs);
        fprintf(stderr, "rg-host-demo: GPU renderer: %s, scale %d\n", gpu_device_name(gpu), gpu_scale);
    }
#else
    if (use_gpu) {
        fprintf(stderr, "rg-host-demo: built without the GPU renderer (src/gpu)\n");
        gs_destroy(gs);
        rg_host_destroy(h);
        return 1;
    }
#endif
    gs_setup(gs);
    static uint32_t frame[640 * 448 * 64];   /* up to --gpu-scale 8 */
    static int16_t pcm[2 * 2048];
    rg_pacer pacer;
    rg_pacer_init(&pacer, !unthrottled);
    double phase = 0.0;
    uint32_t w = 0, hgt = 0;
    int rc = 0;
    uint64_t title_ns = 0;
    uint32_t title_k = 0;
    uint64_t ns_draw = 0, ns_read = 0, ns_present = 0, nframes = 0;

    for (uint32_t k = 0; frames < 0 || k < (uint32_t)frames; k++) {
        if (!rg_host_pump(h)) break;
        if (window_shot && frames > 0 && k + 1 == (uint32_t)frames)
            rg_host_request_window_shot(h, window_shot);
        rg_pad pad;
        rg_host_read_pad(h, 0, k, &pad);
        uint64_t t0 = SDL_GetTicksNS();
        draw_frame(gs, k, &pad);
        gs_vsync(gs);
        uint64_t t1 = SDL_GetTicksNS();
        int drc;
#ifdef RG_HAVE_GPU
        if (gpu) {
            /* graphics.* (docs/GPU.md "Graphics settings"): enhancements,
             * internal resolution (unless --gpu-scale), post chain sized to
             * the window rectangle */
            gpu_gfx gx;
            gpu_gfx_from_settings(&gx, settings);
            gpu_set_enhance(gpu, &gx.enh);
            uint32_t nw = 0, nh = 0;
            gpu_post post;
            gpu_post_default(&post);
            if (gpu_display_size(gpu, &nw, &nh) == 0 && nw && nh) {
                int ww = 0, wh = 0, fac = 0, ss = 1;
                rg_host_window_size(h, &ww, &wh);
                rg_rect dst = { 0, 0, 0, 0 };
                if (ww > 0 && wh > 0) dst = rg_fit_rect(ww, wh, (int)nw, (int)nh, 4, 3, rg_host_scale(h), &fac);
                int sc = gpu_gfx_scale(&gx, dst.h, (int)nh, &ss);
                if (!gpu_scale_set) gpu_set_scale(gpu, sc);
                else ss = 1;
                post = gx.post;
                post.ssaa = ss;
                if (!gpu_post_identity(&post)) {
                    post.out_w = dst.w;
                    post.out_h = dst.h;
                    rg_scale_mode m = rg_host_scale(h);
                    post.upscale = m == RG_SCALE_NEAREST ? GPU_RS_NEAREST
                                 : (m == RG_SCALE_INTEGER ? GPU_RS_SHARP : GPU_RS_BILINEAR);
                }
            }
            drc = gpu_read_output(gpu, GS_READ_FRAME, &post, frame, sizeof frame / 4, &w, &hgt);
        } else
#endif
        drc = gs_read_display(gs, GS_READ_FRAME, frame, sizeof frame / 4, &w, &hgt);
        if (drc) {
            fprintf(stderr, "rg-host-demo: display read-out failed (%ux%u)\n", w, hgt);
            rc = 1;
            break;
        }
        uint64_t t2 = SDL_GetTicksNS();
        rg_host_present(h, frame, w, hgt);
        uint64_t t3 = SDL_GetTicksNS();
        ns_draw += t1 - t0;
        ns_read += t2 - t1;
        ns_present += t3 - t2;
        nframes++;

        /* test tone for this field */
        uint32_t ns = (uint32_t)(samples_at(k + 1) - samples_at(k));
        double hz = (pad.buttons & RG_BTN_CROSS) ? 660.0 : 440.0;
        for (uint32_t i = 0; i < ns; i++) {
            int16_t s = (int16_t)lrint(sin(phase) * 4000.0);
            pcm[2 * i] = pcm[2 * i + 1] = s;
            phase += 6.283185307179586 * hz / RG_AUDIO_RATE;
            if (phase > 6.283185307179586) phase -= 6.283185307179586;
        }
        if (rg_host_audio_queued(h) < RG_AUDIO_RATE / 5)   /* keep < 200 ms queued */
            rg_host_audio_push(h, pcm, ns);

        rg_pacer_hook(rg_field_cycles(k), rg_field_cycles(k + 1), &pacer);

        if (!hc.headless && (k % 30) == 29) {
            uint64_t now = pacer.now_ns(NULL);
            double fps = title_ns ? (double)(k - title_k) * 1e9 / (double)(now - title_ns) : 0.0;
            title_ns = now;
            title_k = k;
            char t[256];
            snprintf(t, sizeof t,
                     "rg-host-demo | pad %04X L(%3u,%3u) R(%3u,%3u) | %.1f fps | %s%s | pads %d%s | prompts %s",
                     pad.buttons, pad.lx, pad.ly, pad.rx, pad.ry, fps,
                     rg_scale_name(rg_host_scale(h)), rg_host_fullscreen(h) ? " fs" : "",
                     rg_host_gamepad_count(h), script.words ? " | script" : "",
                     rg_prompt_style_name(rg_host_prompt_style(h)));
            rg_host_set_title(h, t);
        }
    }

    const uint32_t *last = rg_host_last_frame(h, &w, &hgt);
    if (last) {
        printf("rg-host-demo: frames=%ld size=%ux%u hash=%016llx audio_frames=%llu\n",
               frames, w, hgt, (unsigned long long)fnv1a(last, (size_t)w * hgt * 4),
               (unsigned long long)rg_host_audio_pushed_total(h));
        if (shot && rg_host_screenshot(h, shot)) {
            fprintf(stderr, "rg-host-demo: cannot write %s\n", shot);
            rc = 1;
        }
        if (nframes)
            fprintf(stderr, "rg-host-demo: %s: per frame: GS draw %.2f ms, display read-out %.2f ms,"
                    " present %.2f ms (%.1f fps without pacing)\n",
                    use_gpu ? "GPU" : "SW", ns_draw / 1e6 / nframes, ns_read / 1e6 / nframes,
                    ns_present / 1e6 / nframes,
                    1e9 * (double)nframes / (double)(ns_draw + ns_read + ns_present));
    } else if (shot) {
        fprintf(stderr, "rg-host-demo: no frame to save\n");
        rc = 1;
    }
#ifdef RG_HAVE_GPU
    if (gpu) gpu_destroy(gpu);   /* detaches (syncs gs->vram) first */
#endif
    gs_destroy(gs);
    rg_host_destroy(h);
    rg_settings_destroy(settings);
    rg_input_script_free(&script);
    return rc;
}

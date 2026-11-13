/* SPDX-License-Identifier: CC0-1.0 */
/* SDL3 window, presentation, live input (through the input-action layer,
 * docs/INPUT.md), the settings overlay (docs/SETTINGS.md), audio stream.
 * docs/HOST.md. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#ifdef _WIN32
#define COBJMACROS 1
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#undef small   /* rpcndr.h: rg_host_rumble has a parameter called small */
#endif
/* only for SDL_SetMainReady(): we own main(), SDL must not wrap it */
#define SDL_MAIN_HANDLED 1
#include <SDL3/SDL_main.h>

#include "host_internal.h"
#include "rg_tstretch.h"
#include "rg_input.h"
#include "rg_menu.h"
#include "rg_settings.h"
#include "rg_display.h"

struct rg_host {
    rg_host_config cfg;
    int headless;
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Texture *tex;        /* streaming, source size */
    int tex_w, tex_h;
    SDL_Texture *pre;        /* render target for the integer prescale */
    int pre_w, pre_h;
#ifdef _WIN32
    /* rg_host_present_shared: shared textures opened on the renderer's
     * device, by handle (the producer alternates two) */
    struct {
        void *handle;
        ID3D11Texture2D *tex;
        IDXGIKeyedMutex *km;
        SDL_Texture *st;
        uint32_t w, h;
        uint32_t used;
    } shr[2];
    uint32_t shr_clock;
    int shr_off;              /* the renderer is not Direct3D 11 */
#endif
    /* rg_host_use_vulkan: the renderer is SDL's Vulkan renderer on the GPU backend's device;
     * rg_host_present_shared wraps the backend's images (rg_host_vk_frame), cached by image */
    int vk;
    struct {
        uint64_t image;
        SDL_Texture *st;
        uint32_t w, h;
        uint32_t used;
    } vks[2];
    uint32_t vk_clock;
    uint32_t *frame;
    uint32_t fw, fh;
    size_t fcap;
    rg_input_map map;        /* legacy text map (--config); rg_host_apply_input_map */
    rg_actions acts;         /* what live input is evaluated with */
    const rg_input_script *script;
    rg_pad_roster roster;
    SDL_Gamepad *pads[RG_MAX_GAMEPADS];   /* by roster slot */
    rg_press_latch latch;
    float mouse_dx, mouse_dy;             /* relative motion since the last pump */
    /* mouse camera (docs/INPUT.md "Mouse camera implementation") */
    rg_look_acc look;                     /* live + injected motion -> look units */
    bool look_active;                     /* rg_host_set_look_active: a camera consumes look */
    int camera_view;                      /* rg_host_set_camera_view: RG_CAMVIEW_* */
    bool look_captured;                   /* relative mouse mode on */
    SDL_AudioStream *audio;
    uint64_t audio_total;
    SDL_AtomicInt starved, starved_frames;   /* device pulls the stream could not fill */
    rg_audio_reg reg;                         /* host_audio.c: latency target, drift */
    uint64_t starved_seen;
    uint32_t starved_frames_seen;             /* (adaptive cushion: frames starved since the last push) */
    /* gameplay.battle_speed (rg_host_audio_set_speed): the pitch-keeping time compression */
    rg_tstretch *ts;                          /* NULL until the option is first on */
    int ts_on;
    double ts_speed;
    int16_t *ts_out;
    int16_t tail[2];                          /* last frame pushed (de-click origin) */
    SDL_AtomicInt tail_packed, starve_faded;  /* for the device thread: tail, fade done */
    int declick;                              /* $RG_AUDIO_DECLICK=0 turns it off (A/B) */
    int declick_pending;                      /* a whole block was dropped: ramp the next */
    FILE *tap, *tap_ev;                       /* $RG_AUDIO_HOST_WAV (+ .events.tsv) */
    uint64_t tap_frames;
    float volume;
    int volume_in_mix;                        /* rg_host_set_volume_in_mix */
    /* output device + focus (audio lane, docs/HOST.md "Audio devices and focus") */
    SDL_AudioDeviceID adev;                   /* logical device the stream is bound to */
    char dev_want[256];                       /* audio.device ("" = system default) */
    char dev_open[256];                       /* the device adev is on ("" = the default) */
    int dev_fallback;                         /* dev_want is missing: playing on the default */
    uint32_t dev_switches;
    int audio_paused;                         /* rg_host_audio_pause (kept across switches) */
    char **dev_names;                         /* playback devices (rg_host_audio_devices) */
    int dev_n, dev_stale;
    int win_focus;                            /* the window has input focus */
    int background;                           /* audio.background: keep playing unfocused */
    int fullscreen;
    int exclusive;            /* fullscreen uses a display mode (display.window_mode) */
    int monitor;
    int vsync;
    rg_scale_mode scale;
    int content_num, content_den;   /* rg_host_set_aspect: frame shape in the canvas (0 = canvas) */
    int shot_seq;
    char shot_dir[512];
    char window_shot[512];    /* pending rg_host_request_window_shot */
    char pdump_dir[512];      /* rg_host_present_dump: every present as raw RGBA (diagnostic) */
    uint64_t pdump_field;     /* game field the next dumps are tagged with */
    uint32_t pdump_n;         /* presents written */
    int sdl_inited;
    uint8_t rumble_small[2], rumble_large[2];
    uint64_t rumble_calls;
    uint32_t pumps;
    /* settings + overlay */
    rg_settings *settings;
    uint64_t settings_gen;
    int applied_w, applied_h, applied_mode;
    int applied_monitor;     /* display.monitor last applied (-1: never) */
    char fs_mode[32];        /* display.fullscreen_mode ("" = closest to the window size) */
    double disp_hz;          /* refresh rate of the window's display / exclusive mode (0: unknown) */
    /* rg_menu choice lists (host_choices): display names, exclusive modes */
    char mon_names[16][160];
    char modes[RG_MENU_MAX_CHOICES][32];
    rg_menu menu;
    rg_ui_nav nav;
    /* P6 menu: rebinding capture, text entry, prompts */
    rg_bind_capture cap;
    bool cap_at_pump, text_at_pump;   /* menu state when this pump started */
    char paste[2048];                 /* Ctrl+V: clipboard text not taken yet (rg_host_take_paste) */
    int paste_n, copy_req;            /* Ctrl+C requests not taken yet */
    bool text_on;                      /* SDL text input started */
    uint32_t last_pad_id;              /* most recently used gamepad */
    rg_prompt_style prompt_prev;
    /* overlay hold chord + overlay prompts (docs/INPUT.md "Opening the settings
     * overlay with a gamepad", "Prompts in the settings overlay") */
    rg_chord chord;
    rg_prompt_style menu_prompt_prev;
    /* display.fps_counter (draw_fps): 0 off, 1 fps, 2 detailed */
    int fps_mode;
    uint64_t fps_t0, fps_last;           /* window start, last present (SDL_GetTicksNS) */
    uint32_t fps_n;                      /* presents in the window */
    double fps_sum_ms, fps_max_ms;       /* present intervals in the window */
    uint64_t fps_logic, fps_logic0;      /* rg_host_fps_logic: game-logic ticks (cumulative) */
    uint32_t fps_starves0;
    char fps_text[128];
    /* present thread (rg_host_present_thread, docs/NATIVE-RENDER.md "Interpolation throughput
     * (2026-10-30)"): ren_lock serialises every use of the renderer between it and the window's
     * thread; one posted frame at a time (pt_has) */
    SDL_Mutex *ren_lock;
    SDL_Thread *pt;
    SDL_ThreadID pt_id;
    SDL_Mutex *pt_m;
    SDL_Condition *pt_c;
    int pt_stop, pt_has, pt_busy;
    void *pt_handle;
    uint32_t pt_w, pt_h;
    uint64_t pt_tag;
    void (*pt_cb)(void *arg, uint64_t tag, int rc);
    void *pt_arg;
    uint32_t pump_skips;
    uint64_t pt_posted, pt_done, pt_failed, pump_skipped, pump_unlocked;
};

static void apply_rumble(rg_host *h, int port);
static uint32_t latency_frames(int ms);
/* the renderer's lock (recursive, SDL mutexes): the present thread and the window's thread */
static void ren_lock(rg_host *h) { if (h->ren_lock) SDL_LockMutex(h->ren_lock); }
static void ren_unlock(rg_host *h) { if (h->ren_lock) SDL_UnlockMutex(h->ren_lock); }
/* SDL_RenderPresent; on the present thread without the renderer's lock: the wait for the display
 * never holds up the window's thread (and a present that needs the window's messages cannot
 * deadlock with it) */
static void render_present(rg_host *h)
{
    int pt = h->pt && SDL_GetCurrentThreadID() == h->pt_id;
    if (pt) ren_unlock(h);
    SDL_RenderPresent(h->ren);
    if (pt) ren_lock(h);
}
static void SDLCALL audio_get_cb(void *user, SDL_AudioStream *s, int additional, int total);
static void tap_header(rg_host *h);
static int audio_bind(rg_host *h, const char *want);
static void dev_names_free(rg_host *h);
static void audio_device_event(rg_host *h, const SDL_Event *e);
static void apply_gain(rg_host *h);
static int host_choices(const char *id, const char **out, int cap, void *user);
static void update_display_hz(rg_host *h);
static uint64_t now_ms(void) { return SDL_GetTicks(); }

static char g_err[512];

const char *rg_host_last_error(void) { return g_err; }

static void set_err(const char *what)
{
    SDL_snprintf(g_err, sizeof g_err, "%s: %s", what, SDL_GetError());
    SDL_Log("rg-host: %s", g_err);
}

void rg_host_config_default(rg_host_config *c)
{
    memset(c, 0, sizeof *c);
    c->title = "Rogue Galaxy";
    c->win_w = 1280;
    c->win_h = 960;
    c->scale = RG_SCALE_LINEAR;
    c->aspect_num = 4;
    c->aspect_den = 3;
    c->audio = 1;
}

void rg_host_config_from_settings(rg_host_config *c, const struct rg_settings *s)
{
    if (rg_settings_find(s, "display.window_mode") >= 0)
        c->fullscreen = rg_settings_get_enum(s, "display.window_mode") != 0;
    if (rg_settings_find(s, "display.width") >= 0) {
        c->win_w = rg_settings_get_int(s, "display.width");
        c->win_h = rg_settings_get_int(s, "display.height");
    }
    if (rg_settings_find(s, "display.scale") >= 0)
        c->scale = (rg_scale_mode)rg_settings_get_enum(s, "display.scale");
    if (rg_settings_find(s, "display.vsync") >= 0)
        c->vsync = rg_settings_get_bool(s, "display.vsync");
    if (rg_settings_find(s, "audio.enabled") >= 0)
        c->audio = rg_settings_get_bool(s, "audio.enabled");
    if (rg_settings_find(s, "audio.latency_ms") >= 0)
        c->audio_latency_ms = rg_settings_get_int(s, "audio.latency_ms") ? rg_settings_get_int(s, "audio.latency_ms") : -1;
    if (rg_settings_find(s, "system.screenshot_dir") >= 0) {
        const char *d = rg_settings_get_string(s, "system.screenshot_dir");
        c->screenshot_dir = d && *d ? d : NULL;
    }
}

/* override only where the config disagrees, so the menu does not show every
 * setting as "(--set)" */
static void override_if(rg_settings *s, const char *id, int v)
{
    if (rg_settings_find(s, id) < 0 || rg_settings_get_int(s, id) == v) return;
    rg_settings_set_int(s, id, v, RG_SRC_CMDLINE);
}

void rg_host_settings_from_config(struct rg_settings *s, const rg_host_config *c)
{
    if (rg_settings_find(s, "display.window_mode") >= 0 &&
        (rg_settings_get_enum(s, "display.window_mode") != 0) != (c->fullscreen != 0))
        rg_settings_set_int(s, "display.window_mode", c->fullscreen ? 1 : 0, RG_SRC_CMDLINE);
    override_if(s, "display.scale", (int)c->scale);
    override_if(s, "display.vsync", c->vsync ? 1 : 0);
    override_if(s, "audio.enabled", c->audio ? 1 : 0);
    if (c->win_w > 0 && c->win_h > 0) {
        override_if(s, "display.width", c->win_w);
        override_if(s, "display.height", c->win_h);
    }
}

rg_host *rg_host_create(const rg_host_config *cfg)
{
    rg_host *h = (rg_host *)calloc(1, sizeof *h);
    if (!h) return NULL;
    rg_host_config_default(&h->cfg);
    if (cfg) h->cfg = *cfg;
    if (h->cfg.win_w <= 0 || h->cfg.win_h <= 0) { h->cfg.win_w = 1280; h->cfg.win_h = 960; }
    if (h->cfg.aspect_num <= 0 || h->cfg.aspect_den <= 0) { h->cfg.aspect_num = 4; h->cfg.aspect_den = 3; }
    if (!h->cfg.title) h->cfg.title = "Rogue Galaxy";
    SDL_snprintf(h->shot_dir, sizeof h->shot_dir, "%s", h->cfg.screenshot_dir ? h->cfg.screenshot_dir : ".");
    h->cfg.screenshot_dir = NULL;   /* the caller's string need not outlive create */
    h->headless = h->cfg.headless;
    h->scale = h->cfg.scale;
    h->vsync = h->cfg.vsync ? 1 : 0;
    h->volume = 1.0f;
    /* config: 0 = default, < 0 = off (rg_host_config) */
    h->win_focus = 1;
    h->background = 1;
    h->dev_stale = 1;
    rg_audio_reg_init(&h->reg, h->cfg.audio_latency_ms < 0 ? 0 : latency_frames(h->cfg.audio_latency_ms ? h->cfg.audio_latency_ms : -1));
    {
        /* adaptive cushion (docs/NATIVE-THREADS.md "3h"): grows after starves up to
         * $RG_AUDIO_ADAPT_MS (default 192; 0 = a fixed cushion) */
        const char *am = SDL_getenv("RG_AUDIO_ADAPT_MS");
        int ms = am && *am ? SDL_atoi(am) : 192;
        rg_audio_reg_adapt(&h->reg, ms > 0 ? (uint32_t)ms * 48u : 0u);
    }
    rg_input_map_default(&h->map);
    rg_actions_default(&h->acts);
    rg_roster_init(&h->roster);
    rg_latch_clear(&h->latch);
    rg_ui_nav_init(&h->nav);
    rg_capture_init(&h->cap);
    rg_look_acc_init(&h->look);
    rg_chord_init(&h->chord);
    h->menu_prompt_prev = RG_PROMPT_PLAYSTATION;
    h->prompt_prev = RG_PROMPT_PLAYSTATION;
    h->applied_mode = -1;
    h->applied_monitor = -1;
    if (h->headless) return h;   /* no window, no audio, no live input */
    h->ren_lock = SDL_CreateMutex();

    SDL_SetMainReady();
    SDL_InitFlags fl = SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | (h->cfg.audio ? SDL_INIT_AUDIO : 0);
    if (!SDL_Init(fl)) { set_err("SDL_Init"); free(h); return NULL; }
    h->sdl_inited = 1;
    h->win = SDL_CreateWindow(h->cfg.title, h->cfg.win_w, h->cfg.win_h,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (!h->win) { set_err("SDL_CreateWindow"); rg_host_destroy(h); return NULL; }
#if defined(_WIN64)
    { extern void rg_x64_va_fence(int); rg_x64_va_fence(1); h->ren = SDL_CreateRenderer(h->win, NULL); rg_x64_va_fence(0); }   /* the presenter's device in the fence too (docs/X64-PLAN.md 0.10) */
#else
#line 301
    h->ren = SDL_CreateRenderer(h->win, NULL);
#endif
#line 302
    if (!h->ren) { set_err("SDL_CreateRenderer"); rg_host_destroy(h); return NULL; }
    SDL_SetRenderVSync(h->ren, h->vsync);
    if (h->cfg.fullscreen) rg_host_set_fullscreen(h, 1);

    if (h->cfg.audio) {
        /* our own stream, bound to a device opened by name (audio.device; the default
         * until the settings are attached), so the device can change under it */
        SDL_AudioSpec spec = { SDL_AUDIO_S16, RG_AUDIO_CHANNELS, RG_AUDIO_RATE };
        h->audio = SDL_CreateAudioStream(&spec, NULL);
        if (h->audio && audio_bind(h, "") != 0) { SDL_DestroyAudioStream(h->audio); h->audio = NULL; }
        if (!h->audio) set_err("audio device (continuing without sound)");
        else {
            const char *dc = SDL_getenv("RG_AUDIO_DECLICK"), *tw = SDL_getenv("RG_AUDIO_HOST_WAV");
            h->declick = !(dc && dc[0] == '0');
            if (tw && *tw && (h->tap = fopen(tw, "wb")) != NULL) {
                char ev[1024];
                tap_header(h);
                SDL_snprintf(ev, sizeof ev, "%s.events.tsv", tw);
                if ((h->tap_ev = fopen(ev, "w")) != NULL)
                    fprintf(h->tap_ev, "# frame\tpush\tqueued\tstarved\tpad\tdrop\tdeclick\n");
            }
            SDL_SetAudioStreamGetCallback(h->audio, audio_get_cb, h);
            SDL_ResumeAudioStreamDevice(h->audio);
        }
        h->win_focus = (SDL_GetWindowFlags(h->win) & SDL_WINDOW_INPUT_FOCUS) != 0;
    }
    /* clear to black at once so the window is not garbage until the first frame */
    SDL_SetRenderDrawColor(h->ren, 0, 0, 0, 255);
    SDL_RenderClear(h->ren);
    SDL_RenderPresent(h->ren);
    return h;
}

/* ------------------------------------------------- virtual gamepad (tests)
 * $RG_VPAD_SCRIPT=FILE (docs/INPUT.md "Recording live input"): an SDL virtual gamepad,
 * attached at the first pump of a windowed host and driven by FILE on the wall clock:
 * lines "MS NAME VALUE" (ms since the attach; NAME an SDL gamepad button ("a", "dpup",
 * "start", ...) with VALUE 0 / 1, or an axis ("leftx", "righttrigger", ...) with VALUE
 * -32768..32767; '#' comments).  The pad reaches the game like a real one (SDL's gamepad
 * events, the roster, the press latch, rg_actions_eval): a machine without a gamepad and
 * without /dev/uinput access can still run the live gamepad path. */
typedef struct vpad_ev { uint32_t ms; int button, axis, value; } vpad_ev;
static struct {
    int state;              /* 0 untested, 1 attached, -1 off */
    SDL_JoystickID id;
    SDL_Joystick *joy;
    vpad_ev *ev;
    int nev, next;
    uint64_t t0;
} g_vpad;

static void vpad_load(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f) { SDL_Log("rg-host: RG_VPAD_SCRIPT %s: cannot read", path); return; }
    char ln[256];
    int cap = 0;
    while (fgets(ln, sizeof ln, f)) {
        char *hash = strchr(ln, '#');
        if (hash) *hash = 0;
        unsigned long ms;
        char name[64];
        int v;
        if (sscanf(ln, "%lu %63s %d", &ms, name, &v) != 3) continue;
        vpad_ev e = { (uint32_t)ms, -1, -1, v };
        SDL_GamepadButton b = SDL_GetGamepadButtonFromString(name);
        if (b != SDL_GAMEPAD_BUTTON_INVALID) e.button = (int)b;
        else {
            SDL_GamepadAxis a = SDL_GetGamepadAxisFromString(name);
            if (a == SDL_GAMEPAD_AXIS_INVALID) { SDL_Log("rg-host: RG_VPAD_SCRIPT: unknown control '%s'", name); continue; }
            e.axis = (int)a;
        }
        if (g_vpad.nev == cap) {
            cap = cap ? cap * 2 : 64;
            vpad_ev *n = (vpad_ev *)SDL_realloc(g_vpad.ev, (size_t)cap * sizeof *n);
            if (!n) break;
            g_vpad.ev = n;
        }
        g_vpad.ev[g_vpad.nev++] = e;
    }
    fclose(f);
}

static void vpad_tick(rg_host *h)
{
    if (g_vpad.state < 0) return;
    if (g_vpad.state == 0) {
        g_vpad.state = -1;
        const char *path = SDL_getenv("RG_VPAD_SCRIPT");
        if (!path || !*path || h->headless) return;
        SDL_VirtualJoystickDesc d;
        SDL_INIT_INTERFACE(&d);
        d.type = SDL_JOYSTICK_TYPE_GAMEPAD;
        d.naxes = SDL_GAMEPAD_AXIS_COUNT;
        d.nbuttons = SDL_GAMEPAD_BUTTON_COUNT;
        d.name = "rg-game virtual pad (RG_VPAD_SCRIPT)";
        g_vpad.id = SDL_AttachVirtualJoystick(&d);
        g_vpad.joy = g_vpad.id ? SDL_OpenJoystick(g_vpad.id) : NULL;
        if (!g_vpad.joy) { SDL_Log("rg-host: RG_VPAD_SCRIPT: no virtual joystick: %s", SDL_GetError()); return; }
        vpad_load(path);
        g_vpad.t0 = SDL_GetTicks();
        g_vpad.state = 1;
        SDL_Log("rg-host: RG_VPAD_SCRIPT: virtual gamepad %u, %d events", (unsigned)g_vpad.id, g_vpad.nev);
    }
    uint64_t now = SDL_GetTicks() - g_vpad.t0;
    while (g_vpad.next < g_vpad.nev && g_vpad.ev[g_vpad.next].ms <= now) {
        const vpad_ev *e = &g_vpad.ev[g_vpad.next++];
        if (e->button >= 0) SDL_SetJoystickVirtualButton(g_vpad.joy, e->button, e->value != 0);
        else SDL_SetJoystickVirtualAxis(g_vpad.joy, e->axis, (Sint16)(e->value < -32768 ? -32768 : e->value > 32767 ? 32767 : e->value));
    }
}

static void vpad_close(void)
{
    if (g_vpad.joy) SDL_CloseJoystick(g_vpad.joy);
    if (g_vpad.id) SDL_DetachVirtualJoystick(g_vpad.id);
    SDL_free(g_vpad.ev);
    memset(&g_vpad, 0, sizeof g_vpad);
    g_vpad.state = -1;
}

void rg_host_destroy(rg_host *h)
{
    if (!h) return;
    rg_input_record_close();
    rg_host_present_thread(h, 0);
    for (int i = 0; i < h->roster.n; i++) SDL_CloseGamepad(h->pads[i]);
    vpad_close();
    if (h->audio) SDL_DestroyAudioStream(h->audio);
    if (h->adev) SDL_CloseAudioDevice(h->adev);
    dev_names_free(h);
    if (h->tap) { tap_header(h); fclose(h->tap); }
    if (h->tap_ev) fclose(h->tap_ev);
    SDL_free(h->ts);
    SDL_free(h->ts_out);
    if (h->vk) rg_host_drop_vulkan(h);
    if (h->pre) SDL_DestroyTexture(h->pre);
    if (h->tex) SDL_DestroyTexture(h->tex);
#ifdef _WIN32
    for (int i = 0; i < 2; i++) {
        if (h->shr[i].st) SDL_DestroyTexture(h->shr[i].st);
        if (h->shr[i].km) IDXGIKeyedMutex_Release(h->shr[i].km);
        if (h->shr[i].tex) ID3D11Texture2D_Release(h->shr[i].tex);
    }
#endif
    if (h->ren) SDL_DestroyRenderer(h->ren);
    if (h->win) SDL_DestroyWindow(h->win);
    if (h->ren_lock) SDL_DestroyMutex(h->ren_lock);
    if (h->sdl_inited) SDL_Quit();
    free(h->frame);
    free(h);
}

/* ---------------------------------------------------------------- window */
void rg_host_set_title(rg_host *h, const char *title)
{
    if (h->win) SDL_SetWindowTitle(h->win, title);
}

void rg_host_set_fullscreen(rg_host *h, int on)
{
    if (!h->win) { h->fullscreen = on ? 1 : 0; return; }
    if (SDL_SetWindowFullscreen(h->win, on ? true : false)) h->fullscreen = on ? 1 : 0;
    else set_err("SDL_SetWindowFullscreen");
}

int rg_host_fullscreen(const rg_host *h) { return h->fullscreen; }

/* display.monitor: index into SDL's display list; an index with no display connected
 * uses the first (rg_display_monitor_index), reported in the log */
static SDL_DisplayID monitor_id(int mon)
{
    int n = 0;
    SDL_DisplayID *ids = SDL_GetDisplays(&n);
    SDL_DisplayID id = 0;
    if (ids && n > 0) id = ids[rg_display_monitor_index(mon, n)];
    SDL_free(ids);
    return id;
}

void rg_host_set_monitor(rg_host *h, int mon)
{
    h->monitor = mon;
    if (!h->win) return;
    SDL_DisplayID id = monitor_id(mon);
    if (!id) return;
    {
        int n = 0;
        SDL_free(SDL_GetDisplays(&n));
        if (mon != rg_display_monitor_index(mon, n))
            SDL_Log("rg-host: display.monitor %d: only %d display(s) connected, using %d (%s)", mon, n,
                    rg_display_monitor_index(mon, n), SDL_GetDisplayName(id) ? SDL_GetDisplayName(id) : "?");
    }
    if (!h->fullscreen)
        SDL_SetWindowPosition(h->win, (int)SDL_WINDOWPOS_CENTERED_DISPLAY(id), (int)SDL_WINDOWPOS_CENTERED_DISPLAY(id));
    else {
        /* leave, move, re-enter: fullscreen follows the window's display */
        SDL_SetWindowFullscreen(h->win, false);
        SDL_SetWindowPosition(h->win, (int)SDL_WINDOWPOS_CENTERED_DISPLAY(id), (int)SDL_WINDOWPOS_CENTERED_DISPLAY(id));
        SDL_SetWindowFullscreen(h->win, true);
    }
}

/* borderless (the desktop mode) or exclusive: display.fullscreen_mode (WxH[@Hz], the
 * closest mode the display has), or when empty the display mode closest to the
 * configured window size (display.width/height) at the desktop refresh rate */
void rg_host_set_fullscreen_mode(rg_host *h, int exclusive)
{
    h->exclusive = exclusive ? 1 : 0;
    if (!h->win) return;
    if (!exclusive) {
        SDL_SetWindowFullscreenMode(h->win, NULL);
        update_display_hz(h);
        return;
    }
    SDL_DisplayID id = SDL_GetDisplayForWindow(h->win);
    SDL_DisplayMode m;
    int w = h->cfg.win_w, hh = h->cfg.win_h;
    double hz = 0.0;
    if (rg_display_mode_parse(h->fs_mode, &w, &hh, &hz) <= 0) { w = h->cfg.win_w; hh = h->cfg.win_h; hz = 0.0; }
    if (id && SDL_GetClosestFullscreenDisplayMode(id, w, hh, (float)hz, true, &m))
        SDL_SetWindowFullscreenMode(h->win, &m);
    else
        set_err("exclusive fullscreen: no display mode (staying borderless)");
    update_display_hz(h);
}

/* the refresh rate presents meet (display.frame_rate "display"): the exclusive mode's,
 * else the current mode of the window's display; cached on the window's thread */
static void update_display_hz(rg_host *h)
{
    double hz = 0.0;
    if (h->win) {
        const SDL_DisplayMode *fm = h->fullscreen && h->exclusive ? SDL_GetWindowFullscreenMode(h->win) : NULL;
        if (fm && fm->refresh_rate > 0.0f) hz = fm->refresh_rate;
        else {
            SDL_DisplayID id = SDL_GetDisplayForWindow(h->win);
            const SDL_DisplayMode *cm = id ? SDL_GetCurrentDisplayMode(id) : NULL;
            if (cm) hz = cm->refresh_rate;
        }
    }
    h->disp_hz = hz;
}

double rg_host_display_hz(const rg_host *h) { return h ? h->disp_hz : 0.0; }
void rg_host_set_scale(rg_host *h, rg_scale_mode m) { h->scale = m; }
rg_scale_mode rg_host_scale(const rg_host *h) { return h->scale; }

void rg_host_set_vsync(rg_host *h, int on)
{
    h->vsync = on ? 1 : 0;
    ren_lock(h);
    if (h->ren) SDL_SetRenderVSync(h->ren, h->vsync);
    ren_unlock(h);
}

void rg_host_set_window_size(rg_host *h, int w, int hh)
{
    if (w <= 0 || hh <= 0) return;
    h->cfg.win_w = w;
    h->cfg.win_h = hh;
    if (h->win && !h->fullscreen) SDL_SetWindowSize(h->win, w, hh);
}

void rg_host_window_size(const rg_host *h, int *w, int *hh)
{
    *w = *hh = 0;
    ren_lock((rg_host *)h);
    if (h->ren) SDL_GetCurrentRenderOutputSize(h->ren, w, hh);
    ren_unlock((rg_host *)h);
}

void *rg_host_native_window(const rg_host *h)
{
#ifdef _WIN32
    if (h && h->win)
        return SDL_GetPointerProperty(SDL_GetWindowProperties(h->win), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
#else
    (void)h;
#endif
    return NULL;
}

int rg_host_set_window_icon(rg_host *h, const uint8_t *rgba, int size)
{
    if (!h || !h->win || !rgba || size <= 0) return -1;
    SDL_Surface *s = SDL_CreateSurfaceFrom(size, size, SDL_PIXELFORMAT_RGBA32, (void *)rgba, size * 4);
    if (!s) return -1;
    int ok = SDL_SetWindowIcon(h->win, s);
    SDL_DestroySurface(s);
    return ok ? 0 : -1;
}

const char *rg_host_screenshot_dir(const rg_host *h) { return h->shot_dir; }

static void next_shot_path(rg_host *h, char *out, size_t cap)
{
    for (int tries = 0; tries < 10000; tries++) {
        SDL_snprintf(out, cap, "%s/rg-shot-%04d.png", h->shot_dir, h->shot_seq++);
        SDL_PathInfo pi;
        if (!SDL_GetPathInfo(out, &pi)) return;   /* does not exist yet */
    }
}

/* ---------------------------------------------------------------- settings */
static void apply_settings(rg_host *h)
{
    rg_settings *s = h->settings;
    if (!s) return;
    h->settings_gen = rg_settings_generation(s);
    rg_actions_from_settings(&h->acts, s);
    rg_look_acc_from_settings(&h->look, s);
    rg_chord_from_settings(&h->chord, s);
    if (rg_settings_find(s, "display.scale") >= 0)
        h->scale = (rg_scale_mode)rg_settings_get_enum(s, "display.scale");
    if (rg_settings_find(s, "display.vsync") >= 0 && rg_settings_get_bool(s, "display.vsync") != (h->vsync != 0))
        rg_host_set_vsync(h, rg_settings_get_bool(s, "display.vsync"));
    if (rg_settings_find(s, "display.monitor") >= 0) {
        int mon = rg_settings_get_int(s, "display.monitor");
        if (mon != h->applied_monitor) {
            int first = h->applied_monitor < 0;
            h->applied_monitor = mon;
            /* the default (0) on the first apply leaves the window where the
             * system put it */
            if (!first || mon != 0) {
                rg_host_set_monitor(h, mon);
                h->applied_mode = -1;   /* re-enter fullscreen on the new display */
            }
        }
    }
    if (rg_settings_find(s, "display.fullscreen_mode") >= 0) {
        const char *fm = rg_settings_get_string(s, "display.fullscreen_mode");
        if (SDL_strcmp(fm ? fm : "", h->fs_mode) != 0) {
            SDL_snprintf(h->fs_mode, sizeof h->fs_mode, "%s", fm ? fm : "");
            /* in exclusive fullscreen now: switch the display mode at once */
            if (h->exclusive && h->fullscreen && h->applied_mode == 2) rg_host_set_fullscreen_mode(h, 1);
        }
    }
    if (rg_settings_find(s, "display.window_mode") >= 0) {
        int mode = rg_settings_get_enum(s, "display.window_mode");
        if (mode != h->applied_mode) {
            h->applied_mode = mode;
            if (mode == 0) {
                if (h->fullscreen) rg_host_set_fullscreen(h, 0);
            } else {
                rg_host_set_fullscreen_mode(h, mode == 2);
                if (!h->fullscreen) rg_host_set_fullscreen(h, 1);
            }
        }
    }
    if (rg_settings_find(s, "display.width") >= 0) {
        int w = rg_settings_get_int(s, "display.width"), hh = rg_settings_get_int(s, "display.height");
        /* only when the setting changed, so a window the user resized by hand
         * keeps its size */
        if (w != h->applied_w || hh != h->applied_h) {
            if (h->applied_w) rg_host_set_window_size(h, w, hh);
            h->applied_w = w;
            h->applied_h = hh;
        }
    }
    if (rg_settings_find(s, "audio.master_volume") >= 0)
        rg_host_set_volume(h, (float)rg_settings_get_int(s, "audio.master_volume") / 100.0f);
    if (rg_settings_find(s, "audio.latency_ms") >= 0)
        rg_host_set_audio_latency(h, rg_settings_get_int(s, "audio.latency_ms"));
    if (rg_settings_find(s, "audio.background") >= 0)
        rg_host_set_audio_background(h, rg_settings_get_bool(s, "audio.background"));
    if (rg_settings_find(s, "audio.device") >= 0) {
        const char *d = rg_settings_get_string(s, "audio.device");
        if (SDL_strcmp(d ? d : "", h->dev_want) != 0) rg_host_set_audio_device(h, d);
    }
    if (rg_settings_find(s, "display.fps_counter") >= 0)
        h->fps_mode = rg_settings_get_enum(s, "display.fps_counter");
    if (rg_settings_find(s, "system.screenshot_dir") >= 0) {
        const char *d = rg_settings_get_string(s, "system.screenshot_dir");
        SDL_snprintf(h->shot_dir, sizeof h->shot_dir, "%s", d && *d ? d : ".");
    }
    for (int p = 0; p < 2; p++) apply_rumble(h, p);
    update_display_hz(h);
}

void rg_host_attach_settings(rg_host *h, struct rg_settings *s, const char *save_path)
{
    h->settings = s;
    if (!s) { h->menu.open = false; return; }
    rg_menu_init(&h->menu, s);
    rg_menu_set_choices(&h->menu, host_choices, h);   /* audio.device, display.monitor, display.fullscreen_mode */
    h->menu.save_path = save_path;
    rg_capture_cancel_hint(&h->cap, h->menu.capture_hint, sizeof h->menu.capture_hint);
    h->applied_w = h->cfg.win_w;
    h->applied_h = h->cfg.win_h;
    h->applied_mode = h->fullscreen ? 1 : 0;
    apply_settings(h);
}

rg_actions *rg_host_actions(rg_host *h) { return &h->acts; }
void rg_host_apply_input_map(rg_host *h) { rg_actions_from_input_map(&h->acts, &h->map); }
bool rg_host_overlay_open(const rg_host *h) { return h->menu.open; }
struct rg_menu *rg_host_settings_menu(rg_host *h) { return &h->menu; }

void rg_host_set_overlay(rg_host *h, bool open)
{
    if (!h->settings || h->menu.open == open) return;
    rg_menu_command(&h->menu, RG_MENU_TOGGLE, now_ms());
}

int rg_host_take_paste(rg_host *h, char *out, size_t cap)
{
    if (!h || !h->paste_n || !out || !cap) return 0;
    SDL_strlcpy(out, h->paste, cap);
    h->paste_n = 0;
    h->paste[0] = 0;
    return 1;
}

int rg_host_take_copy_request(rg_host *h)
{
    if (!h || !h->copy_req) return 0;
    h->copy_req = 0;
    return 1;
}

int rg_host_set_clipboard(rg_host *h, const char *text)
{
    if (!h || h->headless || !text) return -1;
    return SDL_SetClipboardText(text) ? 0 : -1;
}

void rg_host_keepalive(rg_host *h)
{
    if (h && !h->headless) SDL_PumpEvents();
}

bool rg_host_port_connected(const rg_host *h, int port)
{
    if (port == 0) return true;
    if (h->script || h->headless) return false;
    return rg_roster_port_connected(&h->roster, h->acts.players, port);
}

int rg_host_active_device(const rg_host *h, char *name, size_t cap)
{
    const char *n = "none";
    if (h->roster.active_kind == RG_DEV_KEYBOARD_MOUSE) n = "keyboard";
    else if (h->roster.active_kind == RG_DEV_GAMEPAD) {
        int s = rg_roster_slot(&h->roster, h->roster.active_id);
        n = s >= 0 && h->pads[s] ? SDL_GetGamepadName(h->pads[s]) : "gamepad";
        if (!n) n = "gamepad";
    }
    if (name && cap) SDL_snprintf(name, cap, "%s", n);
    return (int)h->roster.active_kind;
}

rg_pad_family rg_host_active_pad_family(const rg_host *h)
{
    if (h->headless || h->roster.n == 0) return RG_PAD_FAMILY_NONE;
    int s = rg_roster_slot(&h->roster, h->last_pad_id);
    if (s < 0) s = 0;
    if (!h->pads[s]) return RG_PAD_FAMILY_NONE;
    return rg_pad_family_from_sdl_type((int)SDL_GetGamepadType(h->pads[s]));
}

rg_prompt_style rg_host_prompt_style(rg_host *h)
{
    int setting = RG_PROMPTS_AUTO;
    if (h->settings && rg_settings_find(h->settings, "prompts.style") >= 0)
        setting = rg_settings_get_enum(h->settings, "prompts.style");
    bool scripted = h->script != NULL || h->headless;
    rg_prompt_style st = rg_prompt_style_resolve(setting, scripted, h->roster.active_kind,
                                                 rg_host_active_pad_family(h), h->prompt_prev);
    if (!scripted) h->prompt_prev = st;
    return st;
}

rg_bind_capture *rg_host_capture(rg_host *h) { return &h->cap; }

/* ---------------------------------------------------------------- devices */
static void pad_added(rg_host *h, SDL_JoystickID id)
{
    if (rg_roster_slot(&h->roster, id) >= 0) return;
    SDL_Gamepad *g = SDL_OpenGamepad(id);
    if (!g) { set_err("SDL_OpenGamepad"); return; }
    int s = rg_roster_add(&h->roster, id);
    if (s < 0) { SDL_CloseGamepad(g); return; }
    h->pads[s] = g;
    SDL_Log("rg-host: gamepad %d: %s", s, SDL_GetGamepadName(g));
}

static void pad_removed(rg_host *h, SDL_JoystickID id)
{
    int s = rg_roster_slot(&h->roster, id);
    if (s < 0) return;
    SDL_CloseGamepad(h->pads[s]);
    int n = h->roster.n;
    memmove(&h->pads[s], &h->pads[s + 1], (size_t)(n - s - 1) * sizeof h->pads[0]);
    h->pads[n - 1] = NULL;
    rg_roster_remove(&h->roster, id);
    rg_latch_remove_slot(&h->latch, s);
    rg_chord_remove_slot(&h->chord, s);
}

static void snap_pad(SDL_Gamepad *g, rg_gamepad_snap *s)
{
    memset(s, 0, sizeof *s);
    for (int b = 0; b < SDL_GAMEPAD_BUTTON_COUNT && b < RG_GP_BUTTONS; b++)
        s->button[b] = SDL_GetGamepadButton(g, (SDL_GamepadButton)b) ? 1 : 0;
    for (int a = 0; a < SDL_GAMEPAD_AXIS_COUNT && a < RG_GP_AXES; a++)
        s->axis[a] = SDL_GetGamepadAxis(g, (SDL_GamepadAxis)a);
}

static int focused(const rg_host *h)
{
    return h->win && SDL_GetKeyboardFocus() == h->win;
}

/* Live snapshot for `port`.  keybuf must hold SDL_SCANCODE_COUNT entries;
 * pads RG_MAX_GAMEPADS. */
static void live_snapshot(rg_host *h, int port, bool *keybuf, rg_gamepad_snap *pads, rg_input_snapshot *in)
{
    memset(in, 0, sizeof *in);
    int slots[RG_MAX_GAMEPADS];
    int ns = rg_roster_port_slots(&h->roster, h->acts.players, port, slots);
    for (int i = 0; i < ns; i++) {
        snap_pad(h->pads[slots[i]], &pads[i]);
        rg_latch_apply_pad(&h->latch, slots[i], &pads[i]);
        rg_chord_filter(&h->chord, slots[i], &pads[i]);   /* the overlay chord never reaches the game */
    }
    in->pads = pads;
    in->npads = ns;
    /* keyboard and mouse only on port 0, only while focused, not while Alt
     * is held (Alt+Enter is the fullscreen hotkey, not START) */
    if (port == 0 && focused(h) && !(SDL_GetModState() & SDL_KMOD_ALT)) {
        int nkeys = 0;
        const bool *keys = SDL_GetKeyboardState(&nkeys);
        rg_latch_apply_keys(&h->latch, keys, nkeys, keybuf, SDL_SCANCODE_COUNT);
        in->keys = keybuf;
        in->nkeys = SDL_SCANCODE_COUNT;
        in->mouse_buttons = rg_latch_apply_mouse(&h->latch, (uint32_t)SDL_GetMouseState(NULL, NULL));
        /* captured for the mouse camera: motion turns the camera directly,
         * not (also) through mouse:x+/y+ bindings */
        in->mouse_dx = h->look_captured ? 0.0f : h->mouse_dx;
        in->mouse_dy = h->look_captured ? 0.0f : h->mouse_dy;
    }
}

/* ---------------------------------------------------------------- overlay */

/* Hands a finished capture to the menu. */
static void capture_finish(rg_host *h)
{
    if (h->cap.state == RG_CAPTURE_DONE) {
        char t[96];
        rg_capture_text(&h->cap, t, sizeof t);
        rg_menu_capture_input(&h->menu, t, now_ms());
    } else if (h->cap.state == RG_CAPTURE_CANCELLED) {
        rg_menu_capture_input(&h->menu, NULL, now_ms());
    } else {
        return;
    }
    rg_capture_end(&h->cap);
}

/* Starts / stops the capture detector and SDL text input to match the menu. */
static void sync_modes(rg_host *h, const rg_gamepad_snap *pads, int npads)
{
    bool capturing = rg_menu_capturing(&h->menu);
    if (capturing && h->cap.state != RG_CAPTURE_WAITING) {
        if (rg_menu_capturing_motion(&h->menu)) rg_capture_begin_motion(&h->cap);
        else rg_capture_begin(&h->cap, pads, npads);
    }
    else if (!capturing && h->cap.state != RG_CAPTURE_IDLE) rg_capture_end(&h->cap);
    bool editing = rg_menu_text_editing(&h->menu);
    if (h->win && editing != h->text_on) {
        if (editing) SDL_StartTextInput(h->win);
        else SDL_StopTextInput(h->win);
        h->text_on = editing;
    }
}

static void overlay_input(rg_host *h)
{
    if (!h->settings) return;
    /* UI actions from every device at once: keyboard (focused) + all pads.
     * While text is being typed, the keyboard belongs to the text field and
     * only the gamepads navigate (the on-screen selector). */
    static bool keybuf[SDL_SCANCODE_COUNT];
    rg_gamepad_snap pads[RG_MAX_GAMEPADS];
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    uint64_t t = now_ms();
    /* the overlay hold chord: one step per pad and pump on the latched state;
     * the same filter then holds its buttons back from the game's reads
     * (live_snapshot) and from the menu actions below */
    bool chord_fired = false;
    for (int i = 0; i < h->roster.n; i++) {
        snap_pad(h->pads[i], &pads[i]);
        rg_gamepad_snap latched = pads[i];
        rg_latch_apply_pad(&h->latch, i, &latched);
        if (rg_chord_update(&h->chord, i, &latched, t)) chord_fired = true;
        rg_chord_filter(&h->chord, i, &pads[i]);
    }
    in.pads = pads;
    in.npads = h->roster.n;
    if (focused(h) && !rg_menu_text_editing(&h->menu)) {
        int nkeys = 0;
        const bool *keys = SDL_GetKeyboardState(&nkeys);
        rg_latch_apply_keys(&h->latch, keys, nkeys, keybuf, SDL_SCANCODE_COUNT);
        in.keys = keybuf;
        in.nkeys = SDL_SCANCODE_COUNT;
    }
    int32_t v[RG_ACT_COUNT];
    rg_actions_values(&h->acts, &in, v);
    int fired[RG_ACT_COUNT - RG_ACT_GAME_COUNT];
    int n = rg_ui_nav_update(&h->nav, v, t, fired);
    /* The press that a capture took (or that committed typed text) is still
     * held: the nav state above absorbs it, and this pump's commands are
     * dropped so it doesn't also act on the menu. */
    bool quiet = h->cap_at_pump || rg_menu_capturing(&h->menu) ||
                 (h->text_at_pump && !rg_menu_text_editing(&h->menu));
    for (int i = 0; i < n && !quiet; i++) {
        rg_menu_cmd c;
        switch (fired[i]) {
        case RG_ACT_UI_UP: c = RG_MENU_UP; break;
        case RG_ACT_UI_DOWN: c = RG_MENU_DOWN; break;
        case RG_ACT_UI_LEFT: c = RG_MENU_LEFT; break;
        case RG_ACT_UI_RIGHT: c = RG_MENU_RIGHT; break;
        case RG_ACT_UI_ACCEPT: c = RG_MENU_ACCEPT; break;
        case RG_ACT_UI_BACK: c = RG_MENU_BACK; break;
        case RG_ACT_UI_PAGE_PREV: c = RG_MENU_PAGE_PREV; break;
        case RG_ACT_UI_PAGE_NEXT: c = RG_MENU_PAGE_NEXT; break;
        case RG_ACT_UI_OVERLAY: c = RG_MENU_TOGGLE; break;
        default: continue;
        }
        if (c != RG_MENU_TOGGLE && !h->menu.open) continue;
        rg_menu_command(&h->menu, c, t);
        /* a capture started: the rest of this batch is not for the menu */
        if (rg_menu_capturing(&h->menu)) break;
    }
    /* not while a press is being captured (it may be a chord button) */
    if (chord_fired && !h->cap_at_pump && !rg_menu_capturing(&h->menu))
        rg_menu_command(&h->menu, RG_MENU_TOGGLE, t);
    if (h->menu.open) {
        /* hints for the device in use (prompts.style; auto = last used) */
        int setting = rg_settings_find(h->settings, "prompts.style") >= 0
                          ? rg_settings_get_enum(h->settings, "prompts.style") : RG_PROMPTS_AUTO;
        rg_prompt_style st = rg_prompt_style_resolve(setting, false, h->roster.active_kind,
                                                     rg_host_active_pad_family(h), h->menu_prompt_prev);
        h->menu_prompt_prev = st;
        int slot = rg_roster_slot(&h->roster, h->last_pad_id);
        if (slot < 0 && h->roster.n) slot = 0;
        int type = slot >= 0 && h->pads[slot] ? (int)SDL_GetGamepadType(h->pads[slot]) : -1;
        rg_menu_prompts_from_input(&h->menu, &h->acts, &h->chord, st, type);
    }
    rg_menu_tick(&h->menu, t);
    sync_modes(h, pads, h->roster.n);
}

int rg_host_menu_script(rg_host *h, const char *script)
{
    static const struct { const char *name; rg_menu_cmd cmd; } k_cmds[] = {
        { "up", RG_MENU_UP }, { "down", RG_MENU_DOWN }, { "left", RG_MENU_LEFT },
        { "right", RG_MENU_RIGHT }, { "accept", RG_MENU_ACCEPT }, { "back", RG_MENU_BACK },
        { "prev", RG_MENU_PAGE_PREV }, { "next", RG_MENU_PAGE_NEXT }, { "toggle", RG_MENU_TOGGLE },
    };
    if (!h->settings || !script) return 0;
    int applied = 0;
    const char *p = script;
    while (*p) {
        const char *e = strchr(p, ',');
        size_t L = e ? (size_t)(e - p) : strlen(p);
        char item[160];
        if (L >= sizeof item) L = sizeof item - 1;
        memcpy(item, p, L);
        item[L] = 0;
        p = e ? e + 1 : p + L;
        if (!item[0]) continue;
        int ok = 0;
        for (size_t i = 0; i < sizeof k_cmds / sizeof k_cmds[0]; i++)
            if (!SDL_strcasecmp(item, k_cmds[i].name)) {
                if (k_cmds[i].cmd == RG_MENU_TOGGLE || h->menu.open)
                    rg_menu_command(&h->menu, k_cmds[i].cmd, now_ms());
                ok = 1;
            }
        if (!SDL_strncasecmp(item, "text:", 5)) { rg_menu_text_input(&h->menu, item + 5); ok = 1; }
        if (!SDL_strncasecmp(item, "motion:", 7)) {   /* motion:DX:DY, relative mouse motion */
            char *end = NULL;
            float dx = SDL_strtod(item + 7, &end);
            if (!end || *end != ':') return -1;
            float dy = SDL_strtod(end + 1, &end);
            if (*end) return -1;
            if (h->cap.state == RG_CAPTURE_WAITING) {
                rg_capture_mouse_motion(&h->cap, dx, dy);
                capture_finish(h);
            }
            ok = 1;
        }
        if (!SDL_strncasecmp(item, "press:", 6)) {
            rg_binding b[RG_BIND_MAX];
            if (rg_binding_parse_list(item + 6, b, NULL, 0) != 1) return -1;
            if (h->cap.state == RG_CAPTURE_WAITING) {
                switch (b[0].kind) {
                case RG_BIND_KEY: rg_capture_key(&h->cap, b[0].code); break;
                case RG_BIND_MOUSE: rg_capture_mouse_button(&h->cap, b[0].code); break;
                case RG_BIND_PAD_BUTTON: rg_capture_pad_button(&h->cap, b[0].code); break;
                case RG_BIND_PAD_AXIS:
                    rg_capture_pad_axis(&h->cap, 0, b[0].code, b[0].pos ? 32767 : -32768);
                    break;
                default: break;
                }
                capture_finish(h);
            }
            ok = 1;
        }
        if (!ok) return -1;
        sync_modes(h, NULL, 0);
        applied++;
    }
    return applied;
}

/* SDL key -> text-field editing key (-1: not one). */
static int text_key_of(SDL_Keycode k)
{
    switch (k) {
    case SDLK_BACKSPACE: return RG_TEXT_BACKSPACE;
    case SDLK_DELETE: return RG_TEXT_DELETE;
    case SDLK_LEFT: return RG_TEXT_LEFT;
    case SDLK_RIGHT: return RG_TEXT_RIGHT;
    case SDLK_HOME: return RG_TEXT_HOME;
    case SDLK_END: return RG_TEXT_END;
    case SDLK_RETURN: case SDLK_KP_ENTER: return RG_TEXT_COMMIT;
    case SDLK_ESCAPE: return RG_TEXT_CANCEL;
    default: return -1;
    }
}

_Static_assert(RG_MENU_MOTION_DIST == RG_CAPTURE_MOUSE_DIST, "menu prompt and detector disagree");

static void draw_overlay(rg_host *h)
{
    if (!h->settings || !h->menu.open || !h->ren) return;
    static rg_menu_line raw[RG_MENU_MAX_ROWS + 16];
    static rg_menu_line lines[4 * (RG_MENU_MAX_ROWS + 16)];
    int nraw = rg_menu_render(&h->menu, now_ms(), raw, (int)(sizeof raw / sizeof raw[0]));
    int ow = 0, oh = 0;
    SDL_GetCurrentRenderOutputSize(h->ren, &ow, &oh);
    /* scale so ~84 characters of 8 px fit the width and ~22 rows the height
     * (at least 1x); longer lines wrap to the columns that fit (docs/SETTINGS.md) */
    float sw = (float)ow / (84.0f * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE + 16.0f);
    float shh = (float)oh / (22.0f * (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE + 4));
    float sc = sw < shh ? sw : shh;
    sc = sc < 1.0f ? 1.0f : sc > 3.0f ? 3.0f : sc;
    float lh = (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE + 4) * sc;
    int cols = (int)(((float)ow / sc - 16.0f) / SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE);
    const int cap = (int)(sizeof lines / sizeof lines[0]);
    /* the title and the hint line stay pinned at the top */
    int pinned = rg_menu_wrap(raw, nraw < 2 ? nraw : 2, cols, lines, cap);
    int n = pinned + (nraw > 2 ? rg_menu_wrap(raw + 2, nraw - 2, cols, lines + pinned, cap - pinned) : 0);
    /* keep the selected row (all of its wrapped lines) visible */
    int sel0 = -1, sel1 = 0;
    for (int i = 0; i < n; i++)
        if (lines[i].selected) { if (sel0 < 0) sel0 = i; sel1 = i; }
    if (sel0 < 0) sel0 = 0;
    int fit = (int)((oh - 16 * sc) / lh);
    int first = 0;
    if (fit > pinned + 2 && n > fit) {
        int body = fit - pinned;
        first = (sel0 + sel1) / 2 - body / 2;
        if (first > sel0) first = sel0;
        if (first < pinned) first = pinned;
        if (first > n - body) first = n - body;
    }
    SDL_SetRenderDrawBlendMode(h->ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(h->ren, 0, 0, 24, 210);
    SDL_FRect bg = { 0, 0, (float)ow, (float)oh };
    SDL_RenderFillRect(h->ren, &bg);
    SDL_SetRenderScale(h->ren, sc, sc);
    float y = 8;
    for (int i = 0; i < n; i++) {
        if (i >= pinned && i < first) continue;
        if (y * sc + lh > oh) break;
        if (lines[i].selected) SDL_SetRenderDrawColor(h->ren, 255, 230, 120, 255);
        else if (lines[i].header) SDL_SetRenderDrawColor(h->ren, 150, 200, 255, 255);
        else SDL_SetRenderDrawColor(h->ren, 230, 230, 230, 255);
        SDL_RenderDebugText(h->ren, 8, y, lines[i].text);
        y += lh / sc;
    }
    SDL_SetRenderScale(h->ren, 1.0f, 1.0f);
}

/* ---------------------------------------------------------- mouse camera */
/* Relative mode while input.mouse_look is on, the game says a camera is
 * consuming look, the window has focus, the overlay is closed and no script
 * drives the run.  Releasing drops pending motion (nothing bursts later). */
static void look_update_capture(rg_host *h)
{
    bool want = h->win && h->look.enabled && h->look_active && !h->script && focused(h) &&
                !(h->settings && h->menu.open);
    if (want == h->look_captured) return;
    if (!SDL_SetWindowRelativeMouseMode(h->win, want) && want) return;   /* refused: stay free */
    h->look_captured = want;
    if (!want) rg_look_acc_reset(&h->look);
}

void rg_host_look_latch(rg_host *h, uint32_t vbl, rg_look *out)
{
    rg_look s = { 0, 0 }, m;
    if (h->script) rg_input_script_look(h->script, vbl, &s);
    rg_look_acc_take(&h->look, &m);   /* under a script: injected motion only */
    int64_t y = (int64_t)s.yaw + m.yaw, p = (int64_t)s.pitch + m.pitch;
    out->yaw = (int32_t)(y > RG_LOOK_MAX ? RG_LOOK_MAX : y < -RG_LOOK_MAX ? -RG_LOOK_MAX : y);
    out->pitch = (int32_t)(p > RG_LOOK_MAX ? RG_LOOK_MAX : p < -RG_LOOK_MAX ? -RG_LOOK_MAX : p);
}

void rg_host_look_inject(rg_host *h, float dx, float dy)
{
    if (h->settings && rg_settings_generation(h->settings) != h->settings_gen) apply_settings(h);
    rg_look_acc_motion(&h->look, dx, dy);
}

void rg_host_set_look_active(rg_host *h, bool active)
{
    h->look_active = active;
    if (h->win) look_update_capture(h);
}

bool rg_host_look_captured(const rg_host *h) { return h->look_captured; }

void rg_host_set_camera_view(rg_host *h, int view)
{
    static int log = -1;
    if (log < 0) log = getenv("RG_CAMVIEW_LOG") != NULL;
    if (log && view != h->camera_view) fprintf(stderr, "CAMVIEW %d -> %d\n", h->camera_view, view);
    h->camera_view = view;
}

/* ---------------------------------------------------------------- events */
static int pump_events(rg_host *h);
int rg_host_pump(rg_host *h)
{
    if (h->headless) {
        /* no events, but settings changes still apply (as windowed) */
        if (h->settings && rg_settings_generation(h->settings) != h->settings_gen) apply_settings(h);
        return 1;
    }
    /* with the present thread running, the pump (settings, overlay, F11, window events) holds the
     * renderer's lock; the present thread holds it only while it draws (not while its present
     * waits for the display: render_present), so this waits a fraction of a ms at most */
    int locked = 0;
    if (h->pt && h->ren_lock) {
        if (!SDL_TryLockMutex(h->ren_lock)) {
            h->pump_skipped++;   /* (counted: the pump waited for a draw) */
            SDL_LockMutex(h->ren_lock);
        }
        locked = 1;
    }
    int run = pump_events(h);
    if (locked) SDL_UnlockMutex(h->ren_lock);
    return run;
}

static int pump_events(rg_host *h)
{
    h->pumps++;
    vpad_tick(h);   /* $RG_VPAD_SCRIPT (tests) */
    if ((h->pumps % 1800u) == 0)
        for (int p = 0; p < 2; p++)
            if (h->rumble_small[p] || h->rumble_large[p]) apply_rumble(h, p);
    rg_latch_step(&h->latch);
    h->mouse_dx = h->mouse_dy = 0;
    int latch = h->acts.min_press_fields;
    int run = 1;
    h->cap_at_pump = h->settings && rg_menu_capturing(&h->menu);
    h->text_at_pump = h->settings && rg_menu_text_editing(&h->menu);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        bool capturing = h->cap.state == RG_CAPTURE_WAITING;
        switch (e.type) {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            run = 0;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (h->text_on && rg_menu_text_editing(&h->menu)) {
                int tk = text_key_of(e.key.key);
                bool once = tk == RG_TEXT_COMMIT || tk == RG_TEXT_CANCEL;
                if (tk >= 0 && !(once && e.key.repeat)) {
                    rg_menu_text_key(&h->menu, (rg_text_key)tk);
                    if (once) {   /* not a hotkey too */
                        rg_latch_key(&h->latch, (int)e.key.scancode, latch);
                        break;
                    }
                }
            }
            /* Ctrl+V / Ctrl+C: the game's text entry (src/game/rg_textentry.c); the key does not
             * reach the pad (C is Circle, V is L3 by default) */
            if ((e.key.mod & SDL_KMOD_CTRL) && (e.key.key == SDLK_V || e.key.key == SDLK_C) && !h->menu.open &&
                !capturing) {
                if (!e.key.repeat && e.key.key == SDLK_V) {
                    char *t = SDL_GetClipboardText();
                    if (t && *t) {
                        SDL_strlcpy(h->paste, t, sizeof h->paste);
                        h->paste_n = (int)SDL_strlen(h->paste);
                    }
                    SDL_free(t);
                } else if (!e.key.repeat)
                    h->copy_req++;
                break;
            }
            if (e.key.repeat) break;
            rg_roster_note_activity(&h->roster, RG_DEV_KEYBOARD_MOUSE, 0);
            rg_latch_key(&h->latch, (int)e.key.scancode, latch);
            if (capturing) {   /* the key is the binding (or Esc cancels): no hotkeys */
                rg_capture_key(&h->cap, (int)e.key.scancode);
                capture_finish(h);
                break;
            }
            /* Esc quits only while the overlay is closed (there it is "back") */
            if (e.key.key == SDLK_ESCAPE && !h->menu.open) run = 0;
            else if (e.key.key == SDLK_F11 ||
                     (e.key.key == SDLK_RETURN && (e.key.mod & SDL_KMOD_ALT))) {
                rg_host_set_fullscreen(h, !h->fullscreen);
                if (h->settings && rg_settings_find(h->settings, "display.window_mode") >= 0) {
                    h->applied_mode = h->fullscreen ? 1 : 0;
                    rg_settings_set_int(h->settings, "display.window_mode", h->applied_mode, RG_SRC_API);
                }
            } else if (e.key.key == SDLK_F12) {
                char path[1024];
                next_shot_path(h, path, sizeof path);
                if (rg_host_screenshot(h, path) == 0) SDL_Log("rg-host: screenshot %s", path);
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            rg_roster_note_activity(&h->roster, RG_DEV_KEYBOARD_MOUSE, 0);
            rg_latch_mouse(&h->latch, e.button.button, latch);
            if (capturing) { rg_capture_mouse_button(&h->cap, e.button.button); capture_finish(h); }
            break;
        case SDL_EVENT_TEXT_INPUT:
            if (h->text_on) rg_menu_text_input(&h->menu, e.text.text);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            h->mouse_dx += e.motion.xrel;
            h->mouse_dy += e.motion.yrel;
            if (capturing) {   /* only a motion capture takes it ("Capture mouse motion") */
                rg_capture_mouse_motion(&h->cap, e.motion.xrel, e.motion.yrel);
                capture_finish(h);
            }
            break;
        case SDL_EVENT_AUDIO_DEVICE_ADDED:
        case SDL_EVENT_AUDIO_DEVICE_REMOVED:
            audio_device_event(h, &e);   /* device list, fallback, hot switch */
            break;
        case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
        case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
        case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
        case SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED:
        case SDL_EVENT_DISPLAY_ADDED:
        case SDL_EVENT_DISPLAY_REMOVED:
            update_display_hz(h);   /* display.frame_rate "display" */
            break;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            rg_host_set_focus(h, e.type == SDL_EVENT_WINDOW_FOCUS_GAINED);   /* audio.background */
            break;
        case SDL_EVENT_GAMEPAD_ADDED:
            pad_added(h, e.gdevice.which);
            break;
        case SDL_EVENT_GAMEPAD_REMOVED:
            pad_removed(h, e.gdevice.which);
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN: {
            int s = rg_roster_slot(&h->roster, e.gbutton.which);
            rg_roster_note_activity(&h->roster, RG_DEV_GAMEPAD, e.gbutton.which);
            h->last_pad_id = e.gbutton.which;
            if (s >= 0) rg_latch_pad(&h->latch, s, e.gbutton.button, latch);
            if (capturing) { rg_capture_pad_button(&h->cap, e.gbutton.button); capture_finish(h); }
            break;
        }
        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            if (e.gaxis.value >= h->acts.threshold || e.gaxis.value <= -h->acts.threshold) {
                rg_roster_note_activity(&h->roster, RG_DEV_GAMEPAD, e.gaxis.which);
                h->last_pad_id = e.gaxis.which;
            }
            if (capturing) {
                rg_capture_pad_axis(&h->cap, rg_roster_slot(&h->roster, e.gaxis.which), e.gaxis.axis,
                                    e.gaxis.value);
                capture_finish(h);
            }
            break;
        default:
            break;
        }
    }
    if (h->settings && rg_settings_generation(h->settings) != h->settings_gen) apply_settings(h);
    overlay_input(h);
    if (h->settings && rg_settings_generation(h->settings) != h->settings_gen) apply_settings(h);
    /* mouse camera: this pump's motion (only while captured; never under a
     * script) becomes look units now, latched by the game's next frame */
    if (h->look_captured && !h->script) rg_look_acc_motion(&h->look, h->mouse_dx, h->mouse_dy);
    look_update_capture(h);
    return run;
}

/* --------------------------------------------------------------- present */
static int ensure_tex(SDL_Renderer *ren, SDL_Texture **t, int *tw, int *th,
                      int w, int hh, SDL_TextureAccess acc)
{
    if (*t && *tw == w && *th == hh) return 0;
    if (*t) SDL_DestroyTexture(*t);
    *t = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA32, acc, w, hh);
    if (!*t) { set_err("SDL_CreateTexture"); *tw = *th = 0; return -1; }
    *tw = w; *th = hh;
    return 0;
}

static int present_tex(rg_host *h, SDL_Texture *t, const SDL_FRect *src, uint32_t w, uint32_t hh, void (*done)(void *),
                       void *arg);

int rg_host_present(rg_host *h, const uint32_t *rgba, uint32_t w, uint32_t hh)
{
    if (!w || !hh) return -1;
    size_t n = (size_t)w * hh;
    if (n > h->fcap) {
        uint32_t *nf = (uint32_t *)realloc(h->frame, n * 4);
        if (!nf) return -1;
        h->frame = nf;
        h->fcap = n;
    }
    memcpy(h->frame, rgba, n * 4);
    h->fw = w; h->fh = hh;
    if (h->headless || !h->ren) return 0;

    ren_lock(h);
    int rc = -1;
    if (!ensure_tex(h->ren, &h->tex, &h->tex_w, &h->tex_h, (int)w, (int)hh, SDL_TEXTUREACCESS_STREAMING)) {
        SDL_UpdateTexture(h->tex, NULL, h->frame, (int)w * 4);
        rc = present_tex(h, h->tex, NULL, w, hh, NULL, NULL);
    }
    ren_unlock(h);
    return rc;
}

/* display.fps_counter: corner text, refreshed every half second from this window's present
 * intervals (and, detailed, the logic ticks rg_host_fps_logic reports and the audio starves).
 * Drawn by the window's renderer after the frame, the settings overlay and any window shot:
 * not part of the game picture, so run hashes, --shot dumps and window shots never see it. */
static void draw_fps(rg_host *h)
{
    if (!h->fps_mode || !h->ren) return;
    uint64_t t = SDL_GetTicksNS();
    if (h->fps_last) {
        double iv = (double)(t - h->fps_last) / 1e6;
        h->fps_sum_ms += iv;
        if (iv > h->fps_max_ms) h->fps_max_ms = iv;
        h->fps_n++;
    }
    h->fps_last = t;
    if (!h->fps_t0) {
        h->fps_t0 = t;
        h->fps_logic0 = h->fps_logic;
        h->fps_starves0 = (uint32_t)SDL_GetAtomicInt(&h->starved);
    }
    double span = (double)(t - h->fps_t0) / 1e9;
    if (span >= 0.5 || !h->fps_text[0]) {
        double fps = span > 0 ? h->fps_n / span : 0.0;
        if (h->fps_mode == 1 || span <= 0) {
            SDL_snprintf(h->fps_text, sizeof h->fps_text, "%.0f FPS", fps);
        } else {
            uint32_t st = (uint32_t)SDL_GetAtomicInt(&h->starved);
            SDL_snprintf(h->fps_text, sizeof h->fps_text, "%.0f FPS %.1f ms (max %.1f) logic %.0f/s%s", fps,
                         h->fps_n ? h->fps_sum_ms / h->fps_n : 0.0, h->fps_max_ms,
                         (double)(h->fps_logic - h->fps_logic0) / span, st != h->fps_starves0 ? " AUDIO STARVED" : "");
            h->fps_starves0 = st;
        }
        if (span >= 0.5) {
            h->fps_t0 = t;
            h->fps_n = 0;
            h->fps_sum_ms = h->fps_max_ms = 0.0;
            h->fps_logic0 = h->fps_logic;
        }
    }
    int ow = 0, oh = 0;
    SDL_GetCurrentRenderOutputSize(h->ren, &ow, &oh);
    float sc = oh >= 1400 ? 3.0f : oh >= 700 ? 2.0f : 1.0f;
    float cw = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    SDL_FRect bg = { 0, 0, (SDL_strlen(h->fps_text) * cw + 8) * sc, (cw + 8) * sc };
    SDL_SetRenderDrawBlendMode(h->ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(h->ren, 0, 0, 0, 160);
    SDL_RenderFillRect(h->ren, &bg);
    SDL_SetRenderScale(h->ren, sc, sc);
    SDL_SetRenderDrawColor(h->ren, 255, 255, 96, 255);
    SDL_RenderDebugText(h->ren, 4, 4, h->fps_text);
    SDL_SetRenderScale(h->ren, 1.0f, 1.0f);
}

void rg_host_fps_logic(rg_host *h, uint64_t logic_ticks) { if (h) h->fps_logic = logic_ticks; }
int rg_host_fps_mode(const rg_host *h) { return h ? h->fps_mode : 0; }
const char *rg_host_fps_text(const rg_host *h) { return h ? h->fps_text : ""; }

/* the frame texture t (w x hh; src: its part holding the frame, NULL = all of it) into the
 * window, the overlay, a pending window shot, present.  done (optional) runs once the frame's
 * draws are submitted (before the overlay) */
static int present_tex(rg_host *h, SDL_Texture *t, const SDL_FRect *src, uint32_t w, uint32_t hh, void (*done)(void *),
                       void *arg)
{
    int ow = 0, oh = 0;
    SDL_GetCurrentRenderOutputSize(h->ren, &ow, &oh);
    int factor = 0;
    rg_rect r = rg_host_fit(h, ow, oh, (int)w, (int)hh, &factor);
    SDL_FRect dst = { (float)r.x, (float)r.y, (float)r.w, (float)r.h };
    SDL_SetRenderDrawColor(h->ren, 0, 0, 0, 255);
    SDL_RenderClear(h->ren);
    if (h->scale == RG_SCALE_INTEGER && factor > 0 &&
        ensure_tex(h->ren, &h->pre, &h->pre_w, &h->pre_h, (int)w * factor, (int)hh * factor,
                   SDL_TEXTUREACCESS_TARGET) == 0) {
        /* sharp scaling: nearest-neighbour to an integer multiple, then a
         * linear pass for the remaining (horizontal, non-integer) aspect */
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
        SDL_SetRenderTarget(h->ren, h->pre);
        SDL_RenderTexture(h->ren, t, src, NULL);
        SDL_SetRenderTarget(h->ren, NULL);
        SDL_SetTextureScaleMode(h->pre, SDL_SCALEMODE_LINEAR);
        SDL_RenderTexture(h->ren, h->pre, NULL, &dst);
    } else {
        SDL_SetTextureScaleMode(t, h->scale == RG_SCALE_NEAREST ? SDL_SCALEMODE_NEAREST
                                                                : SDL_SCALEMODE_LINEAR);
        SDL_RenderTexture(h->ren, t, src, &dst);
    }
    if (done) {
        SDL_FlushRenderer(h->ren);
        done(arg);
    }
    draw_overlay(h);
    /* $RG_WINDOW_SHOT_HOST=1 (measurement): the window shot after the FPS counter too (the
     * window's own back buffer as presented: what the zero-copy paths really show) */
    static int shot_host = -1;
    if (shot_host < 0) { const char *e = SDL_getenv("RG_WINDOW_SHOT_HOST"); shot_host = e && e[0] == '1'; }
    if (shot_host && h->window_shot[0]) draw_fps(h);
    if (h->pdump_dir[0]) {   /* rg_host_present_dump: what this present shows, before the overlay */
        SDL_Surface *sf = SDL_RenderReadPixels(h->ren, NULL);
        SDL_Surface *cv = sf ? SDL_ConvertSurface(sf, SDL_PIXELFORMAT_RGBA32) : NULL;
        if (cv && cv->pitch == cv->w * 4) {
            char p[600];
            SDL_snprintf(p, sizeof p, "%s/p%06u_f%06llu_%dx%d.rgba", h->pdump_dir, (unsigned)h->pdump_n,
                         (unsigned long long)h->pdump_field, cv->w, cv->h);
            FILE *f = fopen(p, "wb");
            if (f) {
                fwrite(cv->pixels, 4, (size_t)cv->w * cv->h, f);
                fclose(f);
            }
            h->pdump_n++;
        }
        if (cv) SDL_DestroySurface(cv);
        if (sf) SDL_DestroySurface(sf);
    }
    if (h->window_shot[0]) {
        SDL_Surface *sf = SDL_RenderReadPixels(h->ren, NULL);
        SDL_Surface *cv = sf ? SDL_ConvertSurface(sf, SDL_PIXELFORMAT_RGBA32) : NULL;
        if (cv && cv->pitch == cv->w * 4)
            rg_png_write(h->window_shot, (const uint32_t *)cv->pixels, (uint32_t)cv->w, (uint32_t)cv->h);
        else
            set_err("window screenshot");
        if (cv) SDL_DestroySurface(cv);
        if (sf) SDL_DestroySurface(sf);
        h->window_shot[0] = 0;
        if (shot_host) { render_present(h); return 0; }
    }
    draw_fps(h);   /* after the window shot: captures never show the counter */
    render_present(h);
    return 0;
}

#ifdef _WIN32
static const GUID k_iid_tex2d = { 0x6f15aaf2, 0xd208, 0x4e89, { 0x9a, 0xb4, 0x48, 0x95, 0x35, 0xd3, 0x4f, 0x9c } };
static const GUID k_iid_keyed = { 0x9d8e1289, 0xd7b3, 0x465f, { 0x81, 0x26, 0x25, 0x0e, 0x34, 0x9a, 0xf8, 0x5d } };

static void shr_release(void *km) { IDXGIKeyedMutex_ReleaseSync((IDXGIKeyedMutex *)km, 0); }

static int present_d3d11(rg_host *h, void *handle, uint32_t w, uint32_t hh)
{
    if (!handle || !w || !hh || h->headless || !h->ren || h->shr_off) return -1;
    ID3D11Device *dev = (ID3D11Device *)SDL_GetPointerProperty(SDL_GetRendererProperties(h->ren),
                                                               SDL_PROP_RENDERER_D3D11_DEVICE_POINTER, NULL);
    if (!dev) { h->shr_off = 1; return -1; }
    int k = -1;
    for (int i = 0; i < 2; i++)
        if (h->shr[i].handle == handle && h->shr[i].w == w && h->shr[i].h == hh) k = i;
    if (k < 0) {
        k = h->shr[0].used <= h->shr[1].used ? 0 : 1;
        if (h->shr[k].st) SDL_DestroyTexture(h->shr[k].st);
        if (h->shr[k].km) IDXGIKeyedMutex_Release(h->shr[k].km);
        if (h->shr[k].tex) ID3D11Texture2D_Release(h->shr[k].tex);
        memset(&h->shr[k], 0, sizeof h->shr[k]);
        ID3D11Texture2D *tex = NULL;
        IDXGIKeyedMutex *km = NULL;
        if (FAILED(ID3D11Device_OpenSharedResource(dev, (HANDLE)handle, &k_iid_tex2d, (void **)&tex)) || !tex)
            return -1;
        if (FAILED(ID3D11Texture2D_QueryInterface(tex, &k_iid_keyed, (void **)&km)) || !km) {
            ID3D11Texture2D_Release(tex);
            return -1;
        }
        SDL_PropertiesID p = SDL_CreateProperties();
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, SDL_PIXELFORMAT_RGBA32);
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, SDL_TEXTUREACCESS_STATIC);
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, w);
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, hh);
        SDL_SetPointerProperty(p, SDL_PROP_TEXTURE_CREATE_D3D11_TEXTURE_POINTER, tex);
        SDL_Texture *st = SDL_CreateTextureWithProperties(h->ren, p);
        SDL_DestroyProperties(p);
        if (!st) {
            IDXGIKeyedMutex_Release(km);
            ID3D11Texture2D_Release(tex);
            set_err("SDL_CreateTextureWithProperties (shared)");
            return -1;
        }
        h->shr[k].handle = handle;
        h->shr[k].tex = tex;
        h->shr[k].km = km;
        h->shr[k].st = st;
        h->shr[k].w = w;
        h->shr[k].h = hh;
    }
    h->shr[k].used = ++h->shr_clock;
    if (IDXGIKeyedMutex_AcquireSync(h->shr[k].km, 1, 500) != S_OK) return -1;
    h->fw = h->fh = 0;   /* no CPU copy of this frame */
    return present_tex(h, h->shr[k].st, NULL, w, hh, shr_release, h->shr[k].km);
}
#endif

/* ---- Vulkan: SDL's Vulkan renderer on the GPU backend's device (rg_host_use_vulkan) */
static void vk_drop_textures(rg_host *h)
{
    for (int i = 0; i < 2; i++) {
        if (h->vks[i].st) SDL_DestroyTexture(h->vks[i].st);
        memset(&h->vks[i], 0, sizeof h->vks[i]);
    }
}

static int present_vk(rg_host *h, const rg_host_vk_frame *f, uint32_t w, uint32_t hh)
{
    if (!f || !f->image || !f->acquire || !f->release || !w || !hh || w > f->img_w || hh > f->img_h || !h->ren)
        return -1;
    int k = -1;
    for (int i = 0; i < 2; i++)
        if (h->vks[i].st && h->vks[i].image == f->image && h->vks[i].w == f->img_w && h->vks[i].h == f->img_h) k = i;
    if (k < 0) {
        /* a new image (the backend's two alternate; they are replaced only when they grow) */
        k = h->vks[0].used <= h->vks[1].used ? 0 : 1;
        if (h->vks[k].st) SDL_DestroyTexture(h->vks[k].st);
        memset(&h->vks[k], 0, sizeof h->vks[k]);
        SDL_PropertiesID p = SDL_CreateProperties();
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, SDL_PIXELFORMAT_RGBA32);
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, SDL_TEXTUREACCESS_STATIC);
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, f->img_w);
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, f->img_h);
        /* the backend leaves it in SHADER_READ_ONLY_OPTIMAL (the property's default) */
        SDL_SetNumberProperty(p, SDL_PROP_TEXTURE_CREATE_VULKAN_TEXTURE_NUMBER, (Sint64)f->image);
        SDL_Texture *st = SDL_CreateTextureWithProperties(h->ren, p);
        SDL_DestroyProperties(p);
        if (!st) { set_err("SDL_CreateTextureWithProperties (Vulkan image)"); return -1; }
        h->vks[k].image = f->image;
        h->vks[k].st = st;
        h->vks[k].w = f->img_w;
        h->vks[k].h = f->img_h;
    }
    h->vks[k].used = ++h->vk_clock;
    if (f->acquire(f->arg) != 0) return -1;
    h->fw = h->fh = 0;   /* no CPU copy of this frame */
    SDL_FRect src = { 0.0f, 0.0f, (float)w, (float)hh };
    /* SDL_FlushRenderer (in present_tex, before release) submits the draw and waits for the queue */
    return present_tex(h, h->vks[k].st, &src, w, hh, f->release, f->arg);
}

static int present_shared(rg_host *h, void *handle, uint32_t w, uint32_t hh)
{
    if (h->vk) return present_vk(h, (const rg_host_vk_frame *)handle, w, hh);
#ifdef _WIN32
    return present_d3d11(h, handle, w, hh);
#else
    (void)handle; (void)w; (void)hh;
    return -1;
#endif
}
int rg_host_present_shared(rg_host *h, void *handle, uint32_t w, uint32_t hh)
{
    ren_lock(h);
    int rc = present_shared(h, handle, w, hh);
    ren_unlock(h);
    return rc;
}

/* ---- the present thread: rg_host_present_shared off the window's thread */
static int SDLCALL present_thread(void *arg)
{
    rg_host *h = (rg_host *)arg;
    h->pt_id = SDL_GetCurrentThreadID();
    SDL_LockMutex(h->pt_m);
    for (;;) {
        while (!h->pt_has && !h->pt_stop) SDL_WaitCondition(h->pt_c, h->pt_m);
        if (!h->pt_has) break;   /* (stop, nothing posted) */
        void *hd = h->pt_handle;
        uint32_t w = h->pt_w, hh = h->pt_h;
        uint64_t tag = h->pt_tag;
        h->pt_has = 0;    /* taken: the next frame may be posted while this one is presented */
        h->pt_busy = 1;
        SDL_BroadcastCondition(h->pt_c);
        SDL_UnlockMutex(h->pt_m);
        ren_lock(h);
        int rc = present_shared(h, hd, w, hh);
        ren_unlock(h);
        SDL_LockMutex(h->pt_m);
        if (rc) h->pt_failed++;
        h->pt_done++;
        h->pt_busy = 0;   /* (before the callback: it may post the next frame at once) */
        SDL_BroadcastCondition(h->pt_c);
        SDL_UnlockMutex(h->pt_m);
        if (h->pt_cb) h->pt_cb(h->pt_arg, tag, rc);
        SDL_LockMutex(h->pt_m);
    }
    SDL_UnlockMutex(h->pt_m);
    return 0;
}

int rg_host_present_thread(rg_host *h, int on)
{
    if (!h) return -1;
    if (on && !h->pt) {
        if (h->headless || !h->ren || !h->ren_lock) return -1;
        h->pt_m = SDL_CreateMutex();
        h->pt_c = SDL_CreateCondition();
        h->pt_stop = 0;
        h->pt_has = 0;
        if (h->pt_m && h->pt_c) h->pt = SDL_CreateThread(present_thread, "rg-present", h);
        if (!h->pt) {
            if (h->pt_c) SDL_DestroyCondition(h->pt_c);
            if (h->pt_m) SDL_DestroyMutex(h->pt_m);
            h->pt_c = NULL;
            h->pt_m = NULL;
            set_err("present thread");
            return -1;
        }
    } else if (!on && h->pt) {
        SDL_LockMutex(h->pt_m);
        h->pt_stop = 1;
        SDL_BroadcastCondition(h->pt_c);
        SDL_UnlockMutex(h->pt_m);
        SDL_WaitThread(h->pt, NULL);
        h->pt = NULL;
        SDL_DestroyCondition(h->pt_c);
        SDL_DestroyMutex(h->pt_m);
        h->pt_c = NULL;
        h->pt_m = NULL;
    }
    return 0;
}

int rg_host_present_thread_on(const rg_host *h) { return h && h->pt != NULL; }

void rg_host_present_callback(rg_host *h, void (*cb)(void *arg, uint64_t tag, int rc), void *arg)
{
    h->pt_cb = cb;
    h->pt_arg = arg;
}

int rg_host_present_post(rg_host *h, void *handle, uint32_t w, uint32_t hh, uint64_t tag)
{
    if (!h || !h->pt) return -1;
    SDL_LockMutex(h->pt_m);
    int busy = h->pt_has;
    if (!busy) {
        h->pt_handle = handle;
        h->pt_w = w;
        h->pt_h = hh;
        h->pt_tag = tag;
        h->pt_has = 1;
        h->pt_posted++;
        SDL_BroadcastCondition(h->pt_c);
    }
    SDL_UnlockMutex(h->pt_m);
    return busy ? 1 : 0;
}

int rg_host_present_pending(rg_host *h)
{
    if (!h || !h->pt) return 0;
    SDL_LockMutex(h->pt_m);
    int p = h->pt_has;
    SDL_UnlockMutex(h->pt_m);
    return p;
}

int rg_host_present_busy(rg_host *h)
{
    if (!h || !h->pt) return 0;
    SDL_LockMutex(h->pt_m);
    int p = h->pt_has || h->pt_busy;
    SDL_UnlockMutex(h->pt_m);
    return p;
}

void rg_host_present_wait(rg_host *h)
{
    if (!h || !h->pt) return;
    SDL_LockMutex(h->pt_m);
    while (h->pt_has || h->pt_busy) SDL_WaitCondition(h->pt_c, h->pt_m);
    SDL_UnlockMutex(h->pt_m);
}

void rg_host_present_thread_stats(const rg_host *h, uint64_t out[5])
{
    out[0] = h->pt_posted;
    out[1] = h->pt_done;
    out[2] = h->pt_failed;
    out[3] = h->pump_skipped;
    out[4] = h->pump_unlocked;
}

static void drop_renderer(rg_host *h)
{
    vk_drop_textures(h);
    if (h->pre) SDL_DestroyTexture(h->pre);
    if (h->tex) SDL_DestroyTexture(h->tex);
    h->pre = h->tex = NULL;
    h->pre_w = h->pre_h = h->tex_w = h->tex_h = 0;
#ifdef _WIN32
    for (int i = 0; i < 2; i++) {
        if (h->shr[i].st) SDL_DestroyTexture(h->shr[i].st);
        if (h->shr[i].km) IDXGIKeyedMutex_Release(h->shr[i].km);
        if (h->shr[i].tex) ID3D11Texture2D_Release(h->shr[i].tex);
        memset(&h->shr[i], 0, sizeof h->shr[i]);
    }
#endif
    if (h->ren) SDL_DestroyRenderer(h->ren);
    h->ren = NULL;
}

static int use_vulkan(rg_host *h, const rg_host_vk_device *d);
int rg_host_use_vulkan(rg_host *h, const rg_host_vk_device *d)
{
    if (!h || h->headless || !h->win || !d || !d->instance || !d->physical_device || !d->device) return -1;
    if (h->vk) return 0;
    if (!SDL_Vulkan_LoadLibrary(NULL)) { set_err("SDL_Vulkan_LoadLibrary"); return -1; }
    if (!SDL_Vulkan_GetPresentationSupport((VkInstance)d->instance, (VkPhysicalDevice)d->physical_device, d->queue_family)) {
        SDL_SetError("queue family %u cannot present to this window system", (unsigned)d->queue_family);
        set_err("SDL_Vulkan_GetPresentationSupport");
        SDL_Vulkan_UnloadLibrary();
        return -1;
    }
    ren_lock(h);
    int rc = use_vulkan(h, d);
    ren_unlock(h);
    return rc;
}
static int use_vulkan(rg_host *h, const rg_host_vk_device *d)
{
    drop_renderer(h);
    SDL_PropertiesID p = SDL_CreateProperties();
    SDL_SetStringProperty(p, SDL_PROP_RENDERER_CREATE_NAME_STRING, "vulkan");
    SDL_SetPointerProperty(p, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, h->win);
    SDL_SetPointerProperty(p, SDL_PROP_RENDERER_CREATE_VULKAN_INSTANCE_POINTER, d->instance);
    SDL_SetPointerProperty(p, SDL_PROP_RENDERER_CREATE_VULKAN_PHYSICAL_DEVICE_POINTER, d->physical_device);
    SDL_SetPointerProperty(p, SDL_PROP_RENDERER_CREATE_VULKAN_DEVICE_POINTER, d->device);
    SDL_SetNumberProperty(p, SDL_PROP_RENDERER_CREATE_VULKAN_GRAPHICS_QUEUE_FAMILY_INDEX_NUMBER, d->queue_family);
    SDL_SetNumberProperty(p, SDL_PROP_RENDERER_CREATE_VULKAN_PRESENT_QUEUE_FAMILY_INDEX_NUMBER, d->queue_family);
    h->ren = SDL_CreateRendererWithProperties(p);
    SDL_DestroyProperties(p);
    if (!h->ren) {
        set_err("SDL_CreateRendererWithProperties (vulkan)");
#if defined(_WIN64)
        { extern void rg_x64_va_fence(int); rg_x64_va_fence(1); h->ren = SDL_CreateRenderer(h->win, NULL); rg_x64_va_fence(0); }   /* back to the default renderer */
#else
#line 1596
        h->ren = SDL_CreateRenderer(h->win, NULL);   /* back to the default renderer */
#endif
#line 1597
        if (h->ren) SDL_SetRenderVSync(h->ren, h->vsync);
        SDL_Vulkan_UnloadLibrary();
        return -1;
    }
    SDL_SetRenderVSync(h->ren, h->vsync);
    h->vk = 1;
#ifdef _WIN32
    h->shr_off = 1;   /* no DXGI handles on this renderer */
#endif
    SDL_SetRenderDrawColor(h->ren, 0, 0, 0, 255);
    SDL_RenderClear(h->ren);
    SDL_RenderPresent(h->ren);
    return 0;
}

void rg_host_drop_vulkan(rg_host *h)
{
    if (!h || !h->vk) return;
    ren_lock(h);
    drop_renderer(h);
    h->vk = 0;
    ren_unlock(h);
    SDL_Vulkan_UnloadLibrary();
}

void rg_host_set_aspect(rg_host *h, int canvas_num, int canvas_den, int content_num,
                        int content_den)
{
    if (canvas_num <= 0 || canvas_den <= 0) { canvas_num = 4; canvas_den = 3; }
    h->cfg.aspect_num = canvas_num;
    h->cfg.aspect_den = canvas_den;
    h->content_num = content_num > 0 && content_den > 0 ? content_num : 0;
    h->content_den = content_num > 0 && content_den > 0 ? content_den : 0;
}

void rg_host_get_aspect(const rg_host *h, int *canvas_num, int *canvas_den, int *content_num,
                        int *content_den)
{
    if (canvas_num) *canvas_num = h->cfg.aspect_num;
    if (canvas_den) *canvas_den = h->cfg.aspect_den;
    if (content_num) *content_num = h->content_num ? h->content_num : h->cfg.aspect_num;
    if (content_den) *content_den = h->content_den ? h->content_den : h->cfg.aspect_den;
}

rg_rect rg_host_fit(const rg_host *h, int win_w, int win_h, int src_w, int src_h, int *factor)
{
    return rg_fit_rect_content(win_w, win_h, src_w, src_h, h->cfg.aspect_num, h->cfg.aspect_den,
                               h->content_num, h->content_den, h->scale, factor);
}

void rg_host_present_dump(rg_host *h, const char *dir, uint64_t field)
{
    SDL_snprintf(h->pdump_dir, sizeof h->pdump_dir, "%s", dir ? dir : "");
    h->pdump_field = field;
}

void rg_host_request_window_shot(rg_host *h, const char *path)
{
    SDL_snprintf(h->window_shot, sizeof h->window_shot, "%s", path ? path : "");
}

const uint32_t *rg_host_last_frame(const rg_host *h, uint32_t *w, uint32_t *hh)
{
    if (w) *w = h->fw;
    if (hh) *hh = h->fh;
    return h->fw ? h->frame : NULL;
}

int rg_host_screenshot(rg_host *h, const char *path)
{
#ifdef _WIN32
    if (!h->fw && h->shr_clock && !h->headless) {
        /* zero-copy presentation keeps no CPU frame: save the next window */
        rg_host_request_window_shot(h, path);
        return 0;
    }
#endif
    if (!h->fw && h->vk_clock && !h->headless) {
        rg_host_request_window_shot(h, path);
        return 0;
    }
    if (!h->fw) return -1;
    return rg_png_write(path, h->frame, h->fw, h->fh);
}

/* ----------------------------------------------------------------- input */
rg_input_map *rg_host_input_map(rg_host *h) { return &h->map; }
void rg_host_set_input_script(rg_host *h, const rg_input_script *s) { h->script = s; }
int rg_host_gamepad_count(const rg_host *h) { return h->roster.n; }

void rg_host_read_pad(rg_host *h, int port, uint32_t vbl, rg_pad *out)
{
    /* A script owns port 0 completely and port 1 reads neutral: no live
     * source, no overlay, no settings touch a scripted run. */
    if (h->script) {
        if (port == 0) rg_input_script_pad(h->script, vbl, out);
        else rg_pad_neutral(out);
        return;
    }
    if (h->headless || h->menu.open) {
        rg_pad_neutral(out);
        if (port == 0) rg_input_record_pad(vbl, out);   /* $RG_INPUT_RECORD */
        return;
    }
    static bool keybuf[SDL_SCANCODE_COUNT];
    rg_gamepad_snap pads[RG_MAX_GAMEPADS];
    rg_input_snapshot in;
    live_snapshot(h, port, keybuf, pads, &in);
    h->acts.camera_view = port == 0 ? h->camera_view : RG_CAMVIEW_NONE;
    rg_actions_eval(&h->acts, &in, out);
    if (port == 0) rg_input_record_pad(vbl, out);       /* $RG_INPUT_RECORD */
}

/* DS2 motors -> SDL gamepad rumble.  The gamepad is the port's (two players)
 * or the most recently used one (one player).  small (motor 0, high
 * frequency) is on/off; large (motor 1, low frequency) is 0..255; both are
 * scaled by input.vibration.  SDL caps a rumble's duration (~65 s), so the
 * state is re-sent by rg_host_pump while a motor runs. */
static void apply_rumble(rg_host *h, int port)
{
    if (h->headless || port < 0 || port > 1) return;
    int s = rg_roster_rumble_slot(&h->roster, h->acts.players, port);
    if (s < 0 || !h->pads[s]) return;
    float k = h->acts.vibration < 0 ? 0 : h->acts.vibration > 1 ? 1 : h->acts.vibration;
    uint16_t lo = (uint16_t)(h->rumble_large[port] * 257u * k);
    uint16_t hi = (uint16_t)((h->rumble_small[port] ? 65535u : 0u) * k);
    SDL_RumbleGamepad(h->pads[s], lo, hi, 0xFFFFu);
}

void rg_host_rumble(rg_host *h, int port, uint8_t small, uint8_t large)
{
    if (port < 0 || port > 1) return;
    h->rumble_small[port] = small;
    h->rumble_large[port] = large;
    h->rumble_calls++;
    apply_rumble(h, port);
}

void rg_host_rumble_state(const rg_host *h, int port, uint8_t *small, uint8_t *large)
{
    int p = port == 1;
    if (small) *small = h->rumble_small[p];
    if (large) *large = h->rumble_large[p];
}

/* ----------------------------------------------------------------- audio */
static uint32_t latency_frames(int ms)
{
    if (ms < 0) ms = RG_AUDIO_LATENCY_DEFAULT_MS;
    if (ms == 0) return 0;
    if (ms > 1000) ms = 1000;
    return (uint32_t)ms * (RG_AUDIO_RATE / 1000);
}

/* $RG_AUDIO_HOST_WAV (docs/NATIVE-AUDIO.md "Pop scan"): a 48 kHz WAV of everything the
 * host feeds the device stream (game frames, pads, de-click fades) plus the silence of
 * each starve, in device order: what is heard, before SDL's rate trim.  Written under
 * the stream lock (the device callback holds it). */
static void tap_header(rg_host *h)
{
    uint32_t data = (uint32_t)(h->tap_frames * 4), riff = data + 36, rate = RG_AUDIO_RATE, bps = RG_AUDIO_RATE * 4;
    uint8_t w[44] = {'R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ', 16, 0, 0, 0, 1, 0, 2, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 16, 0, 'd', 'a', 't', 'a', 0, 0, 0, 0};
    SDL_memcpy(w + 4, &riff, 4);
    SDL_memcpy(w + 24, &rate, 4);
    SDL_memcpy(w + 28, &bps, 4);
    SDL_memcpy(w + 40, &data, 4);
    fseek(h->tap, 0, SEEK_SET);
    fwrite(w, 1, sizeof w, h->tap);
    fseek(h->tap, 0, SEEK_END);
}

static void tap_write(rg_host *h, const int16_t *lr, uint32_t frames)
{
    static const int16_t zero[2 * 1024];
    if (!h->tap) return;
    uint64_t before = h->tap_frames;
    while (frames) {
        uint32_t n = frames < 1024 ? frames : 1024;
        fwrite(lr ? lr : zero, 4, n, h->tap);
        if (lr) lr += 2 * n;
        frames -= n;
        h->tap_frames += n;
    }
    if (h->tap_frames / RG_AUDIO_RATE != before / RG_AUDIO_RATE) tap_header(h);
}

static bool aput(rg_host *h, const int16_t *lr, uint32_t frames)
{
    tap_write(h, lr, frames);
    return SDL_PutAudioStreamData(h->audio, lr, (int)(frames * 2 * sizeof(int16_t)));
}

/* The device thread pulls from the stream; `additional` is what the stream
 * could not supply (a starve).  Counted only once the game has pushed. */
static void SDLCALL audio_get_cb(void *user, SDL_AudioStream *s, int additional, int total)
{
    rg_host *h = (rg_host *)user;
    (void)s;
    (void)total;
    if (additional > 0 && h->audio_total) {
        SDL_AddAtomicInt(&h->starved, 1);
        SDL_AddAtomicInt(&h->starved_frames, additional / (int)(RG_AUDIO_CHANNELS * sizeof(int16_t)));
        /* the stream ran dry mid-waveform: fade its last frame out instead of
         * stepping to silence (once per starve; the next push clears it) */
        uint32_t need = (uint32_t)additional / (RG_AUDIO_CHANNELS * sizeof(int16_t));
        if (h->declick && SDL_CompareAndSwapAtomicInt(&h->starve_faded, 0, 1)) {
            uint32_t t = (uint32_t)SDL_GetAtomicInt(&h->tail_packed);
            int16_t from[2] = {(int16_t)(t & 0xFFFF), (int16_t)(t >> 16)};
            int16_t fade[2 * RG_AUDIO_DECLICK_FRAMES] = {0};
            rg_audio_declick(fade, RG_AUDIO_DECLICK_FRAMES, from);
            aput(h, fade, RG_AUDIO_DECLICK_FRAMES);
            need = need > RG_AUDIO_DECLICK_FRAMES ? need - RG_AUDIO_DECLICK_FRAMES : 0;
        }
        tap_write(h, NULL, need); /* the device plays silence */
    }
}

static int push_locked(rg_host *h, const int16_t *lr, uint32_t frames, int starved);

#define TS_OUT_CAP 16384u

void rg_host_audio_set_speed(rg_host *h, double speed)
{
    if (speed <= 0.0) {
        h->ts_on = 0;             /* (the next "on" starts a fresh stage) */
        return;
    }
    if (!h->ts) {
        h->ts = (rg_tstretch *)SDL_malloc(sizeof *h->ts);
        h->ts_out = (int16_t *)SDL_malloc(TS_OUT_CAP * 2 * sizeof(int16_t));
        if (!h->ts || !h->ts_out) { SDL_free(h->ts); SDL_free(h->ts_out); h->ts = NULL; h->ts_out = NULL; return; }
    }
    if (!h->ts_on) rg_tstretch_init(h->ts);
    h->ts_on = 1;
    h->ts_speed = speed;
}

static int push_raw(rg_host *h, const int16_t *lr, uint32_t frames);

int rg_host_audio_push(rg_host *h, const int16_t *lr, uint32_t frames)
{
    h->audio_total += frames;
    if (!h->audio || !frames) return 0;
    if (h->ts_on && h->ts) {
        /* gameplay.battle_speed: game time played ts_speed times as fast, pitch kept */
        int rc = 0;
        while (frames) {
            uint32_t k = frames < 4096u ? frames : 4096u;
            uint32_t n = rg_tstretch_process(h->ts, lr, k, h->ts_speed, h->ts_out, TS_OUT_CAP);
            if (n && push_raw(h, h->ts_out, n) != 0) rc = -1;
            lr += 2 * k;
            frames -= k;
        }
        return rc;
    }
    return push_raw(h, lr, frames);
}

static int push_raw(rg_host *h, const int16_t *lr, uint32_t frames)
{
    uint64_t st = (uint64_t)(uint32_t)SDL_GetAtomicInt(&h->starved);
    int starved = st != h->starved_seen;
    h->starved_seen = st;
    uint32_t sf = (uint32_t)SDL_GetAtomicInt(&h->starved_frames);
    h->reg.starve_in = sf - h->starved_frames_seen;
    h->starved_frames_seen = sf;
    SDL_LockAudioStream(h->audio);
    int rc = push_locked(h, lr, frames, starved);
    SDL_UnlockAudioStream(h->audio);
    return rc;
}

static int push_locked(rg_host *h, const int16_t *lr, uint32_t frames, int starved)
{
    uint32_t pad = 0, drop = 0;
    double ratio0 = h->reg.ratio;
    uint32_t queued = rg_host_audio_queued(h);
    rg_audio_reg_push(&h->reg, queued, starved, frames, &pad, &drop);
    /* de-click (rg_audio_declick): what the device plays just before this block.
     * Drained or starved (the callback faded the tail out): silence; else the tail. */
    int16_t from[2] = {h->tail[0], h->tail[1]};
    int brk = h->declick && (starved || !queued || pad || drop || h->declick_pending);
    if (starved || !queued) from[0] = from[1] = 0;
    SDL_SetAtomicInt(&h->starve_faded, 0);
    if (h->tap_ev && (starved || pad || drop))
        fprintf(h->tap_ev, "%llu\t%llu\t%u\t%d\t%u\t%u\t%d\n", (unsigned long long)h->tap_frames,
                (unsigned long long)h->reg.pushes, queued, starved, pad, drop, brk);
    if (pad) {
        static const int16_t zero[2 * 1024];
        uint32_t f = pad < RG_AUDIO_DECLICK_FRAMES ? pad : RG_AUDIO_DECLICK_FRAMES;
        if (h->declick && (from[0] || from[1])) { /* fade the tail into the silence */
            int16_t fade[2 * RG_AUDIO_DECLICK_FRAMES] = {0};
            rg_audio_declick(fade, f, from);
            aput(h, fade, f);
            pad -= f;
            from[0] = from[1] = 0;
        }
        while (pad) {
            uint32_t n = pad < 1024 ? pad : 1024;
            aput(h, zero, n);
            pad -= n;
        }
    }
    if (h->reg.ratio != ratio0)
        SDL_SetAudioStreamFrequencyRatio(h->audio, (float)h->reg.ratio);
    if (drop >= frames) {
        h->declick_pending = brk; /* the splice is at the next block's start */
        return 0;
    }
    h->declick_pending = 0;
    const int16_t *p = lr + 2 * drop;
    uint32_t n = frames - drop;
    h->tail[0] = p[2 * (n - 1)];
    h->tail[1] = p[2 * (n - 1) + 1];
    SDL_SetAtomicInt(&h->tail_packed, (int)((uint32_t)(uint16_t)h->tail[0] | (uint32_t)(uint16_t)h->tail[1] << 16));
    if (brk) { /* crossfade from what was playing into the block */
        int16_t head[2 * RG_AUDIO_DECLICK_FRAMES];
        uint32_t k = n < RG_AUDIO_DECLICK_FRAMES ? n : RG_AUDIO_DECLICK_FRAMES;
        SDL_memcpy(head, p, k * 2 * sizeof(int16_t));
        rg_audio_declick(head, k, from);
        if (!aput(h, head, k)) return -1;
        p += 2 * k;
        n -= k;
        if (!n) return 0;
    }
    return aput(h, p, n) ? 0 : -1;
}

void rg_host_set_audio_latency(rg_host *h, int ms)
{
    uint32_t t = latency_frames(ms);
    if (t == h->reg.target) return;
    h->reg.target = t;
    h->reg.base_target = t;     /* (the adaptive cushion grows from the new setting) */
    h->reg.primed = 0;          /* re-prime to the new target at the next push */
    if (!t) {
        h->reg.ratio = 1.0;
        if (h->audio) SDL_SetAudioStreamFrequencyRatio(h->audio, 1.0f);
    }
}

void rg_host_audio_resync(rg_host *h) { rg_audio_reg_resync(&h->reg); }

void rg_host_audio_owed(rg_host *h, uint32_t frames) { h->reg.owed_in = frames; }

void rg_host_audio_stats(const rg_host *h, rg_audio_stats *o)
{
    SDL_zerop(o);
    o->pushed = h->audio_total;
    o->starves = (uint32_t)SDL_GetAtomicInt((SDL_AtomicInt *)&h->starved);
    o->starve_frames = (uint32_t)SDL_GetAtomicInt((SDL_AtomicInt *)&h->starved_frames);
    o->primes = h->reg.primes;
    o->pad_frames = h->reg.pad_frames;
    o->drops = h->reg.drops;
    o->drop_frames = h->reg.drop_frames;
    o->queued = rg_host_audio_queued(h);
    o->target = h->reg.target;
    o->ratio = h->reg.ratio;
}

uint32_t rg_host_audio_queued(const rg_host *h)
{
    if (!h->audio) return 0;
    int q = SDL_GetAudioStreamQueued(h->audio);
    return q > 0 ? (uint32_t)q / (2 * sizeof(int16_t)) : 0;
}

uint64_t rg_host_audio_pushed_total(const rg_host *h) { return h->audio_total; }

void rg_host_audio_pause(rg_host *h, int paused)
{
    h->audio_paused = paused != 0;
    if (!h->audio) return;
    if (paused) SDL_PauseAudioStreamDevice(h->audio);
    else SDL_ResumeAudioStreamDevice(h->audio);
}

/* the stream gain: master volume x focus mute (audio.background); presentation only */
static void apply_gain(rg_host *h)
{
    if (h->audio)
        SDL_SetAudioStreamGain(h->audio, rg_audio_output_gain(h->volume_in_mix ? 1.0f : h->volume, h->win_focus,
                                                              h->background));
}

void rg_host_set_volume_in_mix(rg_host *h, int on)
{
    if (!h || h->volume_in_mix == (on != 0))
        return;
    h->volume_in_mix = on != 0;
    apply_gain(h);
}

void rg_host_set_volume(rg_host *h, float gain)
{
    h->volume = gain < 0 ? 0 : gain > 1 ? 1 : gain;
    apply_gain(h);
}

void rg_host_set_audio_background(rg_host *h, int keep_playing)
{
    h->background = keep_playing != 0;
    apply_gain(h);
}

void rg_host_set_focus(rg_host *h, int focused)
{
    h->win_focus = focused != 0;
    apply_gain(h);
}

/* ---- output device (docs/HOST.md "Audio devices and focus") ----
 * The stream is ours (SDL_CreateAudioStream) and is bound to a logical device: switching
 * unbinds it and binds it to a newly opened device, so what is queued keeps playing and
 * the regulator, de-click and rate trim see one continuous stream. */
static void dev_names_free(rg_host *h)
{
    for (int i = 0; i < h->dev_n; i++) SDL_free(h->dev_names[i]);
    SDL_free(h->dev_names);
    h->dev_names = NULL;
    h->dev_n = 0;
}

static void dev_names_refresh(rg_host *h)
{
    dev_names_free(h);
    h->dev_stale = 0;
    if (!h->sdl_inited || !h->cfg.audio) return;
    int n = 0;
    SDL_AudioDeviceID *ids = SDL_GetAudioPlaybackDevices(&n);
    if (!ids) return;
    h->dev_names = (char **)SDL_calloc((size_t)(n > 0 ? n : 1), sizeof(char *));
    for (int i = 0; h->dev_names && i < n; i++) {
        const char *nm = SDL_GetAudioDeviceName(ids[i]);
        h->dev_names[h->dev_n++] = SDL_strdup(nm ? nm : "");
    }
    SDL_free(ids);
}

/* the physical device named `want` (0 = none / the default) */
static SDL_AudioDeviceID find_playback(const char *want)
{
    if (!want || !*want) return 0;
    int n = 0;
    SDL_AudioDeviceID *ids = SDL_GetAudioPlaybackDevices(&n), id = 0;
    if (!ids) return 0;
    const char **names = (const char **)SDL_calloc((size_t)(n > 0 ? n : 1), sizeof(char *));
    if (names) {
        for (int i = 0; i < n; i++) names[i] = SDL_GetAudioDeviceName(ids[i]);
        int k = rg_audio_device_pick(want, names, n);
        if (k >= 0) id = ids[k];
        SDL_free(names);
    }
    SDL_free(ids);
    return id;
}

static int audio_bind(rg_host *h, const char *want)
{
    if (!h->audio) return -1;
    SDL_AudioSpec spec = { SDL_AUDIO_S16, RG_AUDIO_CHANNELS, RG_AUDIO_RATE };
    SDL_AudioDeviceID phys = find_playback(want);
    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(phys ? phys : SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    if (!dev && phys) {   /* it went away between the lookup and the open */
        phys = 0;
        dev = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    }
    if (!dev) return -1;
    if (h->adev) SDL_UnbindAudioStream(h->audio);
    if (!SDL_BindAudioStream(dev, h->audio)) {
        SDL_CloseAudioDevice(dev);
        if (h->adev) SDL_BindAudioStream(h->adev, h->audio);   /* keep the old one */
        return -1;
    }
    if (h->adev) SDL_CloseAudioDevice(h->adev);
    h->adev = dev;
    SDL_snprintf(h->dev_open, sizeof h->dev_open, "%s", phys ? want : "");
    h->dev_fallback = want && *want && !phys;
    h->dev_switches++;
    if (h->audio_paused) SDL_PauseAudioDevice(dev);
    if (h->dev_switches > 1 || h->dev_fallback)
        SDL_Log("rg-host: audio on %s%s", phys ? want : "the system default",
                h->dev_fallback ? " (the chosen device is missing)" : "");
    return 0;
}

int rg_host_set_audio_device(rg_host *h, const char *name)
{
    SDL_snprintf(h->dev_want, sizeof h->dev_want, "%s", name ? name : "");
    if (!h->audio) return h->headless || !h->cfg.audio ? 0 : -1;
    /* already there (a missing name stays on the default until it appears) */
    if (h->adev && !SDL_strcmp(h->dev_open, h->dev_want)) return 0;
    return audio_bind(h, h->dev_want);
}

static void audio_device_event(rg_host *h, const SDL_Event *e)
{
    if (e->adevice.recording) return;
    h->dev_stale = 1;
    if (!h->audio) return;
    if (e->type == SDL_EVENT_AUDIO_DEVICE_REMOVED && e->adevice.which == h->adev) {
        /* our device is gone (unplugged, disabled): the default, the queue intact */
        SDL_Log("rg-host: audio device removed");
        SDL_UnbindAudioStream(h->audio);
        SDL_CloseAudioDevice(h->adev);
        h->adev = 0;
        if (audio_bind(h, "") == 0) h->dev_fallback = h->dev_want[0] != 0;
    } else if (e->type == SDL_EVENT_AUDIO_DEVICE_ADDED && h->dev_fallback && find_playback(h->dev_want)) {
        audio_bind(h, h->dev_want);   /* the chosen device is back */
    }
}

int rg_host_audio_devices(rg_host *h, const char **out, int cap)
{
    if (h->dev_stale) dev_names_refresh(h);
    int k = 0;
    if (k < cap) out[k++] = "";
    for (int i = 0; i < h->dev_n && k < cap; i++) out[k++] = h->dev_names[i];
    return k;
}

float rg_host_audio_output_gain(const rg_host *h)
{
    return rg_audio_output_gain(h->volume_in_mix ? 1.0f : h->volume, h->win_focus, h->background);
}
uint32_t rg_host_audio_device_id(const rg_host *h) { return h->adev; }
uint32_t rg_host_audio_device_switches(const rg_host *h) { return h->dev_switches; }

const char *rg_host_audio_device(const rg_host *h, int *fallback)
{
    if (fallback) *fallback = h->dev_fallback;
    return h->dev_open;
}

/* rg_menu choices: LEFT / RIGHT on audio.device steps through the devices present,
 * on display.monitor through the connected displays (shown by name), on
 * display.fullscreen_mode through the modes of the chosen display ("" first) */
static int host_choices(const char *id, const char **out, int cap, void *user)
{
    rg_host *h = (rg_host *)user;
    if (!SDL_strcmp(id, "audio.device")) return h->audio ? rg_host_audio_devices(h, out, cap) : 0;
    int monitor = !SDL_strcmp(id, "display.monitor"), modes = !SDL_strcmp(id, "display.fullscreen_mode");
    if (!monitor && !modes) return 0;
    if (h->headless || !SDL_WasInit(SDL_INIT_VIDEO)) return 0;
    int n = 0, k = 0;
    SDL_DisplayID *ids = SDL_GetDisplays(&n);
    if (!ids || n <= 0) { SDL_free(ids); return 0; }
    if (monitor) {
        SDL_DisplayID prim = SDL_GetPrimaryDisplay();
        for (int i = 0; i < n && k < cap && k < 16; i++) {
            const SDL_DisplayMode *dm = SDL_GetDesktopDisplayMode(ids[i]);
            const char *nm = SDL_GetDisplayName(ids[i]);
            if (dm)
                SDL_snprintf(h->mon_names[k], sizeof h->mon_names[k], "%d: %s (%dx%d, %.0f Hz)%s", i + 1,
                             nm ? nm : "display", dm->w, dm->h, (double)dm->refresh_rate,
                             ids[i] == prim ? " [primary]" : "");
            else
                SDL_snprintf(h->mon_names[k], sizeof h->mon_names[k], "%d: %s", i + 1, nm ? nm : "display");
            out[k] = h->mon_names[k];
            k++;
        }
    } else {
        int mon = h->settings ? rg_settings_get_int(h->settings, "display.monitor") : 0;
        SDL_DisplayID id = ids[rg_display_monitor_index(mon, n)];
        int nm = 0;
        SDL_DisplayMode **ml = SDL_GetFullscreenDisplayModes(id, &nm);
        if (k < cap) { h->modes[k][0] = 0; out[k] = h->modes[k]; k++; }
        for (int i = 0; ml && i < nm && k < cap && k < RG_MENU_MAX_CHOICES; i++) {
            char t[32];
            rg_display_mode_format(ml[i]->w, ml[i]->h, (double)ml[i]->refresh_rate, t, sizeof t);
            int dup = 0;
            for (int j = 1; j < k && !dup; j++) dup = !SDL_strcmp(h->modes[j], t);
            if (dup) continue;   /* (the same size / rate at another pixel density) */
            SDL_snprintf(h->modes[k], sizeof h->modes[k], "%s", t);
            out[k] = h->modes[k];
            k++;
        }
        SDL_free(ml);
        const SDL_DisplayMode *dm = SDL_GetDesktopDisplayMode(id);
        if (k == 1 && dm && k < cap) {   /* (a driver that lists no modes: the desktop's) */
            rg_display_mode_format(dm->w, dm->h, (double)dm->refresh_rate, h->modes[k], sizeof h->modes[k]);
            out[k] = h->modes[k];
            k++;
        }
    }
    SDL_free(ids);
    return k;
}

float rg_host_volume(const rg_host *h) { return h->volume; }

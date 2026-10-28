/* SPDX-License-Identifier: CC0-1.0 */
/* Host shell (PLAN.md "host/", D5 SDL3).  docs/HOST.md.
 *
 *   window   create / resize / fullscreen toggle, present an RGBA frame (the
 *            GS display read-out) with 4:3 aspect and a choice of scaling
 *   input    keyboard + gamepads -> a DualShock 2 report, remappable through a
 *            text config; a deterministic input script (tools/trace/input.py
 *            table format) overrides live input for regression runs
 *   audio    an SDL audio stream the mixer pushes 48 kHz stereo s16 PCM into
 *   pacing   a ps2k_pacing_fn-compatible real-time throttle for the kernel's
 *            virtual clock, with an unthrottled mode for tests
 *   PNG      screenshots (own stored-deflate encoder, no third-party code)
 *
 * The pure parts (pad mapping, scripts, scaling math, PNG, pacing math) need no
 * window and no SDL_Init; tests use them directly.  Only rg_host_* touches SDL
 * video/audio/events.  One host thread owns an rg_host.
 *
 * Live input goes through the input-action layer (rg_input.h, docs/INPUT.md);
 * the rg_input_map below is the older per-PS2-input text map, still accepted
 * (rg_host_apply_input_map converts it).
 */
#ifndef RG_HOST_H
#define RG_HOST_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ===================================================================== pad */

/* Button bits of the game's active-high word: the SCE pad bits, identical to
 * tools/trace/input.py BUTTONS (word = 0xFFFF ^ (raw[2] << 8 | raw[3])). */
enum {
    RG_BTN_L2 = 0x0001, RG_BTN_R2 = 0x0002, RG_BTN_L1 = 0x0004, RG_BTN_R1 = 0x0008,
    RG_BTN_TRIANGLE = 0x0010, RG_BTN_CIRCLE = 0x0020, RG_BTN_CROSS = 0x0040,
    RG_BTN_SQUARE = 0x0080, RG_BTN_SELECT = 0x0100, RG_BTN_L3 = 0x0200,
    RG_BTN_R3 = 0x0400, RG_BTN_START = 0x0800, RG_BTN_UP = 0x1000,
    RG_BTN_RIGHT = 0x2000, RG_BTN_DOWN = 0x4000, RG_BTN_LEFT = 0x8000
};

/* Mappable inputs: 0..15 are the button bit numbers above; 16..23 are the
 * analog stick half-axes (NEG = left/up = toward 0x00). */
enum {
    RG_IN_LX_NEG = 16, RG_IN_LX_POS, RG_IN_LY_NEG, RG_IN_LY_POS,
    RG_IN_RX_NEG, RG_IN_RX_POS, RG_IN_RY_NEG, RG_IN_RY_POS,
    RG_IN_COUNT
};

/* Pressure byte order of the DS2 report (bytes 8..19). */
enum {
    RG_PRS_RIGHT, RG_PRS_LEFT, RG_PRS_UP, RG_PRS_DOWN, RG_PRS_TRIANGLE,
    RG_PRS_CIRCLE, RG_PRS_CROSS, RG_PRS_SQUARE, RG_PRS_L1, RG_PRS_R1,
    RG_PRS_L2, RG_PRS_R2, RG_PRS_COUNT
};

typedef struct rg_pad {
    uint16_t buttons;            /* active high, RG_BTN_* */
    uint8_t lx, ly, rx, ry;      /* 0x00..0xFF, 0x80 = centre, 0x00 = left/up */
    uint8_t pressure[RG_PRS_COUNT]; /* 0 or 255 (digital sources only) */
} rg_pad;

#define RG_DS2_REPORT_BYTES 20

/* Neutral pad: no buttons, sticks centred, no pressure. */
void rg_pad_neutral(rg_pad *p);
/* pressure[] = 255 for each pressed pressure-sensitive button, else 0. */
void rg_pad_fill_pressure(rg_pad *p);
/* The scePadRead buffer of a DualShock 2 in analog + pressure mode:
 * [0] 0x00 (ok), [1] 0x79 (id 7, 9 halfwords), [2..3] buttons ACTIVE LOW
 * (raw[2] = word >> 8, raw[3] = word & 0xFF, inverted), [4] rx [5] ry [6] lx
 * [7] ly, [8..19] pressure in RG_PRS_* order.  Returns RG_DS2_REPORT_BYTES. */
int rg_pad_ds2_report(const rg_pad *p, uint8_t out[RG_DS2_REPORT_BYTES]);
/* Name of input i (0..RG_IN_COUNT-1): "CROSS", "LX-", ...; NULL if invalid.
 * rg_input_from_name is case-insensitive; returns -1 if unknown. */
const char *rg_input_name(int i);
int rg_input_from_name(const char *name);

/* ----------------------------------------------------------- input map */
#define RG_MAP_SLOTS 4
#define RG_GP_BUTTONS 32         /* >= SDL_GAMEPAD_BUTTON_COUNT */
#define RG_GP_AXES 8             /* >= SDL_GAMEPAD_AXIS_COUNT */

/* Bindings per input.  key = SDL_Scancode (0 = none).  pad_button =
 * SDL_GamepadButton (-1 = none).  pad_axis = SDL_GamepadAxis * 2 + (1 for
 * the positive direction, 0 for negative) (-1 = none). */
typedef struct rg_input_map {
    uint16_t key[RG_IN_COUNT][RG_MAP_SLOTS];
    int8_t pad_button[RG_IN_COUNT][RG_MAP_SLOTS];
    int8_t pad_axis[RG_IN_COUNT][RG_MAP_SLOTS];
    int deadzone;           /* stick deadzone, 0..32767 (default 8000) */
    int threshold;          /* axis -> digital button threshold (default 12000) */
} rg_input_map;

/* One gamepad's raw state, indexed by the SDL enums. */
typedef struct rg_gamepad_snap {
    uint8_t button[RG_GP_BUTTONS];
    int16_t axis[RG_GP_AXES];
} rg_gamepad_snap;

void rg_input_map_default(rg_input_map *m);
/* Config text (docs/HOST.md):  INPUT = binding[, binding...]   where a binding
 * is key:<SDL scancode name> | pad:<SDL gamepad button name> |
 * axis:<SDL gamepad axis name>+ or - ;  also  deadzone = N,  threshold = N.
 * A line for an input REPLACES that input's default bindings.  '#' comments.
 * Returns 0, or -1 with a "line N: ..." message in err. */
int rg_input_map_parse(rg_input_map *m, const char *text, char *err, size_t errcap);
int rg_input_map_load(rg_input_map *m, const char *path, char *err, size_t errcap);
/* Writes the map as config text (round-trips through rg_input_map_parse).
 * Returns the length written (always NUL-terminated if cap > 0). */
size_t rg_input_map_format(const rg_input_map *m, char *out, size_t cap);
/* Live evaluation.  keys: SDL keyboard state (SDL_GetKeyboardState), indexed
 * by scancode, nkeys entries; may be NULL.  pads: gamepads merged into this
 * report (may be NULL / 0).  Pressure is filled from the buttons. */
void rg_input_eval(const rg_input_map *m, const bool *keys, int nkeys,
                   const rg_gamepad_snap *pads, int npads, rg_pad *out);

/* -------------------------------------------------------- input script */
/* tools/trace/input.py: MAX_ENTRIES = (0x00100000 - 0x000F0100 - 8) / 2. */
#define RG_SCRIPT_MAX_ENTRIES 32636u

/* Compiled script: one u16 button word per GAME VBlank counter value
 * ([0x004810C4]), always RG_SCRIPT_MAX_ENTRIES long, zero padded (exactly
 * input.py build_table()).  `span` = highest last_vbl + 1 (0 when empty). */
typedef struct rg_input_script {
    uint16_t *words;
    uint32_t count;      /* RG_SCRIPT_MAX_ENTRIES once loaded */
    uint32_t span;
    int16_t *look;       /* the look channel: 2 * count (yaw, pitch per VBlank);
                            NULL = the script has no "#!look 1 0" line */
    uint8_t *stick;      /* the stick channel: 4 * count (lx, ly, rx, ry per VBlank,
                            0x80 = centre); NULL = no "#!stick 1 0" line */
} rg_input_script;

/* Mouse camera (docs/INPUT.md "Mouse camera implementation"): one latched
 * look delta in look units = Q12 radians (1/4096 rad), after the mouse
 * settings and quantisation.  yaw > 0 turns right, pitch > 0 looks up. */
typedef struct rg_look { int32_t yaw, pitch; } rg_look;
#define RG_LOOK_MAX 32767

/* Same grammar and errors as input.py parse_script(): per line
 * "first last BUTTON[+BUTTON...]" (inclusive) or "vbl BUTTON"; '#' comments;
 * integers as Python int(x, 0).  Returns 0, or -1 with a message in err. */
int rg_input_script_parse(rg_input_script *s, const char *text, const char *name,
                          char *err, size_t errcap);
int rg_input_script_load(rg_input_script *s, const char *path, char *err, size_t errcap);
void rg_input_script_free(rg_input_script *s);
/* Word for game VBlank `vbl` (0 at or beyond `count`, as the trampoline). */
uint16_t rg_input_script_word(const rg_input_script *s, uint32_t vbl);
/* The pad the game sees on VBlank `vbl` under the script: the word, sticks
 * centred, pressure 0/255 from the word.  Live input is NOT merged (a
 * regression run has no host input sources, like the PCSX2 harness). */
void rg_input_script_pad(const rg_input_script *s, uint32_t vbl, rg_pad *out);
/* input.py's PINE blob: u32 count then count u16 words, little endian.  Returns
 * bytes needed; writes only if cap is large enough. */
size_t rg_input_script_blob(const rg_input_script *s, uint8_t *out, size_t cap);
/* The look channel (lines input.py reads as comments, so the table and blob
 * above never change):  "#!look 1 0" (version, required first), then
 * "#!look VBL YAW PITCH" or "#!look FIRST LAST YAW PITCH" (signed look units,
 * overlapping lines add, |sum| <= RG_LOOK_MAX).  *out = the delta latched at
 * game VBlank `vbl` (0 elsewhere); returns 1 when the script has the channel,
 * else 0 (and *out = 0). */
int rg_input_script_look(const rg_input_script *s, uint32_t vbl, rg_look *out);
/* The stick channel (also comment lines to input.py; docs/INPUT.md "Scripted
 * sticks"): "#!stick 1 0" (version, required first), then
 * "#!stick FIRST LAST LX LY [RX RY]" (inclusive game VBlank range, stick bytes
 * 0..255, 0x80 = centre, 0 = left/up; a later line overrides an earlier one on
 * the VBlanks they share; right stick centred when omitted).
 * rg_input_script_pad() applies it. */

/* ============================================================== scaling */
typedef enum rg_scale_mode {
    RG_SCALE_LINEAR = 0,   /* largest aspect-correct fit, bilinear */
    RG_SCALE_NEAREST,      /* largest aspect-correct fit, nearest */
    RG_SCALE_INTEGER,      /* height = integer multiple of the source lines,
                              width from the aspect; sharp (nearest prescale,
                              then linear to the final width) */
    RG_SCALE_STRETCH       /* fill the window, ignore the aspect */
} rg_scale_mode;

typedef struct rg_rect { int x, y, w, h; } rg_rect;

/* Destination rectangle of a src_w x src_h frame in a win_w x win_h window
 * displayed at aspect num:den (4:3 for the PS2; num or den 0 = square source
 * pixels).  Centred.  INTEGER falls back to the LINEAR fit when even one
 * multiple does not fit.  Returns the integer factor in *factor (may be NULL;
 * 0 when not an integer mode/fallback). */
rg_rect rg_fit_rect(int win_w, int win_h, int src_w, int src_h,
                    int aspect_num, int aspect_den, rg_scale_mode mode, int *factor);
const char *rg_scale_name(rg_scale_mode m);
int rg_scale_from_name(const char *name);   /* -1 if unknown */
/* Widescreen (docs/WIDESCREEN.md): the canvas rg_fit_rect gives for an:ad,
 * with the frame shown at content shape cn:cd inside it (centred; a narrower
 * content is pillarboxed at the canvas height, STRETCH keeps the proportion
 * of the stretched canvas).  cn or cd 0, or cn:cd == an:ad: rg_fit_rect
 * exactly.  *factor is the canvas's. */
rg_rect rg_fit_rect_content(int win_w, int win_h, int src_w, int src_h,
                            int aspect_num, int aspect_den, int content_num, int content_den,
                            rg_scale_mode mode, int *factor);
/* The presented picture at the source height, for headless screenshots: a
 * canvas of round(src_h * an / ad) x src_h, the frame resampled horizontally
 * (linear) into its cn:cd rectangle (rg_fit_rect_content, LINEAR), opaque
 * black outside.  *out_w is always set; returns 0, or -1 when out_cap pixels
 * are too few (or a bad argument). */
int rg_present_image(const uint32_t *src, uint32_t src_w, uint32_t src_h, int aspect_num,
                     int aspect_den, int content_num, int content_den, uint32_t *out,
                     size_t out_cap, uint32_t *out_w);

/* ================================================================== PNG */
/* RGBA8 (bytes R,G,B,A per pixel) -> PNG (colour type 6, filter 0, stored
 * deflate).  rg_png_encode returns a malloc'd buffer (free()) or NULL. */
uint8_t *rg_png_encode(const uint32_t *rgba, uint32_t w, uint32_t h, size_t *len);
int rg_png_write(const char *path, const uint32_t *rgba, uint32_t w, uint32_t h);
uint32_t rg_crc32(uint32_t crc, const void *data, size_t n);   /* PNG/zlib CRC */
uint32_t rg_adler32(uint32_t adler, const void *data, size_t n);

/* =============================================================== pacing */
#define RG_BUSCLK 147456000u

/* Bus cycles -> nanoseconds, exact (x * 15625 / 2304), floor. */
uint64_t rg_cycles_to_ns(uint64_t cycles);
/* Start of NTSC field k in bus cycles: k * 2460060, the kernel's
 * PS2K_FIELD_SUB/PS2K_SUB (matches PCSX2: BUSCLK/59.94; docs/KERNEL.md). */
uint64_t rg_field_cycles(uint64_t k);

typedef struct rg_pacer {
    int throttle;                 /* 0 = unthrottled (tests, --headless) */
    int anchored;
    uint64_t anchor_cycles, anchor_ns;
    uint64_t max_lag_ns;          /* behind by more -> re-anchor (default 250 ms) */
    uint64_t sleeps, slept_ns, resyncs;
    uint64_t (*now_ns)(void *user);          /* default: SDL_GetTicksNS */
    void (*sleep_ns)(void *user, uint64_t ns); /* default: SDL_DelayPrecise */
    void *clock_user;
} rg_pacer;

void rg_pacer_init(rg_pacer *p, int throttle);
/* Forget the anchor (after a pause, a load, a mode switch). */
void rg_pacer_reset(rg_pacer *p);
/* ps2k_pacing_fn-compatible (src/ps2/kernel/ps2k.h): the kernel is about to
 * jump virtual time from `from` to `to`; user = rg_pacer*.  Sleeps until the
 * wall clock reaches the time that `to` maps to. */
void rg_pacer_hook(uint64_t from_cycles, uint64_t to_cycles, void *user);

/* =============================================================== window */
#define RG_AUDIO_RATE 48000
#define RG_AUDIO_CHANNELS 2

typedef struct rg_host_config {
    const char *title;
    int win_w, win_h;          /* initial window client size (0 = 1280x960) */
    int fullscreen;
    rg_scale_mode scale;
    int aspect_num, aspect_den; /* 0/0 = 4:3 */
    int vsync;                 /* renderer vsync (default 0: the pacer paces) */
    int headless;              /* no window, no audio device, no live input */
    int audio;                 /* open the audio device (ignored headless) */
    int audio_latency_ms;      /* audio.latency_ms: device queue target (0 = default) */
    const char *screenshot_dir; /* F12 target directory (NULL = ".") */
} rg_host_config;

typedef struct rg_host rg_host;

void rg_host_config_default(rg_host_config *c);
/* Returns NULL on failure (message on stderr / rg_host_last_error). */
rg_host *rg_host_create(const rg_host_config *c);
void rg_host_destroy(rg_host *h);
const char *rg_host_last_error(void);

/* Process pending events (window, keyboard, gamepad hot-plug, hotkeys:
 * Alt+Enter / F11 fullscreen, F12 screenshot, Esc quit).  Returns 0 when
 * the user asked to quit. */
int rg_host_pump(rg_host *h);
void rg_host_set_title(rg_host *h, const char *title);
void rg_host_set_fullscreen(rg_host *h, int on);
int rg_host_fullscreen(const rg_host *h);
void rg_host_set_scale(rg_host *h, rg_scale_mode m);
rg_scale_mode rg_host_scale(const rg_host *h);
/* Client size in pixels (0 x 0 headless). */
void rg_host_window_size(const rg_host *h, int *w, int *h_);
/* Display shape (docs/WIDESCREEN.md): the canvas the window shows (4:3, or
 * 16:9 for graphics.aspect = 16:9) and the frame's shape inside it (the same,
 * or 4:3 pillarboxed for screens that are not WIDE-aware).  0 = canvas.
 * Starts at the config's aspect (4:3).  Presentation only. */
void rg_host_set_aspect(rg_host *h, int canvas_num, int canvas_den, int content_num,
                        int content_den);
void rg_host_get_aspect(const rg_host *h, int *canvas_num, int *canvas_den, int *content_num,
                        int *content_den);
/* Where rg_host_present puts a src_w x src_h frame in a win_w x win_h output
 * (rg_fit_rect_content with the host's scale mode and aspect). */
rg_rect rg_host_fit(const rg_host *h, int win_w, int win_h, int src_w, int src_h, int *factor);

/* Present an RGBA8 frame (gs_read_display output).  The frame is copied; the
 * last one is kept for screenshots.  Returns 0 or -1. */
int rg_host_present(rg_host *h, const uint32_t *rgba, uint32_t w, uint32_t hgt);
/* Zero-copy presentation (docs/PERF-3D.md): present a w x hgt RGBA8 frame
 * that lives in a Direct3D 11 texture shared from another device (a DXGI
 * shared handle with a keyed mutex: key 1 = ready to present, released back
 * as key 0, gpu_present_shared).  Only when the window's renderer is
 * Direct3D 11; returns -1 otherwise (or when the texture cannot be opened),
 * and the caller presents with rg_host_present instead.  The frame stays on
 * the GPU: rg_host_last_frame has none, and F12 then saves the window. */
int rg_host_present_shared(rg_host *h, void *handle, uint32_t w, uint32_t hgt);
/* display.fps_counter (docs/SETTINGS.md): the mode applied (0 off, 1 fps, 2 detailed), the
 * text last drawn, and the game-logic tick count the detailed line's rate is taken from (the
 * runtime reports it every field; presentation only) */
int rg_host_fps_mode(const rg_host *h);
const char *rg_host_fps_text(const rg_host *h);
void rg_host_fps_logic(rg_host *h, uint64_t logic_ticks);
/* Zero-copy presentation with the native device's Vulkan backend (docs/NATIVE-VULKAN.md
 * "Presentation"): rg_host_use_vulkan replaces the window's renderer by SDL's Vulkan renderer on
 * the backend's own device (gpu_vk_present_device: instance with the surface extensions, the
 * device with VK_KHR_swapchain, queue 0 of queue_family for the renderer).  After it,
 * rg_host_present_shared's handle is an rg_host_vk_frame * (layout = gpu.h gpu_vk_frame): the
 * image is wrapped as a texture (cached by image, two), acquire() before drawing, release() once
 * the renderer's work that read it has completed.  Returns 0, or -1 with the old renderer kept
 * (no Vulkan presentation support for that queue, renderer creation failed; headless).
 * rg_host_drop_vulkan destroys that renderer (no renderer after it): call it before the device
 * is destroyed. */
typedef struct rg_host_vk_device {
    void *instance, *physical_device, *device;
    uint32_t queue_family;
} rg_host_vk_device;
typedef struct rg_host_vk_frame {
    uint64_t image;            /* VkImage, R8G8B8A8_UNORM, SHADER_READ_ONLY_OPTIMAL once acquired */
    uint32_t img_w, img_h;     /* its size; the frame is its top-left w x hgt */
    int (*acquire)(void *arg); /* 0 = ok */
    void (*release)(void *arg);
    void *arg;
} rg_host_vk_frame;
int rg_host_use_vulkan(rg_host *h, const rg_host_vk_device *d);
void rg_host_drop_vulkan(rg_host *h);
/* The last presented frame (NULL if none). */
const uint32_t *rg_host_last_frame(const rg_host *h, uint32_t *w, uint32_t *hgt);
/* PNG of the last presented frame, at source resolution. */
int rg_host_screenshot(rg_host *h, const char *path);
/* PNG of the next presented WINDOW (scaled frame + overlay), written inside
 * the next rg_host_present.  Windowed only (headless never presents). */
void rg_host_request_window_shot(rg_host *h, const char *path);
/* The folder F12 writes to (system.screenshot_dir, applied live; "." by
 * default). */
const char *rg_host_screenshot_dir(const rg_host *h);

/* ---- input ---- */
rg_input_map *rg_host_input_map(rg_host *h);   /* editable in place */
/* Install a script (ownership stays with the caller; NULL removes it).  While
 * a script is installed, port 0 reads come only from it. */
void rg_host_set_input_script(rg_host *h, const rg_input_script *s);
/* The pad on `port` (0 or 1) for game VBlank `vbl`.  Port 0 = keyboard +
 * first gamepad (or the script); port 1 = second gamepad (neutral under a
 * script or headless). */
void rg_host_read_pad(rg_host *h, int port, uint32_t vbl, rg_pad *out);
int rg_host_gamepad_count(const rg_host *h);
/* Mouse camera (docs/INPUT.md "Mouse camera implementation").
 * rg_host_look_latch: the look delta for the latch at game VBlank `vbl`
 * (rg-game calls it once per game frame, from MainLoop): with a script, the
 * script's look channel (0 without one; live mouse ignored); else the motion
 * accumulated since the previous latch (input.mouse_look on, mouse captured),
 * which is then reset.  Motion given to rg_host_look_inject (scripted
 * verification runs: rg-game --mouse-motion) goes through the same settings
 * and is added in both cases.  rg_host_set_look_active: the game's hint that a
 * camera consumed look recently; the window captures the mouse (relative
 * mode) only while input.mouse_look is on, the camera is active, the window is
 * focused and the overlay is closed. */
void rg_host_look_latch(rg_host *h, uint32_t vbl, rg_look *out);
void rg_host_look_inject(rg_host *h, float dx, float dy);
void rg_host_set_look_active(rg_host *h, bool active);
bool rg_host_look_captured(const rg_host *h);
/* The game's hint which camera read the right stick in the last few fields
 * (RG_CAMVIEW_* in rg_input.h: none, the orbit camera, first person), for the
 * camera stick convention (docs/INPUT.md "Camera stick convention"); live
 * port-0 input only (a script's bytes are never changed). */
void rg_host_set_camera_view(rg_host *h, int view);
/* Vibration (libpad SetActDirect via padman's rumble hook): small = motor 0
 * on/off, large = motor 1 0..255.  Maps to SDL_RumbleGamepad on the port's
 * gamepad; headless it is only recorded. */
void rg_host_rumble(rg_host *h, int port, uint8_t small, uint8_t large);
void rg_host_rumble_state(const rg_host *h, int port, uint8_t *small, uint8_t *large);

/* ---- settings + input actions (docs/SETTINGS.md, docs/INPUT.md) ---- */
struct rg_settings;
struct rg_actions;
/* Fills the window/scale/vsync/audio/screenshot fields from a registry that
 * has the core settings (rg_settings_register_core); absent ids are left. */
void rg_host_config_from_settings(rg_host_config *c, const struct rg_settings *s);
/* The reverse, for programs whose own flags (--scale, --fullscreen, --vsync,
 * --mute) set rg_host_config after rg_host_config_from_settings: every field
 * that differs from the registry becomes a command-line override (not saved),
 * so attaching the registry does not undo the flag. */
void rg_host_settings_from_config(struct rg_settings *s, const rg_host_config *c);
/* Live settings: the host applies display.*, audio.master_volume,
 * system.screenshot_dir and input.* now and whenever they change (checked
 * every pump, headless too), and owns the settings overlay (F1 / gamepad Guide; drawn in
 * rg_host_present; "Save", or closing it after a change, writes to save_path when non-NULL).  The registry
 * must outlive the host or be detached with NULL. */
void rg_host_attach_settings(rg_host *h, struct rg_settings *s, const char *save_path);
/* The action map live input is evaluated with (editable in place; a later
 * settings change rebuilds it from the registry). */
struct rg_actions *rg_host_actions(rg_host *h);
/* Rebuild the action map from the legacy rg_host_input_map (--config). */
void rg_host_apply_input_map(rg_host *h);
/* Port 0 is always connected; port 1 only in a live two-player setup
 * (input.players = two, >= 2 gamepads, no script, not headless). */
bool rg_host_port_connected(const rg_host *h, int port);
/* Most recently used device (rg_device_kind) and a printable name. */
int rg_host_active_device(const rg_host *h, char *name, size_t cap);
/* While the overlay is open, live pad reads are neutral (scripts unaffected). */
bool rg_host_overlay_open(const rg_host *h);
/* Open / close the overlay from code (no-op without attached settings). */
void rg_host_set_overlay(rg_host *h, bool open);
/* Drives the overlay from code (smoke runs: rg-host-demo --menu).  A
 * comma-separated list of up, down, left, right, accept, back, prev, next,
 * toggle (menu commands), text:<chars> (typed text), and press:<binding>
 * (e.g. press:key:F, press:pad:y, press:axis:lefttrigger+), which goes through
 * the rebinding detector exactly like a live press.  Returns the number of
 * items applied, or -1 at the first unknown item. */
int rg_host_menu_script(rg_host *h, const char *script);
void rg_host_set_vsync(rg_host *h, int on);
/* display.monitor: move the window (and fullscreen) to display index mon
 * (0 = first, clamped to the displays present). */
void rg_host_set_monitor(rg_host *h, int mon);
/* display.window_mode fullscreen flavour for the next/current fullscreen:
 * 0 borderless at the desktop mode, 1 exclusive at the display mode closest
 * to the window size. */
void rg_host_set_fullscreen_mode(rg_host *h, int exclusive);
void rg_host_set_window_size(rg_host *h, int w, int hgt);

/* ---- audio: 48 kHz, stereo, s16 interleaved ---- */
/* Output gain 0..1 (audio.master_volume / 100). */
void rg_host_set_volume(rg_host *h, float gain);
float rg_host_volume(const rg_host *h);
/* Queue `frames` frames.  Headless or without a device the data is counted
 * and dropped.  Returns 0 or -1. */
int rg_host_audio_push(rg_host *h, const int16_t *lr, uint32_t frames);
/* Frames queued and not yet played (0 headless). */
uint32_t rg_host_audio_queued(const rg_host *h);
uint64_t rg_host_audio_pushed_total(const rg_host *h);
void rg_host_audio_pause(rg_host *h, int paused);
/* The output queue target (audio.latency_ms, live; < 0 = the default
 * RG_AUDIO_LATENCY_DEFAULT_MS, 0 = off: push as produced, no regulation). */
void rg_host_set_audio_latency(rg_host *h, int ms);
/* Wall time was dropped (the pacer re-anchored): refill the cushion with
 * silence at the next push if the queue is short (docs/SOUND.md
 * "Load-screen audio"). */
void rg_host_audio_resync(rg_host *h);
/* Before this field's pushes: frames of audio the pacer owes and will push right away
 * (host-clock catch-up), so a refill after a starve does not stack silence on top of them
 * (docs/NATIVE-THREADS.md "3h"). */
void rg_host_audio_owed(rg_host *h, uint32_t frames);
/* Output device (audio.device, live; docs/HOST.md "Audio devices and focus").  The stream
 * is bound to a device opened by name; "" = the system default (follows the default as it
 * changes).  A name that is not present, or a device that goes away while playing, falls
 * back to the default without losing the queued audio; the named device is taken again
 * when it comes back.  Returns 0, or -1 when no device could be opened. */
int rg_host_set_audio_device(rg_host *h, const char *name);
/* The playback devices present now ("" first = the system default); strings stay valid
 * until the next device event or call.  Returns the count. */
int rg_host_audio_devices(rg_host *h, const char **out, int cap);
/* What plays now: the device name, "" for the default.  *fallback (may be NULL) is set
 * when audio.device names a device that is missing. */
const char *rg_host_audio_device(const rg_host *h, int *fallback);
/* audio.background: 1 keeps the sound while the window has no focus, 0 mutes it. */
void rg_host_set_audio_background(rg_host *h, int keep_playing);
/* The window focus as the host last saw it (tests drive it directly). */
void rg_host_set_focus(rg_host *h, int focused);
/* Tests: the gain the stream gets now (master x focus mute), the SDL logical device id the
 * stream is bound to (0 none), and how many times it was (re)bound. */
float rg_host_audio_output_gain(const rg_host *h);
uint32_t rg_host_audio_device_id(const rg_host *h);
uint32_t rg_host_audio_device_switches(const rg_host *h);

/* ---- output-queue regulator (pure; host_audio.c, docs/SOUND.md
 * "Load-screen audio").  The game pushes one field of audio (800/801
 * frames) per field on the virtual clock; the device drains on its own
 * clock.  The regulator keeps a cushion of `target` frames in the queue:
 * silence before the first push and after a starve that left the queue
 * short, a slight playback-rate trim (|ratio - 1| <= 0.5 %) for clock drift,
 * and a drop of the front of a push when the queue is far over target (after
 * a hitch the pacer caught up).  Presentation only: what the game rendered
 * (RG_AUDIO_WAV, the run hash) never changes. */
#define RG_AUDIO_LATENCY_DEFAULT_MS 64
#define RG_AUDIO_RATIO_MAX 0.005
typedef struct rg_audio_reg {
    uint32_t target;          /* frames; 0 = off */
    int primed;
    int resync;               /* rg_audio_reg_resync pending */
    double err_avg;           /* smoothed (queued before push - target), frames */
    double ratio;             /* playback rate to apply (1 = nominal) */
    uint64_t pushes, primes, pad_frames, drops, drop_frames;
    /* adaptive cushion (docs/NATIVE-THREADS.md "3h"): after a starve the target grows by the
     * silence the device played (up to max_target), and decays back to base_target in steps
     * once no starve was seen for a while.  max_target 0 = off (a fixed target). */
    uint32_t base_target, max_target;
    uint32_t starve_in;       /* caller, before a push: frames the device starved since the last */
    uint32_t owed_in;         /* caller, before a push: audio the pacer will push at once (owed
                                 phases of a catch-up): the refill after a starve leaves room */
    uint64_t calm;            /* pushes since the last starve */
    uint64_t grows, shrinks;
} rg_audio_reg;
typedef struct rg_audio_stats {
    uint64_t pushed;          /* frames the game handed over */
    uint64_t starves, starve_frames; /* device pulls the queue could not fill */
    uint64_t primes, pad_frames, drops, drop_frames;
    uint32_t queued, target;  /* frames */
    double ratio;
} rg_audio_stats;
void rg_audio_reg_init(rg_audio_reg *r, uint32_t target_frames);
void rg_audio_reg_resync(rg_audio_reg *r);
/* adaptive cushion: grow up to max_frames after starves (0: off) */
void rg_audio_reg_adapt(rg_audio_reg *r, uint32_t max_frames);
/* One push of `frames`: `queued` is the backlog now, `starved` says the
 * device ran dry since the last push.  Returns the silence to queue first in
 * *pad and the frames to discard from the front of the block in *drop;
 * r->ratio is updated. */
void rg_audio_reg_push(rg_audio_reg *r, uint32_t queued, int starved, uint32_t frames,
                       uint32_t *pad, uint32_t *drop);
/* De-click (docs/HOST.md "Audio"): every place the host breaks the stream (a starve, a
 * pad of silence, frames dropped from a block's front) is a step in the waveform, heard
 * as a pop.  rg_audio_declick crossfades the first n frames of lr from the constant
 * frame `from` (what the device was last playing) into the signal; on a buffer of zeros
 * it is a fade from `from` to silence. */
#define RG_AUDIO_DECLICK_FRAMES 96 /* 2 ms */
void rg_audio_declick(int16_t *lr, uint32_t n, const int16_t from[2]);
void rg_host_audio_stats(const rg_host *h, rg_audio_stats *out);
/* Pure helpers of the device and focus logic (host_audio.c; ctest host.audio_device,
 * host.audio_focus).  rg_audio_device_pick: index of `want` in names[] (exact, then
 * ignoring case), -1 for "" or a missing name (= the system default).
 * rg_audio_output_gain: the stream gain for a master volume, the focus and
 * audio.background (0 when unfocused and not keep-playing). */
int rg_audio_device_pick(const char *want, const char *const *names, int n);
float rg_audio_output_gain(float volume, int focused, int keep_playing);

#ifdef __cplusplus
}
#endif
#endif

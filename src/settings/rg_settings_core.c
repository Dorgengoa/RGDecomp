/* SPDX-License-Identifier: CC0-1.0 */
/* The P4 core settings: display, audio, system, and the planned graphics /
 * gameplay options as placeholders (PLAN.md P6 "Graphics settings").
 * docs/SETTINGS.md has the table.  Input settings are registered by the input
 * layer (src/host/rg_input.h, rg_actions_register_settings). */
#include "rg_settings.h"

#define N(a) ((int)(sizeof(a) / sizeof((a)[0])))

static const char *const k_window_mode[] = { "windowed", "fullscreen", "exclusive" };
static const char *const k_window_mode_l[] = { "Windowed", "Borderless fullscreen", "Exclusive fullscreen" };
/* display.fps_counter (docs/SETTINGS.md): a host overlay drawn at present time */
static const char *const k_fps[] = { "off", "fps", "detailed" };
static const char *const k_fps_l[] = { "Off", "FPS", "FPS + frame time + logic rate + audio" };
static const char *const k_backend[] = { "d3d11", "vulkan" };
static const char *const k_backend_l[] = { "Direct3D 11", "Vulkan" };
/* same order as rg_scale_mode (src/host/host.h) */
static const char *const k_scale[] = { "linear", "nearest", "integer", "stretch" };
static const char *const k_scale_l[] = { "Smooth (bilinear)", "Sharp (nearest)", "Integer + smooth", "Stretch to window" };
static const char *const k_frame_rate[] = { "original", "30", "60", "120", "144", "uncapped" };
static const char *const k_frame_rate_l[] = { "Original (30/60)", "30 fps", "60 fps", "120 fps", "144 fps", "Uncapped" };
/* display.pacing (docs/NATIVE-THREADS.md "Paced mode") */
static const char *const k_pacing[] = { "retail", "host" };
static const char *const k_pacing_l[] = { "Retail (one frame per VBlank)", "Host clock (fixed-step logic)" };
static const char *const k_res[] = { "native", "2x", "3x", "4x", "5x", "6x", "7x", "8x", "window" };
static const char *const k_res_l[] = { "Native (640x448)", "2x", "3x", "4x", "5x", "6x", "7x", "8x", "Match window" };
/* rg_aspect.h order (docs/WIDESCREEN.md "Stage 1") */
static const char *const k_aspect[] = { "4:3", "16:9", "16:10", "21:9", "auto" };
static const char *const k_aspect_l[] = { "4:3 (original)", "16:9", "16:10", "21:9 (ultrawide)",
                                          "Match the window" };
static const char *const k_movie_aspect[] = { "keep", "stretch" };
static const char *const k_movie_aspect_l[] = { "Keep 4:3 (pillarbox)", "Stretch to the screen" };
/* rg_layout.h RG_UI_LAYOUT_* (docs/WIDESCREEN.md "Stage 2") */
static const char *const k_ui_layout[] = { "keep", "stretch" };
static const char *const k_ui_layout_l[] = { "Keep proportions (anchored)", "Stretch (PS2 on a 16:9 TV)" };
/* MSAA is not offered: the renderer decides coverage in the pixel shader
 * (exact triangles, docs/GPU.md), so hardware multisampling would not see
 * the GS edges; supersampling through the internal resolution does */
static const char *const k_aa[] = { "off", "fxaa", "ssaa2", "ssaa3", "ssaa4" };
static const char *const k_aa_l[] = { "Off", "FXAA (post-process)", "SSAA 2x", "SSAA 3x", "SSAA 4x" };
static const char *const k_downsample[] = { "box", "bilinear", "bicubic", "lanczos" };
static const char *const k_downsample_l[] = { "Box (area average)", "Bilinear", "Bicubic (Mitchell)", "Lanczos-2" };
static const char *const k_aniso[] = { "off", "2x", "4x", "8x", "16x" };
static const char *const k_texfilter[] = { "original", "bilinear", "nearest" };
static const char *const k_texfilter_l[] = { "Original (GS)", "Force bilinear", "Force nearest" };
static const char *const k_effect[] = { "original", "enhanced", "off" };
static const char *const k_shadow[] = { "original", "2x", "4x" };
static const char *const k_output_filter[] = { "off", "scanlines", "crt" };
static const char *const k_output_filter_l[] = { "Off", "Scanlines", "CRT (scanlines + mask)" };
static const char *const k_text_speed[] = { "original", "fast", "instant" };

#define ORIG RG_SETF_HAS_ORIGINAL
#define PH RG_SETF_PLACEHOLDER
#define DISP RG_SETF_DISPLAY
#define RS RG_SETF_RESTART
#define GP RG_SETF_GAMEPLAY

static const rg_setting_def k_core[] = {
    /* ---------------------------------------------------------- display */
    { .id = "display.window_mode", .type = RG_SET_ENUM, .label = "Window mode",
      .help = "borderless covers the monitor at its desktop mode; exclusive switches to the mode closest to the window size",
      .flags = DISP | ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_window_mode, .enum_labels = k_window_mode_l, .enum_count = N(k_window_mode) },
    { .id = "display.width", .type = RG_SET_INT, .label = "Window width",
      .help = "client width in windowed mode", .flags = DISP,
      .def_i = 1280, .min_i = 320, .max_i = 16384, .step_i = 160 },
    { .id = "display.height", .type = RG_SET_INT, .label = "Window height",
      .help = "client height in windowed mode", .flags = DISP,
      .def_i = 960, .min_i = 224, .max_i = 16384, .step_i = 120 },
    { .id = "display.monitor", .type = RG_SET_INT, .label = "Monitor",
      .help = "0 = primary; the window and fullscreen modes use this display", .flags = DISP,
      .def_i = 0, .min_i = 0, .max_i = 15, .step_i = 1 },
    { .id = "display.scale", .type = RG_SET_ENUM, .label = "Scaling",
      .help = "how the 4:3 frame fills the window", .flags = DISP | ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_scale, .enum_labels = k_scale_l, .enum_count = N(k_scale) },
    { .id = "display.vsync", .type = RG_SET_BOOL, .label = "VSync",
      .help = "off: the pacer owns timing; with host-clock pacing, on = presents wait for the display (logic stays 59.94 Hz)",
      .flags = DISP | ORIG, .def_i = 0, .orig_i = 0 },
    { .id = "display.pacing", .type = RG_SET_ENUM, .label = "Frame pacing",
      .help = "retail: one present per VBlank, the virtual clock slept to wall time; host clock: the logic's VBlank phases follow host time (a bounded fixed-step accumulator) and presents follow the frame cap / VSync",
      .flags = ORIG, .def_i = 1, .orig_i = 0,
      .enum_names = k_pacing, .enum_labels = k_pacing_l, .enum_count = N(k_pacing) },
    { .id = "display.frame_rate", .type = RG_SET_ENUM, .label = "Frame rate cap",
      .help = "caps presentation only; game logic keeps the virtual clock (host-clock pacing: presents follow the cap; without display.interpolation at most one per VBlank phase)",
      .flags = ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_frame_rate, .enum_labels = k_frame_rate_l, .enum_count = N(k_frame_rate) },
    { .id = "display.interpolation", .type = RG_SET_BOOL, .label = "Unlocked frame rate (interpolation)",
      .help = "presents in-between images: models and camera interpolated between the last two game frames (one frame of delay), 2D and effects shown as the latest frame; logic keeps its retail cadence. Above 60 fps with host-clock pacing and a frame cap of 120 / 144 / uncapped (docs/NATIVE-RENDER.md \"Interpolated presentation\")",
      .flags = ORIG, .def_i = 0, .orig_i = 0 },
    { .id = "display.fps_counter", .type = RG_SET_ENUM, .label = "FPS counter",
      .help = "corner text drawn by the window at present time (not part of the game picture: screenshots, captures and run hashes leave it out). FPS = presents per second; detailed adds the frame time (mean / max over the last half second), the game-logic rate and audio starves (a stalled sound queue)",
      .flags = ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_fps, .enum_labels = k_fps_l, .enum_count = N(k_fps) },
    { .id = "display.backend", .type = RG_SET_ENUM, .label = "Graphics API",
      .help = "the renderer's graphics API (docs/NATIVE-VULKAN.md); Vulkan falls back to Direct3D 11 when no Vulkan 1.3 device is found. $RG_GPU_API overrides it",
      .flags = RS | ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_backend, .enum_labels = k_backend_l, .enum_count = N(k_backend) },

    /* ---------------------------------------------------------- graphics (P6) */
    { .id = "graphics.internal_res", .type = RG_SET_ENUM, .label = "Internal resolution",
      .help = "GPU renderer only; applied live (render targets reload from local memory)",
      .flags = ORIG, .def_i = 8, .orig_i = 0,
      .enum_names = k_res, .enum_labels = k_res_l, .enum_count = N(k_res) },
    { .id = "graphics.aspect", .type = RG_SET_ENUM, .label = "Aspect ratio",
      .help = "wide aspects use the game's own widescreen mode, widened to any shape (wider view; the 2D keeps its shapes, see Wide-screen UI); the title is shown 4:3",
      .flags = DISP | ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_aspect, .enum_labels = k_aspect_l, .enum_count = N(k_aspect) },
    { .id = "graphics.movie_aspect", .type = RG_SET_ENUM, .label = "Movie aspect",
      .help = "with a wide aspect: movies pillarboxed at 4:3, or stretched (the PS2 on a 16:9 TV)",
      .flags = ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_movie_aspect, .enum_labels = k_movie_aspect_l, .enum_count = N(k_movie_aspect) },
    { .id = "graphics.ui_layout", .type = RG_SET_ENUM, .label = "Wide-screen UI",
      .help = "with a wide aspect: menus, text and HUD keep their 4:3 shapes, scaled by height and anchored to the left / centre / right, or stretch with the picture (the PS2 on a 16:9 TV)",
      .flags = ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_ui_layout, .enum_labels = k_ui_layout_l, .enum_count = N(k_ui_layout) },
    { .id = "graphics.antialiasing", .type = RG_SET_ENUM, .label = "Anti-aliasing",
      .help = "SSAA renders at N x the internal resolution and filters down; FXAA is a post-process edge blend",
      .flags = ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_aa, .enum_labels = k_aa_l, .enum_count = N(k_aa) },
    { .id = "graphics.downsample", .type = RG_SET_ENUM, .label = "Downsampling filter",
      .help = "for SSAA and whenever the image is larger than the window",
      .flags = ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_downsample, .enum_labels = k_downsample_l, .enum_count = N(k_downsample) },
    { .id = "graphics.anisotropic", .type = RG_SET_ENUM, .label = "Anisotropic filtering",
      .help = "3D textures the GS filters bilinearly, on exact-triangle GPUs",
      .flags = ORIG, .def_i = 4, .orig_i = 0, .enum_names = k_aniso, .enum_count = N(k_aniso) },
    { .id = "graphics.texture_filter", .type = RG_SET_ENUM, .label = "Texture filtering",
      .help = "3D textures from ordinary memory; 2D sprites and screen effects keep the GS filter",
      .flags = ORIG, .def_i = 1, .orig_i = 0,   /* USER 10-18: low-res weapons/faces at scale > 1 */
      .enum_names = k_texfilter, .enum_labels = k_texfilter_l, .enum_count = N(k_texfilter) },
    { .id = "graphics.bloom", .type = RG_SET_ENUM, .label = "Bloom",
      .help = "planned: needs the game's effect passes identified (docs/GPU.md \"Screen effects\")",
      .flags = PH | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_effect, .enum_count = N(k_effect) },
    { .id = "graphics.depth_of_field", .type = RG_SET_ENUM, .label = "Depth of field",
      .help = "planned: needs the game's effect passes identified (docs/GPU.md \"Screen effects\")",
      .flags = PH | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_effect, .enum_count = N(k_effect) },
    { .id = "graphics.motion_blur", .type = RG_SET_ENUM, .label = "Motion blur",
      .help = "planned: needs the game's effect passes identified (docs/GPU.md \"Screen effects\")",
      .flags = PH | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_effect, .enum_count = N(k_effect) },
    { .id = "graphics.lod_bias", .type = RG_SET_FLOAT, .label = "Draw distance / LOD bias",
      .flags = PH | ORIG, .def_f = 0.0, .orig_f = 0.0, .min_f = -2.0, .max_f = 2.0, .step_f = 0.25 },
    { .id = "graphics.shadow_res", .type = RG_SET_ENUM, .label = "Shadow resolution",
      .flags = PH | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_shadow, .enum_count = N(k_shadow) },
    { .id = "graphics.gamma", .type = RG_SET_FLOAT, .label = "Gamma",
      .help = "above 1 brightens mid-tones (output only)",
      .flags = ORIG, .def_f = 1.0, .orig_f = 1.0, .min_f = 0.5, .max_f = 2.0, .step_f = 0.05 },
    { .id = "graphics.brightness", .type = RG_SET_FLOAT, .label = "Brightness",
      .help = "output multiplier", .flags = ORIG, .def_f = 1.0, .orig_f = 1.0, .min_f = 0.5, .max_f = 1.5,
      .step_f = 0.05 },
    { .id = "graphics.sharpen", .type = RG_SET_FLOAT, .label = "Sharpening",
      .help = "contrast-adaptive, after anti-aliasing",
      .flags = ORIG, .def_f = 0.0, .orig_f = 0.0, .min_f = 0.0, .max_f = 1.0, .step_f = 0.1 },
    { .id = "graphics.output_filter", .type = RG_SET_ENUM, .label = "Output filter",
      .help = "applied at the window resolution", .flags = ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_output_filter, .enum_labels = k_output_filter_l, .enum_count = N(k_output_filter) },

    /* ---------------------------------------------------------- audio */
    { .id = "audio.enabled", .type = RG_SET_BOOL, .label = "Sound",
      .help = "open the audio device", .flags = RS | ORIG, .def_i = 1, .orig_i = 1 },
    { .id = "audio.master_volume", .type = RG_SET_INT, .label = "Master volume",
      .help = "percent", .flags = ORIG, .def_i = 100, .orig_i = 100, .min_i = 0, .max_i = 100, .step_i = 5 },
    { .id = "audio.latency_ms", .type = RG_SET_INT, .label = "Audio buffer (ms)",
      .help = "output queue target; raise it if sound crackles, 0 = off", .def_i = 64,
      .min_i = 0, .max_i = 500, .step_i = 8 },
    /* per-source volumes: the engine's presentation mix, after the run hash point
     * (src/native/audio/ra_present.c, docs/NATIVE-AUDIO.md "Source volumes") */
    { .id = "audio.music_volume", .type = RG_SET_INT, .label = "Music volume",
      .help = "percent: BGM, jingles and sequenced music",
      .flags = ORIG, .def_i = 100, .orig_i = 100, .min_i = 0, .max_i = 100, .step_i = 5 },
    { .id = "audio.effects_volume", .type = RG_SET_INT, .label = "Effects volume",
      .help = "percent: everything the game plays from its sound-effect banks",
      .flags = ORIG, .def_i = 100, .orig_i = 100, .min_i = 0, .max_i = 100, .step_i = 5 },
    { .id = "audio.voice_volume", .type = RG_SET_INT, .label = "Voice volume",
      .help = "percent: streamed dialogue (event scenes, LiveTalk)",
      .flags = ORIG, .def_i = 100, .orig_i = 100, .min_i = 0, .max_i = 100, .step_i = 5 },
    { .id = "audio.movie_volume", .type = RG_SET_INT, .label = "Movie volume",
      .help = "percent: the sound of the full-motion videos",
      .flags = ORIG, .def_i = 100, .orig_i = 100, .min_i = 0, .max_i = 100, .step_i = 5 },
    /* host_sdl.c (focus events, device list / hot switch) */
    { .id = "audio.background", .type = RG_SET_BOOL, .label = "Play audio when unfocused",
      .help = "off mutes the sound while another window has the focus",
      .flags = ORIG, .def_i = 1, .orig_i = 1 },
    { .id = "audio.device", .type = RG_SET_STRING, .label = "Output device",
      .help = "left / right picks a device, empty = system default; a missing device falls back to the default",
      .def_s = "", .max_len = 255 },

    /* ---------------------------------------------------------- gameplay (labelled) */
    { .id = "gameplay.text_speed", .type = RG_SET_ENUM, .label = "Text speed",
      .flags = GP | PH | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_text_speed, .enum_count = N(k_text_speed) },
    { .id = "gameplay.skip_seen_movies", .type = RG_SET_BOOL, .label = "Allow skipping seen movies",
      .flags = PH | ORIG, .def_i = 1, .orig_i = 0 },

    /* ---------------------------------------------------------- system */
    { .id = "system.throttle", .type = RG_SET_BOOL, .label = "Real-time pacing",
      .help = "off runs as fast as possible (testing)", .flags = RS | ORIG | RG_SETF_HIDDEN,
      .def_i = 1, .orig_i = 1 },
    { .id = "system.screenshot_dir", .type = RG_SET_STRING, .label = "Screenshot folder",
      .help = "F12 writes rg-shot-NNNN.png here (applies at once)", .def_s = ".", .max_len = 511 },
};

int rg_settings_register_core(rg_settings *s)
{
    return rg_settings_register(s, k_core, N(k_core));
}

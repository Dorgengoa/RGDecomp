/* SPDX-License-Identifier: CC0-1.0 */
/* The P4 core settings: display, audio, system, and the planned graphics /
 * gameplay options as placeholders (PLAN.md P6 "Graphics settings").
 * docs/SETTINGS.md has the table.  Input settings are registered by the input
 * layer (src/host/rg_input.h, rg_actions_register_settings). */
#include "rg_settings.h"
#include "rg_display.h"

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
/* rg_display.h RG_FRAME_RATE_* order (rg_frame_cap_fps) */
static const char *const k_frame_rate[] = { "original", "30", "60", "120", "144", "165", "240", "display", "uncapped" };
static const char *const k_frame_rate_l[] = { "Original (30/60)", "30 fps", "60 fps", "120 fps", "144 fps", "165 fps",
                                              "240 fps", "Match the display refresh rate", "Uncapped" };
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
static const char *const k_flash[] = { "original", "reduced", "minimal" };
static const char *const k_cblind[] = { "off", "protanopia", "deuteranopia", "tritanopia" };
static const char *const k_cblind_l[] = { "Off", "Protanopia (red-weak)", "Deuteranopia (green-weak)",
                                          "Tritanopia (blue-weak)" };
static const char *const k_shadow[] = { "original", "2x", "4x" };
static const char *const k_rt[] = { "off", "shadows", "shadows_ao", "shadows_ao_refl" };   /* (debug colours: $RG_RT=2, docs/RAYTRACING.md; shadows_ao = gpu_config 3, shadows_ao_refl = 4 (rt5)) */
static const char *const k_rt_l[] = { "Off", "Shadows", "Shadows + AO", "Shadows + AO + reflections" };
static const char *const k_rte[] = { "off", "on", "overlay" };   /* (rt8) gpu_config.rt_emissive 0 / 1 / 2 */
static const char *const k_rte_l[] = { "Off", "On", "On + debug overlay" };
static const char *const k_output_filter[] = { "off", "scanlines", "crt" };
static const char *const k_output_filter_l[] = { "Off", "Scanlines", "CRT (scanlines + mask)" };
static const char *const k_text_speed[] = { "original", "fast", "instant" };
static const char *const k_text_speed_l[] = { "Original", "Fast (2x)", "Instant (page at once)" };
static const char *const k_battle_speed[] = { "original", "1.5x", "2x", "3x" };
static const char *const k_battle_speed_l[] = { "Original (1x)", "1.5x", "2x", "3x" };

#define ORIG RG_SETF_HAS_ORIGINAL
#define PH RG_SETF_PLACEHOLDER
#define DISP RG_SETF_DISPLAY
#define RS RG_SETF_RESTART
#define GP RG_SETF_GAMEPLAY

static const rg_setting_def k_core[] = {
    /* ---------------------------------------------------------- display */
    { .id = "display.window_mode", .type = RG_SET_ENUM, .label = "Window mode",
      .help = "borderless covers the monitor at its desktop mode; exclusive switches the display to Exclusive mode (below)",
      .flags = DISP | ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_window_mode, .enum_labels = k_window_mode_l, .enum_count = N(k_window_mode) },
    { .id = "display.width", .type = RG_SET_INT, .label = "Window width",
      .help = "client width in windowed mode", .flags = DISP,
      .def_i = 1280, .min_i = 320, .max_i = 16384, .step_i = 160 },
    { .id = "display.height", .type = RG_SET_INT, .label = "Window height",
      .help = "client height in windowed mode", .flags = DISP,
      .def_i = 960, .min_i = 224, .max_i = 16384, .step_i = 120 },
    { .id = "display.monitor", .type = RG_SET_INT, .label = "Monitor",
      .help = "the display the window and fullscreen use (left / right steps through the connected displays; one that is not connected uses the primary)",
      .flags = DISP, .def_i = 0, .min_i = 0, .max_i = 15, .step_i = 1 },
    { .id = "display.fullscreen_mode", .type = RG_SET_STRING, .label = "Exclusive mode",
      .help = "resolution and refresh rate of exclusive fullscreen: left / right steps through the monitor's modes; empty = the mode closest to the window size at the desktop refresh rate (WIDTHxHEIGHT@HZ)",
      .flags = DISP, .def_s = "", .max_len = 31, .validate = rg_display_mode_validate },
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
      .help = "caps presentation only; game logic keeps the virtual clock (host-clock pacing: presents follow the cap; without display.interpolation at most one per VBlank phase). Match the display = the refresh rate of the window's display (exclusive: the chosen mode's)",
      .flags = ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_frame_rate, .enum_labels = k_frame_rate_l, .enum_count = N(k_frame_rate) },
    { .id = "display.interpolation", .type = RG_SET_BOOL, .label = "Unlocked frame rate (interpolation)",
      .help = "presents in-between images: models and camera interpolated between the last two game frames (one frame of delay), 2D and effects shown as the latest frame; logic keeps its retail cadence. Above 60 fps with host-clock pacing and a frame cap above 60 (120 ... 240, a faster display, uncapped) (docs/NATIVE-RENDER.md \"Interpolated presentation\")",
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
      .help = "3D textures filtered bilinearly (by the GS or the texture-filter override), sharper at grazing angles; 2D, sprites and screen effects keep the GS filter. Off = Original",
      .flags = ORIG, .def_i = 4, .orig_i = 0, .enum_names = k_aniso, .enum_count = N(k_aniso) },
    { .id = "graphics.texture_filter", .type = RG_SET_ENUM, .label = "Texture filtering",
      .help = "3D textures from ordinary memory; 2D sprites and screen effects keep the GS filter",
      .flags = ORIG, .def_i = 1, .orig_i = 0,   /* USER 10-18: low-res weapons/faces at scale > 1 */
      .enum_names = k_texfilter, .enum_labels = k_texfilter_l, .enum_count = N(k_texfilter) },
    { .id = "graphics.bloom", .type = RG_SET_ENUM, .label = "Bloom",
      .help = "the glow around bright areas (field glare, the treasure chests' glow): enhanced draws the glow's passes at the internal resolution instead of the PS2's 192x192 buffers (smooth, no blocky texels, the PS2's strength); off leaves the glow out. Drawing only",
      .flags = ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_effect, .enum_count = N(k_effect) },
    { .id = "graphics.depth_of_field", .type = RG_SET_ENUM, .label = "Depth of field",
      .help = "the blur of distant scenery (and the scenes' focus blur): enhanced makes the half-size blurred copy by averaging every pixel (smooth, no shimmer at high internal resolutions); off keeps everything sharp. Drawing only",
      .flags = ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_effect, .enum_count = N(k_effect) },
    { .id = "graphics.motion_blur", .type = RG_SET_ENUM, .label = "Motion blur",
      .help = "the afterimage trail the game draws behind fast-moving characters in some scenes (e.g. event fights): the game's buffer is already full size, so enhanced = original; off leaves the trail out (the battle aura of a charged weapon, drawn by the same pass, stays). Drawing only",
      .flags = ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_effect, .enum_count = N(k_effect) },
    { .id = "graphics.lod_bias", .type = RG_SET_FLOAT, .label = "Draw distance / LOD bias",
      .flags = PH | ORIG, .def_f = 0.0, .orig_f = 0.0, .min_f = -2.0, .max_f = 2.0, .step_f = 0.25 },
    { .id = "graphics.shadow_res", .type = RG_SET_ENUM, .label = "Shadow resolution",
      .flags = PH | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_shadow, .enum_count = N(k_shadow) },
    /* docs/RAYTRACING.md (RT2: shown in the menu, off by default); Vulkan + a ray-query capable
     * device only (x64 builds: the 32-bit NVIDIA driver exposes no ray tracing) */
    { .id = "graphics.raytracing", .type = RG_SET_ENUM, .label = "Ray tracing",
      .help = "ray-traced sun shadows of the map and the characters (leaves cut out, soft edges, filtered over frames), layered on the baked lighting; faded out indoors; + AO: ambient occlusion too (indoors and at night as well); + reflections: ray-traced reflections on the art's environment-mapped / reflective surfaces (spike). Needs display.backend=vulkan, the 64-bit exe and a ray-tracing GPU, else off. Drawing only. Off = Original",
      .flags = RS | ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_rt, .enum_labels = k_rt_l, .enum_count = N(k_rt) },
    /* (rt8) docs/RAYTRACING.md "RT8": a sub-option of ray tracing (any value but off) */
    { .id = "graphics.rt_emissive", .type = RG_SET_ENUM, .label = "Ray-traced emissive light",
      .help = "lamps, screens, crystals, lava and glowing signs the art paints bright light the surfaces around them (ray-traced, with shadows); overlay: the surfaces taken as emitters drawn magenta. Needs ray tracing on. Drawing only. Off = Original",
      .flags = RS | ORIG, .def_i = 0, .orig_i = 0,
      .enum_names = k_rte, .enum_labels = k_rte_l, .enum_count = N(k_rte) },
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
    /* docs/TEXTURES.md (lane hdtex): HD texture packs in the PCSX2 layout and naming */
    { .id = "graphics.texture_replace", .type = RG_SET_BOOL, .label = "HD texture pack",
      .help = "draws the textures of a pack in textures/SCUS-97490/replacements beside the exe (PCSX2 texture-pack names, PNG / DDS, any size) instead of the game's own; loaded in the background, the original shows until a file is ready. Drawing only. Off = Original",
      .flags = ORIG, .def_i = 0, .orig_i = 0 },
    { .id = "graphics.texture_dump", .type = RG_SET_BOOL, .label = "Dump textures",
      .help = "for pack makers: writes every texture the first time it is drawn as a PNG in textures/SCUS-97490/dumps (the names a pack uses). Drawing only. Off = Original",
      .flags = ORIG, .def_i = 0, .orig_i = 0 },
    { .id = "graphics.texture_dump_movies", .type = RG_SET_BOOL, .label = "Dump movie frames",
      .help = "with Dump textures: also writes the frames of the movies (off: skipped, as PCSX2 does; hundreds of MB that no pack can replace). Drawing only. Off = Original",
      .flags = ORIG, .def_i = 0, .orig_i = 0 },

    /* ---------------------------------------------------------- accessibility (P6) */
    /* presentation only (the run hash and audio hash hold: docs/SETTINGS.md "Accessibility") */
    { .id = "accessibility.ui_scale", .type = RG_SET_INT, .label = "UI / text scale",
      .help = "percent: in-field windows, message text and subtitles, the HUD and on-screen labels grow or shrink about their corner / edge / centre (each kept on the screen), at 4:3 and on wide screens; full-screen menus fill the height already and keep their size. 100 = Original",
      .flags = ORIG, .def_i = 100, .orig_i = 100, .min_i = 75, .max_i = 150, .step_i = 5 },
    { .id = "accessibility.camera_shake", .type = RG_SET_INT, .label = "Camera shake",
      .help = "percent of the game's screen shake (quakes, hits, explosions) shown; the game's own camera is unchanged (drawing only). 100 = Original, 0 = none",
      .flags = ORIG, .def_i = 100, .orig_i = 100, .min_i = 0, .max_i = 100, .step_i = 25 },
    { .id = "accessibility.flashing", .type = RG_SET_ENUM, .label = "Reduced flashing",
      .help = "bright flashes kept dimmer and brought in gradually: fades to white or a bright colour, full-screen effect flashes, and the total light of an effect's many smaller bursts and glows in one frame: reduced = at most about a quarter of the screen's full white, minimal = faint. Fades to black are unchanged. Drawing only",
      .flags = ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_flash, .enum_count = N(k_flash) },
    { .id = "accessibility.colour_blind", .type = RG_SET_ENUM, .label = "Colour-blind markers",
      .help = "markers told apart by colour alone get colours that stay distinct for this kind of colour vision: the stat-change digits (green up / red down) and the stat-arrow icons; the rest of the picture is unchanged. Drawing only",
      .flags = ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_cblind, .enum_labels = k_cblind_l,
      .enum_count = N(k_cblind) },

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

    /* ---------------------------------------------------------- saves (docs/SAVES.md section 3) */
    { .id = "saves.dir", .type = RG_SET_STRING, .label = "Saves folder",
      .help = "where the memory cards (card1, card2) and their backups live; empty = the saves folder beside the game. --saves and $RG_SAVES take precedence",
      .flags = RS, .def_s = "", .max_len = 511 },
    { .id = "saves.backup_keep", .type = RG_SET_INT, .label = "Save backups kept",
      .help = "snapshots of a card kept before each overwrite (saves/backups); 0 = none",
      .flags = RS, .def_i = 5, .min_i = 0, .max_i = 50, .step_i = 1 },

    /* ---------------------------------------------------------- gameplay (labelled) */
    { .id = "gameplay.text_speed", .type = RG_SET_ENUM, .label = "Text speed",
      .help = "how fast message windows type their text out: fast = twice the game's speed, instant = each page (up to the game's own pauses) at once. Changes the pacing of scenes and dialogue, so it is a gameplay option: Original = the game's speed",
      .flags = GP | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_text_speed, .enum_labels = k_text_speed_l,
      .enum_count = N(k_text_speed) },
    { .id = "gameplay.battle_speed", .type = RG_SET_ENUM, .label = "Battle speed",
      .help = "runs battles faster while the fight is on (not in battle menus, tutorials, event scenes, the results or movies): the whole game clock runs this many times as fast, so every frame of the fight is the same as at 1x, only sooner; sound keeps its pitch (tempo follows). Changes the pacing of battles, so it is a gameplay option: Original = 1x. Needs a PC fast enough to run the game at that multiple",
      .flags = GP | ORIG, .def_i = 0, .orig_i = 0, .enum_names = k_battle_speed, .enum_labels = k_battle_speed_l,
      .enum_count = N(k_battle_speed) },
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

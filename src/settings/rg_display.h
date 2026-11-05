/* SPDX-License-Identifier: CC0-1.0 */
/* Display-setting helpers shared by the registry, the host and the runtime
 * (pure C, no SDL; docs/SETTINGS.md "Display"): the exclusive-fullscreen mode
 * text of display.fullscreen_mode, the display.monitor index policy and the
 * display.frame_rate cap. */
#ifndef RG_DISPLAY_H
#define RG_DISPLAY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* display.fullscreen_mode text: "" (automatic: the mode closest to the window
 * size at the desktop refresh rate), "WxH" (that size, the desktop refresh
 * rate or the closest) or "WxH@HZ" (HZ may have decimals, e.g. 59.94).
 * Returns 1 and fills w / h / hz (0 = any) for a mode, 0 for "", -1 invalid. */
int rg_display_mode_parse(const char *text, int *w, int *h, double *hz);
/* The canonical text: "WxH@HZ" (HZ with up to 2 decimals, trailing zeros
 * dropped), "WxH" when hz <= 0. */
void rg_display_mode_format(int w, int h, double hz, char *out, size_t cap);
/* rg_setting_validate_fn for display.fullscreen_mode (normalises the text). */
int rg_display_mode_validate(const char *text, char *norm, size_t normcap, char *err, size_t errcap, void *user);

/* display.monitor: the display index used for a wanted index when n displays
 * are connected: the wanted one when present, else 0 (the primary). */
int rg_display_monitor_index(int want, int n);

/* display.frame_rate values (rg_settings_core.c k_frame_rate order). */
enum {
    RG_FRAME_RATE_ORIGINAL = 0, RG_FRAME_RATE_30, RG_FRAME_RATE_60, RG_FRAME_RATE_120, RG_FRAME_RATE_144,
    RG_FRAME_RATE_165, RG_FRAME_RATE_240, RG_FRAME_RATE_DISPLAY, RG_FRAME_RATE_UNCAPPED, RG_FRAME_RATE_COUNT
};
/* The presentation cap in frames per second for a display.frame_rate value
 * (0 = none: Original and Uncapped).  "Match the display" rounds display_hz
 * (the refresh rate of the window's display, 59.94 -> 60); unknown (<= 0,
 * headless) counts as 60. */
int rg_frame_cap_fps(int frame_rate, double display_hz);

#ifdef __cplusplus
}
#endif

#endif

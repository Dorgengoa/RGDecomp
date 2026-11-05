/* SPDX-License-Identifier: CC0-1.0 */
/* Display-setting helpers (rg_display.h). */
#include "rg_display.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rg_display_mode_parse(const char *t, int *w, int *h, double *hz)
{
    int W = 0, H = 0;
    double Z = 0.0;
    if (w) *w = 0;
    if (h) *h = 0;
    if (hz) *hz = 0.0;
    if (!t) return 0;
    while (*t == ' ') t++;
    if (!*t) return 0;
    char *e;
    long a = strtol(t, &e, 10);
    if (e == t || (*e != 'x' && *e != 'X') || a < 320 || a > 16384) return -1;
    const char *p = e + 1;
    long b = strtol(p, &e, 10);
    if (e == p || b < 200 || b > 16384) return -1;
    W = (int)a;
    H = (int)b;
    if (*e == '@') {
        p = e + 1;
        Z = strtod(p, &e);
        if (e == p || Z < 1.0 || Z > 1000.0) return -1;
    }
    while (*e == ' ') e++;
    if (*e) return -1;
    if (w) *w = W;
    if (h) *h = H;
    if (hz) *hz = Z;
    return 1;
}

void rg_display_mode_format(int w, int h, double hz, char *out, size_t cap)
{
    if (!out || !cap) return;
    if (hz <= 0.0) { snprintf(out, cap, "%dx%d", w, h); return; }
    char z[32];
    snprintf(z, sizeof z, "%.2f", hz);
    size_t n = strlen(z);
    while (n > 0 && z[n - 1] == '0') z[--n] = 0;
    if (n > 0 && z[n - 1] == '.') z[--n] = 0;
    snprintf(out, cap, "%dx%d@%s", w, h, z);
}

int rg_display_mode_validate(const char *text, char *norm, size_t normcap, char *err, size_t errcap, void *user)
{
    (void)user;
    int w, h;
    double hz;
    int r = rg_display_mode_parse(text, &w, &h, &hz);
    if (r < 0) {
        if (err && errcap) snprintf(err, errcap, "expected WIDTHxHEIGHT or WIDTHxHEIGHT@HZ (e.g. 2560x1440@165), or empty");
        return -1;
    }
    if (norm && normcap) {
        if (r == 0) norm[0] = 0;
        else rg_display_mode_format(w, h, hz, norm, normcap);
    }
    return 0;
}

int rg_display_monitor_index(int want, int n)
{
    if (n <= 0 || want < 0 || want >= n) return 0;
    return want;
}

int rg_frame_cap_fps(int v, double display_hz)
{
    switch (v) {
    case RG_FRAME_RATE_30: return 30;
    case RG_FRAME_RATE_60: return 60;
    case RG_FRAME_RATE_120: return 120;
    case RG_FRAME_RATE_144: return 144;
    case RG_FRAME_RATE_165: return 165;
    case RG_FRAME_RATE_240: return 240;
    case RG_FRAME_RATE_DISPLAY: {
        if (display_hz <= 0.0) return 60;
        int f = (int)(display_hz + 0.5);
        return f < 24 ? 24 : (f > 1000 ? 1000 : f);
    }
    default: return 0;   /* original, uncapped */
    }
}

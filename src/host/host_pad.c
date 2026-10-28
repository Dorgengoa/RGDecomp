/* SPDX-License-Identifier: CC0-1.0 */
/* DS2 pad report, input names, the remappable keyboard/gamepad map and its
 * config text.  Pure: no SDL_Init needed (only SDL's name tables). */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "host_internal.h"

static const char *const k_names[RG_IN_COUNT] = {
    "L2", "R2", "L1", "R1", "TRIANGLE", "CIRCLE", "CROSS", "SQUARE",
    "SELECT", "L3", "R3", "START", "UP", "RIGHT", "DOWN", "LEFT",
    "LX-", "LX+", "LY-", "LY+", "RX-", "RX+", "RY-", "RY+"
};

/* bit number of the button feeding each pressure byte */
static const int k_prs_bit[RG_PRS_COUNT] = {
    13 /*RIGHT*/, 15 /*LEFT*/, 12 /*UP*/, 14 /*DOWN*/, 4 /*TRIANGLE*/,
    5 /*CIRCLE*/, 6 /*CROSS*/, 7 /*SQUARE*/, 2 /*L1*/, 3 /*R1*/, 0 /*L2*/, 1 /*R2*/
};

char *rgh_read_file(const char *path, size_t *len)
{
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    size_t cap = 4096, n = 0;
    char *buf = (char *)malloc(cap + 1);
    for (;;) {
        if (!buf) { fclose(f); return NULL; }
        size_t r = fread(buf + n, 1, cap - n, f);
        n += r;
        if (n < cap) break;
        cap *= 2;
        char *nb = (char *)realloc(buf, cap + 1);
        if (!nb) { free(buf); fclose(f); return NULL; }
        buf = nb;
    }
    int bad = ferror(f);
    fclose(f);
    if (bad) { free(buf); return NULL; }
    buf[n] = 0;
    if (len) *len = n;
    return buf;
}

const char *rg_input_name(int i)
{
    return (i >= 0 && i < RG_IN_COUNT) ? k_names[i] : NULL;
}

int rg_input_from_name(const char *name)
{
    for (int i = 0; i < RG_IN_COUNT; i++)
        if (SDL_strcasecmp(name, k_names[i]) == 0) return i;
    return -1;
}

void rg_pad_neutral(rg_pad *p)
{
    memset(p, 0, sizeof *p);
    p->lx = p->ly = p->rx = p->ry = 0x80;
}

void rg_pad_fill_pressure(rg_pad *p)
{
    for (int i = 0; i < RG_PRS_COUNT; i++)
        p->pressure[i] = (p->buttons >> k_prs_bit[i]) & 1 ? 255 : 0;
}

int rg_pad_ds2_report(const rg_pad *p, uint8_t out[RG_DS2_REPORT_BYTES])
{
    uint16_t raw = (uint16_t)~p->buttons;
    out[0] = 0x00;
    out[1] = 0x79;
    out[2] = (uint8_t)(raw >> 8);
    out[3] = (uint8_t)raw;
    out[4] = p->rx;
    out[5] = p->ry;
    out[6] = p->lx;
    out[7] = p->ly;
    memcpy(out + 8, p->pressure, RG_PRS_COUNT);
    return RG_DS2_REPORT_BYTES;
}

/* ------------------------------------------------------------------ map */
static void map_clear(rg_input_map *m, int i)
{
    for (int s = 0; s < RG_MAP_SLOTS; s++) {
        m->key[i][s] = 0;
        m->pad_button[i][s] = -1;
        m->pad_axis[i][s] = -1;
    }
}

static int add_key(rg_input_map *m, int i, int sc)
{
    for (int s = 0; s < RG_MAP_SLOTS; s++)
        if (!m->key[i][s]) { m->key[i][s] = (uint16_t)sc; return 0; }
    return -1;
}
static int add_btn(rg_input_map *m, int i, int b)
{
    for (int s = 0; s < RG_MAP_SLOTS; s++)
        if (m->pad_button[i][s] < 0) { m->pad_button[i][s] = (int8_t)b; return 0; }
    return -1;
}
static int add_axis(rg_input_map *m, int i, int axis, int pos)
{
    for (int s = 0; s < RG_MAP_SLOTS; s++)
        if (m->pad_axis[i][s] < 0) { m->pad_axis[i][s] = (int8_t)(axis * 2 + (pos ? 1 : 0)); return 0; }
    return -1;
}

void rg_input_map_default(rg_input_map *m)
{
    memset(m, 0, sizeof *m);
    for (int i = 0; i < RG_IN_COUNT; i++) map_clear(m, i);
    m->deadzone = 8000;
    m->threshold = 12000;
#define B(name) (__builtin_ctz(RG_BTN_##name))
    /* keyboard */
    add_key(m, B(CROSS), SDL_SCANCODE_X);
    add_key(m, B(CIRCLE), SDL_SCANCODE_C);
    add_key(m, B(SQUARE), SDL_SCANCODE_Z);
    add_key(m, B(TRIANGLE), SDL_SCANCODE_S);
    add_key(m, B(L1), SDL_SCANCODE_Q);
    add_key(m, B(R1), SDL_SCANCODE_E);
    add_key(m, B(L2), SDL_SCANCODE_1);
    add_key(m, B(R2), SDL_SCANCODE_3);
    add_key(m, B(L3), SDL_SCANCODE_V);
    add_key(m, B(R3), SDL_SCANCODE_B);
    add_key(m, B(START), SDL_SCANCODE_RETURN);
    add_key(m, B(SELECT), SDL_SCANCODE_BACKSPACE);
    add_key(m, B(UP), SDL_SCANCODE_UP);
    add_key(m, B(DOWN), SDL_SCANCODE_DOWN);
    add_key(m, B(LEFT), SDL_SCANCODE_LEFT);
    add_key(m, B(RIGHT), SDL_SCANCODE_RIGHT);
    add_key(m, RG_IN_LX_NEG, SDL_SCANCODE_A);
    add_key(m, RG_IN_LX_POS, SDL_SCANCODE_D);
    add_key(m, RG_IN_LY_NEG, SDL_SCANCODE_W);
    add_key(m, RG_IN_LY_POS, SDL_SCANCODE_F);
    add_key(m, RG_IN_RX_NEG, SDL_SCANCODE_J);
    add_key(m, RG_IN_RX_POS, SDL_SCANCODE_L);
    add_key(m, RG_IN_RY_NEG, SDL_SCANCODE_I);
    add_key(m, RG_IN_RY_POS, SDL_SCANCODE_K);
    /* gamepad (SDL positional layout: SOUTH = DS2 cross) */
    add_btn(m, B(CROSS), SDL_GAMEPAD_BUTTON_SOUTH);
    add_btn(m, B(CIRCLE), SDL_GAMEPAD_BUTTON_EAST);
    add_btn(m, B(SQUARE), SDL_GAMEPAD_BUTTON_WEST);
    add_btn(m, B(TRIANGLE), SDL_GAMEPAD_BUTTON_NORTH);
    add_btn(m, B(L1), SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
    add_btn(m, B(R1), SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);
    add_axis(m, B(L2), SDL_GAMEPAD_AXIS_LEFT_TRIGGER, 1);
    add_axis(m, B(R2), SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, 1);
    add_btn(m, B(L3), SDL_GAMEPAD_BUTTON_LEFT_STICK);
    add_btn(m, B(R3), SDL_GAMEPAD_BUTTON_RIGHT_STICK);
    add_btn(m, B(START), SDL_GAMEPAD_BUTTON_START);
    add_btn(m, B(SELECT), SDL_GAMEPAD_BUTTON_BACK);
    add_btn(m, B(UP), SDL_GAMEPAD_BUTTON_DPAD_UP);
    add_btn(m, B(DOWN), SDL_GAMEPAD_BUTTON_DPAD_DOWN);
    add_btn(m, B(LEFT), SDL_GAMEPAD_BUTTON_DPAD_LEFT);
    add_btn(m, B(RIGHT), SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    add_axis(m, RG_IN_LX_NEG, SDL_GAMEPAD_AXIS_LEFTX, 0);
    add_axis(m, RG_IN_LX_POS, SDL_GAMEPAD_AXIS_LEFTX, 1);
    add_axis(m, RG_IN_LY_NEG, SDL_GAMEPAD_AXIS_LEFTY, 0);
    add_axis(m, RG_IN_LY_POS, SDL_GAMEPAD_AXIS_LEFTY, 1);
    add_axis(m, RG_IN_RX_NEG, SDL_GAMEPAD_AXIS_RIGHTX, 0);
    add_axis(m, RG_IN_RX_POS, SDL_GAMEPAD_AXIS_RIGHTX, 1);
    add_axis(m, RG_IN_RY_NEG, SDL_GAMEPAD_AXIS_RIGHTY, 0);
    add_axis(m, RG_IN_RY_POS, SDL_GAMEPAD_AXIS_RIGHTY, 1);
#undef B
}

static char *trim(char *s)
{
    while (*s && isspace((unsigned char)*s)) s++;
    char *e = s + strlen(s);
    while (e > s && isspace((unsigned char)e[-1])) *--e = 0;
    return s;
}

static int parse_uint(const char *s, int *out)
{
    char *end;
    long v = strtol(s, &end, 10);
    if (end == s || *trim(end) || v < 0 || v > 32767) return -1;
    *out = (int)v;
    return 0;
}

int rg_input_map_parse(rg_input_map *m, const char *text, char *err, size_t errcap)
{
    size_t n = strlen(text);
    char *buf = (char *)malloc(n + 1);
    if (!buf) { rgh_err(err, errcap, "out of memory"); return -1; }
    memcpy(buf, text, n + 1);
    int rc = 0, ln = 0;
    for (char *line = buf; line && !rc; ) {
        char *nl = strchr(line, '\n');
        if (nl) *nl = 0;
        ln++;
        char *hash = strchr(line, '#');
        if (hash) *hash = 0;
        char *t = trim(line);
        line = nl ? nl + 1 : NULL;
        if (!*t) continue;
        char *eq = strchr(t, '=');
        if (!eq) { rgh_err(err, errcap, "line %d: expected NAME = bindings", ln); rc = -1; break; }
        *eq = 0;
        char *lhs = trim(t), *rhs = trim(eq + 1);
        if (!SDL_strcasecmp(lhs, "deadzone") || !SDL_strcasecmp(lhs, "threshold")) {
            int v;
            if (parse_uint(rhs, &v)) { rgh_err(err, errcap, "line %d: %s wants 0..32767", ln, lhs); rc = -1; break; }
            if (!SDL_strcasecmp(lhs, "deadzone")) m->deadzone = v; else m->threshold = v;
            continue;
        }
        int in = rg_input_from_name(lhs);
        if (in < 0) { rgh_err(err, errcap, "line %d: unknown input '%s'", ln, lhs); rc = -1; break; }
        map_clear(m, in);
        char *save = rhs;
        while (save && *save) {
            char *comma = strchr(save, ',');
            if (comma) *comma = 0;
            char *b = trim(save);
            save = comma ? comma + 1 : NULL;
            if (!*b) continue;
            char *colon = strchr(b, ':');
            if (!colon) { rgh_err(err, errcap, "line %d: binding '%s' needs key:/pad:/axis:", ln, b); rc = -1; break; }
            *colon = 0;
            char *kind = trim(b), *val = trim(colon + 1);
            int r = -1;
            if (!SDL_strcasecmp(kind, "key")) {
                SDL_Scancode sc = SDL_GetScancodeFromName(val);
                if (sc == SDL_SCANCODE_UNKNOWN) { rgh_err(err, errcap, "line %d: unknown key '%s'", ln, val); rc = -1; break; }
                r = add_key(m, in, (int)sc);
            } else if (!SDL_strcasecmp(kind, "pad")) {
                SDL_GamepadButton gb = SDL_GetGamepadButtonFromString(val);
                if (gb == SDL_GAMEPAD_BUTTON_INVALID || (int)gb >= RG_GP_BUTTONS) {
                    rgh_err(err, errcap, "line %d: unknown gamepad button '%s'", ln, val); rc = -1; break;
                }
                r = add_btn(m, in, (int)gb);
            } else if (!SDL_strcasecmp(kind, "axis")) {
                size_t L = strlen(val);
                int pos = L ? (val[L - 1] == '+' ? 1 : val[L - 1] == '-' ? 0 : -1) : -1;
                if (pos < 0) { rgh_err(err, errcap, "line %d: axis '%s' needs a + or - suffix", ln, val); rc = -1; break; }
                val[L - 1] = 0;
                SDL_GamepadAxis ga = SDL_GetGamepadAxisFromString(trim(val));
                if (ga == SDL_GAMEPAD_AXIS_INVALID || (int)ga >= RG_GP_AXES) {
                    rgh_err(err, errcap, "line %d: unknown gamepad axis '%s'", ln, val); rc = -1; break;
                }
                r = add_axis(m, in, (int)ga, pos);
            } else {
                rgh_err(err, errcap, "line %d: unknown binding kind '%s'", ln, kind); rc = -1; break;
            }
            if (r) { rgh_err(err, errcap, "line %d: more than %d %s bindings for %s", ln, RG_MAP_SLOTS, kind, lhs); rc = -1; break; }
        }
    }
    free(buf);
    return rc;
}

int rg_input_map_load(rg_input_map *m, const char *path, char *err, size_t errcap)
{
    char *t = rgh_read_file(path, NULL);
    if (!t) { rgh_err(err, errcap, "%s: cannot read", path); return -1; }
    char e2[256] = "";
    int rc = rg_input_map_parse(m, t, e2, sizeof e2);
    if (rc) rgh_err(err, errcap, "%s: %s", path, e2);
    free(t);
    return rc;
}

typedef struct sbuf { char *p; size_t cap, len; } sbuf;
static void sb_put(sbuf *b, const char *fmt, ...)
{
    char tmp[256];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(tmp, sizeof tmp, fmt, ap);
    va_end(ap);
    if (n < 0) return;
    for (int i = 0; i < n && tmp[i]; i++) {
        if (b->cap && b->len + 1 < b->cap) b->p[b->len] = tmp[i];
        b->len++;
    }
    if (b->cap) b->p[b->len < b->cap ? b->len : b->cap - 1] = 0;
}

size_t rg_input_map_format(const rg_input_map *m, char *out, size_t cap)
{
    sbuf b = { out, cap, 0 };
    if (cap) out[0] = 0;
    sb_put(&b, "# rg-host input map (docs/HOST.md). INPUT = key:<name>, pad:<button>, axis:<axis>+/-\n");
    sb_put(&b, "deadzone = %d\nthreshold = %d\n", m->deadzone, m->threshold);
    for (int i = 0; i < RG_IN_COUNT; i++) {
        sb_put(&b, "%s =", k_names[i]);
        int first = 1;
        for (int s = 0; s < RG_MAP_SLOTS; s++) {
            if (!m->key[i][s]) continue;
            sb_put(&b, "%s key:%s", first ? "" : ",", SDL_GetScancodeName((SDL_Scancode)m->key[i][s]));
            first = 0;
        }
        for (int s = 0; s < RG_MAP_SLOTS; s++) {
            if (m->pad_button[i][s] < 0) continue;
            sb_put(&b, "%s pad:%s", first ? "" : ",",
                   SDL_GetGamepadStringForButton((SDL_GamepadButton)m->pad_button[i][s]));
            first = 0;
        }
        for (int s = 0; s < RG_MAP_SLOTS; s++) {
            int a = m->pad_axis[i][s];
            if (a < 0) continue;
            sb_put(&b, "%s axis:%s%c", first ? "" : ",",
                   SDL_GetGamepadStringForAxis((SDL_GamepadAxis)(a >> 1)), (a & 1) ? '+' : '-');
            first = 0;
        }
        sb_put(&b, "\n");
    }
    return b.len;
}

/* ----------------------------------------------------------------- eval */
static int axis_dir(int16_t v, int pos)
{
    int x = pos ? v : -(int)v;
    return x < 0 ? 0 : x > 32767 ? 32767 : x;
}

static int deadzoned(int mag, int dz)
{
    if (mag <= dz) return 0;
    if (dz >= 32767) return 0;
    return (int)((int64_t)(mag - dz) * 32767 / (32767 - dz));
}

void rg_input_eval(const rg_input_map *m, const bool *keys, int nkeys,
                   const rg_gamepad_snap *pads, int npads, rg_pad *out)
{
    int mag[RG_IN_COUNT];
    for (int i = 0; i < RG_IN_COUNT; i++) {
        int v = 0;
        for (int s = 0; s < RG_MAP_SLOTS; s++) {
            int k = m->key[i][s];
            if (k && keys && k < nkeys && keys[k]) v = 32767;
        }
        for (int p = 0; p < npads; p++) {
            for (int s = 0; s < RG_MAP_SLOTS; s++) {
                int b = m->pad_button[i][s];
                if (b >= 0 && b < RG_GP_BUTTONS && pads[p].button[b]) v = 32767;
                int a = m->pad_axis[i][s];
                if (a >= 0 && (a >> 1) < RG_GP_AXES) {
                    int d = axis_dir(pads[p].axis[a >> 1], a & 1);
                    if (i < 16) d = d >= m->threshold ? 32767 : 0;
                    else d = deadzoned(d, m->deadzone);
                    if (d > v) v = d;
                }
            }
        }
        mag[i] = v;
    }
    rg_pad_neutral(out);
    for (int i = 0; i < 16; i++)
        if (mag[i]) out->buttons |= (uint16_t)(1u << i);
    uint8_t *st[4] = { &out->lx, &out->ly, &out->rx, &out->ry };
    for (int k = 0; k < 4; k++) {
        int v = mag[RG_IN_LX_POS + 2 * k] - mag[RG_IN_LX_NEG + 2 * k];
        int o = 128 + v * 128 / 32767;
        *st[k] = (uint8_t)(o < 0 ? 0 : o > 255 ? 255 : o);
    }
    rg_pad_fill_pressure(out);
}

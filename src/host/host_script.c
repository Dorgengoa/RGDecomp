/* SPDX-License-Identifier: CC0-1.0 */
/* Deterministic input scripts: the tools/trace/input.py format, compiled to
 * the same table (parse_script + build_table), so a port run and a PCSX2
 * reference run see the same button word on the same game VBlank. */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "host_internal.h"

static const struct { const char *name; uint16_t bit; } k_buttons[] = {
    { "L2", RG_BTN_L2 }, { "R2", RG_BTN_R2 }, { "L1", RG_BTN_L1 }, { "R1", RG_BTN_R1 },
    { "TRIANGLE", RG_BTN_TRIANGLE }, { "CIRCLE", RG_BTN_CIRCLE },
    { "CROSS", RG_BTN_CROSS }, { "SQUARE", RG_BTN_SQUARE },
    { "SELECT", RG_BTN_SELECT }, { "L3", RG_BTN_L3 }, { "R3", RG_BTN_R3 },
    { "START", RG_BTN_START }, { "UP", RG_BTN_UP }, { "RIGHT", RG_BTN_RIGHT },
    { "DOWN", RG_BTN_DOWN }, { "LEFT", RG_BTN_LEFT },
};

/* Python int(s, 0) for non-negative values: 0x/0o/0b prefixes, decimal
 * without leading zeros (except all zeros), '_' between digits, optional '+'.
 * Negative values are rejected (input.py would index the table from its end). */
static int py_int0(const char *s, int64_t *out)
{
    if (*s == '+') s++;
    else if (*s == '-') return -2;
    int base = 10;
    if (s[0] == '0' && s[1]) {
        char c = (char)tolower((unsigned char)s[1]);
        if (c == 'x') base = 16; else if (c == 'o') base = 8; else if (c == 'b') base = 2;
        if (base != 10) {
            s += 2;
            if (*s == '_') s++;
        }
    }
    if (!*s) return -1;
    int64_t v = 0;
    int nd = 0, prev_us = 0, all_zero = 1;
    const char *first = s;
    for (; *s; s++) {
        if (*s == '_') {
            if (prev_us || nd == 0) return -1;
            prev_us = 1;
            continue;
        }
        int c = tolower((unsigned char)*s), d;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'a' && c <= 'z') d = c - 'a' + 10;
        else return -1;
        if (d >= base) return -1;
        if (d) all_zero = 0;
        if (v > (INT64_MAX - d) / base) return -1;
        v = v * base + d;
        nd++;
        prev_us = 0;
    }
    if (prev_us || nd == 0) return -1;
    if (base == 10 && first[0] == '0' && !all_zero) return -1;  /* "010" */
    *out = v;
    return 0;
}

static int parse_mask(const char *btn, uint16_t *mask, char *bad, size_t badcap)
{
    /* input.py: btn.upper().split("+"), each part must be a BUTTONS key */
    *mask = 0;
    const char *p = btn;
    for (;;) {
        const char *e = strchr(p, '+');
        size_t L = e ? (size_t)(e - p) : strlen(p);
        int found = 0;
        for (size_t i = 0; i < sizeof k_buttons / sizeof k_buttons[0]; i++) {
            if (strlen(k_buttons[i].name) == L) {
                size_t j = 0;
                while (j < L && toupper((unsigned char)p[j]) == k_buttons[i].name[j]) j++;
                if (j == L) { *mask |= k_buttons[i].bit; found = 1; break; }
            }
        }
        if (!found) {
            size_t n = L < badcap - 1 ? L : badcap - 1;
            for (size_t j = 0; j < n; j++) bad[j] = (char)toupper((unsigned char)p[j]);
            bad[n] = 0;
            return -1;
        }
        if (!e) return 0;
        p = e + 1;
    }
}

int rg_input_script_parse(rg_input_script *s, const char *text, const char *name,
                          char *err, size_t errcap)
{
    memset(s, 0, sizeof *s);
    if (!name) name = "<script>";
    typedef struct ev { uint32_t a, b; uint16_t m; } ev;
    ev *evs = NULL;
    size_t nev = 0, cap = 0;
    typedef struct lev { uint32_t a, b; int32_t yaw, pitch; int ln; } lev;
    lev *levs = NULL;
    size_t nlev = 0, lcap = 0;
    int look_on = 0;   /* "#!look 1 0" seen */
    typedef struct sev { uint32_t a, b; uint8_t v[4]; } sev;
    sev *sevs = NULL;
    size_t nsev = 0, scap = 0;
    int stick_on = 0;  /* "#!stick 1 0" seen */
    int rc = 0, ln = 0;
    int64_t maxb = -1;
    if ((unsigned char)text[0] == 0xEF && (unsigned char)text[1] == 0xBB &&
        (unsigned char)text[2] == 0xBF)
        text += 3;
    const char *p = text;
    while (*p && !rc) {
        const char *nl = strchr(p, '\n');
        size_t L = nl ? (size_t)(nl - p) : strlen(p);
        char line[512];
        ln++;
        if (L >= sizeof line) { rgh_err(err, errcap, "%s:%d: line too long", name, ln); rc = -1; break; }
        memcpy(line, p, L);
        line[L] = 0;
        p = nl ? nl + 1 : p + L;
        {   /* the look channel (docs/INPUT.md "Mouse camera implementation") */
            char *q = line;
            while (*q && isspace((unsigned char)*q)) q++;
            if (!strncmp(q, "#!look", 6) && (!q[6] || isspace((unsigned char)q[6]))) {
                char *h2 = strchr(q + 6, '#');
                if (h2) *h2 = 0;
                char *lt[5];
                int ln_n = 0;
                for (char *r = q + 6; *r && ln_n < 5; ) {
                    while (*r && isspace((unsigned char)*r)) r++;
                    if (!*r) break;
                    lt[ln_n++] = r;
                    while (*r && !isspace((unsigned char)*r)) r++;
                    if (*r) *r++ = 0;
                }
                long long v[4];
                int bad = ln_n < 2 || ln_n > 4;
                for (int i = 0; i < ln_n && !bad; i++) {
                    char *e;
                    v[i] = strtoll(lt[i], &e, 10);
                    if (e == lt[i] || *e) bad = 1;
                }
                if (bad) { rgh_err(err, errcap, "%s:%d: expected '#!look 1 0', '#!look VBL YAW PITCH' or '#!look FIRST LAST YAW PITCH'", name, ln); rc = -1; break; }
                if (ln_n == 2) {
                    if (look_on || v[0] != 1 || v[1] != 0) { rgh_err(err, errcap, "%s:%d: %s", name, ln, look_on ? "repeated '#!look' version line" : "unknown look channel version (want '#!look 1 0')"); rc = -1; break; }
                    look_on = 1;
                    continue;
                }
                if (!look_on) { rgh_err(err, errcap, "%s:%d: '#!look 1 0' must come before look lines", name, ln); rc = -1; break; }
                long long fa = v[0], fb = ln_n == 4 ? v[1] : v[0];
                long long yaw = v[ln_n - 2], pitch = v[ln_n - 1];
                if (fa < 0 || fb < fa || fb >= (long long)RG_SCRIPT_MAX_ENTRIES) { rgh_err(err, errcap, "%s:%d: bad look VBlank range", name, ln); rc = -1; break; }
                if (yaw < -RG_LOOK_MAX || yaw > RG_LOOK_MAX || pitch < -RG_LOOK_MAX || pitch > RG_LOOK_MAX) { rgh_err(err, errcap, "%s:%d: look value out of range (+-%d)", name, ln, RG_LOOK_MAX); rc = -1; break; }
                if (nlev == lcap) {
                    lcap = lcap ? lcap * 2 : 64;
                    lev *nl = (lev *)realloc(levs, lcap * sizeof *levs);
                    if (!nl) { rgh_err(err, errcap, "out of memory"); rc = -1; break; }
                    levs = nl;
                }
                levs[nlev].a = (uint32_t)fa;
                levs[nlev].b = (uint32_t)fb;
                levs[nlev].yaw = (int32_t)yaw;
                levs[nlev].pitch = (int32_t)pitch;
                levs[nlev].ln = ln;
                nlev++;
                continue;
            }
        }
        {   /* the stick channel (docs/INPUT.md "Scripted sticks") */
            char *q = line;
            while (*q && isspace((unsigned char)*q)) q++;
            if (!strncmp(q, "#!stick", 7) && (!q[7] || isspace((unsigned char)q[7]))) {
                char *h2 = strchr(q + 7, '#');
                if (h2) *h2 = 0;
                char *st[7];
                int sn = 0;
                for (char *r = q + 7; *r && sn < 7; ) {
                    while (*r && isspace((unsigned char)*r)) r++;
                    if (!*r) break;
                    st[sn++] = r;
                    while (*r && !isspace((unsigned char)*r)) r++;
                    if (*r) *r++ = 0;
                }
                long long v[6];
                int bad = !(sn == 2 || sn == 4 || sn == 6);
                for (int i = 0; i < sn && !bad; i++) {
                    char *e;
                    v[i] = strtoll(st[i], &e, 0);
                    if (e == st[i] || *e) bad = 1;
                }
                if (bad) { rgh_err(err, errcap, "%s:%d: expected '#!stick 1 0' or '#!stick FIRST LAST LX LY [RX RY]'", name, ln); rc = -1; break; }
                if (sn == 2) {
                    if (stick_on || v[0] != 1 || v[1] != 0) { rgh_err(err, errcap, "%s:%d: %s", name, ln, stick_on ? "repeated '#!stick' version line" : "unknown stick channel version (want '#!stick 1 0')"); rc = -1; break; }
                    stick_on = 1;
                    continue;
                }
                if (!stick_on) { rgh_err(err, errcap, "%s:%d: '#!stick 1 0' must come before stick lines", name, ln); rc = -1; break; }
                if (v[0] < 0 || v[1] < v[0] || v[1] >= (long long)RG_SCRIPT_MAX_ENTRIES) { rgh_err(err, errcap, "%s:%d: bad stick VBlank range", name, ln); rc = -1; break; }
                for (int i = 2; i < sn && !bad; i++)
                    if (v[i] < 0 || v[i] > 255) bad = 1;
                if (bad) { rgh_err(err, errcap, "%s:%d: stick value out of range (0..255)", name, ln); rc = -1; break; }
                if (nsev == scap) {
                    scap = scap ? scap * 2 : 64;
                    sev *ns = (sev *)realloc(sevs, scap * sizeof *sevs);
                    if (!ns) { rgh_err(err, errcap, "out of memory"); rc = -1; break; }
                    sevs = ns;
                }
                sevs[nsev].a = (uint32_t)v[0];
                sevs[nsev].b = (uint32_t)v[1];
                sevs[nsev].v[0] = (uint8_t)v[2];
                sevs[nsev].v[1] = (uint8_t)v[3];
                sevs[nsev].v[2] = sn == 6 ? (uint8_t)v[4] : 0x80;
                sevs[nsev].v[3] = sn == 6 ? (uint8_t)v[5] : 0x80;
                nsev++;
                continue;
            }
        }
        char *h = strchr(line, '#');
        if (h) *h = 0;
        char *tok[4];
        int nt = 0;
        for (char *q = line; *q && nt < 4; ) {
            while (*q && isspace((unsigned char)*q)) q++;
            if (!*q) break;
            tok[nt++] = q;
            while (*q && !isspace((unsigned char)*q)) q++;
            if (*q) *q++ = 0;
        }
        if (nt == 0) continue;
        if (nt == 1) { rgh_err(err, errcap, "%s:%d: expected 'first last BUTTONS' or 'vbl BUTTONS'", name, ln); rc = -1; break; }
        int64_t a, b;
        const char *btn;
        int r = py_int0(tok[0], &a);
        if (nt == 2) { b = a; btn = tok[1]; }
        else { if (!r) r = py_int0(tok[1], &b); btn = tok[2]; }
        if (r) {
            rgh_err(err, errcap, r == -2 ? "%s:%d: negative VBlank" : "%s:%d: bad integer", name, ln);
            rc = -1; break;
        }
        uint16_t mask;
        char bad[64];
        if (parse_mask(btn, &mask, bad, sizeof bad)) {
            rgh_err(err, errcap, "%s:%d: unknown button '%s'", name, ln, bad);
            rc = -1; break;
        }
        if (b > maxb) maxb = b;
        if (maxb + 1 > (int64_t)RG_SCRIPT_MAX_ENTRIES) {
            rgh_err(err, errcap, "input script too long (%lld vblanks, max %u)",
                    (long long)(maxb + 1), RG_SCRIPT_MAX_ENTRIES);
            rc = -1; break;
        }
        if (nev == cap) {
            cap = cap ? cap * 2 : 64;
            ev *ne = (ev *)realloc(evs, cap * sizeof *evs);
            if (!ne) { rgh_err(err, errcap, "out of memory"); rc = -1; break; }
            evs = ne;
        }
        evs[nev].a = (uint32_t)a;
        evs[nev].b = (uint32_t)b;
        evs[nev].m = mask;
        nev++;
    }
    if (!rc) {
        s->words = (uint16_t *)calloc(RG_SCRIPT_MAX_ENTRIES, sizeof(uint16_t));
        if (!s->words) { rgh_err(err, errcap, "out of memory"); rc = -1; }
    }
    if (!rc) {
        s->count = RG_SCRIPT_MAX_ENTRIES;
        s->span = (uint32_t)(maxb + 1);
        for (size_t i = 0; i < nev; i++)
            for (uint32_t v = evs[i].a; v <= evs[i].b; v++)   /* b < MAX: no wrap */
                s->words[v] |= evs[i].m;
    }
    if (!rc && look_on) {
        /* sum per VBlank (int32), check, narrow */
        int32_t *sum = (int32_t *)calloc(2 * (size_t)RG_SCRIPT_MAX_ENTRIES, sizeof(int32_t));
        s->look = (int16_t *)calloc(2 * (size_t)RG_SCRIPT_MAX_ENTRIES, sizeof(int16_t));
        if (!sum || !s->look) { rgh_err(err, errcap, "out of memory"); rc = -1; }
        for (size_t i = 0; !rc && i < nlev; i++)
            for (uint32_t v = levs[i].a; v <= levs[i].b; v++) {
                sum[2 * v] += levs[i].yaw;
                sum[2 * v + 1] += levs[i].pitch;
                if (sum[2 * v] < -RG_LOOK_MAX || sum[2 * v] > RG_LOOK_MAX ||
                    sum[2 * v + 1] < -RG_LOOK_MAX || sum[2 * v + 1] > RG_LOOK_MAX) {
                    rgh_err(err, errcap, "%s:%d: look sum at VBlank %u out of range (+-%d)", name, levs[i].ln, v, RG_LOOK_MAX);
                    rc = -1;
                    break;
                }
            }
        for (size_t i = 0; !rc && i < 2 * (size_t)RG_SCRIPT_MAX_ENTRIES; i++) s->look[i] = (int16_t)sum[i];
        free(sum);
    }
    if (!rc && stick_on) {
        s->stick = (uint8_t *)malloc(4 * (size_t)RG_SCRIPT_MAX_ENTRIES);
        if (!s->stick) { rgh_err(err, errcap, "out of memory"); rc = -1; }
        else {
            memset(s->stick, 0x80, 4 * (size_t)RG_SCRIPT_MAX_ENTRIES);
            for (size_t i = 0; i < nsev; i++)
                for (uint32_t v = sevs[i].a; v <= sevs[i].b; v++)
                    memcpy(s->stick + 4 * (size_t)v, sevs[i].v, 4);
        }
    }
    if (rc) rg_input_script_free(s);
    free(sevs);
    free(levs);
    free(evs);
    return rc;
}

int rg_input_script_load(rg_input_script *s, const char *path, char *err, size_t errcap)
{
    char *t = rgh_read_file(path, NULL);
    if (!t) {
        memset(s, 0, sizeof *s);
        rgh_err(err, errcap, "%s: cannot read", path);
        return -1;
    }
    int rc = rg_input_script_parse(s, t, path, err, errcap);
    free(t);
    return rc;
}

void rg_input_script_free(rg_input_script *s)
{
    free(s->words);
    free(s->look);
    free(s->stick);
    memset(s, 0, sizeof *s);
}

uint16_t rg_input_script_word(const rg_input_script *s, uint32_t vbl)
{
    return (s && s->words && vbl < s->count) ? s->words[vbl] : 0;
}

void rg_input_script_pad(const rg_input_script *s, uint32_t vbl, rg_pad *out)
{
    rg_pad_neutral(out);
    out->buttons = rg_input_script_word(s, vbl);
    if (s && s->stick && vbl < s->count) {
        const uint8_t *st = s->stick + 4 * (size_t)vbl;
        out->lx = st[0];
        out->ly = st[1];
        out->rx = st[2];
        out->ry = st[3];
    }
    rg_pad_fill_pressure(out);
}

size_t rg_input_script_blob(const rg_input_script *s, uint8_t *out, size_t cap)
{
    size_t need = 4 + 2 * (size_t)s->count;
    if (!out || cap < need) return need;
    out[0] = (uint8_t)s->count; out[1] = (uint8_t)(s->count >> 8);
    out[2] = (uint8_t)(s->count >> 16); out[3] = (uint8_t)(s->count >> 24);
    for (uint32_t i = 0; i < s->count; i++) {
        out[4 + 2 * i] = (uint8_t)s->words[i];
        out[5 + 2 * i] = (uint8_t)(s->words[i] >> 8);
    }
    return need;
}

int rg_input_script_look(const rg_input_script *s, uint32_t vbl, rg_look *out)
{
    out->yaw = out->pitch = 0;
    if (!s || !s->look) return 0;
    if (vbl < s->count) {
        out->yaw = s->look[2 * vbl];
        out->pitch = s->look[2 * vbl + 1];
    }
    return 1;
}

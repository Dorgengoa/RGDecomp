/* SPDX-License-Identifier: CC0-1.0 */
/* Pad input/output shared by the native pad service and the padman HLE: input source,
 * latched reports, rumble hook, scripted replay.  See rg_pad_io.h, docs/NATIVE-IOP.md. */
#include "rg_pad_io.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct {
    rg_pad_report latched[RG_PAD_PORTS];
    int latched_set;
    rg_pad_input_fn src;
    void *src_user;
    rg_pad_rumble_fn rumble;
    void *rumble_user;
} IO;

void rg_pad_report_neutral(rg_pad_report *r)
{
    memset(r, 0, sizeof *r);
    r->connected = 1;
    r->lx = r->ly = r->rx = r->ry = 0x80;
}

void rg_pad_io_reset_latched(const int default_connected[RG_PAD_PORTS])
{
    static const int def[RG_PAD_PORTS] = {1, 0};
    if (!default_connected)
        default_connected = def;
    for (int i = 0; i < RG_PAD_PORTS; i++) {
        rg_pad_report_neutral(&IO.latched[i]);
        IO.latched[i].connected = (uint8_t)(default_connected[i] != 0);
    }
    IO.latched_set = 1;
}

static void ensure_latched(void)
{
    if (!IO.latched_set)
        rg_pad_io_reset_latched(NULL);
}

void rg_pad_set_input_source(rg_pad_input_fn fn, void *user)
{
    IO.src = fn;
    IO.src_user = user;
}

void rg_pad_push_report(int port, const rg_pad_report *r)
{
    ensure_latched();
    if (port < 0 || port >= RG_PAD_PORTS || !r)
        return;
    IO.latched[port] = *r;
}

void rg_pad_set_rumble_hook(rg_pad_rumble_fn fn, void *user)
{
    IO.rumble = fn;
    IO.rumble_user = user;
}

void rg_pad_io_report(int port, uint64_t vb, rg_pad_report *r)
{
    ensure_latched();
    if (IO.src) {
        rg_pad_report t;
        rg_pad_report_neutral(&t);
        if (IO.src(IO.src_user, port, vb, &t)) {
            *r = t;
            return;
        }
    }
    *r = IO.latched[port];
}

void rg_pad_io_rumble(int port, uint8_t small, uint8_t large)
{
    if (IO.rumble)
        IO.rumble(IO.rumble_user, port, small, large);
}

/* ---- scripted input ---------------------------------------------------------------- */
typedef struct span {
    int64_t first, last;
    uint16_t buttons;
} span;

struct rg_pad_script {
    span *v;
    int n, cap;
    int64_t offset;
};

static const struct {
    const char *name;
    uint16_t bit;
} k_btn[] = {
    {"L2", RG_PAD_L2},         {"R2", RG_PAD_R2},         {"L1", RG_PAD_L1},       {"R1", RG_PAD_R1},
    {"TRIANGLE", RG_PAD_TRIANGLE}, {"CIRCLE", RG_PAD_CIRCLE}, {"CROSS", RG_PAD_CROSS}, {"SQUARE", RG_PAD_SQUARE},
    {"SELECT", RG_PAD_SELECT}, {"L3", RG_PAD_L3},         {"R3", RG_PAD_R3},       {"START", RG_PAD_START},
    {"UP", RG_PAD_UP},         {"RIGHT", RG_PAD_RIGHT},   {"DOWN", RG_PAD_DOWN},   {"LEFT", RG_PAD_LEFT},
};

static int parse_buttons(const char *s, uint16_t *out)
{
    uint16_t m = 0;
    char tok[32];
    while (*s) {
        int n = 0;
        while (*s && *s != '+' && n < 31)
            tok[n++] = (char)toupper((unsigned char)*s++);
        tok[n] = 0;
        if (*s == '+')
            s++;
        int found = 0;
        for (size_t i = 0; i < sizeof k_btn / sizeof k_btn[0]; i++)
            if (strcmp(tok, k_btn[i].name) == 0) {
                m |= k_btn[i].bit;
                found = 1;
            }
        if (!found)
            return -1;
    }
    *out = m;
    return 0;
}

rg_pad_script *rg_pad_script_parse(const char *text, char *err, int errlen)
{
    rg_pad_script *s = (rg_pad_script *)calloc(1, sizeof *s);
    if (!s)
        return NULL;
    int lineno = 0;
    const char *p = text;
    while (p && *p) {
        const char *e = strchr(p, '\n');
        size_t len = e ? (size_t)(e - p) : strlen(p);
        char line[256];
        if (len >= sizeof line)
            len = sizeof line - 1;
        memcpy(line, p, len);
        line[len] = 0;
        p = e ? e + 1 : NULL;
        lineno++;
        char *h = strchr(line, '#');
        if (h)
            *h = 0;
        long long a, b;
        char btn[160];
        char *q = line;
        while (*q == ' ' || *q == '\t' || *q == '\r')
            q++;
        if (!*q)
            continue;
        if (sscanf(q, "%lld %lld %159s", &a, &b, btn) != 3 || b < a) {
            if (err)
                snprintf(err, (size_t)errlen, "line %d: expected 'first last BUTTON[+BUTTON]'", lineno);
            rg_pad_script_free(s);
            return NULL;
        }
        uint16_t m;
        if (parse_buttons(btn, &m) != 0) {
            if (err)
                snprintf(err, (size_t)errlen, "line %d: unknown button in '%s'", lineno, btn);
            rg_pad_script_free(s);
            return NULL;
        }
        if (s->n == s->cap) {
            int nc = s->cap ? s->cap * 2 : 16;
            span *nv = (span *)realloc(s->v, (size_t)nc * sizeof *nv);
            if (!nv) {
                rg_pad_script_free(s);
                return NULL;
            }
            s->v = nv;
            s->cap = nc;
        }
        s->v[s->n].first = a;
        s->v[s->n].last = b;
        s->v[s->n].buttons = m;
        s->n++;
    }
    return s;
}

rg_pad_script *rg_pad_script_load(const char *path, char *err, int errlen)
{
    FILE *f = fopen(path, "rb");
    if (!f) {
        if (err)
            snprintf(err, (size_t)errlen, "cannot open %s", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *t = (char *)malloc((size_t)sz + 1);
    if (!t) {
        fclose(f);
        return NULL;
    }
    size_t got = fread(t, 1, (size_t)sz, f);
    t[got] = 0;
    fclose(f);
    rg_pad_script *s = rg_pad_script_parse(t, err, errlen);
    free(t);
    return s;
}

void rg_pad_script_free(rg_pad_script *s)
{
    if (!s)
        return;
    free(s->v);
    free(s);
}

void rg_pad_script_set_offset(rg_pad_script *s, int64_t off)
{
    if (s)
        s->offset = off;
}

uint16_t rg_pad_script_buttons(const rg_pad_script *s, int64_t frame)
{
    uint16_t m = 0;
    if (!s)
        return 0;
    for (int i = 0; i < s->n; i++)
        if (frame >= s->v[i].first && frame <= s->v[i].last)
            m |= s->v[i].buttons;
    return m;
}

int rg_pad_script_source(void *user, int port, uint64_t vblank, rg_pad_report *out)
{
    const rg_pad_script *s = (const rg_pad_script *)user;
    if (!s || port != 0)
        return 0;
    rg_pad_report_neutral(out);
    out->buttons = rg_pad_script_buttons(s, (int64_t)vblank - s->offset);
    return 1;
}

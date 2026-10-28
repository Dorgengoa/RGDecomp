/* SPDX-License-Identifier: CC0-1.0 */
/* Typed settings registry: definitions, two value layers, INI text, presets,
 * command line, change tracking, display trials.  docs/SETTINGS.md. */
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_settings.h"

#define MAX_CATS 64
#define MAX_CBS 16
#define MAX_ALIAS 64
#define MAX_TRIAL 16
#define DEF_MAX_LEN 1023

typedef struct sval { int i; double f; char *s; } sval;

typedef struct entry {
    rg_setting_def d;
    char *id_own;               /* owned copy of d.id */
    sval eff, base, applied;
    int has_applied;
    rg_setting_source src;      /* of the effective value */
    rg_setting_source base_src;
    int overridden;             /* effective value is a command-line override */
} entry;

typedef struct kv { char *id, *val; } kv;

typedef struct preset {
    char *name, *label;
    kv *items;
    int n;
} preset;

typedef struct trial_slot {
    int idx;
    sval eff, base;
    rg_setting_source src, base_src;
    int overridden;
} trial_slot;

struct rg_settings {
    entry *e;
    int n, cap;
    const char *cats[MAX_CATS];
    int ncats;
    kv *unk;
    int nunk, capunk;
    preset *pre;
    int npre;
    struct { rg_settings_change_fn fn; void *user; } cb[MAX_CBS];
    int ncb;
    rg_settings_warn_fn warn;
    void *warn_user;
    unsigned nwarn;
    char lastwarn[512];
    uint64_t gen;
    int trial_on;
    uint64_t trial_deadline;
    uint32_t trial_timeout;
    trial_slot trial[MAX_TRIAL];
    int ntrial;
    struct { char *old_id; int idx; } alias[MAX_ALIAS];
    int nalias;
};

/* ------------------------------------------------------------- helpers */
static char *xstrdup(const char *s)
{
    size_t n = strlen(s ? s : "");
    char *d = (char *)malloc(n + 1);
    if (d) memcpy(d, s ? s : "", n + 1);
    return d;
}

static int ieq(const char *a, const char *b)
{
    for (; *a && *b; a++, b++)
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
    return *a == *b;
}

static char *trim(char *s)
{
    while (*s && isspace((unsigned char)*s)) s++;
    char *e = s + strlen(s);
    while (e > s && isspace((unsigned char)e[-1])) *--e = 0;
    return s;
}

static void seterr(char *err, size_t cap, const char *fmt, ...)
{
    if (!err || !cap) return;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(err, cap, fmt, ap);
    va_end(ap);
}

static void stderr_warn(void *user, const char *msg)
{
    (void)user;
    fprintf(stderr, "rg-settings: %s\n", msg);
}

static void warnf(rg_settings *s, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(s->lastwarn, sizeof s->lastwarn, fmt, ap);
    va_end(ap);
    s->nwarn++;
    if (s->warn) s->warn(s->warn_user, s->lastwarn);
}

typedef struct sbuf { char *p; size_t cap, len; } sbuf;
static void sb_putn(sbuf *b, const char *t, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (b->cap && b->len + 1 < b->cap) b->p[b->len] = t[i];
        b->len++;
    }
    if (b->cap) b->p[b->len < b->cap ? b->len : b->cap - 1] = 0;
}
static void sb_put(sbuf *b, const char *fmt, ...)
{
    char tmp[2048];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(tmp, sizeof tmp, fmt, ap);
    va_end(ap);
    if (n < 0) return;
    if ((size_t)n >= sizeof tmp) n = (int)sizeof tmp - 1;
    sb_putn(b, tmp, (size_t)n);
}

static int is_text_type(rg_setting_type t) { return t == RG_SET_STRING || t == RG_SET_BINDING; }

static void sval_free(sval *v) { free(v->s); v->s = NULL; }

static void sval_copy(sval *dst, const sval *src)
{
    char *ns = src->s ? xstrdup(src->s) : NULL;
    free(dst->s);
    dst->i = src->i;
    dst->f = src->f;
    dst->s = ns;
}

static int sval_eq(const entry *e, const sval *a, const sval *b)
{
    switch (e->d.type) {
    case RG_SET_FLOAT: return a->f == b->f;
    case RG_SET_STRING:
    case RG_SET_BINDING: return strcmp(a->s ? a->s : "", b->s ? b->s : "") == 0;
    default: return a->i == b->i;
    }
}

/* shortest %g that round-trips */
static void fmt_float(double v, char *out, size_t cap)
{
    for (int p = 6; p <= 17; p++) {
        snprintf(out, cap, "%.*g", p, v);
        if (strtod(out, NULL) == v) break;
    }
}

static size_t sval_text(const entry *e, const sval *v, char *out, size_t cap)
{
    char tmp[64];
    const char *t = tmp;
    switch (e->d.type) {
    case RG_SET_BOOL: t = v->i ? "true" : "false"; break;
    case RG_SET_INT: snprintf(tmp, sizeof tmp, "%d", v->i); break;
    case RG_SET_FLOAT: fmt_float(v->f, tmp, sizeof tmp); break;
    case RG_SET_ENUM: t = (v->i >= 0 && v->i < e->d.enum_count) ? e->d.enum_names[v->i] : ""; break;
    default: t = v->s ? v->s : ""; break;
    }
    size_t n = strlen(t);
    if (cap) {
        size_t c = n < cap - 1 ? n : cap - 1;
        memcpy(out, t, c);
        out[c] = 0;
    }
    return n;
}

int rg_settings_parse_bool(const char *t, bool *out)
{
    static const char *const yes[] = { "true", "on", "yes", "1", "enabled" };
    static const char *const no[] = { "false", "off", "no", "0", "disabled" };
    for (size_t i = 0; i < sizeof yes / sizeof yes[0]; i++)
        if (ieq(t, yes[i])) { *out = true; return 0; }
    for (size_t i = 0; i < sizeof no / sizeof no[0]; i++)
        if (ieq(t, no[i])) { *out = false; return 0; }
    return -1;
}

/* Parse text for entry e into *v (v->s malloc'd for text types). */
static int parse_value(const entry *e, const char *text, sval *v, char *err, size_t errcap)
{
    const rg_setting_def *d = &e->d;
    memset(v, 0, sizeof *v);
    char *end;
    switch (d->type) {
    case RG_SET_BOOL: {
        bool b;
        if (rg_settings_parse_bool(text, &b)) { seterr(err, errcap, "'%s' is not a bool (true/false)", text); return -1; }
        v->i = b;
        return 0;
    }
    case RG_SET_INT: {
        errno = 0;
        long x = strtol(text, &end, 0);
        while (*end && isspace((unsigned char)*end)) end++;
        if (end == text || *end || errno) { seterr(err, errcap, "'%s' is not an integer", text); return -1; }
        if (x < d->min_i || x > d->max_i) {
            seterr(err, errcap, "%ld is outside %d..%d", x, d->min_i, d->max_i);
            return -1;
        }
        v->i = (int)x;
        return 0;
    }
    case RG_SET_FLOAT: {
        errno = 0;
        double x = strtod(text, &end);
        while (*end && isspace((unsigned char)*end)) end++;
        if (end == text || *end || errno || !isfinite(x)) { seterr(err, errcap, "'%s' is not a number", text); return -1; }
        if (x < d->min_f || x > d->max_f) {
            char a[32], b[32];
            fmt_float(d->min_f, a, sizeof a);
            fmt_float(d->max_f, b, sizeof b);
            seterr(err, errcap, "%s is outside %s..%s", text, a, b);
            return -1;
        }
        v->f = x;
        return 0;
    }
    case RG_SET_ENUM:
        for (int i = 0; i < d->enum_count; i++)
            if (ieq(text, d->enum_names[i])) { v->i = i; return 0; }
        {
            char list[512] = "";
            size_t L = 0;
            for (int i = 0; i < d->enum_count && L < sizeof list - 1; i++)
                L += (size_t)snprintf(list + L, sizeof list - L, "%s%s", i ? "|" : "", d->enum_names[i]);
            seterr(err, errcap, "'%s' is not one of %s", text, list);
        }
        return -1;
    default: {
        size_t maxl = d->max_len ? d->max_len : DEF_MAX_LEN;
        if (strlen(text) > maxl) { seterr(err, errcap, "longer than %u characters", (unsigned)maxl); return -1; }
        if (d->validate) {
            size_t ncap = maxl + 1 > 64 ? maxl + 1 : 64;
            char *norm = (char *)calloc(1, ncap);
            if (!norm) { seterr(err, errcap, "out of memory"); return -1; }
            if (d->validate(text, norm, ncap, err, errcap, d->validate_user)) { free(norm); return -1; }
            if (norm[0]) { v->s = norm; return 0; }
            free(norm);
        }
        v->s = xstrdup(text);
        return 0;
    }
    }
}

static void default_val(const entry *e, sval *v)
{
    memset(v, 0, sizeof *v);
    v->i = e->d.def_i;
    v->f = e->d.def_f;
    if (is_text_type(e->d.type)) v->s = xstrdup(e->d.def_s ? e->d.def_s : "");
}

static void original_val(const entry *e, sval *v)
{
    if (!(e->d.flags & RG_SETF_HAS_ORIGINAL)) { default_val(e, v); return; }
    memset(v, 0, sizeof *v);
    v->i = e->d.orig_i;
    v->f = e->d.orig_f;
    if (is_text_type(e->d.type)) v->s = xstrdup(e->d.orig_s ? e->d.orig_s : "");
}

static void fire(rg_settings *s, int idx)
{
    s->gen++;
    for (int i = 0; i < s->ncb; i++) s->cb[i].fn(s, idx, s->cb[i].user);
}

/* The core write.  CMDLINE: effective only (+ overridden).  MENU/API: both
 * layers, clears an override.  DEFAULT/PRESET/FILE: persistent layer; the
 * effective value follows unless overridden. */
static void store(rg_settings *s, int idx, const sval *v, rg_setting_source src)
{
    entry *e = &s->e[idx];
    sval old = { 0 };
    sval_copy(&old, &e->eff);
    if (src == RG_SRC_CMDLINE) {
        sval_copy(&e->eff, v);
        e->src = src;
        e->overridden = 1;
    } else if (src == RG_SRC_MENU || src == RG_SRC_API) {
        sval_copy(&e->base, v);
        e->base_src = src;
        sval_copy(&e->eff, v);
        e->src = src;
        e->overridden = 0;
    } else {
        sval_copy(&e->base, v);
        e->base_src = src;
        if (!e->overridden) { sval_copy(&e->eff, v); e->src = src; }
    }
    int changed = !sval_eq(e, &old, &e->eff);
    sval_free(&old);
    if (changed) fire(s, idx);
}

/* ------------------------------------------------------------- lifecycle */
rg_settings *rg_settings_create(void)
{
    rg_settings *s = (rg_settings *)calloc(1, sizeof *s);
    if (!s) return NULL;
    s->warn = stderr_warn;
    return s;
}

static void free_preset(preset *p)
{
    for (int i = 0; i < p->n; i++) { free(p->items[i].id); free(p->items[i].val); }
    free(p->items);
    free(p->name);
    free(p->label);
}

void rg_settings_destroy(rg_settings *s)
{
    if (!s) return;
    for (int i = 0; i < s->n; i++) {
        sval_free(&s->e[i].eff);
        sval_free(&s->e[i].base);
        sval_free(&s->e[i].applied);
        free(s->e[i].id_own);
    }
    for (int i = 0; i < s->nunk; i++) { free(s->unk[i].id); free(s->unk[i].val); }
    for (int i = 0; i < s->npre; i++) free_preset(&s->pre[i]);
    for (int i = 0; i < s->ntrial; i++) { sval_free(&s->trial[i].eff); sval_free(&s->trial[i].base); }
    for (int i = 0; i < s->ncats; i++) free((char *)s->cats[i]);
    for (int i = 0; i < s->nalias; i++) free(s->alias[i].old_id);
    free(s->pre);
    free(s->unk);
    free(s->e);
    free(s);
}

void rg_settings_set_warn(rg_settings *s, rg_settings_warn_fn fn, void *user)
{
    s->warn = fn;
    s->warn_user = user;
}
unsigned rg_settings_warnings(const rg_settings *s) { return s->nwarn; }
const char *rg_settings_last_warning(const rg_settings *s) { return s->lastwarn; }

static int valid_id(const char *id)
{
    if (!id || !*id || *id == '.') return 0;
    for (const char *p = id; *p; p++)
        if (!(islower((unsigned char)*p) || isdigit((unsigned char)*p) || *p == '_' || *p == '.'))
            return 0;
    return id[strlen(id) - 1] != '.';
}

static const char *intern_cat(rg_settings *s, const char *cat, char *tmp, size_t cap, const char *id)
{
    const char *c = cat;
    if (!c) {
        const char *dot = strchr(id, '.');
        size_t n = dot ? (size_t)(dot - id) : strlen(id);
        if (n >= cap) n = cap - 1;
        memcpy(tmp, id, n);
        tmp[n] = 0;
        c = tmp;
    }
    for (int i = 0; i < s->ncats; i++)
        if (!strcmp(s->cats[i], c)) return s->cats[i];
    if (s->ncats >= MAX_CATS) return s->cats[s->ncats - 1];
    char *own = xstrdup(c);   /* freed by rg_settings_destroy */
    s->cats[s->ncats++] = own;
    return own;
}

static int check_def(const rg_setting_def *d, char *why, size_t cap)
{
    if (!valid_id(d->id)) { seterr(why, cap, "bad id '%s'", d->id ? d->id : "(null)"); return -1; }
    switch (d->type) {
    case RG_SET_BOOL:
        if ((d->def_i != 0 && d->def_i != 1) ||
            ((d->flags & RG_SETF_HAS_ORIGINAL) && d->orig_i != 0 && d->orig_i != 1)) {
            seterr(why, cap, "bool default/original not 0/1"); return -1;
        }
        break;
    case RG_SET_INT:
        if (d->min_i > d->max_i || d->def_i < d->min_i || d->def_i > d->max_i ||
            ((d->flags & RG_SETF_HAS_ORIGINAL) && (d->orig_i < d->min_i || d->orig_i > d->max_i))) {
            seterr(why, cap, "default/original outside %d..%d", d->min_i, d->max_i); return -1;
        }
        break;
    case RG_SET_FLOAT:
        if (!(d->min_f <= d->max_f) || d->def_f < d->min_f || d->def_f > d->max_f ||
            ((d->flags & RG_SETF_HAS_ORIGINAL) && (d->orig_f < d->min_f || d->orig_f > d->max_f))) {
            seterr(why, cap, "default/original outside the range"); return -1;
        }
        break;
    case RG_SET_ENUM:
        if (!d->enum_names || d->enum_count <= 0 || d->def_i < 0 || d->def_i >= d->enum_count ||
            ((d->flags & RG_SETF_HAS_ORIGINAL) && (d->orig_i < 0 || d->orig_i >= d->enum_count))) {
            seterr(why, cap, "enum default/original outside its names"); return -1;
        }
        break;
    case RG_SET_STRING:
    case RG_SET_BINDING:
        break;
    default:
        seterr(why, cap, "unknown type"); return -1;
    }
    return 0;
}

int rg_settings_register(rg_settings *s, const rg_setting_def *defs, int n)
{
    int rc = 0;
    for (int k = 0; k < n; k++) {
        const rg_setting_def *d = &defs[k];
        char why[256];
        int bad = check_def(d, why, sizeof why);
        if (!bad && rg_settings_find(s, d->id) >= 0) { snprintf(why, sizeof why, "duplicate id"); bad = 1; }
        if (bad) {
            warnf(s, "definition '%s' refused: %s", d->id ? d->id : "(null)", why);
            rc = -1;
            continue;
        }
        if (s->n == s->cap) {
            int nc = s->cap ? s->cap * 2 : 64;
            entry *ne = (entry *)realloc(s->e, (size_t)nc * sizeof *ne);
            if (!ne) { warnf(s, "out of memory"); return -1; }
            s->e = ne;
            s->cap = nc;
        }
        entry *e = &s->e[s->n];
        memset(e, 0, sizeof *e);
        e->d = *d;
        e->id_own = xstrdup(d->id);
        e->d.id = e->id_own;
        char tmp[64];
        e->d.category = intern_cat(s, d->category, tmp, sizeof tmp, d->id);
        /* a text default must itself validate */
        default_val(e, &e->base);
        if (is_text_type(d->type)) {
            sval v;
            char err[256];
            if (parse_value(e, e->base.s, &v, err, sizeof err) == 0) {
                sval_free(&e->base);
                e->base = v;
            } else {
                warnf(s, "definition '%s': default '%s' invalid: %s", d->id, e->base.s, err);
            }
        }
        sval_copy(&e->eff, &e->base);
        e->src = e->base_src = RG_SRC_DEFAULT;
        s->n++;
        /* a previously-unknown key from a file loaded before registration */
        for (int u = 0; u < s->nunk; u++) {
            if (strcmp(s->unk[u].id, d->id)) continue;
            char err[256];
            sval v;
            if (parse_value(e, s->unk[u].val, &v, err, sizeof err) == 0) {
                store(s, s->n - 1, &v, RG_SRC_FILE);
                sval_free(&v);
            } else {
                warnf(s, "%s: %s; using the default", d->id, err);
            }
            free(s->unk[u].id);
            free(s->unk[u].val);
            s->unk[u] = s->unk[--s->nunk];
            break;
        }
    }
    return rc;
}

/* ------------------------------------------------------------- lookup */
int rg_settings_count(const rg_settings *s) { return s->n; }

int rg_settings_find(const rg_settings *s, const char *id)
{
    if (!id) return -1;
    for (int i = 0; i < s->n; i++)
        if (!strcmp(s->e[i].d.id, id)) return i;
    for (int i = 0; i < s->nalias; i++)
        if (!strcmp(s->alias[i].old_id, id)) return s->alias[i].idx;
    return -1;
}

int rg_settings_add_alias(rg_settings *s, const char *old_id, const char *id)
{
    int idx = rg_settings_find(s, id);
    if (!old_id || !valid_id(old_id) || idx < 0 || rg_settings_find(s, old_id) >= 0 || s->nalias >= MAX_ALIAS) {
        warnf(s, "alias '%s' -> '%s' refused", old_id ? old_id : "(null)", id ? id : "(null)");
        return -1;
    }
    s->alias[s->nalias].old_id = xstrdup(old_id);
    s->alias[s->nalias].idx = idx;
    s->nalias++;
    return 0;
}

const rg_setting_def *rg_settings_def(const rg_settings *s, int i)
{
    return i >= 0 && i < s->n ? &s->e[i].d : NULL;
}

const char *rg_settings_category(const rg_settings *s, int i)
{
    return i >= 0 && i < s->n ? s->e[i].d.category : NULL;
}

int rg_settings_categories(const rg_settings *s, const char **out, int cap)
{
    int k = 0;
    for (int i = 0; i < s->ncats && k < cap; i++) out[k++] = s->cats[i];
    return s->ncats;
}

rg_setting_source rg_settings_source(const rg_settings *s, int i)
{
    return i >= 0 && i < s->n ? s->e[i].src : RG_SRC_DEFAULT;
}

bool rg_settings_is_default(const rg_settings *s, int i)
{
    if (i < 0 || i >= s->n) return false;
    sval d;
    default_val(&s->e[i], &d);
    bool r = sval_eq(&s->e[i], &d, &s->e[i].eff);
    sval_free(&d);
    return r;
}

bool rg_settings_overridden(const rg_settings *s, int i)
{
    return i >= 0 && i < s->n && s->e[i].overridden;
}

/* ------------------------------------------------------------- typed get/set */
static const entry *get_e(const rg_settings *s, const char *id)
{
    int i = rg_settings_find(s, id);
    return i < 0 ? NULL : &s->e[i];
}

bool rg_settings_get_bool(const rg_settings *s, const char *id)
{
    const entry *e = get_e(s, id);
    return e && e->d.type == RG_SET_BOOL && e->eff.i;
}

int rg_settings_get_int(const rg_settings *s, const char *id)
{
    const entry *e = get_e(s, id);
    if (!e) return 0;
    if (e->d.type == RG_SET_INT || e->d.type == RG_SET_BOOL || e->d.type == RG_SET_ENUM) return e->eff.i;
    if (e->d.type == RG_SET_FLOAT) return (int)e->eff.f;
    return 0;
}

double rg_settings_get_float(const rg_settings *s, const char *id)
{
    const entry *e = get_e(s, id);
    if (!e) return 0.0;
    if (e->d.type == RG_SET_FLOAT) return e->eff.f;
    if (e->d.type == RG_SET_INT) return e->eff.i;
    return 0.0;
}

const char *rg_settings_get_string(const rg_settings *s, const char *id)
{
    const entry *e = get_e(s, id);
    if (!e) return "";
    if (is_text_type(e->d.type)) return e->eff.s ? e->eff.s : "";
    if (e->d.type == RG_SET_ENUM && e->eff.i >= 0 && e->eff.i < e->d.enum_count) return e->d.enum_names[e->eff.i];
    if (e->d.type == RG_SET_BOOL) return e->eff.i ? "true" : "false";
    return "";
}

int rg_settings_get_enum(const rg_settings *s, const char *id)
{
    const entry *e = get_e(s, id);
    return e && e->d.type == RG_SET_ENUM ? e->eff.i : -1;
}

static int set_checked(rg_settings *s, int idx, sval *v, rg_setting_source src)
{
    entry *e = &s->e[idx];
    int same = sval_eq(e, v, &e->eff) && (src == RG_SRC_CMDLINE ? 1 : sval_eq(e, v, &e->base));
    store(s, idx, v, src);
    return same ? RG_SET_UNCHANGED : RG_SET_OK;
}

int rg_settings_set_bool(rg_settings *s, const char *id, bool b, rg_setting_source src)
{
    int i = rg_settings_find(s, id);
    if (i < 0) return RG_SET_UNKNOWN;
    if (s->e[i].d.type != RG_SET_BOOL) return RG_SET_TYPE;
    sval v = { b ? 1 : 0, 0, NULL };
    return set_checked(s, i, &v, src);
}

int rg_settings_set_int(rg_settings *s, const char *id, int x, rg_setting_source src)
{
    int i = rg_settings_find(s, id);
    if (i < 0) return RG_SET_UNKNOWN;
    const rg_setting_def *d = &s->e[i].d;
    if (d->type == RG_SET_BOOL) return rg_settings_set_bool(s, id, x != 0, src);
    if (d->type == RG_SET_ENUM) {
        if (x < 0 || x >= d->enum_count) return RG_SET_INVALID;
    } else if (d->type == RG_SET_INT) {
        if (x < d->min_i || x > d->max_i) return RG_SET_INVALID;
    } else {
        return RG_SET_TYPE;
    }
    sval v = { x, 0, NULL };
    return set_checked(s, i, &v, src);
}

int rg_settings_set_float(rg_settings *s, const char *id, double x, rg_setting_source src)
{
    int i = rg_settings_find(s, id);
    if (i < 0) return RG_SET_UNKNOWN;
    const rg_setting_def *d = &s->e[i].d;
    if (d->type != RG_SET_FLOAT) return RG_SET_TYPE;
    if (!isfinite(x) || x < d->min_f || x > d->max_f) return RG_SET_INVALID;
    sval v = { 0, x, NULL };
    return set_checked(s, i, &v, src);
}

int rg_settings_set_string(rg_settings *s, const char *id, const char *t, rg_setting_source src)
{
    int i = rg_settings_find(s, id);
    if (i < 0) return RG_SET_UNKNOWN;
    return rg_settings_set_text(s, i, t ? t : "", src, NULL, 0);
}

int rg_settings_set_text(rg_settings *s, int idx, const char *text, rg_setting_source src,
                         char *err, size_t errcap)
{
    if (idx < 0 || idx >= s->n) { seterr(err, errcap, "no such setting"); return RG_SET_UNKNOWN; }
    sval v;
    if (parse_value(&s->e[idx], text, &v, err, errcap)) return RG_SET_INVALID;
    int r = set_checked(s, idx, &v, src);
    sval_free(&v);
    return r;
}

size_t rg_settings_value_text(const rg_settings *s, int i, char *out, size_t cap)
{
    if (i < 0 || i >= s->n) { if (cap) *out = 0; return 0; }
    return sval_text(&s->e[i], &s->e[i].eff, out, cap);
}

size_t rg_settings_persistent_text(const rg_settings *s, int i, char *out, size_t cap)
{
    if (i < 0 || i >= s->n) { if (cap) *out = 0; return 0; }
    return sval_text(&s->e[i], &s->e[i].base, out, cap);
}

size_t rg_settings_default_text(const rg_settings *s, int i, char *out, size_t cap)
{
    if (i < 0 || i >= s->n) { if (cap) *out = 0; return 0; }
    sval d;
    default_val(&s->e[i], &d);
    size_t n = sval_text(&s->e[i], &d, out, cap);
    sval_free(&d);
    return n;
}

size_t rg_settings_display_text(const rg_settings *s, int i, char *out, size_t cap)
{
    if (i < 0 || i >= s->n) { if (cap) *out = 0; return 0; }
    const entry *e = &s->e[i];
    const char *t = NULL;
    if (e->d.type == RG_SET_BOOL) t = e->eff.i ? "On" : "Off";
    else if (e->d.type == RG_SET_ENUM && e->d.enum_labels && e->eff.i >= 0 && e->eff.i < e->d.enum_count)
        t = e->d.enum_labels[e->eff.i];
    if (!t) return sval_text(e, &e->eff, out, cap);
    size_t n = strlen(t);
    if (cap) { size_t c = n < cap - 1 ? n : cap - 1; memcpy(out, t, c); out[c] = 0; }
    return n;
}

void rg_settings_reset(rg_settings *s, int i)
{
    if (i < 0 || i >= s->n) return;
    sval d;
    default_val(&s->e[i], &d);
    s->e[i].overridden = 0;
    store(s, i, &d, RG_SRC_API);
    s->e[i].src = s->e[i].base_src = RG_SRC_DEFAULT;
    sval_free(&d);
}

void rg_settings_reset_all(rg_settings *s)
{
    for (int i = 0; i < s->n; i++) rg_settings_reset(s, i);
}

/* ------------------------------------------------------------- presets */
static const preset *find_user_preset(const rg_settings *s, const char *name)
{
    for (int i = 0; i < s->npre; i++)
        if (ieq(s->pre[i].name, name)) return &s->pre[i];
    return NULL;
}

/* The preset's value for entry idx (malloc'd s for text types). */
static void preset_val(rg_settings *s, int kind, const preset *p, int idx, sval *v)
{
    entry *e = &s->e[idx];
    if (kind == 1) { original_val(e, v); return; }
    if (kind == 2 && p) {
        for (int k = 0; k < p->n; k++) {
            if (strcmp(p->items[k].id, e->d.id)) continue;
            char err[256];
            if (parse_value(e, p->items[k].val, v, err, sizeof err) == 0) return;
            warnf(s, "preset %s: %s: %s; using the default", p->name, e->d.id, err);
            break;
        }
    }
    default_val(e, v);
}

static int preset_kind(const rg_settings *s, const char *name, const preset **p)
{
    *p = NULL;
    if (ieq(name, "original")) return 1;
    if (ieq(name, "default") || ieq(name, "defaults")) return 0;
    *p = find_user_preset(s, name);
    return *p ? 2 : -1;
}

int rg_settings_apply_preset(rg_settings *s, const char *name)
{
    const preset *p;
    int kind = preset_kind(s, name, &p);
    if (kind < 0) { warnf(s, "unknown preset '%s'", name); return -1; }
    for (int i = 0; i < s->n; i++) {
        sval v;
        preset_val(s, kind, p, i, &v);
        store(s, i, &v, RG_SRC_PRESET);
        sval_free(&v);
    }
    return 0;
}

bool rg_settings_matches_preset(const rg_settings *s, const char *name)
{
    const preset *p;
    int kind = preset_kind(s, name, &p);
    if (kind < 0) return false;
    for (int i = 0; i < s->n; i++) {
        sval v;
        preset_val((rg_settings *)s, kind, p, i, &v);
        int eq = sval_eq(&s->e[i], &v, &s->e[i].eff);
        sval_free(&v);
        if (!eq) return false;
    }
    return true;
}

int rg_settings_preset_count(const rg_settings *s) { return 2 + s->npre; }

const char *rg_settings_preset_name(const rg_settings *s, int i)
{
    if (i == 0) return "original";
    if (i == 1) return "default";
    i -= 2;
    return i >= 0 && i < s->npre ? s->pre[i].name : NULL;
}

const char *rg_settings_preset_label(const rg_settings *s, int i)
{
    if (i == 0) return "Original (PS2)";
    if (i == 1) return "Default";
    i -= 2;
    return i >= 0 && i < s->npre ? s->pre[i].label : NULL;
}

/* ------------------------------------------------------------- INI text */
/* Splits INI text into (id, value) pairs; calls fn for each.  `preset = x` at
 * top level is passed with id "preset".  Returns the number of syntax errors
 * (each reported through warnf). */
typedef void (*pair_fn)(rg_settings *s, const char *id, const char *val, int line, const char *name, void *u);

static char *unquote(char *v)
{
    size_t n = strlen(v);
    if (n >= 2 && v[0] == '"' && v[n - 1] == '"') {
        char *w = v;
        for (char *r = v + 1; r < v + n - 1; r++) {
            if (*r == '\\' && r + 1 < v + n - 1) r++;
            *w++ = *r;
        }
        *w = 0;
    }
    return v;
}

/* strip a comment: '#' at the start or after whitespace, outside quotes */
static void strip_comment(char *l)
{
    int inq = 0;
    for (char *p = l; *p; p++) {
        if (*p == '\\' && inq && p[1]) { p++; continue; }
        if (*p == '"') inq = !inq;
        if (*p == '#' && !inq && (p == l || isspace((unsigned char)p[-1]))) { *p = 0; return; }
    }
}

static void walk_ini(rg_settings *s, const char *text, const char *name, pair_fn fn, void *u)
{
    size_t n = strlen(text);
    char *buf = (char *)malloc(n + 1);
    if (!buf) { warnf(s, "%s: out of memory", name); return; }
    memcpy(buf, text, n + 1);
    char section[128] = "";
    int ln = 0;
    for (char *line = buf; line; ) {
        char *nl = strchr(line, '\n');
        if (nl) *nl = 0;
        ln++;
        char *cur = line;
        line = nl ? nl + 1 : NULL;
        if (ln == 1 && (unsigned char)cur[0] == 0xEF && (unsigned char)cur[1] == 0xBB &&
            (unsigned char)cur[2] == 0xBF)
            cur += 3;   /* UTF-8 BOM (Notepad) */
        strip_comment(cur);
        char *t = trim(cur);
        if (!*t) continue;
        if (*t == '[') {
            char *close = strchr(t, ']');
            if (!close || *trim(close + 1)) { warnf(s, "%s:%d: bad section header", name, ln); continue; }
            *close = 0;
            snprintf(section, sizeof section, "%s", trim(t + 1));
            for (char *p = section; *p; p++) *p = (char)tolower((unsigned char)*p);
            continue;
        }
        char *eq = strchr(t, '=');
        if (!eq) { warnf(s, "%s:%d: expected key = value", name, ln); continue; }
        *eq = 0;
        char *key = trim(t), *val = unquote(trim(eq + 1));
        if (!*key) { warnf(s, "%s:%d: empty key", name, ln); continue; }
        char id[256];
        if (section[0]) snprintf(id, sizeof id, "%s.%s", section, key);
        else snprintf(id, sizeof id, "%s", key);
        for (char *p = id; *p; p++) *p = (char)tolower((unsigned char)*p);
        fn(s, id, val, ln, name, u);
    }
    free(buf);
}

static void keep_unknown(rg_settings *s, const char *id, const char *val)
{
    for (int i = 0; i < s->nunk; i++)
        if (!strcmp(s->unk[i].id, id)) {
            free(s->unk[i].val);
            s->unk[i].val = xstrdup(val);
            return;
        }
    if (s->nunk == s->capunk) {
        int nc = s->capunk ? s->capunk * 2 : 16;
        kv *nu = (kv *)realloc(s->unk, (size_t)nc * sizeof *nu);
        if (!nu) return;
        s->unk = nu;
        s->capunk = nc;
    }
    s->unk[s->nunk].id = xstrdup(id);
    s->unk[s->nunk].val = xstrdup(val);
    s->nunk++;
}

static void file_pair(rg_settings *s, const char *id, const char *val, int ln, const char *name, void *u)
{
    (void)u;
    if (!strcmp(id, "preset")) {
        if (rg_settings_apply_preset(s, val)) warnf(s, "%s:%d: unknown preset '%s'", name, ln, val);
        return;
    }
    int idx = rg_settings_find(s, id);
    if (idx < 0) {
        warnf(s, "%s:%d: unknown setting '%s' (kept)", name, ln, id);
        keep_unknown(s, id, val);
        return;
    }
    char err[256];
    sval v;
    if (parse_value(&s->e[idx], val, &v, err, sizeof err)) {
        char dt[128];
        rg_settings_default_text(s, idx, dt, sizeof dt);
        warnf(s, "%s:%d: %s: %s; using the default (%s)", name, ln, id, err, dt);
        default_val(&s->e[idx], &v);
    }
    store(s, idx, &v, RG_SRC_FILE);
    sval_free(&v);
}

int rg_settings_parse(rg_settings *s, const char *text, const char *name)
{
    unsigned before = s->nwarn;
    walk_ini(s, text ? text : "", name ? name : "settings", file_pair, NULL);
    return (int)(s->nwarn - before);
}

int rg_settings_load(rg_settings *s, const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) return errno == ENOENT ? 0 : (warnf(s, "%s: cannot open", path), -1);
    size_t cap = 4096, n = 0;
    char *buf = (char *)malloc(cap + 1);
    for (;;) {
        if (!buf) { fclose(f); warnf(s, "%s: out of memory", path); return -1; }
        n += fread(buf + n, 1, cap - n, f);
        if (n < cap) break;
        cap *= 2;
        char *nb = (char *)realloc(buf, cap + 1);
        if (!nb) { free(buf); buf = NULL; continue; }
        buf = nb;
    }
    int bad = ferror(f);
    fclose(f);
    if (bad) { free(buf); warnf(s, "%s: read error", path); return -1; }
    buf[n] = 0;
    rg_settings_parse(s, buf, path);
    free(buf);
    return 0;
}

static int needs_quotes(const char *v)
{
    if (!*v) return 0;
    if (isspace((unsigned char)v[0]) || isspace((unsigned char)v[strlen(v) - 1]) || v[0] == '"') return 1;
    for (const char *p = v; *p; p++)
        if (*p == '#' || *p == '\n' || *p == '\r') return 1;
    return 0;
}

static void put_value(sbuf *b, const char *v)
{
    if (!needs_quotes(v)) { sb_putn(b, v, strlen(v)); return; }
    sb_putn(b, "\"", 1);
    for (const char *p = v; *p; p++) {
        if (*p == '"' || *p == '\\') sb_putn(b, "\\", 1);
        if (*p == '\n' || *p == '\r') continue;
        sb_putn(b, p, 1);
    }
    sb_putn(b, "\"", 1);
}

static void section_of(const char *id, char *sec, size_t cap, const char **key)
{
    const char *dot = strchr(id, '.');
    size_t n = dot ? (size_t)(dot - id) : 0;
    if (n >= cap) n = cap - 1;
    memcpy(sec, id, n);
    sec[n] = 0;
    *key = dot ? dot + 1 : id;
}

static void put_comment(sbuf *b, const entry *e, const rg_settings *s, int idx)
{
    const rg_setting_def *d = &e->d;
    sb_put(b, "# %s", d->label ? d->label : d->id);
    if (d->help) sb_put(b, ": %s", d->help);
    sb_put(b, "\n# ");
    switch (d->type) {
    case RG_SET_BOOL: sb_put(b, "true | false"); break;
    case RG_SET_INT: sb_put(b, "integer %d..%d", d->min_i, d->max_i); break;
    case RG_SET_FLOAT: {
        char a[32], c[32];
        fmt_float(d->min_f, a, sizeof a);
        fmt_float(d->max_f, c, sizeof c);
        sb_put(b, "number %s..%s", a, c);
        break;
    }
    case RG_SET_ENUM:
        for (int i = 0; i < d->enum_count; i++) sb_put(b, "%s%s", i ? " | " : "", d->enum_names[i]);
        break;
    case RG_SET_STRING: sb_put(b, "text"); break;
    case RG_SET_BINDING: sb_put(b, "bindings (docs/INPUT.md)"); break;
    }
    char dt[512];
    rg_settings_default_text(s, idx, dt, sizeof dt);
    sb_put(b, "  (default: %s)", dt[0] ? dt : "\"\"");
    if (d->flags & RG_SETF_RESTART) sb_put(b, " [restart]");
    if (d->flags & RG_SETF_GAMEPLAY) sb_put(b, " [gameplay]");
    if (d->flags & RG_SETF_PLACEHOLDER) sb_put(b, " [planned: no effect yet]");
    sb_put(b, "\n");
}

size_t rg_settings_format(const rg_settings *s, char *out, size_t cap, unsigned flags)
{
    sbuf b = { out, cap, 0 };
    if (cap) out[0] = 0;
    int comments = !(flags & RG_FMT_NO_COMMENTS);
    if (comments)
        sb_put(&b, "# Rogue Galaxy PC port settings (docs/SETTINGS.md).\n"
                   "# Edit freely: invalid values fall back to the default with a warning.\n"
                   "# Command line: --set section.key=value, --preset original|default.\n");
    /* sections in order of first appearance: known settings, then unknown */
    int total = s->n + s->nunk;
    char *val = (char *)malloc(DEF_MAX_LEN * 4 + 64);
    if (!val) return b.len;
    for (int k = 0; k < total; k++) {
        const char *id = k < s->n ? s->e[k].d.id : s->unk[k - s->n].id;
        char sec[128];
        const char *key;
        section_of(id, sec, sizeof sec, &key);
        /* has this section been written already? compare with earlier ids */
        int written = 0;
        for (int j = 0; j < k && !written; j++) {
            const char *pid = j < s->n ? s->e[j].d.id : s->unk[j - s->n].id;
            char ps[128];
            const char *pk;
            section_of(pid, ps, sizeof ps, &pk);
            if (!strcmp(ps, sec)) written = 1;
        }
        if (written) continue;
        int header = 0;
        for (int j = k; j < total; j++) {
            const char *jid = j < s->n ? s->e[j].d.id : s->unk[j - s->n].id;
            char js[128];
            const char *jk;
            section_of(jid, js, sizeof js, &jk);
            if (strcmp(js, sec)) continue;
            if (j < s->n) {
                const entry *e = &s->e[j];
                sval d;
                default_val(e, &d);
                int isdef = sval_eq(e, &d, &e->base);
                sval_free(&d);
                if ((flags & RG_FMT_CHANGED_ONLY) && isdef) continue;
                if (!header) {
                    if (sec[0]) sb_put(&b, "\n[%s]\n", sec); else sb_put(&b, "\n");
                    header = 1;
                }
                if (comments) put_comment(&b, e, s, j);
                sval_text(e, &e->base, val, DEF_MAX_LEN * 4 + 64);
                sb_put(&b, "%s = ", jk);
                put_value(&b, val);
                sb_put(&b, "\n");
            } else {
                if (!header) {
                    if (sec[0]) sb_put(&b, "\n[%s]\n", sec); else sb_put(&b, "\n");
                    header = 1;
                }
                if (comments) sb_put(&b, "# (not a setting of this version; kept)\n");
                sb_put(&b, "%s = ", jk);
                put_value(&b, s->unk[j - s->n].val);
                sb_put(&b, "\n");
            }
        }
    }
    free(val);
    return b.len;
}

int rg_settings_save(const rg_settings *s, const char *path, unsigned flags)
{
    size_t n = rg_settings_format(s, NULL, 0, flags);
    char *buf = (char *)malloc(n + 1);
    if (!buf) return -1;
    rg_settings_format(s, buf, n + 1, flags);
    size_t pl = strlen(path);
    char *tmp = (char *)malloc(pl + 5);
    if (!tmp) { free(buf); return -1; }
    memcpy(tmp, path, pl);
    memcpy(tmp + pl, ".tmp", 5);
    FILE *f = fopen(tmp, "wb");
    int rc = -1;
    if (f) {
        size_t w = fwrite(buf, 1, n, f);
        int ok = w == n && fflush(f) == 0;
        if (fclose(f) != 0) ok = 0;
        if (ok) {
            /* rename() does not replace an existing file on Windows: remove the
             * old one first.  The window where neither exists is one call long;
             * the .tmp file is complete by then. */
            if (rename(tmp, path) == 0) rc = 0;
            else { remove(path); rc = rename(tmp, path) == 0 ? 0 : -1; }
        }
        if (rc) remove(tmp);
    }
    free(tmp);
    free(buf);
    return rc;
}


struct preset_coll { preset *p; int bad; char *err; size_t errcap; };

static void preset_pair(rg_settings *s, const char *id, const char *val, int ln, const char *name, void *u)
{
    struct preset_coll *c = (struct preset_coll *)u;
    if (c->bad) return;
    int idx = rg_settings_find(s, id);
    char err[256];
    sval v;
    if (idx < 0) {
        seterr(c->err, c->errcap, "%s:%d: unknown setting '%s'", name, ln, id);
        c->bad = 1;
        return;
    }
    if (parse_value(&s->e[idx], val, &v, err, sizeof err)) {
        seterr(c->err, c->errcap, "%s:%d: %s: %s", name, ln, id, err);
        c->bad = 1;
        return;
    }
    sval_free(&v);
    kv *ni = (kv *)realloc(c->p->items, (size_t)(c->p->n + 1) * sizeof *ni);
    if (!ni) { c->bad = 1; return; }
    c->p->items = ni;
    ni[c->p->n].id = xstrdup(id);
    ni[c->p->n].val = xstrdup(val);
    c->p->n++;
}

int rg_settings_add_preset(rg_settings *s, const char *name, const char *label,
                           const char *text, char *err, size_t errcap)
{
    const preset *dummy;
    if (!name || !*name || preset_kind(s, name, &dummy) >= 0) {
        seterr(err, errcap, "bad or duplicate preset name '%s'", name ? name : "");
        return -1;
    }
    preset p;
    memset(&p, 0, sizeof p);
    struct preset_coll c = { &p, 0, err, errcap };
    unsigned w = s->nwarn;
    walk_ini(s, text ? text : "", name, preset_pair, &c);
    if (s->nwarn != w && !c.bad) { seterr(err, errcap, "%s", s->lastwarn); c.bad = 1; }
    preset *np = c.bad ? NULL : (preset *)realloc(s->pre, (size_t)(s->npre + 1) * sizeof *np);
    if (!np) { free_preset(&p); if (!c.bad) seterr(err, errcap, "out of memory"); return -1; }
    p.name = xstrdup(name);
    p.label = xstrdup(label ? label : name);
    s->pre = np;
    s->pre[s->npre++] = p;
    return 0;
}

/* ------------------------------------------------------------- command line */
int rg_settings_override(rg_settings *s, const char *a)
{
    const char *eq = a ? strchr(a, '=') : NULL;
    if (!eq) { warnf(s, "--set '%s': expected id=value", a ? a : ""); return RG_SET_INVALID; }
    char id[256];
    size_t n = (size_t)(eq - a);
    if (n >= sizeof id) n = sizeof id - 1;
    memcpy(id, a, n);
    id[n] = 0;
    char *t = trim(id);
    for (char *p = t; *p; p++) *p = (char)tolower((unsigned char)*p);
    int idx = rg_settings_find(s, t);
    if (idx < 0) { warnf(s, "--set: unknown setting '%s'", t); return RG_SET_UNKNOWN; }
    char vbuf[2048];
    snprintf(vbuf, sizeof vbuf, "%s", eq + 1);
    char err[256];
    int r = rg_settings_set_text(s, idx, unquote(trim(vbuf)), RG_SRC_CMDLINE, err, sizeof err);
    if (r < 0) warnf(s, "--set %s: %s (ignored)", t, err);
    return r < 0 ? r : RG_SET_OK;
}

void rg_settings_clear_overrides(rg_settings *s)
{
    for (int i = 0; i < s->n; i++) {
        entry *e = &s->e[i];
        if (!e->overridden) continue;
        e->overridden = 0;
        sval b = { 0 };
        sval_copy(&b, &e->base);
        store(s, i, &b, e->base_src);
        sval_free(&b);
    }
}

static int arg_value(int argc, char **argv, int *i, const char *flag, const char **val)
{
    size_t L = strlen(flag);
    const char *a = argv[*i];
    if (strncmp(a, flag, L)) return 0;
    if (a[L] == '=') { *val = a + L + 1; return 1; }
    if (a[L]) return 0;
    if (*i + 1 >= argc) { *val = NULL; return 1; }
    *val = argv[++*i];
    return 1;
}

int rg_settings_apply_args(rg_settings *s, int argc, char **argv, int *errors, const char **settings_path)
{
    int out = argc > 0 ? 1 : 0, bad = 0;
    if (settings_path) *settings_path = NULL;
    for (int i = 1; i < argc; i++) {
        const char *v;
        if (arg_value(argc, argv, &i, "--set", &v)) {
            if (!v || rg_settings_override(s, v) < 0) bad++;
        } else if (arg_value(argc, argv, &i, "--preset", &v)) {
            if (!v || rg_settings_apply_preset(s, v)) bad++;
        } else if (arg_value(argc, argv, &i, "--settings", &v)) {
            if (!v) { warnf(s, "--settings needs a path"); bad++; }
            else {
                if (rg_settings_load(s, v)) bad++;
                if (settings_path) *settings_path = v;
            }
        } else {
            argv[out++] = argv[i];
        }
    }
    if (out < argc) argv[out] = NULL;
    if (errors) *errors = bad;
    return out;
}

/* ------------------------------------------------------------- change tracking */
int rg_settings_on_change(rg_settings *s, rg_settings_change_fn fn, void *user)
{
    if (!fn || s->ncb >= MAX_CBS) return -1;
    s->cb[s->ncb].fn = fn;
    s->cb[s->ncb].user = user;
    s->ncb++;
    return 0;
}

void rg_settings_mark_applied(rg_settings *s)
{
    for (int i = 0; i < s->n; i++) {
        sval_copy(&s->e[i].applied, &s->e[i].eff);
        s->e[i].has_applied = 1;
    }
}

int rg_settings_restart_pending(const rg_settings *s, int *out, int cap)
{
    int k = 0;
    for (int i = 0; i < s->n; i++) {
        const entry *e = &s->e[i];
        if (!(e->d.flags & RG_SETF_RESTART) || !e->has_applied) continue;
        if (sval_eq(e, &e->applied, &e->eff)) continue;
        if (out && k < cap) out[k] = i;
        k++;
    }
    return k;
}

uint64_t rg_settings_generation(const rg_settings *s) { return s->gen; }

/* ------------------------------------------------------------- menu helpers */
int rg_settings_step(rg_settings *s, int idx, int dir)
{
    if (idx < 0 || idx >= s->n) return RG_SET_UNKNOWN;
    entry *e = &s->e[idx];
    const rg_setting_def *d = &e->d;
    sval v = { e->eff.i, e->eff.f, NULL };
    int sg = dir < 0 ? -1 : 1;
    switch (d->type) {
    case RG_SET_BOOL: v.i = !v.i; break;
    case RG_SET_ENUM: v.i = ((v.i + sg) % d->enum_count + d->enum_count) % d->enum_count; break;
    case RG_SET_INT: {
        long x = (long)v.i + (long)sg * (d->step_i > 0 ? d->step_i : 1);
        v.i = (int)(x < d->min_i ? d->min_i : x > d->max_i ? d->max_i : x);
        break;
    }
    case RG_SET_FLOAT: {
        double st = d->step_f > 0 ? d->step_f : (d->max_f - d->min_f) / 20.0;
        double x = v.f + sg * st;
        /* snap to the step grid (from the minimum) so steps do not drift */
        if (st > 0) x = d->min_f + floor((x - d->min_f) / st + 0.5) * st;
        x = x < d->min_f ? d->min_f : x > d->max_f ? d->max_f : x;
        char t[32];
        snprintf(t, sizeof t, "%.6g", x);   /* clean decimal (0.3, not 0.30000000000000004) */
        v.f = strtod(t, NULL);
        if (v.f < d->min_f) v.f = d->min_f;
        if (v.f > d->max_f) v.f = d->max_f;
        break;
    }
    default:
        return RG_SET_TYPE;
    }
    return set_checked(s, idx, &v, RG_SRC_MENU);
}

int rg_settings_trial_begin(rg_settings *s, int idx, uint64_t now_ms, uint32_t timeout_ms)
{
    if (idx < 0 || idx >= s->n) return -1;
    if (!s->trial_on) { s->trial_on = 1; s->ntrial = 0; }
    s->trial_deadline = now_ms + timeout_ms;
    s->trial_timeout = timeout_ms;
    for (int i = 0; i < s->ntrial; i++)
        if (s->trial[i].idx == idx) return 0;
    if (s->ntrial >= MAX_TRIAL) return -1;
    trial_slot *t = &s->trial[s->ntrial++];
    memset(t, 0, sizeof *t);
    t->idx = idx;
    sval_copy(&t->eff, &s->e[idx].eff);
    sval_copy(&t->base, &s->e[idx].base);
    t->src = s->e[idx].src;
    t->base_src = s->e[idx].base_src;
    t->overridden = s->e[idx].overridden;
    return 0;
}

static void trial_clear(rg_settings *s)
{
    for (int i = 0; i < s->ntrial; i++) { sval_free(&s->trial[i].eff); sval_free(&s->trial[i].base); }
    s->ntrial = 0;
    s->trial_on = 0;
}

void rg_settings_trial_confirm(rg_settings *s) { trial_clear(s); }

void rg_settings_trial_revert(rg_settings *s)
{
    for (int i = s->ntrial - 1; i >= 0; i--) {
        trial_slot *t = &s->trial[i];
        entry *e = &s->e[t->idx];
        sval old = { 0 };
        sval_copy(&old, &e->eff);
        sval_copy(&e->base, &t->base);
        sval_copy(&e->eff, &t->eff);
        e->src = t->src;
        e->base_src = t->base_src;
        e->overridden = t->overridden;
        int changed = !sval_eq(e, &old, &e->eff);
        sval_free(&old);
        if (changed) fire(s, t->idx);
    }
    trial_clear(s);
}

bool rg_settings_trial_active(const rg_settings *s) { return s->trial_on != 0; }

uint32_t rg_settings_trial_remaining(const rg_settings *s, uint64_t now_ms)
{
    if (!s->trial_on || now_ms >= s->trial_deadline) return 0;
    return (uint32_t)(s->trial_deadline - now_ms);
}

int rg_settings_tick(rg_settings *s, uint64_t now_ms)
{
    if (!s->trial_on || now_ms < s->trial_deadline) return 0;
    rg_settings_trial_revert(s);
    return 1;
}

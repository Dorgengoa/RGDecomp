/* SPDX-License-Identifier: CC0-1.0
 *
 * The native module table: the overlay manager of a native-only rg-game
 * (ovl.h, docs/OVERLAY.md section 8, PLAN.md D9).
 *
 * The five retail overlays are statically linked modules.  Each has its own data
 * segment (generated ovl_native_gen.c: `<ov>_seg`, its .data then its .bss, every
 * data/bss symbol a label in it) and a pristine .data image (relocated host words).
 * Retail's OverlayLoadFile (read the file over the arena, zero the bss after it,
 * run the .ctors range; no dtors, no entry point) becomes:
 *
 *     load(ovl):  copy the pristine .data into the segment, zero the .bss,
 *                 make ovl the active module, run its .ctors in table order.
 *
 * Reloading the active module does it all again (retail does).  No retail address
 * is used anywhere: there is no arena, no address map, no PS2 address arithmetic.
 * MAIN's calls to overlay code by retail name (`func_4F6AB0`, data2c slot names)
 * go through generated trampolines into rg_ovl_call_import_at(), which picks the
 * active module's entry of a build-time table (import x module).
 *
 * Differences to the arena manager (src/ps2/overlay), none observable by the game
 * as far as the retail code goes (docs/OVERLAY.md section 8 "Semantics"): overlays
 * no longer share bytes (a load does not clobber another overlay's data, which
 * retail code never reads while that overlay is not resident), there is no MWo3
 * header / text range in memory (nothing reads it), and no load address.
 *
 * Single-threaded: guest context only.
 */
#include "ovl.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UNKNOWN 128

static struct {
    const rg_ovl_registry *reg;
    int cur;
    int run_dtors;
    int fatal;
    uint64_t loads[RG_OVL_MAX];
    rg_ovl_report_fn report;
    void *report_user;
    rg_ovl_unknown unk[MAX_UNKNOWN];
    int nunk;
} M = {.cur = -1, .fatal = 1};

static rg_ovl_load_hook_fn g_load_hook;
static void *g_load_hook_user;

/* ------------------------------------------------------------ reporting */
/* records are keyed by (kind, module, name); `addr` stays 0 (no addresses) */
static void report(int kind, int ovl, const char *name, const char *msg)
{
    int i;
    for (i = 0; i < M.nunk; i++)
        if (M.unk[i].kind == kind && M.unk[i].ovl == ovl &&
            (M.unk[i].name == name || (M.unk[i].name && name && !strcmp(M.unk[i].name, name)))) {
            M.unk[i].count++;
            return;
        }
    if (M.nunk < MAX_UNKNOWN) {
        rg_ovl_unknown *u = &M.unk[M.nunk++];
        u->kind = kind;
        u->ovl = ovl;
        u->addr = 0;
        u->count = 1;
        u->name = name;
    }
    if (M.report)
        M.report(M.report_user, kind, ovl, 0, msg);
    else
        fprintf(stderr, "ovl: %s (module %s%s%s) -- reported once\n", msg,
                (M.reg && ovl >= 0 && ovl < M.reg->novls) ? M.reg->ovls[ovl].name : "-",
                name ? ", " : "", name ? name : "");
}

void rg_ovl_set_report(rg_ovl_report_fn fn, void *user)
{
    M.report = fn;
    M.report_user = user;
}

int rg_ovl_unknown_count(void) { return M.nunk; }
const rg_ovl_unknown *rg_ovl_unknown_get(int i) { return (i >= 0 && i < M.nunk) ? &M.unk[i] : NULL; }
void rg_ovl_unknown_clear(void) { M.nunk = 0; }
void rg_ovl_set_fatal(int on) { M.fatal = on; }
void rg_ovl_set_run_dtors(int on) { M.run_dtors = on; }

/* ------------------------------------------------------------ binding */
static int bind_fail(const char *what, int ovl)
{
    report(RG_OVL_REP_BIND, ovl, NULL, what);
    return -1;
}

void rg_ovl_unbind(void)
{
    memset(M.loads, 0, sizeof M.loads);
    M.reg = NULL;
    M.cur = -1;
}

int rg_ovl_bind(const rg_ovl_registry *reg)
{
    int i, k;
    rg_ovl_unbind();
    if (!reg || reg->novls <= 0 || reg->novls > RG_OVL_MAX)
        return bind_fail("registry: bad module count", -1);
    M.reg = reg;        /* for messages */
    if (reg->arena)
        return bind_fail("registry: an arena registry (retail addresses), not a module table", -1);
    for (i = 0; i < reg->novls; i++) {
        const rg_ovl_desc *d = &reg->ovls[i];
        if (!d->seg && (d->data_size || d->bss_size))
            return bind_fail("registry: module without a data segment", i);
        if (d->data_size && !d->data_image)
            return bind_fail("registry: module without a .data image", i);
        if (d->objects || d->funcs || d->labels)
            return bind_fail("registry: address-keyed tables in a module table", i);
    }
    for (k = 0; k < reg->nimports; k++)
        if (!reg->imports[k].fns || reg->imports[k].addr)
            return bind_fail("registry: import without a module table (or with an address)", -1);
    M.reg = reg;
    M.cur = -1;
    return 0;
}

const rg_ovl_registry *rg_ovl_bound(void) { return M.reg; }
int rg_ovl_count(void) { return M.reg ? M.reg->novls : 0; }

const rg_ovl_desc *rg_ovl_desc_at(int ovl)
{
    return (M.reg && ovl >= 0 && ovl < M.reg->novls) ? &M.reg->ovls[ovl] : NULL;
}

static int ieq(const char *a, const char *b)
{
    for (; *a && *b; a++, b++)
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
    return *a == *b;
}

int rg_ovl_find(const char *name)
{
    int i;
    if (!M.reg || !name)
        return -1;
    for (i = 0; i < M.reg->novls; i++)
        if (ieq(M.reg->ovls[i].name, name))
            return i;
    return -1;
}

int rg_ovl_find_index(int loader_index)
{
    int i;
    if (!M.reg)
        return -1;
    for (i = 0; i < M.reg->novls; i++)
        if (M.reg->ovls[i].index == loader_index)
            return i;
    return -1;
}

/* "cdrom0:\BIN\NORMAL.BIN;1", "host0:BIN/normal.bin" -> the module named by the
 * file name (the device and directory and the ";1" version do not matter) */
int rg_ovl_find_file(const char *path)
{
    const char *base = path, *p;
    char buf[64];
    size_t n;
    int i;
    if (!M.reg || !path)
        return -1;
    for (p = path; *p; p++)
        if (*p == '\\' || *p == '/' || *p == ':')
            base = p + 1;
    for (n = 0; base[n] && base[n] != ';' && n < sizeof buf - 1; n++)
        buf[n] = base[n];
    buf[n] = 0;
    for (i = 0; i < M.reg->novls; i++)
        if (ieq(M.reg->ovls[i].file, buf))
            return i;
    return -1;
}

/* ------------------------------------------------------------ load */
void rg_ovl_set_load_hook(rg_ovl_load_hook_fn fn, void *user)
{
    g_load_hook = fn;
    g_load_hook_user = user;
}

int rg_ovl_load(int ovl)
{
    const rg_ovl_desc *d = rg_ovl_desc_at(ovl);
    int k;
    if (!d)
        return -1;
    if (g_load_hook)
        g_load_hook(g_load_hook_user, ovl, 0);
    if (M.run_dtors && M.cur >= 0) {
        const rg_ovl_desc *o = &M.reg->ovls[M.cur];
        for (k = 0; k < o->ndtors; k++)
            if (o->dtors[k])
                o->dtors[k]();
    }
    if (d->data_size)
        memcpy(d->seg, d->data_image, d->data_size);            /* pristine .data */
    if (d->bss_size)
        memset(d->seg + d->data_size, 0, d->bss_size);          /* .bss */
    M.cur = ovl;            /* active from here on: ctors may call into it */
    M.loads[ovl]++;
    for (k = 0; k < d->nctors; k++)
        if (d->ctors[k])
            d->ctors[k]();
    if (g_load_hook)
        g_load_hook(g_load_hook_user, ovl, 1);
    return 0;
}

int rg_ovl_current(void) { return M.cur; }

uint64_t rg_ovl_load_count(int ovl)
{
    uint64_t n = 0;
    int i;
    if (ovl >= 0)
        return ovl < RG_OVL_MAX ? M.loads[ovl] : 0;
    for (i = 0; i < RG_OVL_MAX; i++)
        n += M.loads[i];
    return n;
}

/* ------------------------------------------------------------ imports */
static int missing_stub(void) { return 0; }

void *rg_ovl_call_import_at(const rg_ovl_import *tab, int idx)
{
    const rg_ovl_import *im = &tab[idx];
    rg_ovl_fn f = NULL;
    if (M.cur < 0) {
        report(RG_OVL_REP_NOT_RESIDENT, -1, im->name, "MAIN calls overlay code before any module load");
    } else {
        f = im->fns[M.cur];
        if (im->domain >= 0 && im->domain != M.cur)
            report(RG_OVL_REP_DOMAIN, M.cur, im->name,
                   "MAIN data slot of another module called; using the active one");
        if (!f)
            report(RG_OVL_REP_UNKNOWN_FN, M.cur, im->name,
                   "MAIN calls an import the active module does not define");
    }
    if (f)
        return (void *)f;
    if (M.fatal) {
        fprintf(stderr, "ovl: fatal: %s has no target in module %s -- aborting\n", im->name,
                M.cur >= 0 ? M.reg->ovls[M.cur].name : "(none)");
        abort();
    }
    return (void *)missing_stub;
}

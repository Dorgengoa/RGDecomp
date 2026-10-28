/* SPDX-License-Identifier: CC0-1.0
 * Overlay manager core (ovl.h, docs/OVERLAY.md).  No dependencies beyond libc. */
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
    unsigned char *pristine[RG_OVL_MAX];    /* object mode: initial bytes of each object */
    rg_ovl_report_fn report;
    void *report_user;
    rg_ovl_unknown unk[MAX_UNKNOWN];
    int nunk;
} M = {.cur = -1, .fatal = 1};

/* ------------------------------------------------------------ reporting */
static void report(int kind, int ovl, uint32_t addr, const char *name, const char *msg)
{
    int i;
    for (i = 0; i < M.nunk; i++)
        if (M.unk[i].kind == kind && M.unk[i].ovl == ovl && M.unk[i].addr == addr) {
            M.unk[i].count++;
            return;
        }
    if (M.nunk < MAX_UNKNOWN) {
        rg_ovl_unknown *u = &M.unk[M.nunk++];
        u->kind = kind;
        u->ovl = ovl;
        u->addr = addr;
        u->count = 1;
        u->name = name;
    }
    if (M.report)
        M.report(M.report_user, kind, ovl, addr, msg);
    else
        fprintf(stderr, "ovl: %s (overlay %s, 0x%08X%s%s) -- reported once\n", msg,
                (M.reg && ovl >= 0 && ovl < M.reg->novls) ? M.reg->ovls[ovl].name : "-",
                addr, name ? ", " : "", name ? name : "");
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
static uint32_t ovl_end(const rg_ovl_desc *d)
{
    return d->load + RG_OVL_HDR_SIZE + d->text_size + d->data_size + d->bss_size;
}

static uint32_t data_vram(const rg_ovl_desc *d) { return d->load + RG_OVL_HDR_SIZE + d->text_size; }
static uint32_t bss_vram(const rg_ovl_desc *d) { return data_vram(d) + d->data_size; }

static int bind_fail(const char *what, int ovl)
{
    report(RG_OVL_REP_BIND, ovl, 0, NULL, what);
    return -1;
}

void rg_ovl_unbind(void)
{
    int i;
    for (i = 0; i < RG_OVL_MAX; i++) {
        free(M.pristine[i]);
        M.pristine[i] = NULL;
        M.loads[i] = 0;
    }
    M.reg = NULL;
    M.cur = -1;
}

int rg_ovl_bind(const rg_ovl_registry *reg)
{
    int i, k;
    rg_ovl_unbind();
    if (!reg || reg->novls <= 0 || reg->novls > RG_OVL_MAX)
        return bind_fail("registry: bad overlay count", -1);
    M.reg = reg;        /* for messages */
    for (i = 0; i < reg->novls; i++) {
        const rg_ovl_desc *d = &reg->ovls[i];
        if (d->load != reg->arena_base)
            return bind_fail("registry: load address != arena base", i);
        if (ovl_end(d) > reg->arena_base + reg->arena_size)
            return bind_fail("registry: overlay larger than the arena", i);
        if (!d->data_image && !d->objects && d->data_size)
            return bind_fail("registry: no data image and no objects", i);
        for (k = 1; k < d->nfuncs; k++)
            if (d->funcs[k - 1].addr >= d->funcs[k].addr)
                return bind_fail("registry: function table not strictly sorted", i);
        for (k = 1; k < d->nlabels; k++)
            if (d->labels[k - 1].addr > d->labels[k].addr)
                return bind_fail("registry: label table not sorted", i);
        if (d->objects && d->nobjects) {
            size_t total = 0;
            unsigned char *p;
            for (k = 0; k < d->nobjects; k++)
                total += d->objects[k].size;
            p = (unsigned char *)malloc(total ? total : 1);
            if (!p)
                return bind_fail("registry: out of memory", i);
            total = 0;
            for (k = 0; k < d->nobjects; k++) {   /* initial image = before any ctor */
                if (d->objects[k].ptr)
                    memcpy(p + total, d->objects[k].ptr, d->objects[k].size);
                total += d->objects[k].size;
            }
            M.pristine[i] = p;
        }
    }
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
static void put32(unsigned char *p, uint32_t v)
{
    p[0] = (unsigned char)v;
    p[1] = (unsigned char)(v >> 8);
    p[2] = (unsigned char)(v >> 16);
    p[3] = (unsigned char)(v >> 24);
}

static void write_header(const rg_ovl_desc *d, unsigned char *h)
{
    size_t i;
    memset(h, 0, RG_OVL_HDR_SIZE);
    memcpy(h, "MWo3", 4);
    put32(h + 0x04, d->id);
    put32(h + 0x08, d->load);
    put32(h + 0x0C, d->text_size);
    put32(h + 0x10, d->data_size);
    put32(h + 0x14, d->bss_size);
    put32(h + 0x18, d->ctor_start);
    put32(h + 0x1C, d->dtor_start);
    for (i = 0; d->name[i] && i < 15; i++)          /* "title.bin" */
        h[0x20 + i] = (unsigned char)tolower((unsigned char)d->name[i]);
    if (i + 4 < 16)
        memcpy(h + 0x20 + i, ".bin", 4);
}

static rg_ovl_load_hook_fn g_load_hook;
static void *g_load_hook_user;

void rg_ovl_set_load_hook(rg_ovl_load_hook_fn fn, void *user)
{
    g_load_hook = fn;
    g_load_hook_user = user;
}

int rg_ovl_load(int ovl)
{
    const rg_ovl_desc *d = rg_ovl_desc_at(ovl);
    const rg_ovl_registry *r = M.reg;
    int k;
    if (!d)
        return -1;
    if (g_load_hook)
        g_load_hook(g_load_hook_user, ovl, 0);
    if (M.run_dtors && M.cur >= 0) {
        const rg_ovl_desc *o = &r->ovls[M.cur];
        for (k = 0; k < o->ndtors; k++)
            if (o->dtors[k])
                o->dtors[k]();
    }
    if (r->arena) {
        unsigned char *a = r->arena;
        write_header(d, a);
        /* text: retail's file read overwrites it with code nobody reads as data */
        memset(a + RG_OVL_HDR_SIZE, 0, d->text_size);
        if (d->data_image)
            memcpy(a + (data_vram(d) - r->arena_base), d->data_image, d->data_size);
        if (!d->objects)
            memset(a + (bss_vram(d) - r->arena_base), 0, d->bss_size);
    }
    if (d->objects) {
        size_t off = 0;
        for (k = 0; k < d->nobjects; k++) {
            const rg_ovl_object *o = &d->objects[k];
            if (o->ptr) {
                if (o->addr >= bss_vram(d))
                    memset(o->ptr, 0, o->size);
                else
                    memcpy(o->ptr, M.pristine[ovl] + off, o->size);
            }
            off += o->size;
        }
    }
    M.cur = ovl;            /* resident from here on: ctors may call into it */
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

/* ------------------------------------------------------------ address map */
static const rg_ovl_func *find_func(const rg_ovl_desc *d, uint32_t addr)
{
    int lo = 0, hi = d->nfuncs - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (d->funcs[mid].addr == addr)
            return &d->funcs[mid];
        if (d->funcs[mid].addr < addr)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return NULL;
}

rg_ovl_fn rg_ovl_lookup_fn(int ovl, uint32_t addr)
{
    const rg_ovl_desc *d = rg_ovl_desc_at(ovl);
    const rg_ovl_func *f = d ? find_func(d, addr) : NULL;
    return f ? f->fn : NULL;
}

const char *rg_ovl_fn_name(int ovl, uint32_t addr)
{
    const rg_ovl_desc *d = rg_ovl_desc_at(ovl);
    const rg_ovl_func *f = d ? find_func(d, addr) : NULL;
    return f ? f->name : NULL;
}

rg_ovl_fn rg_ovl_resolve_fn(uint32_t addr)
{
    rg_ovl_fn f;
    if (M.cur < 0) {
        report(RG_OVL_REP_NOT_RESIDENT, -1, addr, NULL, "call into the arena with no overlay loaded");
        return NULL;
    }
    f = rg_ovl_lookup_fn(M.cur, addr);
    if (!f)
        report(RG_OVL_REP_UNKNOWN_FN, M.cur, addr, NULL,
               "call to an address that is no function entry of the resident overlay");
    return f;
}

void *rg_ovl_host_ptr(uint32_t addr)
{
    const rg_ovl_registry *r = M.reg;
    if (!r || !r->arena || addr < r->arena_base || addr >= r->arena_base + r->arena_size)
        return NULL;
    return r->arena + (addr - r->arena_base);
}

uint32_t rg_ovl_ps2_addr(const void *p)
{
    const rg_ovl_registry *r = M.reg;
    const unsigned char *c = (const unsigned char *)p;
    int i, k;
    if (!r)
        return 0;
    if (r->arena && c >= r->arena && c < r->arena + r->arena_size)
        return r->arena_base + (uint32_t)(c - r->arena);
    for (i = 0; i < r->novls; i++)      /* object mode */
        for (k = 0; k < r->ovls[i].nobjects; k++) {
            const rg_ovl_object *o = &r->ovls[i].objects[k];
            if (o->ptr && c >= o->ptr && c < o->ptr + o->size)
                return o->addr + (uint32_t)(c - o->ptr);
        }
    return 0;
}

void *rg_ovl_resident_ptr(int ovl, uint32_t addr)
{
    const rg_ovl_desc *d = rg_ovl_desc_at(ovl);
    int k;
    if (!d || ovl != M.cur || addr < data_vram(d) || addr >= ovl_end(d))
        return NULL;
    if (d->objects) {
        for (k = 0; k < d->nobjects; k++) {
            const rg_ovl_object *o = &d->objects[k];
            if (addr >= o->addr && addr < o->addr + o->size)
                return o->ptr ? o->ptr + (addr - o->addr) : NULL;
        }
        return NULL;
    }
    return rg_ovl_host_ptr(addr);
}

const char *rg_ovl_label_at(int ovl, uint32_t addr, uint32_t *off)
{
    const rg_ovl_desc *d = rg_ovl_desc_at(ovl);
    int lo, hi, best = -1;
    if (!d || !d->nlabels)
        return NULL;
    lo = 0;
    hi = d->nlabels - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (d->labels[mid].addr <= addr) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (best < 0)
        return NULL;
    if (off)
        *off = addr - d->labels[best].addr;
    return d->labels[best].name;
}

void *rg_ovl_hwbus_resolve(void *user, const char *ovl, const char *sym, uint32_t sym_addr)
{
    int i = rg_ovl_find(ovl);
    void *p;
    (void)user;
    if (i < 0) {
        report(RG_OVL_REP_NOT_RESIDENT, -1, sym_addr, sym, "RG_OVL_DATA names an unknown overlay");
        return NULL;
    }
    p = rg_ovl_resident_ptr(i, sym_addr);
    if (!p)
        report(RG_OVL_REP_NOT_RESIDENT, i, sym_addr, sym,
               "RG_OVL_DATA of an overlay that is not resident (or outside its data/bss)");
    return p;
}

/* ------------------------------------------------------------ imports */
static int missing_stub(void) { return 0; }

void *rg_ovl_call_import_at(const rg_ovl_import *tab, int idx)
{
    const rg_ovl_import *im = &tab[idx];
    rg_ovl_fn f = NULL;
    if (M.cur < 0) {
        report(RG_OVL_REP_NOT_RESIDENT, -1, im->addr, im->name, "MAIN calls into the arena before any overlay load");
    } else {
        f = rg_ovl_lookup_fn(M.cur, im->addr);
        if (im->domain >= 0 && im->domain != M.cur)
            report(RG_OVL_REP_DOMAIN, M.cur, im->addr, im->name,
                   "MAIN data slot attributed to another overlay called; using the resident one");
        if (!f)
            report(RG_OVL_REP_UNKNOWN_FN, M.cur, im->addr, im->name,
                   "MAIN calls an address that is no function entry of the resident overlay");
    }
    if (f)
        return (void *)f;
    if (M.fatal) {
        fprintf(stderr, "ovl: fatal: %s (0x%08X) has no target -- aborting\n", im->name, im->addr);
        abort();
    }
    return (void *)missing_stub;
}

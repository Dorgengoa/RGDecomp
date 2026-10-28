/* SPDX-License-Identifier: CC0-1.0 */
/* Native IOP lane: mode switch and census counters. See rg_iop.h, docs/NATIVE-IOP.md. */
#include "rg_iop.h"

#include <stdlib.h>
#include <string.h>

static struct {
    int mode_set;
    int mode;
    int requested; /* -1 = not read yet */
} M = {0, RG_IOP_MODE_NATIVE, -1};

int rg_iop_requested_mode(void)
{
    if (M.requested < 0) {
        const char *e = getenv("RG_IOP");
        M.requested = (e && (!strcmp(e, "hle") || !strcmp(e, "HLE") || !strcmp(e, "1"))) ? RG_IOP_MODE_HLE : RG_IOP_MODE_NATIVE;
#if !RG_IOP_ORACLE
        if (M.requested == RG_IOP_MODE_HLE) {
            fprintf(stderr, "rg_iop: RG_IOP=%s ignored: native-only build (no IOP HLE compiled in)\n", e);
            M.requested = RG_IOP_MODE_NATIVE;
        }
#endif
    }
    return M.requested;
}

int rg_iop_mode(void)
{
    if (!M.mode_set) {
        M.mode = rg_iop_requested_mode();
        M.mode_set = 1;
    }
    return M.mode;
}

/* (parenthesised: native-only builds make the names constant macros, rg_iop.h) */
int (rg_iop_native)(void) { return rg_iop_mode() == RG_IOP_MODE_NATIVE; }
int (rg_iop_hle)(void) { return rg_iop_mode() == RG_IOP_MODE_HLE; }

void rg_iop_set_mode(int mode)
{
    M.mode = mode == RG_IOP_MODE_HLE ? RG_IOP_MODE_HLE : RG_IOP_MODE_NATIVE;
#if !RG_IOP_ORACLE
    M.mode = RG_IOP_MODE_NATIVE; /* native-only build: no HLE to switch to */
#endif
    M.mode_set = 1;
}

/* ---- census: open-addressing table keyed by (name pointer, id) ---------------- */
#define CAP 1024
typedef struct row {
    const char *name;
    uint32_t id;
    uint8_t layer; /* 0 api, 1 hle */
    uint64_t n;
} row;
static row g_rows[CAP];
static int g_nrows;
static uint64_t g_hle_total, g_hle_native, g_api_total, g_unconv;
static int g_assert = -1;

static row *find(const char *name, uint32_t id, int layer)
{
    uintptr_t h = ((uintptr_t)name >> 2) * 2654435761u ^ id * 40503u ^ (uintptr_t)layer;
    for (int i = 0; i < CAP; i++) {
        row *r = &g_rows[(h + (uintptr_t)i) & (CAP - 1)];
        if (!r->name) {
            if (g_nrows >= CAP - 1)
                return NULL;
            r->name = name;
            r->id = id;
            r->layer = (uint8_t)layer;
            g_nrows++;
            return r;
        }
        if (r->name == name && r->id == id && r->layer == layer)
            return r;
    }
    return NULL;
}

void rg_iop_count_api(const char *name, uint32_t id)
{
    row *r = find(name, id, 0);
    if (r)
        r->n++;
    g_api_total++;
}

void rg_iop_count_hle(const char *name, uint32_t id)
{
    row *r = find(name, id, 1);
    if (r)
        r->n++;
    g_hle_total++;
    if (rg_iop_native()) {
        g_hle_native++;
        if (g_assert < 0) {
            const char *e = getenv("RG_IOP_ASSERT");
            g_assert = e && *e && *e != '0';
        }
        if (g_assert) {
            fprintf(stderr, "rg_iop: FATAL: HLE entry %s (0x%X) in native mode (RG_IOP_ASSERT)\n", name,
                    (unsigned)id);
            fflush(stderr);
            abort();
        }
    }
}

void rg_iop_unconverted(const char *name, uint32_t id)
{
    row *r = find(name, id, 2);
    if (r && r->n++ == 0)
        fprintf(stderr, "rg_iop: native mode: unconverted IOP use %s (0x%X): no native service, ignored\n", name,
                (unsigned)id);
    g_unconv++;
}

uint64_t rg_iop_unconverted_total(void) { return g_unconv; }

static uint32_t g_heap_next;
uint32_t rg_iop_native_heap_handle(uint32_t size)
{
    if (g_heap_next < 0x000C0000u || g_heap_next + size + 256u > 0x001F0000u)
        g_heap_next = 0x000C0000u;
    uint32_t a = g_heap_next;
    g_heap_next += (size + 255u) & ~255u;
    if (g_heap_next == a)
        g_heap_next += 256u;
    return a;
}

uint64_t rg_iop_hle_total(void) { return g_hle_total; }
uint64_t rg_iop_hle_total_native(void) { return g_hle_native; }

static uint64_t count_by(const char *name, int layer)
{
    uint64_t n = 0;
    for (int i = 0; i < CAP; i++)
        if (g_rows[i].name && g_rows[i].layer == layer && !strcmp(g_rows[i].name, name))
            n += g_rows[i].n;
    return n;
}

uint64_t rg_iop_api_count(const char *name) { return count_by(name, 0); }
uint64_t rg_iop_hle_count(const char *name) { return count_by(name, 1); }

void rg_iop_census_reset(void)
{
    memset(g_rows, 0, sizeof g_rows);
    g_nrows = 0;
    g_hle_total = g_hle_native = g_api_total = g_unconv = 0;
}

static int cmp_row(const void *a, const void *b)
{
    const row *x = (const row *)a, *y = (const row *)b;
    if (x->layer != y->layer)
        return x->layer - y->layer;
    int c = strcmp(x->name, y->name);
    if (c)
        return c;
    return x->id < y->id ? -1 : x->id > y->id;
}

int rg_iop_census_write(FILE *f)
{
    row *v = (row *)malloc(sizeof(row) * (size_t)(g_nrows ? g_nrows : 1));
    int n = 0;
    if (!v)
        return -1;
    for (int i = 0; i < CAP; i++)
        if (g_rows[i].name)
            v[n++] = g_rows[i];
    qsort(v, (size_t)n, sizeof *v, cmp_row);
    fprintf(f, "# rg_iop census: mode %s (requested %s); layer api = SDK entries the game reached, "
               "hle = entries into src/ps2/{sif,iop}, padman/mcserv, the sound HLE\n",
            rg_iop_native() ? "native" : "hle", rg_iop_requested_mode() == RG_IOP_MODE_HLE ? "hle" : "native");
    fprintf(f, "layer\tname\tid\tcount\n");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s\t%s\t0x%X\t%llu\n", v[i].layer == 2 ? "unconverted" : v[i].layer ? "hle" : "api",
                v[i].name, (unsigned)v[i].id, (unsigned long long)v[i].n);
    fprintf(f, "# totals\tapi %llu\thle %llu\thle_in_native_mode %llu\tunconverted %llu\n",
            (unsigned long long)g_api_total, (unsigned long long)g_hle_total, (unsigned long long)g_hle_native,
            (unsigned long long)g_unconv);
    free(v);
    return 0;
}

void rg_iop_report(int quiet)
{
    const char *path = getenv("RG_IOP_CENSUS");
    if (path && *path) {
        FILE *f = fopen(path, "w");
        if (f) {
            rg_iop_census_write(f);
            fclose(f);
        } else {
            fprintf(stderr, "rg_iop: cannot write %s\n", path);
        }
    }
    if (!quiet)
        fprintf(stderr, "rg_iop: mode %s, %llu HLE entries (%llu in native mode), %llu SDK calls, %llu unconverted\n",
                rg_iop_native() ? "native" : "hle", (unsigned long long)g_hle_total,
                (unsigned long long)g_hle_native, (unsigned long long)g_api_total, (unsigned long long)g_unconv);
}

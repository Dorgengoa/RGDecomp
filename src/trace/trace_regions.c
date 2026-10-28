/* SPDX-License-Identifier: CC0-1.0
 * Region files (tools/trace/trace.py load_regions grammar), the port-side
 * annotations (tools/trace/port_regions.cfg) and the bytes each region
 * hashes (trace.py region_bytes semantics).  docs/TRACE-PORT.md. */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "rg_trace.h"

/* A 32-bit game-memory word can hold a host pointer: on i686, and on the x64 build, whose
 * whole address space is below 2 GB (strategy A, docs/X64-PLAN.md; without this the x64
 * trace read every stored host pointer as "ptr:?", e.g. sym:RandState). */
#if defined(_WIN64)
#define RG_TRACE_HOSTPTR32 1
#else
#define RG_TRACE_HOSTPTR32 (sizeof(void *) == 4)
#endif
static void seterr(char *err, size_t cap, const char *fmt, ...)
{
    if (!err || !cap)
        return;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(err, cap, fmt, ap);
    va_end(ap);
}

/* Python int(s, 0): 0x/0o/0b prefixes, decimal, '_' separators.  A leading 0
 * on a decimal number other than 0 is an error, as in Python. */
static int pyint(const char *s, uint64_t *out)
{
    char buf[80];
    size_t k = 0;
    for (const char *p = s; *p; p++) {
        if (*p == '_')
            continue;
        if (k + 1 >= sizeof buf)
            return -1;
        buf[k++] = *p;
    }
    buf[k] = 0;
    if (!k)
        return -1;
    int base = 10;
    const char *d = buf;
    if (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X')) base = 16, d = buf + 2;
    else if (buf[0] == '0' && (buf[1] == 'o' || buf[1] == 'O')) base = 8, d = buf + 2;
    else if (buf[0] == '0' && (buf[1] == 'b' || buf[1] == 'B')) base = 2, d = buf + 2;
    else if (buf[0] == '0' && buf[1]) {
        for (const char *p = buf; *p; p++)
            if (*p != '0')
                return -1;
        *out = 0;
        return 0;
    }
    if (!*d)
        return -1;
    uint64_t v = 0;
    for (const char *p = d; *p; p++) {
        int c = tolower((unsigned char)*p), dig;
        if (c >= '0' && c <= '9') dig = c - '0';
        else if (c >= 'a' && c <= 'z') dig = c - 'a' + 10;
        else return -1;
        if (dig >= base)
            return -1;
        v = v * (uint64_t)base + (uint64_t)dig;
    }
    *out = v;
    return 0;
}

static int split(char *line, char **tok, int max)
{
    char *h = strchr(line, '#');
    if (h)
        *h = 0;
    int n = 0;
    char *p = line;
    while (*p && n < max) {
        while (*p && isspace((unsigned char)*p))
            p++;
        if (!*p)
            break;
        tok[n++] = p;
        while (*p && !isspace((unsigned char)*p))
            p++;
        if (*p)
            *p++ = 0;
    }
    return n;
}

static rg_trace_region *push(rg_trace_regions *rs)
{
    if (rs->n == rs->cap) {
        int cap = rs->cap ? rs->cap * 2 : 64;
        rg_trace_region *r = (rg_trace_region *)realloc(rs->r, (size_t)cap * sizeof *r);
        if (!r)
            return NULL;
        rs->r = r;
        rs->cap = cap;
    }
    rg_trace_region *g = &rs->r[rs->n++];
    memset(g, 0, sizeof *g);
    return g;
}

static int space_of(const char *s)
{
    if (!strcmp(s, "ee")) return RG_TRACE_SPACE_EE;
    if (!strcmp(s, "iop")) return RG_TRACE_SPACE_IOP;
    if (!strcmp(s, "spr")) return RG_TRACE_SPACE_SPR;
    return -1;
}

static void dirname_of(const char *path, char *out, size_t cap)
{
    snprintf(out, cap, "%s", path);
    char *a = strrchr(out, '/'), *b = strrchr(out, '\\');
    char *s = a > b ? a : b;
    if (s)
        s[1] = 0;
    else
        out[0] = 0;
}

static int load(rg_trace_regions *rs, const char *path, char *err, size_t cap, int depth)
{
    if (depth > 8) {
        seterr(err, cap, "%s: include nesting too deep", path);
        return -1;
    }
    FILE *f = fopen(path, "r");
    if (!f) {
        seterr(err, cap, "cannot open %s", path);
        return -1;
    }
    char dir[512];
    dirname_of(path, dir, sizeof dir);
    char line[1024];
    int ln = 0, rc = 0;
    while (fgets(line, sizeof line, f)) {
        ln++;
        char *t[8];
        int n = split(line, t, 8);
        if (!n)
            continue;
        if (!strcmp(t[0], "include")) {
            char sub[1024];
            if (n < 2) {
                seterr(err, cap, "%s:%d: include needs a file", path, ln);
                rc = -1;
                break;
            }
            snprintf(sub, sizeof sub, "%s%s", dir, t[1]);
            if (load(rs, sub, err, cap, depth + 1) != 0) {
                rc = -1;
                break;
            }
            continue;
        }
        int sp = space_of(t[0]);
        if (n < 4 || sp < 0 || strlen(t[1]) >= sizeof rs->r[0].name - 10) {
            seterr(err, cap, "%s:%d: need 'space name start end [chunk]' or 'space name *PTR[+OFF] size'", path, ln);
            rc = -1;
            break;
        }
        if (t[2][0] == '*') {
            char *plus = strchr(t[2] + 1, '+');
            uint64_t ptr, off = 0, size;
            if (plus)
                *plus = 0;
            if (pyint(t[2] + 1, &ptr) || (plus && pyint(plus + 1, &off)) || pyint(t[3], &size) ||
                ptr > 0xFFFFFFFFu || off > 0xFFFFFFFFu || size > RG_TRACE_EE_RAM_SIZE) {
                seterr(err, cap, "%s:%d: bad deref region", path, ln);
                rc = -1;
                break;
            }
            rg_trace_region *g = push(rs);
            if (!g) { rc = -1; break; }
            snprintf(g->name, sizeof g->name, "%s", t[1]);
            g->space = sp;
            g->deref = 1;
            g->ptr = (uint32_t)ptr;
            g->off = (uint32_t)off;
            g->start = 0;
            g->end = (uint32_t)size;
            continue;
        }
        uint64_t a, b, chunk = 0;
        if (pyint(t[2], &a) || pyint(t[3], &b) || (n > 4 && pyint(t[4], &chunk)) || a > 0xFFFFFFFFu ||
            b > 0xFFFFFFFFu) {
            seterr(err, cap, "%s:%d: bad number", path, ln);
            rc = -1;
            break;
        }
        if (chunk) {
            for (uint64_t x = a; x < b; x += chunk) {
                rg_trace_region *g = push(rs);
                if (!g) { rc = -1; break; }
                snprintf(g->name, sizeof g->name, "%s@%08X", t[1], (unsigned)x);
                g->space = sp;
                g->start = (uint32_t)x;
                g->end = (uint32_t)(x + chunk < b ? x + chunk : b);
            }
            if (rc)
                break;
        } else {
            rg_trace_region *g = push(rs);
            if (!g) { rc = -1; break; }
            snprintf(g->name, sizeof g->name, "%s", t[1]);
            g->space = sp;
            g->start = (uint32_t)a;
            g->end = (uint32_t)b;
        }
    }
    fclose(f);
    return rc;
}

int rg_trace_regions_load(rg_trace_regions *rs, const char *path, char *err, size_t errcap)
{
    return load(rs, path, err, errcap, 0);
}

rg_trace_region *rg_trace_region_find(rg_trace_regions *rs, const char *name)
{
    for (int i = 0; i < rs->n; i++)
        if (!strcmp(rs->r[i].name, name))
            return &rs->r[i];
    return NULL;
}

int rg_trace_portcfg_load(rg_trace_regions *rs, const char *path, char *err, size_t cap)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        seterr(err, cap, "cannot open %s", path);
        return -1;
    }
    char line[1024];
    int ln = 0, rc = 0;
    while (fgets(line, sizeof line, f)) {
        ln++;
        char *t[40];
        int n = split(line, t, 40);
        if (!n)
            continue;
        if (!strcmp(t[0], "exclude") || !strcmp(t[0], "pending"))
            continue; /* compare-side (port_trace.py) */
        if (strcmp(t[0], "ptrs") && strcmp(t[0], "ps2ptr")) {
            seterr(err, cap, "%s:%d: unknown keyword '%s'", path, ln, t[0]);
            rc = -1;
            break;
        }
        if (n < 2) {
            seterr(err, cap, "%s:%d: %s needs a region name", path, ln, t[0]);
            rc = -1;
            break;
        }
        rg_trace_region *g = rg_trace_region_find(rs, t[1]);
        if (!g) {
            seterr(err, cap, "%s:%d: no region '%s' in the region file", path, ln, t[1]);
            rc = -1;
            break;
        }
        if (!strcmp(t[0], "ps2ptr")) {
            g->ps2ptr = 1;
            continue;
        }
        for (int i = 2; i < n && !rc; i++) {
            char *p = t[i];
            while (p && *p) {
                char *c = strchr(p, ',');
                if (c)
                    *c = 0;
                uint64_t o;
                if (*p) {
                    if (pyint(p, &o) || g->nslots >= RG_TRACE_MAX_SLOTS) {
                        seterr(err, cap, "%s:%d: bad slot offset '%s' (max %d slots)", path, ln, p,
                               RG_TRACE_MAX_SLOTS);
                        rc = -1;
                        break;
                    }
                    g->slots[g->nslots++] = (uint32_t)o;
                }
                p = c ? c + 1 : NULL;
            }
        }
        if (rc)
            break;
        if (!g->nslots) {
            seterr(err, cap, "%s:%d: ptrs needs offsets", path, ln);
            rc = -1;
            break;
        }
    }
    fclose(f);
    return rc;
}

void rg_trace_regions_free(rg_trace_regions *rs)
{
    free(rs->r);
    rs->r = NULL;
    rs->n = rs->cap = 0;
}

/* ---------------------------------------------------------------- bytes */
static uint32_t le32(const uint8_t *p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }
static void st32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

int rg_trace_host_readable(const void *p, size_t n)
{
#ifdef _WIN32
    const uint8_t *a = (const uint8_t *)p, *end = a + n;
    while (a < end) {
        MEMORY_BASIC_INFORMATION mi;
        if (!VirtualQuery(a, &mi, sizeof mi) || mi.State != MEM_COMMIT ||
            (mi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) ||
            !(mi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ |
                            PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            return 0;
        const uint8_t *next = (const uint8_t *)mi.BaseAddress + mi.RegionSize;
        if (next <= a)
            return 0;
        a = next;
    }
    return 1;
#else
    (void)p;
    (void)n;
    return 0; /* no portable check: an untranslatable host pointer gets a marker */
#endif
}

static int marker(uint8_t *buf, size_t cap, const char *fmt, uint32_t v)
{
    char m[32];
    int k = snprintf(m, sizeof m, fmt, v);
    if (k < 0 || (size_t)k > cap)
        return -1;
    memcpy(buf, m, (size_t)k);
    return k;
}

size_t rg_trace_region_max_bytes(const rg_trace_region *rg)
{
    size_t n = rg->end - rg->start;
    if (rg->deref && n < 32)
        n = 32;
    return n;
}

int rg_trace_region_bytes(const rg_trace_region *rg, int ps2_pointers, uint8_t *buf, size_t cap, char *why,
                          size_t whycap, int *untranslated)
{
    int ps2 = ps2_pointers || rg->ps2ptr;
    uint32_t bad = 0;
    if (why && whycap)
        why[0] = 0;
    if (rg->space != RG_TRACE_SPACE_EE) {
        seterr(why, whycap, "space %s has no port equivalent", rg->space == RG_TRACE_SPACE_IOP ? "iop" : "spr");
        return -1;
    }
    uint32_t n;
    if (!rg->deref) {
        /* trace.py slices data[a:b]: clipped at the end of EE RAM */
        uint32_t a = rg->start, b = rg->end < RG_TRACE_EE_RAM_SIZE ? rg->end : RG_TRACE_EE_RAM_SIZE;
        n = b > a ? b - a : 0;
        if (n > cap)
            return -1;
        if (n && rg_trace_read(a, buf, n, &bad) != 0) {
            seterr(why, whycap, "unmapped at 0x%08X", bad);
            return -1;
        }
    } else {
        uint8_t w[4];
        n = rg->end;
        if (rg_trace_read(rg->ptr, w, 4, &bad) != 0) {
            seterr(why, whycap, "pointer 0x%08X unmapped", rg->ptr);
            return -1;
        }
        uint32_t v = le32(w);
        if (ps2) {
            /* trace.py: ptr = u32 & 0x1FFFFFFF; null or past RAM -> "ptr:%08x" */
            uint32_t p = v & 0x1FFFFFFFu;
            uint64_t a = (uint64_t)p + rg->off;
            if (p == 0 || a + n > RG_TRACE_EE_RAM_SIZE)
                return marker(buf, cap, "ptr:%08x", p);
            if (n > cap)
                return -1;
            if (rg_trace_read((uint32_t)a, buf, n, &bad) != 0) {
                seterr(why, whycap, "pointee unmapped at 0x%08X", bad);
                return -1;
            }
        } else {
            if (v == 0)
                return marker(buf, cap, "ptr:%08x", 0);
            if (!RG_TRACE_HOSTPTR32) {
                if (untranslated)
                    ++*untranslated;
                return marker(buf, cap, "ptr:?%08x", v); /* a 32-bit field can't hold a host pointer */
            }
            const uint8_t *hp = (const uint8_t *)(uintptr_t)v + rg->off;
            uint32_t pa;
            if (n > cap)
                return -1;
            if (rg_trace_ps2_addr(hp, &pa) == 0 && rg_trace_read(pa, buf, n, &bad) == 0) {
                /* read through the map: the same bytes, but spanning objects safely */
            } else if (rg_trace_host_readable(hp, n)) {
                memcpy(buf, hp, n);
                seterr(why, whycap, "deref of host pointer %08x outside the address map (read raw)", v);
                if (untranslated)
                    ++*untranslated;
            } else {
                if (untranslated)
                    ++*untranslated;
                return marker(buf, cap, "ptr:?%08x", v);
            }
        }
    }
    if (!ps2) {
        for (int i = 0; i < rg->nslots; i++) {
            uint32_t o = rg->slots[i];
            if ((uint64_t)o + 4 > n)
                continue;
            uint32_t v = le32(buf + o), pa;
            if (!v)
                continue;
            if (RG_TRACE_HOSTPTR32 && rg_trace_ps2_addr((const void *)(uintptr_t)v, &pa) == 0)
                st32(buf + o, pa);
            else if (untranslated)
                ++*untranslated;
        }
    }
    return (int)n;
}

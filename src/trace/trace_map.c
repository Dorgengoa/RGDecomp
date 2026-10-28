/* SPDX-License-Identifier: CC0-1.0
 * PS2 address <-> host address map for the trace recorder (rg_trace.h,
 * docs/TRACE-PORT.md "Address map"). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ovl.h"
#include "rg_trace.h"

static struct {
    rg_trace_sym *by_addr;  /* sorted by PS2 address */
    rg_trace_sym *by_host;  /* sorted by host address (reverse map) */
    int n, cap;
    uint8_t *ram;           /* host address of PS2 address ram_lo (the game heap start) */
    uint32_t ram_lo, ram_hi;
    uint8_t *arena;
    uint32_t arena_base, arena_size;
    int arena_set;
} M;

static int cmp_addr(const void *a, const void *b)
{
    uint32_t x = ((const rg_trace_sym *)a)->addr, y = ((const rg_trace_sym *)b)->addr;
    return x < y ? -1 : x > y;
}

static int cmp_host(const void *a, const void *b)
{
    uintptr_t x = (uintptr_t)((const rg_trace_sym *)a)->host, y = (uintptr_t)((const rg_trace_sym *)b)->host;
    return x < y ? -1 : x > y;
}

int rg_trace_add_symbols(const rg_trace_sym *syms, int n)
{
    if (n <= 0)
        return 0;
    for (int i = 0; i < n; i++) {
        if (!syms[i].size || !syms[i].host) {
            fprintf(stderr, "rg_trace: symbol %s: empty or null\n", syms[i].name ? syms[i].name : "?");
            return -1;
        }
    }
    int total = M.n + n;
    rg_trace_sym *a = (rg_trace_sym *)malloc((size_t)total * sizeof *a);
    rg_trace_sym *h = (rg_trace_sym *)malloc((size_t)total * sizeof *h);
    if (!a || !h) {
        free(a);
        free(h);
        return -1;
    }
    if (M.n)
        memcpy(a, M.by_addr, (size_t)M.n * sizeof *a);
    memcpy(a + M.n, syms, (size_t)n * sizeof *syms);
    qsort(a, (size_t)total, sizeof *a, cmp_addr);
    for (int i = 1; i < total; i++) {
        const rg_trace_sym *p = &a[i - 1], *q = &a[i];
        if ((uint64_t)p->addr + p->size > q->addr) {
            fprintf(stderr, "rg_trace: symbols overlap: %s 0x%08X+0x%X and %s 0x%08X\n", p->name ? p->name : "?",
                    p->addr, p->size, q->name ? q->name : "?", q->addr);
            free(a);
            free(h);
            return -1;
        }
    }
    memcpy(h, a, (size_t)total * sizeof *a);
    qsort(h, (size_t)total, sizeof *h, cmp_host);
    free(M.by_addr);
    free(M.by_host);
    M.by_addr = a;
    M.by_host = h;
    M.n = M.cap = total;
    return 0;
}

int rg_trace_add_symbol(uint32_t addr, uint32_t size, void *host, const char *name)
{
    rg_trace_sym s;
    s.addr = addr;
    s.size = size;
    s.host = host;
    s.name = name;
    return rg_trace_add_symbols(&s, 1);
}

void rg_trace_clear_symbols(void)
{
    free(M.by_addr);
    free(M.by_host);
    M.by_addr = M.by_host = NULL;
    M.n = M.cap = 0;
}

int rg_trace_symbol_count(void) { return M.n; }

const rg_trace_sym *rg_trace_symbol_at(uint32_t addr)
{
    int lo = 0, hi = M.n - 1, best = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (M.by_addr[mid].addr <= addr) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (best < 0)
        return NULL;
    const rg_trace_sym *s = &M.by_addr[best];
    return addr - s->addr < s->size ? s : NULL;
}

void rg_trace_set_heap(void *host_start, uint32_t lo, uint32_t size)
{
    M.ram = (uint8_t *)host_start;
    M.ram_lo = lo;
    M.ram_hi = host_start ? (size > RG_TRACE_EE_RAM_SIZE - lo ? RG_TRACE_EE_RAM_SIZE : lo + size) : 0;
}

void rg_trace_set_ram(void *host, uint32_t lo, uint32_t hi)
{
    if (!host || hi <= lo)
        rg_trace_set_heap(NULL, 0, 0);
    else
        rg_trace_set_heap((uint8_t *)host + lo, lo, hi - lo);
}

void rg_trace_set_arena(void *host, uint32_t base, uint32_t size)
{
    M.arena = (uint8_t *)host;
    M.arena_base = base;
    M.arena_size = size;
    M.arena_set = host != NULL;
}

static int arena(uint8_t **host, uint32_t *base, uint32_t *size)
{
    if (M.arena_set) {
        *host = M.arena;
        *base = M.arena_base;
        *size = M.arena_size;
        return 1;
    }
    const rg_ovl_registry *r = rg_ovl_bound();
    if (r && r->arena && r->arena_size) {
        *host = r->arena;
        *base = r->arena_base;
        *size = r->arena_size;
        return 1;
    }
    return 0;
}

/* The native module table (src/native/ovl, docs/OVERLAY.md section 8) has no arena: each
 * overlay is a module with its own data segment (.data then .bss).  The ACTIVE module's
 * segment is what retail held at [load + 0x40 header + text_size, + data_size + bss_size)
 * of the arena (load = RG_TRACE_ARENA_BASE; the descriptor keeps text_size, a size, and no
 * address; the arena manager's data_vram() is the same sum), so a PS2 address there maps
 * into it.  The text range (retail code; zeros in the arena
 * manager) and the bytes past a module's .bss have no host memory: unmapped.  Reverse: a
 * pointer into any module's segment maps to that module's retail data address (segments
 * never overlap on the host, so this does not depend on which module is active). */
static uint32_t module_data_addr(const rg_ovl_desc *d)
{
    return (d->load ? d->load : RG_TRACE_ARENA_BASE) + RG_OVL_HDR_SIZE + d->text_size;
}

static void *module_host_ptr(uint32_t addr, uint32_t *avail)
{
    const rg_ovl_registry *r = rg_ovl_bound();
    const rg_ovl_desc *d;
    uint32_t lo, size;
    if (!r || r->arena || addr < RG_TRACE_ARENA_BASE || addr >= RG_TRACE_ARENA_END)
        return NULL;
    d = rg_ovl_desc_at(rg_ovl_current());
    if (!d || !d->seg || !d->text_size)
        return NULL;
    lo = module_data_addr(d);
    size = d->data_size + d->bss_size;
    if (addr < lo || addr - lo >= size)
        return NULL;
    if (avail)
        *avail = size - (addr - lo);
    return d->seg + (addr - lo);
}

static int module_ps2_addr(uintptr_t x, uint32_t *out)
{
    const rg_ovl_registry *r = rg_ovl_bound();
    int i;
    if (!r || r->arena)
        return -1;
    for (i = 0; i < r->novls; i++) {
        const rg_ovl_desc *d = &r->ovls[i];
        uint32_t size = d->data_size + d->bss_size;
        if (d->seg && d->text_size && x >= (uintptr_t)d->seg && x - (uintptr_t)d->seg < size) {
            *out = module_data_addr(d) + (uint32_t)(x - (uintptr_t)d->seg);
            return 0;
        }
    }
    return -1;
}

void *rg_trace_host_ptr(uint32_t addr, uint32_t *avail)
{
    const rg_trace_sym *s = rg_trace_symbol_at(addr);
    if (s) {
        if (avail)
            *avail = s->size - (addr - s->addr);
        return (uint8_t *)s->host + (addr - s->addr);
    }
    uint8_t *ah;
    uint32_t ab, as;
    if (arena(&ah, &ab, &as) && addr >= ab && addr - ab < as) {
        if (avail)
            *avail = as - (addr - ab);
        return ah + (addr - ab);
    }
    {
        void *mp = module_host_ptr(addr, avail);
        if (mp)
            return mp;
    }
    if (M.ram && addr >= M.ram_lo && addr < M.ram_hi) {
        if (avail)
            *avail = M.ram_hi - addr;
        return M.ram + (addr - M.ram_lo);
    }
    return NULL;
}

int rg_trace_read(uint32_t addr, void *dst, uint32_t n, uint32_t *bad)
{
    uint8_t *d = (uint8_t *)dst;
    uint64_t a = addr, end = (uint64_t)addr + n;
    while (a < end) {
        uint32_t avail = 0;
        void *p = a < 0x100000000ULL ? rg_trace_host_ptr((uint32_t)a, &avail) : NULL;
        if (!p || !avail) {
            if (bad)
                *bad = (uint32_t)a;
            return -1;
        }
        uint64_t k = end - a < avail ? end - a : avail;
        memcpy(d, p, (size_t)k);
        d += k;
        a += k;
    }
    return 0;
}

int rg_trace_ps2_addr(const void *p, uint32_t *out)
{
    uintptr_t x = (uintptr_t)p;
    int lo = 0, hi = M.n - 1, best = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if ((uintptr_t)M.by_host[mid].host <= x) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (best >= 0) {
        const rg_trace_sym *s = &M.by_host[best];
        if (x - (uintptr_t)s->host < s->size) {
            *out = s->addr + (uint32_t)(x - (uintptr_t)s->host);
            return 0;
        }
    }
    uint8_t *ah;
    uint32_t ab, as;
    if (arena(&ah, &ab, &as) && x >= (uintptr_t)ah && x - (uintptr_t)ah < as) {
        *out = ab + (uint32_t)(x - (uintptr_t)ah);
        return 0;
    }
    if (module_ps2_addr(x, out) == 0)
        return 0;
    if (M.ram && x >= (uintptr_t)M.ram && x - (uintptr_t)M.ram < M.ram_hi - M.ram_lo) {
        *out = M.ram_lo + (uint32_t)(x - (uintptr_t)M.ram);
        return 0;
    }
    return -1;
}

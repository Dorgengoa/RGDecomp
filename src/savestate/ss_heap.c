/* SPDX-License-Identifier: CC0-1.0
 * Port save states: the state region and the state heap
 * (docs/TEST-FIXTURES.md "Save states").
 *
 * The state region is three reservations made at the start of main, before
 * any window, GPU device or audio thread exists, so they land at the same
 * addresses in every run of the same build (a load checks that):
 *
 *   game heap   RG_CRT0_HEAP_ALLOC (26.7 MB) at 0x0A000000 (crt0 commits it and starts
 *               the heap at +0x200; docs/NATIVE-CPU.md section 8)
 *   fiber arena guest thread stacks (ps2k_ss.h), 64 MB at 0x0C100000
 *   state heap  every allocation made by game or model code, 256 MB
 *               reserved at 0x20000000
 * (fixed addresses; when one is taken the lowest free range is used and a
 * warning says that this process's states load nowhere else)
 *
 * The state heap replaces malloc/calloc/realloc/free/strdup for the
 * whole executable.  Each allocation is routed by its CALLER: code of a host
 * library (SDL, CRT, GPU renderer, host shell, settings, trace, native file
 * service, memory-card files, this module; ss_map.c) gets the CRT heap, all
 * other code (the game, the port's models) gets the state heap.  A free or
 * realloc goes to whichever heap holds the pointer.  The allocator keeps its
 * metadata inside the state heap, so saving [heap, top) raw and writing it
 * back at the same address restores every model allocation, every pointer
 * between them and the allocator itself.
 *
 * Init allocations happen in the same order in every run with the same
 * options, so their addresses are equal too: the loading process's host
 * code (GPU renderer -> gs_state, the runtime -> models) keeps valid
 * pointers into the restored heap.  ss_heap_init_fingerprint() hashes that
 * sequence; a load refuses a state whose saver had a different one.
 *
 * Allocator: boundary-tagged chunks (16-byte header, 16-byte aligned
 * payloads), 152 segregated free lists, first fit, coalescing on free, a
 * wilderness top that commits 1 MB at a time.  One lock (a host static).
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_runtime.h"   /* RG_CRT0_HEAP_ALLOC, RG_HEAP_DMA_* */
#include "rg_savestate.h"
#include "ss_internal.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#if defined(_WIN32) && (defined(__i386__) || defined(_M_IX86) || defined(__x86_64__))
#define SS_HEAP_SUPPORTED 1
/* the static UCRT's underlying heap functions (what its malloc & co. call) */
void *__cdecl _malloc_base(size_t);
void *__cdecl _calloc_base(size_t, size_t);
void *__cdecl _realloc_base(void *, size_t);
void __cdecl _free_base(void *);
#else
#define SS_HEAP_SUPPORTED 0
#endif

#define SS_RAM_SIZE   RG_CRT0_HEAP_ALLOC  /* the game heap + one page (crt0.c) */
#define SS_ARENA_SIZE (0x04000000u)        /* 64 MB: 60 guest stacks of 1 MB */
#define SS_HEAP_SIZE  (0x10000000u)        /* 256 MB reserved, committed as used */
#define SS_COMMIT_STEP (1u << 20)
/* Fixed addresses: what is free at main differs run to run (CRT heap
 * segments, loader allocations), so "lowest free" gave 0x05900000 in one run
 * and 0x05940000 in the next.  These ranges are free at main in practice;
 * reserving them first keeps every later allocation (window, GPU driver,
 * audio) out of them.  With RG_HEAP_DMA_PLACEMENT the game heap must end below
 * 0x10000000 (the emulated DMA path's 28-bit masks) and lie above the PS2 RAM range
 * (rg_runtime.h). */
#define SS_RAM_AT   0x0A000000u
#define SS_ARENA_AT 0x0C100000u
#define SS_HEAP_AT  0x20000000u

#define CH_HDR    16u
#define CH_MIN    32u
#define CH_INUSE  1u
#define CH_PINUSE 2u
#define NBINS     152
#define HS_MAGIC  0x50414548u /* "HEAP" */

typedef struct chunk {
    uint32_t size;      /* total bytes incl. header | CH_INUSE | CH_PINUSE */
    uint32_t prev_size; /* size of the previous chunk when it is free */
    uint32_t req;       /* requested bytes (in use) */
    uint32_t caller;    /* return address of the allocating call (audits) */
    /* free chunks: next, prev in the payload */
} chunk;

typedef struct free_links {
    struct chunk *next, *prev;
} free_links;

/* allocator state: at the start of the heap reservation (saved with it) */
typedef struct hstate {
    uint32_t magic;
    uint32_t version;
    uintptr_t first;     /* first chunk */
    uintptr_t top;       /* end of the last chunk = start of the wilderness */
    uintptr_t commit;    /* committed up to here */
    uintptr_t limit;     /* end of the reservation */
    uint32_t last_inuse; /* the chunk ending at top is in use (or there is none) */
    uint32_t pad;
    chunk *bin[NBINS];
    uint64_t allocs, frees, live;
} hstate;

static struct {
    int on;                 /* state heap active */
    int lock_init;
#ifdef _WIN32
    CRITICAL_SECTION lock;
#endif
    ss_region_info reg;
    hstate *hs;
    uint64_t fp;            /* init fingerprint */
    int fp_on;
    uint64_t host_allocs, model_allocs;
    /* pages this process really committed.  hs->commit lives in the heap and comes
     * back from the saver with a load: when the saver had committed past its top
     * (top shrinks on free, commit never), trusting it would let an allocation grow
     * into pages this process never committed (write fault in heap_alloc; found by
     * the native IOP lane, docs/NATIVE-IOP.md) */
    uintptr_t committed;
    char err[256];
} H;

/* ------------------------------------------------------------ hashing */
uint64_t ss_hash64(const void *p, size_t n, uint64_t seed)
{
    const uint8_t *b = (const uint8_t *)p;
    uint64_t h = 0xcbf29ce484222325ull ^ (seed * 0x9E3779B97F4A7C15ull);
    size_t i = 0;
    for (; i + 8 <= n; i += 8) {
        uint64_t v;
        memcpy(&v, b + i, 8);
        h ^= v;
        h *= 0x100000001b3ull;
        h ^= h >> 29;
    }
    for (; i < n; i++) {
        h ^= b[i];
        h *= 0x100000001b3ull;
    }
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccdull;
    h ^= h >> 33;
    return h;
}

static void fp_mix(uint32_t op, uint32_t a, uint32_t b)
{
    if (!H.fp_on)
        return;
    uint32_t v[3] = {op, a, b};
    H.fp = ss_hash64(v, sizeof v, H.fp);
}

/* ------------------------------------------------------------ region */
#if SS_HEAP_SUPPORTED
static uintptr_t reserve_lowest(uintptr_t from, size_t size, uintptr_t below)
{
    uintptr_t a = from;
    MEMORY_BASIC_INFORMATION mi;
    while (a + size <= below && VirtualQuery((void *)a, &mi, sizeof mi)) {
        uintptr_t rb = (uintptr_t)mi.BaseAddress, re = rb + mi.RegionSize;
        if (mi.State == MEM_FREE) {
            uintptr_t s = (a + 0xFFFFu) & ~(uintptr_t)0xFFFFu;
            if (s + size <= re && VirtualAlloc((void *)s, size, MEM_RESERVE, PAGE_READWRITE))
                return s;
        }
        if (re <= a)
            break;
        a = re;
    }
    return 0;
}
#endif

#if SS_HEAP_SUPPORTED
static uintptr_t reserve_at(uintptr_t a, size_t size)
{
    void *p = VirtualAlloc((void *)a, size, MEM_RESERVE, PAGE_READWRITE);
    if (p == (void *)a)
        return a;
    if (p)
        VirtualFree(p, 0, MEM_RELEASE);
    return 0;
}
#endif

static void lock(void)
{
#ifdef _WIN32
    if (H.lock_init)
        EnterCriticalSection(&H.lock);
#endif
}
static void unlock(void)
{
#ifdef _WIN32
    if (H.lock_init)
        LeaveCriticalSection(&H.lock);
#endif
}
void ss_heap_lock(void) { lock(); }
void ss_heap_unlock(void) { unlock(); }

int rg_ss_init(void)
{
    if (H.on)
        return 0;
    if (H.err[0])
        return -1;
#if SS_HEAP_SUPPORTED
    if (ss_map_load(H.err, sizeof H.err) != 0)
        return -1;
    int moved = 0;
    H.reg.ram = reserve_at(SS_RAM_AT, SS_RAM_SIZE);
    if (!H.reg.ram && (moved = 1))
#if RG_HEAP_DMA_PLACEMENT
        H.reg.ram = reserve_lowest(RG_HEAP_DMA_LO, SS_RAM_SIZE, RG_HEAP_DMA_HI);
#else
        H.reg.ram = reserve_lowest(0x04000000u, SS_RAM_SIZE, 0x7FFF0000u);
#endif
    if (H.reg.ram)
        H.reg.ram_size = SS_RAM_SIZE;
    H.reg.arena = reserve_at(SS_ARENA_AT, SS_ARENA_SIZE);
    if (!H.reg.arena && (moved = 1))
        H.reg.arena = reserve_lowest(H.reg.ram ? H.reg.ram + SS_RAM_SIZE : 0x04000000u, SS_ARENA_SIZE, 0x7FFF0000u);
    if (H.reg.arena)
        H.reg.arena_size = SS_ARENA_SIZE;
    H.reg.heap = reserve_at(SS_HEAP_AT, SS_HEAP_SIZE);
    if (!H.reg.heap && (moved = 1))
        H.reg.heap = reserve_lowest(H.reg.arena ? H.reg.arena + SS_ARENA_SIZE : 0x04000000u, SS_HEAP_SIZE, 0x7FFF0000u);
    if (moved)
        fprintf(stderr, "rg_savestate: warning: a fixed state range was taken; states of this process "
                        "will not load elsewhere (RAM %p, arena %p, heap %p)\n",
                (void *)H.reg.ram, (void *)H.reg.arena, (void *)H.reg.heap);
    if (!H.reg.ram || !H.reg.arena || !H.reg.heap) {
        snprintf(H.err, sizeof H.err, "cannot reserve the state region (RAM %p, arena %p, heap %p)",
                 (void *)H.reg.ram, (void *)H.reg.arena, (void *)H.reg.heap);
        return -1;
    }
    H.reg.heap_size = SS_HEAP_SIZE;
    if (!VirtualAlloc((void *)H.reg.heap, SS_COMMIT_STEP, MEM_COMMIT, PAGE_READWRITE)) {
        snprintf(H.err, sizeof H.err, "cannot commit the state heap");
        return -1;
    }
    hstate *hs = (hstate *)H.reg.heap;
    memset(hs, 0, sizeof *hs);
    hs->magic = HS_MAGIC;
    hs->version = 1;
    hs->first = (H.reg.heap + sizeof(hstate) + 15u) & ~(uintptr_t)15u;
    hs->top = hs->first;
    hs->commit = H.reg.heap + SS_COMMIT_STEP;
    H.committed = hs->commit;
    hs->limit = H.reg.heap + SS_HEAP_SIZE;
    hs->last_inuse = 1;
    H.hs = hs;
    InitializeCriticalSection(&H.lock);
    H.lock_init = 1;
    H.fp = 0x5354415445ull;
    H.fp_on = 1;
    H.on = 1;
    return 0;
#else
    snprintf(H.err, sizeof H.err, "save states need i686 Windows for now");
    return -1;
#endif
}

const char *rg_ss_error(void) { return H.err[0] ? H.err : NULL; }
int rg_ss_active(void) { return H.on; }
int ss_heap_on(void) { return H.on; }
const ss_region_info *ss_region(void) { return &H.reg; }

void *rg_ss_ram_alloc(size_t size)
{
#if SS_HEAP_SUPPORTED
    if (!H.on || size > H.reg.ram_size)
        return NULL;
    return VirtualAlloc((void *)H.reg.ram, size, MEM_COMMIT, PAGE_READWRITE);
#else
    (void)size;
    return NULL;
#endif
}

void rg_ss_arena(void **base, size_t *size)
{
    *base = H.on ? (void *)H.reg.arena : NULL;
    *size = H.on ? H.reg.arena_size : 0;
}

void rg_ss_mark_init_done(void)
{
    lock();
    H.fp_on = 0;
    unlock();
}

uint64_t ss_heap_init_fingerprint(void) { return H.fp; }

uintptr_t ss_heap_top(void) { return H.hs ? H.hs->top : 0; }

void ss_heap_stats(uint64_t out[6])
{
    out[0] = H.hs ? H.hs->allocs : 0;
    out[1] = H.hs ? H.hs->frees : 0;
    out[2] = H.hs ? H.hs->live : 0;
    out[3] = H.hs ? H.hs->top - H.reg.heap : 0;
    out[4] = H.host_allocs;
    out[5] = H.model_allocs;
}

#if SS_HEAP_SUPPORTED
static int commit_to(uintptr_t end)
{
    hstate *hs = H.hs;
    if (end <= H.committed)
        return 0;
    if (end > hs->limit)
        return -1;
    uintptr_t want = (end + SS_COMMIT_STEP - 1) & ~(uintptr_t)(SS_COMMIT_STEP - 1);
    if (want > hs->limit)
        want = hs->limit;
    if (!VirtualAlloc((void *)H.committed, want - H.committed, MEM_COMMIT, PAGE_READWRITE))
        return -1;
    H.committed = want;
    if (want > hs->commit)
        hs->commit = want;
    return 0;
}
#endif

int ss_heap_prepare(uintptr_t top)
{
#if SS_HEAP_SUPPORTED
    if (!H.on || top < H.reg.heap || top > H.reg.heap + H.reg.heap_size)
        return -1;
    uintptr_t want = (top + SS_COMMIT_STEP - 1) & ~(uintptr_t)(SS_COMMIT_STEP - 1);
    if (want > H.committed)
        return commit_to(want);
    return 0;
#else
    (void)top;
    return -1;
#endif
}

/* ------------------------------------------------------------ allocator */
static inline uint32_t csize(const chunk *c) { return c->size & ~(CH_INUSE | CH_PINUSE); }
static inline free_links *links(chunk *c) { return (free_links *)(c + 1); }

static int bin_of(uint32_t sz)
{
    if (sz < 1024)
        return (int)(sz >> 4);           /* 0..63 (sizes are >= 32) */
    int lg = 31 - __builtin_clz(sz);     /* 10..31 */
    int sub = (int)((sz >> (lg - 2)) & 3u);
    int b = 64 + (lg - 10) * 4 + sub;
    return b < NBINS ? b : NBINS - 1;
}

static void bin_insert(chunk *c)
{
    hstate *hs = H.hs;
    int b = bin_of(csize(c));
    free_links *l = links(c);
    l->prev = NULL;
    l->next = hs->bin[b];
    if (hs->bin[b])
        links(hs->bin[b])->prev = c;
    hs->bin[b] = c;
}

static void bin_remove(chunk *c)
{
    hstate *hs = H.hs;
    free_links *l = links(c);
    if (l->prev)
        links(l->prev)->next = l->next;
    else
        hs->bin[bin_of(csize(c))] = l->next;
    if (l->next)
        links(l->next)->prev = l->prev;
}

/* mark c (size sz, already out of the bins) in use; split off the rest */
static void use_chunk(chunk *c, uint32_t need)
{
    hstate *hs = H.hs;
    uint32_t sz = csize(c), pin = c->size & CH_PINUSE;
    if (sz - need >= CH_MIN) {
        chunk *r = (chunk *)((uint8_t *)c + need);
        uint32_t rs = sz - need;
        r->size = rs | CH_PINUSE;
        r->caller = 0;
        r->req = 0;
        chunk *after = (chunk *)((uint8_t *)r + rs);
        if ((uintptr_t)after < hs->top) {
            after->prev_size = rs;
            after->size &= ~CH_PINUSE;
        }
        bin_insert(r);
        sz = need;
    } else {
        chunk *after = (chunk *)((uint8_t *)c + sz);
        if ((uintptr_t)after < hs->top)
            after->size |= CH_PINUSE;
        else
            hs->last_inuse = 1;
    }
    c->size = sz | CH_INUSE | pin;
}

static void *heap_alloc(size_t n)
{
    hstate *hs = H.hs;
    if (n > 0x0FFFFFFFu)
        return NULL;
    uint32_t need = (uint32_t)((n + CH_HDR + 15u) & ~(size_t)15u);
    if (need < CH_MIN)
        need = CH_MIN;
    for (int b = bin_of(need); b < NBINS; b++) {
        for (chunk *c = hs->bin[b]; c; c = links(c)->next) {
            if (csize(c) >= need) {
                bin_remove(c);
                use_chunk(c, need);
                c->req = (uint32_t)n;
                hs->allocs++;
                hs->live += csize(c);
                return c + 1;
            }
            if (b >= 64)
                continue;      /* exact-size bins below 1 KB: any entry fits */
        }
    }
    /* the wilderness */
    uintptr_t at = hs->top;
#if SS_HEAP_SUPPORTED
    if (commit_to(at + need) != 0)
        return NULL;
#endif
    chunk *c = (chunk *)at;
    c->caller = 0;
    c->size = need | CH_INUSE | (hs->last_inuse ? CH_PINUSE : 0);
    c->req = (uint32_t)n;
    hs->top = at + need;
    hs->last_inuse = 1;
    hs->allocs++;
    hs->live += need;
    return c + 1;
}

static void heap_free(void *p)
{
    hstate *hs = H.hs;
    chunk *c = (chunk *)p - 1;
    if (!(c->size & CH_INUSE) || csize(c) < CH_MIN || (uintptr_t)c + csize(c) > hs->top) {
        fprintf(stderr, "rg_savestate: state heap: bad free %p\n", p);
        abort();
    }
    uint32_t sz = csize(c);
    hs->frees++;
    hs->live -= sz;
    c->size &= ~CH_INUSE;
    /* coalesce with the previous chunk */
    if (!(c->size & CH_PINUSE) && (uintptr_t)c > hs->first) {
        chunk *pv = (chunk *)((uint8_t *)c - c->prev_size);
        bin_remove(pv);
        sz += csize(pv);
        pv->size = sz | (pv->size & CH_PINUSE);
        c = pv;
    }
    /* with the next one, or give the space back to the wilderness */
    chunk *nx = (chunk *)((uint8_t *)c + sz);
    if ((uintptr_t)nx >= hs->top) {
        hs->top = (uintptr_t)c;
        hs->last_inuse = (c->size & CH_PINUSE) ? 1 : 0;
        if ((uintptr_t)c == hs->first)
            hs->last_inuse = 1;
        return;
    }
    if (!(nx->size & CH_INUSE)) {
        bin_remove(nx);
        sz += csize(nx);
        c->size = sz | (c->size & CH_PINUSE);
        nx = (chunk *)((uint8_t *)c + sz);
        if ((uintptr_t)nx >= hs->top) {
            hs->top = (uintptr_t)c;
            hs->last_inuse = (c->size & CH_PINUSE) ? 1 : 0;
            if ((uintptr_t)c == hs->first)
                hs->last_inuse = 1;
            return;
        }
    }
    c->size = sz | (c->size & CH_PINUSE);
    nx->prev_size = sz;
    nx->size &= ~CH_PINUSE;
    bin_insert(c);
}

static void *heap_realloc(void *p, size_t n)
{
    chunk *c = (chunk *)p - 1;
    uint32_t need = (uint32_t)((n + CH_HDR + 15u) & ~(size_t)15u);
    if (need < CH_MIN)
        need = CH_MIN;
    if (n <= 0x0FFFFFFFu && csize(c) >= need && csize(c) - need < 4096) {
        c->req = (uint32_t)n;  /* fits; keep (bounded slack) */
        return p;
    }
    void *q = heap_alloc(n);
    if (!q)
        return NULL;
    memcpy(q, p, c->req < n ? c->req : n);
    heap_free(p);
    return q;
}

static inline int in_heap(const void *p)
{
    return H.on && (uintptr_t)p >= H.reg.heap && (uintptr_t)p < H.reg.heap + H.reg.heap_size;
}

static inline int wants_state(uintptr_t caller)
{
    return H.on && ss_map_code_class(caller) != SS_HOST;
}

/* Walk the chunks in use: fn(payload, bytes, caller) (audits; heap locked). */
void ss_heap_walk(void (*fn)(void *user, uintptr_t p, uint32_t n, uintptr_t caller), void *user)
{
    if (!H.on)
        return;
    lock();
    for (uintptr_t a = H.hs->first; a < H.hs->top;) {
        chunk *c = (chunk *)a;
        uint32_t sz = csize(c);
        if (sz < CH_MIN)
            break;
        if (c->size & CH_INUSE)
            fn(user, (uintptr_t)(c + 1), c->req, c->caller);
        a += sz;
    }
    unlock();
}

/* ------------------------------------------------------------ interposition */
#if SS_HEAP_SUPPORTED

static void *ss_alloc_for(uintptr_t caller, size_t n, int zero)
{
    if (wants_state(caller)) {
        lock();
        void *p = heap_alloc(n ? n : 1);
        if (p) {
            ((chunk *)p - 1)->caller = (uint32_t)caller;
            H.model_allocs++;
            fp_mix(1, (uint32_t)n, (uint32_t)((uintptr_t)p - H.reg.heap));
        }
        unlock();
        if (p && zero)
            memset(p, 0, n);
        return p;
    }
    H.host_allocs++;
    return zero ? _calloc_base(1, n) : _malloc_base(n);
}

void *__cdecl malloc(size_t n) { return ss_alloc_for((uintptr_t)__builtin_return_address(0), n, 0); }

void *__cdecl calloc(size_t a, size_t b)
{
    if (b && a > (size_t)-1 / b)
        return NULL;
    return ss_alloc_for((uintptr_t)__builtin_return_address(0), a * b, 1);
}

void __cdecl free(void *p)
{
    if (!p)
        return;
    if (in_heap(p)) {
        lock();
        fp_mix(2, 0, (uint32_t)((uintptr_t)p - H.reg.heap));
        heap_free(p);
        unlock();
        return;
    }
    _free_base(p);
}

void *__cdecl realloc(void *p, size_t n)
{
    if (!p)
        return ss_alloc_for((uintptr_t)__builtin_return_address(0), n, 0);
    if (!n) {
        free(p);
        return NULL;
    }
    if (in_heap(p)) {
        lock();
        uint32_t caller = ((chunk *)p - 1)->caller;
        void *q = heap_realloc(p, n);
        if (q)
            ((chunk *)q - 1)->caller = caller;
        fp_mix(3, (uint32_t)n, (uint32_t)((uintptr_t)q - H.reg.heap));
        unlock();
        return q;
    }
    return _realloc_base(p, n);
}

/* _msize is NOT replaced: libucrt's msize.obj (pulled in by the CRT's own
 * _recalloc) defines it with _msize_base.  Nothing in the port calls _msize;
 * the CRT's own callers only see CRT-heap blocks. */

static char *dup_for(uintptr_t caller, const char *s)
{
    if (!s)
        return NULL;
    size_t n = strlen(s) + 1;
    char *d = (char *)ss_alloc_for(caller, n, 0);
    if (d)
        memcpy(d, s, n);
    return d;
}
char *__cdecl _strdup(const char *s) { return dup_for((uintptr_t)__builtin_return_address(0), s); }
char *__cdecl strdup(const char *s) { return dup_for((uintptr_t)__builtin_return_address(0), s); }

#endif /* SS_HEAP_SUPPORTED */

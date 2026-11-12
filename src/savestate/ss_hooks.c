/* SPDX-License-Identifier: CC0-1.0
 * Port save states: the default subsystem hooks and the host-pointer audit
 * (docs/TEST-FIXTURES.md "Save states").
 *
 * One hook per subsystem whose state needs more than raw bytes:
 *   kernel   the EE kernel HLE's K (kstate_ss.c): game threads, semaphores,
 *            alarms, clock; keeps this process's scheduler fiber and hooks
 *   runtime  rg_runtime (runtime.c): run progress + stats, VU0/1, VIF0/1;
 *            rebuilds the GS worker thread and the renderer binding
 * A native subsystem (D9) adds its own with rg_ss_add_hook before
 * rg_ss_mark_init_done.
 *
 * RG_SS_AUDIT=1 (rg_ss_audit): every word of the restored memory (captured
 * statics, state heap chunks, live fiber stacks, game RAM) that points into a
 * block of the CRT (host) heap.  Such a word is a host pointer inside saved
 * state: after a load it points into the loading process's unrelated heap.
 * Each hit names the owner (symbol / allocating caller), so the fix is a
 * policy row in ss_map.c or a hook.
 *
 * Linux (2026-11-08, lane linux32): the host heap is glibc's.  Its blocks are
 * found by walking the main arena's chunks in the brk heap ("[heap]" of
 * /proc/self/maps; a chunk is in use when the next chunk's PREV_INUSE bit is
 * set, so tcache / fastbin chunks count as blocks too).  Not walked: other
 * arenas (threads' heaps) and mmapped chunks; with RG_SS_AUDIT set,
 * rg_ss_init caps glibc at one arena so host threads allocate in the walked
 * one.  Where the walk stops parsing, the rest of the brk heap is one block.  The
 * linked initial data are the file-backed parts of the writable PT_LOADs.
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps2k_ss.h"
#include "rg_runtime.h"
#include "rg_savestate.h"
#include "ss_internal.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <malloc.h>
#include <windows.h>
#elif defined(__linux__)
#include <elf.h>
#include <fcntl.h>
#include <link.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

static size_t k_size(void) { return ps2k_ss_size(); }
static int k_save(void *b, size_t n) { return ps2k_ss_save(b, n); }
static int k_load(const void *b, size_t n) { return ps2k_ss_load(b, n); }

int rg_ss_register_default_hooks(void)
{
    static const rg_ss_hook kernel = {
        "kernel", NULL, NULL, k_size, k_save, NULL, k_load, NULL,
    };
    static const rg_ss_hook runtime = {
        "runtime",          rg_runtime_ss_can_save, rg_runtime_ss_pre_save, rg_runtime_ss_size,
        rg_runtime_ss_save, rg_runtime_ss_pre_load, rg_runtime_ss_load,     rg_runtime_ss_post_load,
    };
    int rc = 0;
    rc |= rg_ss_add_hook(&kernel);
    rc |= rg_ss_add_hook(&runtime);
    return rc ? -1 : 0;
}

/* ------------------------------------------------------------ audit */
#if defined(_WIN32) || defined(__linux__)
typedef struct hblk {
    uintptr_t lo, hi;
} hblk;

static hblk *g_blk;
static int g_nblk;

static int cmp_blk(const void *a, const void *b)
{
    const hblk *x = (const hblk *)a, *y = (const hblk *)b;
    return x->lo < y->lo ? -1 : x->lo > y->lo;
}

#ifdef _WIN32
static void collect_host_blocks(void)
{
    HANDLE h = (HANDLE)_get_heap_handle();
    int cap = 1 << 16;
    g_nblk = 0;
    g_blk = (hblk *)HeapAlloc(GetProcessHeap(), 0, sizeof(hblk) * (size_t)cap);
    if (!g_blk)
        return;
    PROCESS_HEAP_ENTRY e;
    memset(&e, 0, sizeof e);
    HeapLock(h);
    while (HeapWalk(h, &e)) {
        if (!(e.wFlags & PROCESS_HEAP_ENTRY_BUSY) || e.cbData < 8)
            continue;
        if (g_nblk == cap) {
            hblk *n = (hblk *)HeapReAlloc(GetProcessHeap(), 0, g_blk, sizeof(hblk) * (size_t)cap * 2);
            if (!n)
                break;
            g_blk = n;
            cap *= 2;
        }
        g_blk[g_nblk].lo = (uintptr_t)e.lpData;
        g_blk[g_nblk].hi = (uintptr_t)e.lpData + e.cbData;
        g_nblk++;
    }
    HeapUnlock(h);
    qsort(g_blk, (size_t)g_nblk, sizeof *g_blk, cmp_blk);
}
#else
/* scratch memory of the audit itself: mmap, so the walked heap does not change under it */
static void *aud_map(size_t n)
{
    void *p = mmap(NULL, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return p == MAP_FAILED ? NULL : p;
}

#define AUD_BLK_CAP (1u << 21)

/* [lo, hi) of the "[heap]" mapping (the brk heap = glibc's main arena); 0 if none */
static int brk_heap(uintptr_t *lo, uintptr_t *hi)
{
    enum { CAP = 1 << 20 };
    char *buf = (char *)aud_map(CAP);
    if (!buf)
        return 0;
    int fd = open("/proc/self/maps", O_RDONLY);
    size_t n = 0;
    if (fd >= 0) {
        ssize_t r;
        while (n < CAP - 1 && (r = read(fd, buf + n, CAP - 1 - n)) > 0)
            n += (size_t)r;
        close(fd);
    }
    buf[n] = 0;
    int ok = 0;
    for (char *ln = buf; ln && *ln;) {
        char *nl = strchr(ln, '\n');
        if (nl)
            *nl = 0;
        if (strstr(ln, "[heap]")) {
            unsigned long long a, b;
            if (sscanf(ln, "%llx-%llx", &a, &b) == 2) {
                *lo = (uintptr_t)a;
                *hi = (uintptr_t)b;
                ok = 1;
            }
            break;
        }
        ln = nl ? nl + 1 : NULL;
    }
    munmap(buf, CAP);
    return ok;
}

static void collect_host_blocks(void)
{
    g_nblk = 0;
    g_blk = (hblk *)aud_map(sizeof(hblk) * AUD_BLK_CAP);
    uintptr_t lo, hi;
    if (!g_blk || !brk_heap(&lo, &hi))
        return;
    uintptr_t end = (uintptr_t)sbrk(0);
    if (end > lo && end < hi)
        hi = end;
    /* glibc chunks: [prev_size][size|flags] then the user data; SZ = sizeof(size_t),
     * MALLOC_ALIGNMENT 16 on i386 (glibc >= 2.26) and x86-64; the first chunk sits where
     * its user data is aligned */
    const uintptr_t SZ = sizeof(size_t), AL = 16;
    uintptr_t c = lo + ((AL - ((lo + 2 * SZ) & (AL - 1))) & (AL - 1));
    int bad = 0;
    while (c + 2 * SZ <= hi) {
        uintptr_t sz = *(const size_t *)(c + SZ) & ~(uintptr_t)7;
        if (c + sz == hi)
            break; /* the top chunk (its size need not be a multiple of 16) */
        if (sz < 2 * SZ || (sz & (AL - 1)) || c + sz > hi) {
            bad = 1;
            break;
        }
        uintptr_t nx = c + sz;
        if (nx + 2 * SZ > hi)
            break; /* the top chunk */
        int inuse = (int)(*(const size_t *)(nx + SZ) & 1);
        if (inuse && sz > 2 * SZ && g_nblk < (int)AUD_BLK_CAP) {
            g_blk[g_nblk].lo = c + 2 * SZ;
            g_blk[g_nblk].hi = nx + SZ; /* the user data runs into the next prev_size */
            g_nblk++;
        }
        c = nx;
    }
    if (bad && c < hi && g_nblk < (int)AUD_BLK_CAP) {
        /* a chunk that does not parse (a fencepost after a foreign sbrk, or a block another
         * thread is changing): the rest of the brk heap counts as one block */
        fprintf(stderr, "SSAUDIT note: glibc heap walk stopped at %08lx (of %08lx-%08lx, size word %lx) "
                        "after %d blocks; the rest is one host block\n",
                (unsigned long)c, (unsigned long)lo, (unsigned long)hi,
                (unsigned long)*(const size_t *)(c + SZ), g_nblk);
        g_blk[g_nblk].lo = c;
        g_blk[g_nblk].hi = hi;
        g_nblk++;
    }
    /* already in address order */
}
#endif

static int host_block(uintptr_t v)
{
    int lo = 0, hi = g_nblk - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (v < g_blk[mid].lo)
            hi = mid - 1;
        else if (v >= g_blk[mid].hi)
            lo = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* The exe's .data as linked (from the file): a static word still equal to it
 * was never written at run time, so it is not a host pointer (VU microcode and
 * other tables in game .data often fall in the CRT heap's address range). */
#ifdef __linux__
/* the file-backed parts of the writable PT_LOADs (.data & co., no .bss) */
#define AUD_INI 8
static struct {
    uintptr_t lo, n;
    uint8_t *b;
} g_ini[AUD_INI];
static int g_nini;

static void load_initial_data(void)
{
    const ss_image *im = ss_map_image();
    g_nini = 0;
    int fd = open(im->exe_path, O_RDONLY);
    if (fd < 0)
        return;
    ElfW(Ehdr) eh;
    if (pread(fd, &eh, sizeof eh, 0) == (ssize_t)sizeof eh && !memcmp(eh.e_ident, ELFMAG, SELFMAG) &&
        eh.e_phentsize == sizeof(ElfW(Phdr))) {
        for (int i = 0; i < eh.e_phnum && g_nini < AUD_INI; i++) {
            ElfW(Phdr) ph;
            if (pread(fd, &ph, sizeof ph, (off_t)(eh.e_phoff + (size_t)i * sizeof ph)) != (ssize_t)sizeof ph)
                break;
            if (ph.p_type != PT_LOAD || !(ph.p_flags & PF_W) || !ph.p_filesz)
                continue;
            uint8_t *b = (uint8_t *)aud_map(ph.p_filesz + 4);
            if (!b)
                break;
            if (pread(fd, b, ph.p_filesz, (off_t)ph.p_offset) != (ssize_t)ph.p_filesz) {
                munmap(b, ph.p_filesz + 4);
                continue;
            }
            /* ET_EXEC: p_vaddr is the address; ET_DYN would add the load bias */
            g_ini[g_nini].lo = (eh.e_type == ET_DYN ? im->base : 0) + ph.p_vaddr;
            g_ini[g_nini].n = ph.p_filesz;
            g_ini[g_nini].b = b;
            g_nini++;
        }
    }
    close(fd);
}

static int unchanged_static(uintptr_t p)
{
    for (int i = 0; i < g_nini; i++)
        if (p >= g_ini[i].lo && p + 4 <= g_ini[i].lo + g_ini[i].n)
            return !memcmp((const void *)p, g_ini[i].b + (p - g_ini[i].lo), 4);
    return 0;
}

static void audit_release(void)
{
    for (int i = 0; i < g_nini; i++)
        munmap(g_ini[i].b, g_ini[i].n + 4);
    g_nini = 0;
    if (g_blk)
        munmap(g_blk, sizeof(hblk) * AUD_BLK_CAP);
    g_blk = NULL;
    g_nblk = 0;
}
#else
static uint8_t *g_init;
static uintptr_t g_init_lo, g_init_n;

static void load_initial_data(void)
{
    const ss_image *im = ss_map_image();
    FILE *f = fopen(im->exe_path, "rb");
    g_init = NULL;
    if (!f)
        return;
    IMAGE_DOS_HEADER dos;
    IMAGE_NT_HEADERS32 nt;
    if (fread(&dos, sizeof dos, 1, f) == 1 && fseek(f, dos.e_lfanew, SEEK_SET) == 0 &&
        fread(&nt, sizeof nt, 1, f) == 1) {
        long sec = dos.e_lfanew + (long)offsetof(IMAGE_NT_HEADERS32, OptionalHeader) +
                   nt.FileHeader.SizeOfOptionalHeader;
        for (int i = 0; i < nt.FileHeader.NumberOfSections; i++) {
            IMAGE_SECTION_HEADER sh;
            if (fseek(f, sec + i * (long)sizeof sh, SEEK_SET) != 0 || fread(&sh, sizeof sh, 1, f) != 1)
                break;
            if (memcmp(sh.Name, ".data", 6) != 0)
                continue;
            g_init_lo = im->base + sh.VirtualAddress;
            g_init_n = sh.Misc.VirtualSize;
            g_init = (uint8_t *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, g_init_n + 4);
            if (g_init && fseek(f, (long)sh.PointerToRawData, SEEK_SET) == 0) {
                size_t raw = sh.SizeOfRawData < g_init_n ? sh.SizeOfRawData : g_init_n;
                if (fread(g_init, 1, raw, f) != raw) {
                    HeapFree(GetProcessHeap(), 0, g_init);
                    g_init = NULL;
                }
            }
            break;
        }
    }
    fclose(f);
}

static int unchanged_static(uintptr_t p)
{
    if (!g_init || p < g_init_lo || p + 4 > g_init_lo + g_init_n)
        return 0;
    return !memcmp((const void *)p, g_init + (p - g_init_lo), 4);
}

static void audit_release(void)
{
    if (g_init)
        HeapFree(GetProcessHeap(), 0, g_init);
    g_init = NULL;
    HeapFree(GetProcessHeap(), 0, g_blk);
    g_blk = NULL;
    g_nblk = 0;
}
#endif

/* hits per owner (static symbol, allocating caller, "fiber-stack", "game-ram") */
#define AUD_OWNERS 512
typedef struct aud_owner {
    char name[160];
    int hits;
} aud_owner;
typedef struct audit {
    int hits, shown, limit;
    FILE *out;
    aud_owner own[AUD_OWNERS];
    int nown;
} audit;

static void owner_hit(audit *a, const char *name)
{
    for (int i = 0; i < a->nown; i++)
        if (!strcmp(a->own[i].name, name)) {
            a->own[i].hits++;
            return;
        }
    if (a->nown < AUD_OWNERS) {
        snprintf(a->own[a->nown].name, sizeof a->own[a->nown].name, "%s", name);
        a->own[a->nown++].hits = 1;
    }
}

static int cmp_owner(const void *x, const void *y)
{
    return ((const aud_owner *)y)->hits - ((const aud_owner *)x)->hits;
}

static void scan(audit *a, const char *what, uintptr_t lo, uintptr_t hi, uintptr_t owner_caller)
{
    int is_static = !strcmp(what, "game-static") || !strcmp(what, "model-static");
    lo = (lo + 3) & ~(uintptr_t)3;
    for (uintptr_t p = lo; p + 4 <= hi; p += 4) {
        uintptr_t v = *(const uint32_t *)p;
        if (v < 0x10000)
            continue;
        int b = host_block(v);
        if (b < 0)
            continue;
        if (is_static && unchanged_static(p))
            continue;
        a->hits++;
        char d1[300], d2[300] = "";
        ss_map_describe(p, d1, sizeof d1);
        if (owner_caller)
            ss_map_describe(owner_caller, d2, sizeof d2);
        {
            /* owner = the symbol (or allocating function) without its +offset */
            char on[160];
            const char *src = owner_caller ? d2 : d1;
            if (!strcmp(what, "fiber-stack") || !strcmp(what, "game-ram"))
                src = "";
            snprintf(on, sizeof on, "%s %s", what, src);
            char *plus = strchr(on, '+');
            char *paren = strchr(on, '(');
            if (plus && paren && plus < paren)
                memmove(plus, paren - 1, strlen(paren - 1) + 1);
            owner_hit(a, on);
        }
        if (a->shown++ >= a->limit)
            continue;
        fprintf(a->out, "SSAUDIT %s at %08lx [%s]%s%s -> host block %08lx+%lx (%lu bytes)\n", what,
                (unsigned long)p, d1, owner_caller ? " alloc by " : "", d2, (unsigned long)g_blk[b].lo,
                (unsigned long)(v - g_blk[b].lo), (unsigned long)(g_blk[b].hi - g_blk[b].lo));
    }
}

static void heap_chunk(void *user, uintptr_t p, uint32_t n, uintptr_t caller)
{
    scan((audit *)user, "heap", p, p + n, caller);
}
#endif

int rg_ss_audit(FILE *out, int limit)
{
#if defined(_WIN32) || defined(__linux__)
    if (!rg_ss_active())
        return -1;
    static audit a;
    memset(&a, 0, sizeof a);
    a.limit = limit >= 0 ? limit : 40;
    a.out = out ? out : stderr;
    collect_host_blocks();
    load_initial_data();
    const ss_range *r;
    int n = ss_map_data_ranges(&r);
    for (int i = 0; i < n; i++)
        if (r[i].cls == SS_GAME || r[i].cls == SS_MODEL)
            scan(&a, r[i].cls == SS_GAME ? "game-static" : "model-static", r[i].lo, r[i].hi, 0);
    ss_heap_walk(heap_chunk, &a);
    uintptr_t st[96][2];
    int ns = ps2k_fiber_arena_stacks(st, 96);
    for (int i = 0; i < ns && i < 96; i++)
        scan(&a, "fiber-stack", st[i][0], st[i][1], 0);
    const ss_region_info *rg = ss_region();
    const rg_ps2_ram *ram = rg_crt0_ram();
    /* game RAM holds loaded assets (microcode, models): noisy, so only on request */
    const char *e = getenv("RG_SS_AUDIT");
    if (ram && ram->heap_start && e && atoi(e) >= 2)
        scan(&a, "game-ram", (uintptr_t)ram->heap_start, (uintptr_t)ram->heap_end, 0);
    (void)rg;
    qsort(a.own, (size_t)a.nown, sizeof a.own[0], cmp_owner);
    for (int i = 0; i < a.nown && i < 60; i++)
        fprintf(a.out, "SSAUDIT owner %6d  %s\n", a.own[i].hits, a.own[i].name);
    fprintf(a.out, "SSAUDIT %d host-heap pointer(s) in saved memory (%d host blocks)\n", a.hits, g_nblk);
    fflush(a.out);
    audit_release();
    return a.hits;
#else
    (void)out;
    (void)limit;
    return -1;
#endif
}

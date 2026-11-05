/* SPDX-License-Identifier: CC0-1.0
 *
 * x64 Linux: the start-up low-address setup and self-check (docs/LINUX.md "x64 Linux",
 * docs/X64-PLAN.md 0.13 / 0.16).  Linked into every executable of an x64 Linux build
 * (cmake/x64.cmake rg_x64_finalize); the Windows counterpart is lowmem_check.c.
 *
 * The game keeps 4-byte pointers in its memory (the ptr32 stage), so every address game
 * code can see must be below 2 GB.  Windows gets that process-wide from LAA:NO; Linux has
 * no such switch, so the pieces game pointers reach are placed low one by one:
 *   - the image: non-PIE at 0x400000 (cmake/toolchain-linux-x64.cmake);
 *   - game RAM and the guest fiber stacks: explicit low mmap hints (src/runtime/crt0.c,
 *     src/native/threads/fiber/fiber_ucontext.c);
 *   - the glibc heap (port code that hands a malloc'd block to game memory): ONE arena
 *     (the main one, grown by brk right above the low image) and the mmap threshold at
 *     its maximum, set here before any thread exists.  A block above the threshold, or
 *     one allocated after brk ran into another mapping, is mmapped high: RG_X64_HEAPCHECK=1
 *     checks a malloc at exit and prints the low map (rg_x64_lowmem_report()).
 * Self-check at start-up: image, brk, a test malloc below 2 GB, else exit 70 with a message.
 * RG_X64_LOWMEM_LOG=1 prints the addresses. */
#if defined(__x86_64__) && defined(__linux__)
#define _GNU_SOURCE 1
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#define RG_X64_LIMIT 0x80000000ull

/* the kernel's program break (the game links its own `sbrk` over EE RAM, src/crt/crt_heap.c,
 * which shadows libc's; glibc's malloc uses __sbrk internally).  x86-64 kernels randomise the
 * start of brk up to 1 GB above a non-PIE image's end: still below 2 GB. */
static void *rg_brk(void) { return (void *)syscall(SYS_brk, 0); }

extern char __executable_start[], _end[];

static int rg_x64_bad(const char *what, const void *p)
{
    if ((uintptr_t)p < RG_X64_LIMIT)
        return 0;
    fprintf(stderr, "rg x64: %s at %p is above 2 GB: game pointers are 4 bytes (docs/LINUX.md \"x64 Linux\")\n",
            what, p);
    return 1;
}

/* the low-address map of the process: mappings below 2 GB and the largest free hole */
void rg_x64_lowmem_report(const char *tag)
{
    FILE *f = fopen("/proc/self/maps", "r");
    char ln[512];
    unsigned long long used = 0, prev = 0x10000, hole = 0;
    if (!f)
        return;
    while (fgets(ln, sizeof ln, f)) {
        unsigned long long a, b;
        if (sscanf(ln, "%llx-%llx", &a, &b) != 2 || a >= RG_X64_LIMIT)
            continue;
        if (b > RG_X64_LIMIT)
            b = RG_X64_LIMIT;
        used += b - a;
        if (a > prev && a - prev > hole)
            hole = a - prev;
        prev = b;
    }
    fclose(f);
    if (RG_X64_LIMIT - prev > hole)
        hole = RG_X64_LIMIT - prev;
    fprintf(stderr, "rg x64 lowmem [%s]: mapped below 2 GB %llu MB, largest hole %llu MB, brk %p\n", tag,
            used >> 20, hole >> 20, rg_brk());
}

static void rg_x64_heapcheck_exit(void)
{
    void *p = malloc(64);
    if ((uintptr_t)p >= RG_X64_LIMIT)
        fprintf(stderr, "rg x64: RG_X64_HEAPCHECK: malloc at exit returned %p (above 2 GB)\n", p);
    free(p);
    rg_x64_lowmem_report("exit");
}

__attribute__((constructor(101))) static void rg_x64_lowmem_init(void)
{
    int bad = 0;
    void *h;
    const char *log = getenv("RG_X64_LOWMEM_LOG");
    const char *hc = getenv("RG_X64_HEAPCHECK");
    /* one arena: threads would otherwise get mmapped (high) arenas */
    mallopt(M_ARENA_MAX, 1);
    /* blocks up to 32 MB (glibc's maximum on LP64) from brk, not from high mmaps */
    mallopt(M_MMAP_THRESHOLD, 32 << 20);
    h = malloc(64);
    bad |= rg_x64_bad("image", __executable_start);
    bad |= rg_x64_bad("image end", _end);
    bad |= rg_x64_bad("brk", rg_brk());
    bad |= rg_x64_bad("heap", h);
    if (log && log[0] == '1')
        fprintf(stderr, "rg x64 lowmem: image %p-%p brk %p malloc %p\n", (void *)__executable_start,
                (void *)_end, rg_brk(), h);
    free(h);
    if (bad)
        _exit(70);
    if ((hc && hc[0] == '1') || (log && log[0] == '1'))
        atexit(rg_x64_heapcheck_exit);
}
#else
typedef int rg_x64_lowmem_linux_empty;
#endif

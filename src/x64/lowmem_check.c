/* SPDX-License-Identifier: CC0-1.0
 *
 * x64 start-up self-check (P7 strategy A, docs/X64-PLAN.md step 1): every
 * address of the process must lie below 2 GB, because game memory stores
 * pointers as 4-byte words (`__ptr32`, ADDR32 data relocations).  Windows
 * guarantees that for an image linked /LARGEADDRESSAWARE:NO with a low fixed
 * base (tools/x64/pecheck.py checks the headers at link time); this checks
 * the running process: the image, the stack, the CRT heap and the highest
 * address VirtualAlloc hands out (MEM_TOP_DOWN).  On failure it reports and
 * exits with code 86 before main.
 *
 * cmake/x64.cmake adds this file to every executable of an x64 build; i686
 * never compiles it.
 */
#if defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RG_X64_LIMIT 0x80000000ull

static int rg_x64_bad(const char *what, const void *p)
{
    if ((uintptr_t)p + 0ull < RG_X64_LIMIT)
        return 0;
    fprintf(stderr,
            "rg x64: %s at %p is above 2 GB: the exe must be linked /LARGEADDRESSAWARE:NO "
            "/DYNAMICBASE:NO /HIGHENTROPYVA:NO with a low /BASE (docs/X64-PLAN.md)\n",
            what, p);
    return 1;
}

int rg_x64_lowmem_selfcheck(void)
{
    volatile int local = 0;
    int bad = 0;
    void *h = malloc(64);
    void *v = VirtualAlloc(NULL, 0x10000, MEM_RESERVE | MEM_TOP_DOWN, PAGE_NOACCESS);
    bad |= rg_x64_bad("image", GetModuleHandleW(NULL));
    bad |= rg_x64_bad("stack", (const void *)&local);
    bad |= rg_x64_bad("heap", h);
    bad |= rg_x64_bad("top-down VirtualAlloc", v);
    free(h);
    if (v)
        VirtualFree(v, 0, MEM_RELEASE);
    return bad;
}

/* Graphics-driver address-space fence (docs/X64-PLAN.md 0.6).  The process's NULL-hint
 * allocations all land below 2 GB, and the NVIDIA 64-bit D3D11 driver reserves a 1 GB
 * contiguous range (its GPU virtual-address mirror, under 1 MB committed) once the device
 * is in use: with the driver's own ~256 MB that left about 650 MB of the 2 GB to the port,
 * and runs died in an out-of-memory calloc after 12,000-22,000 fields (nr_mesh_decode).
 * Given no contiguous hole that large below 2 GB, the driver puts the range above 4 GB
 * instead, which is harmless: no driver address is ever stored in game memory.  The
 * fence: one 64 KB reservation ("post") every 512 MB below 2 GB, placed before the
 * graphics device is created and kept for the life of the process (the driver reserves
 * lazily, after device creation), so no free hole below 2 GB is 512 MB or larger.
 * The port's own large reservations (save-state heap 256 MB, game RAM, arenas) are made
 * before the device.  RG_X64_VA_FENCE=0 turns the fence off (the control);
 * RG_X64_VA_LOG=1 prints the free space below 2 GB at rg_x64_va_fence(1) / (0). */
#define RG_X64_POST_STEP (512u << 20)
#define RG_X64_POSTS 4
static void *g_posts[RG_X64_POSTS];

void rg_x64_va_report(const char *tag)
{
    MEMORY_BASIC_INFORMATION m;
    uintptr_t a = 0x10000, fr = 0, big = 0;
    while (a < RG_X64_LIMIT && VirtualQuery((void *)a, &m, sizeof m)) {
        if (m.State == MEM_FREE) {
            fr += m.RegionSize;
            if (m.RegionSize > big)
                big = m.RegionSize;
        }
        a = (uintptr_t)m.BaseAddress + m.RegionSize;
    }
    fprintf(stderr, "rg x64: %s: %u MB free below 2 GB (largest hole %u MB)\n", tag,
            (unsigned)(fr >> 20), (unsigned)(big >> 20));
}

void rg_x64_va_fence(int on)
{
    const char *e = getenv("RG_X64_VA_FENCE");
    const char *lg = getenv("RG_X64_VA_LOG");
    int log = lg && lg[0] == '1';
    if (on && !(e && e[0] == '0')) {
        MEMORY_BASIC_INFORMATION m;
        uintptr_t p;
        int n = 0;
        for (p = RG_X64_POST_STEP; p < RG_X64_LIMIT && n < RG_X64_POSTS; p += RG_X64_POST_STEP) {
            if (g_posts[n]) { n++; continue; }   /* placed by an earlier device */
            if (VirtualQuery((void *)p, &m, sizeof m) && m.State == MEM_FREE &&
                (g_posts[n] = VirtualAlloc((void *)p, 0x10000, MEM_RESERVE, PAGE_NOACCESS)) != NULL)
                n++;
        }
    }
    if (log)
        rg_x64_va_report(on ? "before the graphics device" : "after the graphics device");
}

__attribute__((constructor)) static void rg_x64_lowmem_ctor(void)
{
    if (rg_x64_lowmem_selfcheck()) {
        fflush(stderr);
        ExitProcess(86);
    }
}
#endif

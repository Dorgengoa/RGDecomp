/* SPDX-License-Identifier: CC0-1.0
 *
 * ctest x64.lowmem_runtime (docs/X64-PLAN.md step 1): in an x64 exe linked
 * with the low-address flags every allocation the port makes stays below
 * 2 GB: CRT heap blocks up to ~1 GB in total, VirtualAlloc (bottom-up and
 * top-down), a second thread's stack, a fiber's stack, and the image.  The
 * start-up self-check (src/x64/lowmem_check.c) has already run before main.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int rg_x64_lowmem_selfcheck(void);

static int fails;

static void chk(const char *what, const void *p)
{
    if (!p) {
        printf("FAIL %s: allocation failed\n", what);
        fails++;
    } else if ((uintptr_t)p >= 0x80000000ull) {
        printf("FAIL %s at %p (above 2 GB)\n", what, p);
        fails++;
    }
}

static DWORD WINAPI thread_fn(LPVOID arg)
{
    volatile int local = 0;
    *(const void **)arg = (const void *)&local;
    return 0;
}

static void *volatile g_fiber_sp;
static void *g_main_fiber;

static VOID WINAPI fiber_fn(LPVOID arg)
{
    volatile int local = 0;
    (void)arg;
    g_fiber_sp = (void *)&local;
    SwitchToFiber(g_main_fiber);
}

int main(void)
{
    if (rg_x64_lowmem_selfcheck())
        fails++;
    chk("image", GetModuleHandleW(NULL));
    void *blocks[16];
    for (int i = 0; i < 16; i++) {
        blocks[i] = malloc(64u << 20); /* 16 x 64 MB = 1 GB */
        chk("malloc 64 MB", blocks[i]);
    }
    void *v = VirtualAlloc(NULL, 256u << 20, MEM_RESERVE, PAGE_NOACCESS);
    chk("VirtualAlloc 256 MB", v);
    void *t = VirtualAlloc(NULL, 1u << 16, MEM_RESERVE | MEM_TOP_DOWN, PAGE_NOACCESS);
    chk("VirtualAlloc top-down", t);
    const void *tsp = NULL;
    HANDLE th = CreateThread(NULL, 1u << 20, thread_fn, (LPVOID)&tsp, 0, NULL);
    if (th) {
        WaitForSingleObject(th, INFINITE);
        CloseHandle(th);
    }
    chk("thread stack", tsp);
    g_main_fiber = ConvertThreadToFiber(NULL);
    void *f = CreateFiber(1u << 20, fiber_fn, NULL);
    if (g_main_fiber && f) {
        SwitchToFiber(f);
        DeleteFiber(f);
    }
    chk("fiber stack", g_fiber_sp);
    for (int i = 0; i < 16; i++)
        free(blocks[i]);
    printf("x64 lowmem: %s (top-down VirtualAlloc %p)\n", fails ? "FAIL" : "ok", t);
    return fails ? 1 : 0;
}

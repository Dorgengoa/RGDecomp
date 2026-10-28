/* SPDX-License-Identifier: CC0-1.0
 * crt0 equivalent: what the retail entry point (game/src/main/sdk/entry.c,
 * `entry` @0x00100008) does before Main_15e700, done host-side.
 * docs/RUNTIME.md "crt0".
 *
 * Retail sequence                          Here
 *   zero GPR/FPR/HI/LO/SA, FCR31 = 0       nothing (host ABI)
 *   clear BSS [0x00481080, 0x00528200)      MAIN .bss is host statics (zero at
 *                                          load); the overlay arena part belongs
 *                                          to the overlay manager (TODO(overlay))
 *   SetupThread (syscall 0x3C): gp,        guest thread 1 is created by the
 *     stack 0x01FD0000 + 0x30000, args     kernel (ps2k_start); guest stacks are
 *     0x00485280, root = 0x00100220        unused; argc/argv built here
 *   SetupHeap (syscall 0x3D): heap from    rg_crt0_init: the heap alone, one host
 *     0x00528200, size -1 -> up to the      allocation of 0x1AA7E00 bytes starting at
 *     stack bottom (EndOfHeap = 0x01FD0000) page + 0x200; sbrk/EndOfHeap below
 *   InitSys_120918 (alarms, timers,        the kernel HLE is already up
 *     threads, ExecPS2, TLB, IOP reset cb)
 *   FlushCache(0); ei                      no-op; thread 1 starts with EIE = 1
 *   Main_15e700(argc, argv)                cfg.entry or rg_game_entry
 *   Exit_12f4e0(ret): atexit list (LIFO),  rg_ps2_exit: rg_crt0_atexit list
 *     __cleanup, Exit syscall              (LIFO), then ExitThread (MAIN_EXIT)
 *
 * Static constructors: Main_15e700 itself calls MainStaticInit_100580 ->
 * RunStaticCtors_100df0(0x0046F9C0, 0x0046FD64, ...), an excluded asm unit;
 * RunStaticCtors_100df0 below is its binding. */
#if defined(__linux__) && !defined(_DEFAULT_SOURCE)
#define _DEFAULT_SOURCE 1 /* MAP_ANONYMOUS */
#endif
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__linux__)
#include <sys/mman.h>
#endif

#include "ps2k.h"
#include "rg_runtime.h"

static struct {
    rg_ps2_ram ram;
    void *alloc;
    void (*atexit_fns[64])(void);
    int natexit;
    int exit_code;
    char *argv[2];
    char boot_path[64];
} C;

/* The game heap is one host allocation of RG_CRT0_HEAP_ALLOC bytes (rg_runtime.h,
 * docs/NATIVE-CPU.md section 8).  With RG_HEAP_DMA_PLACEMENT (the still-emulated DMA path:
 * DMA tags hold host pointers, a tag's ADDR is 31 bits and three render overrides keep 28)
 * it must lie in [RG_HEAP_DMA_LO, RG_HEAP_DMA_HI); without it, anywhere. */
#define HEAP_MAP_SIZE ((size_t)RG_CRT0_HEAP_ALLOC)
#if defined(__linux__)
static void *heap_alloc(void)
{
#if RG_HEAP_DMA_PLACEMENT
    /* an i686 process under an x86-64 kernel maps top-down from ~4 GB: ask for low ranges
     * explicitly (a hint is only taken when the range is free; each result is checked) */
    for (uintptr_t hint = RG_HEAP_DMA_LO; hint + HEAP_MAP_SIZE <= RG_HEAP_DMA_HI; hint += 0x01000000u) {
        void *p = mmap((void *)hint, HEAP_MAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED)
            return NULL;
        if ((uintptr_t)p >= RG_HEAP_DMA_LO && (uintptr_t)p + HEAP_MAP_SIZE <= RG_HEAP_DMA_HI)
            return p;
        munmap(p, HEAP_MAP_SIZE);
    }
    return NULL;
#else
    void *p = mmap(NULL, HEAP_MAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return p == MAP_FAILED ? NULL : p;
#endif
}
static void heap_free(void *p)
{
    if (p)
        munmap(p, HEAP_MAP_SIZE);
}
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
static void *heap_alloc(void)
{
#if RG_HEAP_DMA_PLACEMENT
    /* malloc gives no placement guarantee: a windowed run creates the SDL window and its
     * D3D11 renderer before this, and malloc then returned 0x1CFCB000 (docs/GPU.md "Real
     * game validation").  Take the lowest free range from RG_HEAP_DMA_LO that fits. */
    uintptr_t a = RG_HEAP_DMA_LO;
    MEMORY_BASIC_INFORMATION mi;
    while (a + HEAP_MAP_SIZE <= RG_HEAP_DMA_HI && VirtualQuery((void *)a, &mi, sizeof mi)) {
        uintptr_t rb = (uintptr_t)mi.BaseAddress, re = rb + mi.RegionSize;
        if (mi.State == MEM_FREE) {
            uintptr_t st = (a + 0xFFFFu) & ~(uintptr_t)0xFFFFu;   /* allocation granularity */
            if (st + HEAP_MAP_SIZE <= re) {
                void *p = VirtualAlloc((void *)st, HEAP_MAP_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
                if (p)
                    return p;
            }
        }
        if (re <= a)
            break;
        a = re;
    }
    /* no low range: anywhere (the runtime warns that the 28-bit masks will fault) */
    return VirtualAlloc(NULL, HEAP_MAP_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
    return VirtualAlloc(NULL, HEAP_MAP_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#endif
}
static void heap_free(void *p)
{
    if (p)
        VirtualFree(p, 0, MEM_RELEASE);
}
#else
static void *heap_alloc(void) { return malloc(HEAP_MAP_SIZE); }
static void heap_free(void *p) { free(p); }
#endif

/* rg_crt0_set_ram_provider (docs/TEST-FIXTURES.md): set once before init */
static void *(*g_ram_provider)(size_t size);
static int g_ram_provided;

void rg_crt0_set_ram_provider(void *(*alloc)(size_t size)) { g_ram_provider = alloc; }

int rg_crt0_init(void)
{
    if (C.alloc)
        return 0;
    g_ram_provided = 0;
    if (g_ram_provider && (C.alloc = g_ram_provider(HEAP_MAP_SIZE)) != NULL)
        g_ram_provided = 1;
    else
        C.alloc = heap_alloc();
    if (!C.alloc) {
        fprintf(stderr, "rg_crt0: cannot allocate the %u-byte game heap%s\n", (unsigned)HEAP_MAP_SIZE,
                RG_HEAP_DMA_PLACEMENT ? " below 0x10000000 (RG_HEAP_DMA_PLACEMENT)" : "");
        return -1;
    }
    /* start = page + 0x200: congruent to the retail heap start (0x00528200) mod 4 KB, so
     * newlib malloc's page rounding of the break (crt_heap.c) decides as on the PS2 */
    uint8_t *start = (uint8_t *)((((uintptr_t)C.alloc + 4095u) & ~(uintptr_t)4095u) +
                                 (RG_PS2_HEAP_START & 4095u));
    memset(start, 0, RG_PS2_HEAP_SIZE);
    C.ram.heap_start = start;
    C.ram.heap_end = start + RG_PS2_HEAP_SIZE;
    C.ram.brk = C.ram.heap_start;
    C.natexit = 0;
    C.exit_code = 0;
    return 0;
}

void rg_crt0_shutdown(void)
{
    if (!g_ram_provided)   /* the provider's range stays its own */
        heap_free(C.alloc);
    g_ram_provided = 0;
    memset(&C, 0, sizeof C);
}

const rg_ps2_ram *rg_crt0_ram(void) { return &C.ram; }

uint32_t rg_crt0_host_to_retail(const void *host)
{
    uintptr_t h = (uintptr_t)host, lo = (uintptr_t)C.ram.heap_start;
    if (!lo || h < lo || h >= (uintptr_t)C.ram.heap_end)
        return 0;
    return RG_PS2_HEAP_START + (uint32_t)(h - lo);
}

void *rg_crt0_retail_to_host(uint32_t retail)
{
    if (!C.ram.heap_start || retail < RG_PS2_HEAP_START || retail >= RG_PS2_HEAP_END)
        return NULL;
    return C.ram.heap_start + (retail - RG_PS2_HEAP_START);
}

void *rg_crt0_end_of_heap(void) { return C.ram.heap_end; }

/* the heap's capacity, EndOfHeap - heap start (= RG_PS2_HEAP_SIZE; before init too): the game's
 * free-heap probe (overrides SysCalcFreeHeapMaybe_15e1d0, D9: was retail link-address arithmetic) */
uint32_t rg_crt0_heap_size(void)
{
    return C.ram.heap_start ? (uint32_t)(C.ram.heap_end - C.ram.heap_start) : RG_PS2_HEAP_SIZE;
}

/* newlib sbrk over the heap block: the break moves within
 * [heap_start, EndOfHeap); retail sets errno = ENOMEM (12) through the reent
 * and returns -1 when the request does not fit. */
void *rg_crt0_sbrk(intptr_t incr)
{
    if (!C.ram.heap_start)
        return (void *)-1;
    uint8_t *old = C.ram.brk;
    if ((incr > 0 && (uintptr_t)incr > (uintptr_t)(C.ram.heap_end - old)) ||
        (incr < 0 && (uintptr_t)(-incr) > (uintptr_t)(old - C.ram.heap_start))) {
        errno = ENOMEM;
        return (void *)-1;
    }
    C.ram.brk = old + incr;
    return old;
}

void rg_crt0_run_ctors(const void *begin, const void *end)
{
    /* the table holds 32-bit code addresses: host function pointers on i686 */
    for (const uint32_t *p = (const uint32_t *)begin; p < (const uint32_t *)end; p++)
        if (*p)
            ((void (*)(void))(uintptr_t)*p)();
}

int rg_crt0_atexit(void (*fn)(void))
{
    if (!fn || C.natexit >= (int)(sizeof C.atexit_fns / sizeof C.atexit_fns[0]))
        return -1;
    C.atexit_fns[C.natexit++] = fn;
    return 0;
}

int rg_ps2_exit_code(void) { return C.exit_code; }

void rg_ps2_exit(int code)
{
    C.exit_code = code;
    while (C.natexit > 0)
        C.atexit_fns[--C.natexit]();
    /* TODO(game link): Exit_12f4e0 also walks newlib's _atexit chain in the
     * game's reent (_impure_ptr->_atexit) and calls __cleanup; bind them here
     * once the libc band links. */
    ps2k_exit_thread();
}

/* The default entry until the game links.  WEAK: the game build's strong
 * rg_game_entry (glue calling Main_15e700) replaces it at link time. */
__attribute__((weak)) int rg_game_entry(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    static int said;
    if (!said++)
        fprintf(stderr, "rg_ps2_main: the game is not linked (rg_game_entry is the weak default)\n");
    return RG_GAME_NOT_LINKED;
}

void rg_ps2_main(void *unused)
{
    (void)unused;
    /* argc/argv as ExecPS2 passes them from SYSTEM.CNF BOOT2 (args block 0x00485280) */
    snprintf(C.boot_path, sizeof C.boot_path, "%s", RG_PS2_BOOT_PATH);
    C.argv[0] = C.boot_path;
    C.argv[1] = NULL;
    if (!C.ram.heap_start && rg_crt0_init() != 0) {
        rg_ps2_exit(-1);
        return;
    }
    const rg_runtime_config *cfg = rg_runtime_get_config();
    rg_game_entry_fn entry = cfg && cfg->entry ? cfg->entry : rg_game_entry;
    int ret = entry(1, C.argv);
    rg_ps2_exit(ret);
}

/* ---- game-tree bindings of the excluded crt0/sdk asm units (PLAN.md
 * transform 6).  Prototypes follow the game's declarations: EndOfHeap and
 * sbrk are declared with s32/void* returns there; under i686 cdecl both
 * return in EAX. */
void *EndOfHeap(void) { return rg_crt0_end_of_heap(); }

/* On Linux this definition in the executable interposes libc's sbrk for every
 * caller outside libc (the game, src/crt/crt_heap.c); glibc's own malloc uses
 * its internal __sbrk and keeps the real program break (docs/LINUX.md). */
void *sbrk(intptr_t incr) { return rg_crt0_sbrk(incr); }

/* RunStaticCtors_100df0(ctor_begin, ctor_end, eh_a, eh_b): call each
 * constructor, then EhRegisterFragmentStubMaybe_1026b0(eh_a, eh_b), which
 * returns 0 and does nothing. */
void RunStaticCtors_100df0(void *begin, void *end, void *eh_a, void *eh_b)
{
    (void)eh_a;
    (void)eh_b;
    rg_crt0_run_ctors(begin, end);
}

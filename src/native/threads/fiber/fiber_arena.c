/* SPDX-License-Identifier: CC0-1.0
 *
 * Fixed-address fiber stacks for save states (ps2k_ss.h, docs/TEST-FIXTURES.md).
 *
 * Layout of the caller's range [base, base + size):
 *
 *   base                 fa_header: slot table (one fa_fiber per slot)
 *   base + 64 KiB        slot 0: guard (reserved, never committed), stack
 *   base + 64 KiB + s    slot 1 ...
 *
 * The stride s (guard + stack) is fixed by the first fiber created.  A fiber
 * that is switched out keeps its context on its own stack: the switch pushes
 * ebp/ebx/esi/edi, the TEB's SEH head, StackBase, StackLimit and
 * DeallocationStack, the x87 control word and MXCSR, then stores esp in the
 * slot.  Nothing else (no OS fiber object) holds state, so writing the header
 * and each stack's live part [sp, top) back at the same addresses restores
 * every suspended fiber exactly.
 *
 * i686 Windows only; elsewhere ps2k_fiber_arena_set returns -1.
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fiber_arena.h"
#include "ps2k_ss.h"

#if defined(_WIN32) && (defined(__i386__) || defined(_M_IX86))
#define FA_SUPPORTED 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(_WIN32) && defined(__x86_64__)
/* x64 (P7, docs/X64-PLAN.md step 4): the switch saves the Win64 non-volatile
 * set (rbx rbp rdi rsi r12-r15, xmm6-15, MXCSR, x87 CW) and the TEB stack
 * fields gs:8 StackBase, gs:0x10 StackLimit, gs:0x1478 DeallocationStack (no
 * SEH chain: x64 unwinding is table based). */
#define FA_SUPPORTED 1
#define FA_X64 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#define FA_SUPPORTED 0
#endif

#define FA_MAGIC      0x41524746u /* "FGRA" */
#define FA_FIBER      0x52424946u /* "FIBR" */
#define FA_SLOTS      96
#define FA_HDR_BYTES  0x10000u    /* the header's share of the range (64 KiB) */
#define FA_GUARD      0x10000u    /* reserved, uncommitted, below each stack */

typedef struct fa_fiber {
    uint32_t      magic;
    int32_t       used;
    int32_t       slot;     /* -1: the adopted host thread */
    int32_t       started;  /* switched to at least once (has a saved context on its stack) */
    void         *sp;       /* saved esp while switched out */
    ps2k_fiber_fn fn;
    void         *arg;
    uintptr_t     lo, hi;   /* committed stack [lo, hi) */
} fa_fiber;

typedef struct fa_header {
    uint32_t magic, version, nslots, stride;
    uint32_t stack_bytes;
    uint32_t pad[3];
    fa_fiber slot[FA_SLOTS];
} fa_header;

_Static_assert(sizeof(fa_header) <= FA_HDR_BYTES, "fa_header must fit the header area");

static uintptr_t g_base;
static size_t g_size;
static fa_header *g_hdr;
static fa_fiber g_host; /* the scheduler (host thread); its sp is written by every switch away */

int fa_on(void) { return g_hdr != NULL; }

int ps2k_fiber_arena_on(void) { return fa_on(); }

int ps2k_fiber_arena_set(void *base, size_t size)
{
#if FA_SUPPORTED
    if (g_hdr || !base || size < FA_HDR_BYTES + 2 * (FA_GUARD + 0x10000u) || ((uintptr_t)base & 0xFFFFu))
        return -1;
    if (!VirtualAlloc(base, FA_HDR_BYTES, MEM_COMMIT, PAGE_READWRITE))
        return -1;
    g_base = (uintptr_t)base;
    g_size = size;
    g_hdr = (fa_header *)base;
    memset(g_hdr, 0, sizeof *g_hdr);
    g_hdr->magic = FA_MAGIC;
    g_hdr->version = 1;
    return 0;
#else
    (void)base;
    (void)size;
    return -1;
#endif
}

void ps2k_fiber_arena_header(void **p, size_t *n)
{
    *p = g_hdr;
    *n = g_hdr ? FA_HDR_BYTES : 0;
}

int ps2k_fiber_arena_stacks(uintptr_t (*out)[2], int cap)
{
    int n = 0;
    if (!g_hdr)
        return 0;
    for (uint32_t i = 0; i < g_hdr->nslots; i++) {
        const fa_fiber *f = &g_hdr->slot[i];
        /* a created fiber that never ran holds its first-switch frame (fa_create) */
        if (!f->used || !f->sp)
            continue;
        if (n < cap) {
            out[n][0] = (uintptr_t)f->sp;
            out[n][1] = f->hi;
        }
        n++;
    }
    return n;
}

int ps2k_fiber_arena_commit(uintptr_t lo, uintptr_t hi)
{
#if FA_SUPPORTED
    if (!g_hdr || lo < g_base || hi > g_base + g_size || lo >= hi)
        return -1;
    /* a stack: commit its whole slot (the saved part starts at the saved
     * esp; the fiber grows below it once it runs again).  The header, with
     * the stride, is written back before the stacks. */
    if (g_hdr->stride && lo >= g_base + FA_HDR_BYTES) {
        uintptr_t i = (lo - g_base - FA_HDR_BYTES) / g_hdr->stride;
        uintptr_t slo = g_base + FA_HDR_BYTES + i * g_hdr->stride + FA_GUARD;
        if (slo < lo)
            lo = slo;
    }
    lo &= ~(uintptr_t)0xFFFu;
    return VirtualAlloc((void *)lo, hi - lo, MEM_COMMIT, PAGE_READWRITE) ? 0 : -1;
#else
    (void)lo;
    (void)hi;
    return -1;
#endif
}

#if FA_SUPPORTED

#if defined(FA_X64)
/* x64 frame, from the saved rsp upward (FA_X64_FRAME bytes, then the return
 * address): xmm6-15 (160), MXCSR (4), x87 CW (4), pad (8), DeallocationStack,
 * StackLimit, StackBase, r15 r14 r13 r12 rsi rdi rbx rbp. */
#define FA_X64_FRAME (176 + 11 * 8)
__attribute__((naked)) static void fa_swap(void **save_sp, void *load_sp)
{
    __asm__ volatile(
        "pushq %rbp\n\t"
        "pushq %rbx\n\t"
        "pushq %rdi\n\t"
        "pushq %rsi\n\t"
        "pushq %r12\n\t"
        "pushq %r13\n\t"
        "pushq %r14\n\t"
        "pushq %r15\n\t"
        "pushq %gs:0x8\n\t"
        "pushq %gs:0x10\n\t"
        "pushq %gs:0x1478\n\t"
        "subq $176, %rsp\n\t"
        "movdqu %xmm6, 0(%rsp)\n\t"
        "movdqu %xmm7, 16(%rsp)\n\t"
        "movdqu %xmm8, 32(%rsp)\n\t"
        "movdqu %xmm9, 48(%rsp)\n\t"
        "movdqu %xmm10, 64(%rsp)\n\t"
        "movdqu %xmm11, 80(%rsp)\n\t"
        "movdqu %xmm12, 96(%rsp)\n\t"
        "movdqu %xmm13, 112(%rsp)\n\t"
        "movdqu %xmm14, 128(%rsp)\n\t"
        "movdqu %xmm15, 144(%rsp)\n\t"
        "stmxcsr 160(%rsp)\n\t"
        "fnstcw 164(%rsp)\n\t"
        "movq %rsp, (%rcx)\n\t"
        "movq %rdx, %rsp\n\t"
        "ldmxcsr 160(%rsp)\n\t"
        "fldcw 164(%rsp)\n\t"
        "movdqu 0(%rsp), %xmm6\n\t"
        "movdqu 16(%rsp), %xmm7\n\t"
        "movdqu 32(%rsp), %xmm8\n\t"
        "movdqu 48(%rsp), %xmm9\n\t"
        "movdqu 64(%rsp), %xmm10\n\t"
        "movdqu 80(%rsp), %xmm11\n\t"
        "movdqu 96(%rsp), %xmm12\n\t"
        "movdqu 112(%rsp), %xmm13\n\t"
        "movdqu 128(%rsp), %xmm14\n\t"
        "movdqu 144(%rsp), %xmm15\n\t"
        "addq $176, %rsp\n\t"
        "popq %gs:0x1478\n\t"
        "popq %gs:0x10\n\t"
        "popq %gs:0x8\n\t"
        "popq %r15\n\t"
        "popq %r14\n\t"
        "popq %r13\n\t"
        "popq %r12\n\t"
        "popq %rsi\n\t"
        "popq %rdi\n\t"
        "popq %rbx\n\t"
        "popq %rbp\n\t"
        "ret\n\t");
}

static void fa_entry(fa_fiber *f);

/* First switch into a fiber returns here (rsp 16-aligned) with the fiber in
 * r12: 32 bytes of shadow space, then fa_entry(f), which never returns. */
__attribute__((naked, used)) static void fa_start(void)
{
    __asm__ volatile(
        "movq %r12, %rcx\n\t"
        "subq $32, %rsp\n\t"
        "call fa_entry\n\t"
        "ud2\n\t");
}
#else
/* fa_swap(&from->sp, to->sp): save the running context on its stack, load the
 * other one.  cdecl; naked, so only the asm runs. */
__attribute__((naked)) static void fa_swap(void **save_sp, void *load_sp)
{
    __asm__ volatile(
        "movl 4(%esp), %eax\n\t"
        "movl 8(%esp), %edx\n\t"
        "pushl %ebp\n\t"
        "pushl %ebx\n\t"
        "pushl %esi\n\t"
        "pushl %edi\n\t"
        "pushl %fs:0\n\t"
        "pushl %fs:4\n\t"
        "pushl %fs:8\n\t"
        "pushl %fs:0xE0C\n\t"
        "subl $8, %esp\n\t"
        "stmxcsr 0(%esp)\n\t"
        "fnstcw 4(%esp)\n\t"
        "movl %esp, (%eax)\n\t"
        "movl %edx, %esp\n\t"
        "ldmxcsr 0(%esp)\n\t"
        "fldcw 4(%esp)\n\t"
        "addl $8, %esp\n\t"
        "popl %fs:0xE0C\n\t"
        "popl %fs:8\n\t"
        "popl %fs:4\n\t"
        "popl %fs:0\n\t"
        "popl %edi\n\t"
        "popl %esi\n\t"
        "popl %ebx\n\t"
        "popl %ebp\n\t"
        "ret\n\t");
}
#endif

/* First switch into a fiber "returns" here with [esp] = 0 (fake return
 * address) and [esp + 4] = the fiber.  Unhandled faults on the fiber go to the
 * process's unhandled-exception filter (rg-game's crash report), as Windows
 * fibers do through BaseFiberStart. */
#if defined(FA_X64)
__attribute__((used, noinline)) static void fa_entry(fa_fiber *f)
#else
static void __cdecl fa_entry(fa_fiber *f)
#endif
{
    __try {
        f->fn(f->arg);
    } __except (UnhandledExceptionFilter(GetExceptionInformation())) {
        ExitProcess(3);
    }
    abort(); /* fn must not return */
}

ps2k_fiber *fa_adopt_host(void)
{
    memset(&g_host, 0, sizeof g_host);
    g_host.magic = FA_FIBER;
    g_host.used = 1;
    g_host.slot = -1;
    g_host.started = 1;
    return (ps2k_fiber *)&g_host;
}

void fa_release_host(ps2k_fiber *host) { (void)host; }

ps2k_fiber *fa_create(size_t stack_size, ps2k_fiber_fn fn, void *arg)
{
    if (!g_hdr)
        return NULL;
    uint32_t stack = (uint32_t)((stack_size + 0xFFFFu) & ~(size_t)0xFFFFu);
    if (!g_hdr->stride) {
        uint32_t stride = stack + FA_GUARD;
        uint32_t n = (uint32_t)((g_size - FA_HDR_BYTES) / stride);
        if (n > FA_SLOTS)
            n = FA_SLOTS;
        if (n < 1)
            return NULL;
        g_hdr->stride = stride;
        g_hdr->stack_bytes = stack;
        g_hdr->nslots = n;
    }
    if (stack > g_hdr->stack_bytes)
        return NULL;
    for (uint32_t i = 0; i < g_hdr->nslots; i++) {
        fa_fiber *f = &g_hdr->slot[i];
        if (f->used)
            continue;
        uintptr_t sb = g_base + FA_HDR_BYTES + (uintptr_t)i * g_hdr->stride;
        uintptr_t lo = sb + FA_GUARD, hi = sb + g_hdr->stride;
        if (!VirtualAlloc((void *)lo, hi - lo, MEM_COMMIT, PAGE_READWRITE))
            return NULL;
        memset(f, 0, sizeof *f);
        f->magic = FA_FIBER;
        f->used = 1;
        f->slot = (int32_t)i;
        f->fn = fn;
        f->arg = arg;
        f->lo = lo;
        f->hi = hi;
#if defined(FA_X64)
        /* the frame fa_swap pops on the first switch (FA_X64_FRAME): `ret` then
         * lands in fa_start with rsp = hi - 64 (16-aligned) and r12 = f */
        uint64_t *q = (uint64_t *)(hi - 64);
        *--q = (uint64_t)(uintptr_t)fa_start;    /* ret target */
        *--q = 0;                                /* rbp */
        *--q = 0;                                /* rbx */
        *--q = 0;                                /* rdi */
        *--q = 0;                                /* rsi */
        *--q = (uint64_t)(uintptr_t)f;           /* r12: fa_entry's argument */
        *--q = 0;                                /* r13 */
        *--q = 0;                                /* r14 */
        *--q = 0;                                /* r15 */
        *--q = (uint64_t)hi;                     /* gs:0x8    StackBase */
        *--q = (uint64_t)lo;                     /* gs:0x10   StackLimit */
        *--q = (uint64_t)sb;                     /* gs:0x1478 DeallocationStack */
        uint8_t *x = (uint8_t *)q - 176;         /* xmm6-15 = 0, MXCSR, x87 CW */
        memset(x, 0, 176);
        __asm__ volatile("stmxcsr %0" : "=m"(*(uint32_t *)(x + 160)));
        __asm__ volatile("fnstcw %0" : "=m"(*(uint16_t *)(x + 164)));
        f->sp = x;
        return (ps2k_fiber *)f;
#else
        /* the frame fa_swap pops on the first switch (see the header) */
        uint32_t *sp = (uint32_t *)(hi - 64);
        *--sp = (uint32_t)(uintptr_t)f;           /* fa_entry's argument */
        *--sp = 0;                                /* fake return address */
        *--sp = (uint32_t)(uintptr_t)fa_entry;    /* ret target */
        *--sp = 0;                                /* ebp */
        *--sp = 0;                                /* ebx */
        *--sp = 0;                                /* esi */
        *--sp = 0;                                /* edi */
        *--sp = 0xFFFFFFFFu;                      /* fs:0  SEH head: end of chain */
        *--sp = (uint32_t)hi;                     /* fs:4  StackBase */
        *--sp = (uint32_t)lo;                     /* fs:8  StackLimit */
        *--sp = (uint32_t)sb;                     /* fs:E0C DeallocationStack */
        uint16_t cw;
        uint32_t mx;
        __asm__ volatile("fnstcw %0" : "=m"(cw));
        __asm__ volatile("stmxcsr %0" : "=m"(mx));
        *--sp = cw;                               /* x87 control word (4(%esp)) */
        *--sp = mx;                               /* MXCSR (0(%esp)) */
        f->sp = sp;
        return (ps2k_fiber *)f;
#endif
    }
    return NULL;
}

void fa_switch(ps2k_fiber *from, ps2k_fiber *to)
{
    fa_fiber *a = (fa_fiber *)from, *b = (fa_fiber *)to;
    b->started = 1;
    fa_swap(&a->sp, b->sp);
}

void fa_destroy(ps2k_fiber *p)
{
    fa_fiber *f = (fa_fiber *)p;
    if (!f || f == &g_host || f->magic != FA_FIBER)
        return;
    f->used = 0;
    f->started = 0;
    f->sp = NULL;
}

#else /* !FA_SUPPORTED */

ps2k_fiber *fa_adopt_host(void) { return NULL; }
void fa_release_host(ps2k_fiber *host) { (void)host; }
ps2k_fiber *fa_create(size_t stack_size, ps2k_fiber_fn fn, void *arg)
{
    (void)stack_size;
    (void)fn;
    (void)arg;
    return NULL;
}
void fa_switch(ps2k_fiber *from, ps2k_fiber *to)
{
    (void)from;
    (void)to;
}
void fa_destroy(ps2k_fiber *f) { (void)f; }

#endif

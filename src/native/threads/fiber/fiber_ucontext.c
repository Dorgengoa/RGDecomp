/* SPDX-License-Identifier: CC0-1.0
 * POSIX ucontext backend for ps2k (see fiber.h): Linux (docs/LINUX.md).
 *
 * Guest threads run on these stacks, and game code may hand the address of a
 * stack object to the DMAC, whose tag ADDR is 31 bits (bit 31 = scratchpad,
 * docs/DMAC.md).  The Windows exe is not large-address-aware, so everything is
 * below 2 GB there; on Linux an i686 process under an x86-64 kernel maps
 * top-down from ~4 GB, so stacks are mmapped below 2 GB explicitly, with a
 * PROT_NONE guard page under each (Windows fibers have one too). */
#ifndef _WIN32

#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE 1 /* MAP_ANONYMOUS */
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <ucontext.h>
#include <unistd.h>

#include "fiber.h"
#include "fiber_arena.h"   /* save states: fixed-address stacks while an arena is set (fiber_arena.c) */

struct ps2k_fiber {
    ucontext_t    ctx;
    void         *stack;     /* mapping base (guard page first) */
    size_t        map_size;
    ps2k_fiber_fn fn;
    void         *arg;
#ifdef RG_ASAN
    const void   *asan_bottom; /* stack bounds for the sanitizer (host: learnt at its first switch) */
    size_t        asan_size;
    void         *asan_fake;
#endif
};

#ifdef RG_ASAN
/* RG_ASAN check build (cmake/game.cmake, docs/UB-AUDIT.md "Local-size check"): every switch
 * is announced, so the sanitizer knows which stack is live and names the overrun local
 * ("located in stack ... frame ... object 'L430'") instead of a wild pointer. */
void __sanitizer_start_switch_fiber(void **fake_stack_save, const void *bottom, size_t size);
void __sanitizer_finish_switch_fiber(void *fake_stack_save, const void **bottom_old, size_t *size_old);
static __thread ps2k_fiber *asan_from;
static void asan_arrived(ps2k_fiber *self)
{
    const void *b = NULL;
    size_t n = 0;
    __sanitizer_finish_switch_fiber(self ? self->asan_fake : NULL, &b, &n);
    if (asan_from && !asan_from->asan_bottom) {
        asan_from->asan_bottom = b;
        asan_from->asan_size = n;
    }
}
#endif

/* A stack below 2 GB: try address hints upward from 256 MB (a hint is only
 * taken when that range is free, so each result is checked). */
static void *stack_map(size_t size)
{
    const uintptr_t limit = (uintptr_t)0x80000000u;
    for (uintptr_t hint = 0x10000000u; hint < limit; hint += 0x01000000u) {
        void *p = mmap((void *)hint, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED)
            return NULL;
        if ((uintptr_t)p < limit && size <= limit - (uintptr_t)p)
            return p;
        munmap(p, size);
    }
    return NULL;
}

/* makecontext passes int arguments; split the pointer in two halves so this
 * also works on LP64. */
static void fiber_entry(int lo, int hi)
{
    uintptr_t p = ((uintptr_t)(unsigned)lo);
#if UINTPTR_MAX > 0xFFFFFFFFu
    p |= ((uintptr_t)(unsigned)hi) << 32;
#else
    (void)hi;
#endif
    ps2k_fiber *f = (ps2k_fiber *)p;
#ifdef RG_ASAN
    asan_arrived(NULL);
#endif
    f->fn(f->arg);
    abort();
}

ps2k_fiber *ps2k_fiber_adopt_host(void)
{
    if (fa_on())
        return fa_adopt_host();
    ps2k_fiber *f = (ps2k_fiber *)calloc(1, sizeof *f);
    return f; /* ctx is filled by the first swapcontext away from it */
}

void ps2k_fiber_release_host(ps2k_fiber *host)
{
    if (fa_on()) {
        fa_release_host(host);
        return;
    }
    free(host);
}

ps2k_fiber *ps2k_fiber_create(size_t stack_size, ps2k_fiber_fn fn, void *arg)
{
    if (fa_on())
        return fa_create(stack_size, fn, arg);
    ps2k_fiber *f = (ps2k_fiber *)calloc(1, sizeof *f);
    if (!f)
        return NULL;
    size_t page = (size_t)sysconf(_SC_PAGESIZE);
    stack_size = (stack_size + page - 1) & ~(page - 1);
    f->map_size = stack_size + page;
    f->stack = stack_map(f->map_size);
    if (!f->stack) {
        free(f);
        return NULL;
    }
    mprotect(f->stack, page, PROT_NONE); /* guard page: overflow faults */
    f->fn = fn;
    f->arg = arg;
    if (getcontext(&f->ctx) != 0) {
        munmap(f->stack, f->map_size);
        free(f);
        return NULL;
    }
    f->ctx.uc_stack.ss_sp = (char *)f->stack + page;
    f->ctx.uc_stack.ss_size = stack_size;
    f->ctx.uc_link = NULL;
#ifdef RG_ASAN
    f->asan_bottom = f->ctx.uc_stack.ss_sp;
    f->asan_size = stack_size;
#endif
    uintptr_t p = (uintptr_t)f;
#if UINTPTR_MAX > 0xFFFFFFFFu
    makecontext(&f->ctx, (void (*)(void))fiber_entry, 2, (int)(unsigned)(p & 0xFFFFFFFFu),
                (int)(unsigned)(p >> 32));
#else
    makecontext(&f->ctx, (void (*)(void))fiber_entry, 2, (int)p, 0);
#endif
    return f;
}

void ps2k_fiber_switch(ps2k_fiber *from, ps2k_fiber *to)
{
    if (fa_on()) {
        fa_switch(from, to);
        return;
    }
#ifdef RG_ASAN
    asan_from = from;
    __sanitizer_start_switch_fiber(&from->asan_fake, to->asan_bottom, to->asan_size);
    swapcontext(&from->ctx, &to->ctx);
    asan_arrived(from);
#else
    swapcontext(&from->ctx, &to->ctx);
#endif
}

void ps2k_fiber_destroy(ps2k_fiber *f)
{
    if (fa_on()) {
        fa_destroy(f);
        return;
    }
    if (!f)
        return;
    if (f->stack)
        munmap(f->stack, f->map_size);
    free(f);
}

const char *ps2k_fiber_backend_name(void) { return "ucontext"; }

#endif /* !_WIN32 */

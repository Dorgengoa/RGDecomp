/* SPDX-License-Identifier: CC0-1.0
 * Windows Fibers backend for ps2k (see fiber.h). */
#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

#include "fiber.h"
#include "fiber_arena.h" /* fixed-address stacks for save states (ps2k_ss.h) */

struct ps2k_fiber {
    LPVOID        handle;
    ps2k_fiber_fn fn;
    void         *arg;
    int           converted; /* host thread converted by us */
};

static VOID CALLBACK fiber_proc(LPVOID param)
{
    ps2k_fiber *f = (ps2k_fiber *)param;
    f->fn(f->arg);
    /* fn must not return; returning from a fiber proc ends the host thread. */
    abort();
}

ps2k_fiber *ps2k_fiber_adopt_host(void)
{
    if (fa_on())
        return fa_adopt_host();
    ps2k_fiber *f = (ps2k_fiber *)calloc(1, sizeof *f);
    if (!f)
        return NULL;
    if (IsThreadAFiber()) {
        f->handle = GetCurrentFiber();
        f->converted = 0;
    } else {
        f->handle = ConvertThreadToFiberEx(NULL, FIBER_FLAG_FLOAT_SWITCH);
        f->converted = 1;
    }
    if (!f->handle) {
        free(f);
        return NULL;
    }
    return f;
}

void ps2k_fiber_release_host(ps2k_fiber *host)
{
    if (fa_on()) {
        fa_release_host(host);
        return;
    }
    if (!host)
        return;
    if (host->converted)
        ConvertFiberToThread();
    free(host);
}

ps2k_fiber *ps2k_fiber_create(size_t stack_size, ps2k_fiber_fn fn, void *arg)
{
    if (fa_on())
        return fa_create(stack_size, fn, arg);
    ps2k_fiber *f = (ps2k_fiber *)calloc(1, sizeof *f);
    if (!f)
        return NULL;
    f->fn = fn;
    f->arg = arg;
    /* commit 64 KiB up front, reserve stack_size */
    f->handle = CreateFiberEx(64 * 1024, stack_size, FIBER_FLAG_FLOAT_SWITCH, fiber_proc, f);
    if (!f->handle) {
        free(f);
        return NULL;
    }
    return f;
}

void ps2k_fiber_switch(ps2k_fiber *from, ps2k_fiber *to)
{
    if (fa_on()) {
        fa_switch(from, to);
        return;
    }
    (void)from;
    SwitchToFiber(to->handle);
}

void ps2k_fiber_destroy(ps2k_fiber *f)
{
    if (fa_on()) {
        fa_destroy(f);
        return;
    }
    if (!f)
        return;
    if (f->handle)
        DeleteFiber(f->handle);
    free(f);
}

const char *ps2k_fiber_backend_name(void) { return fa_on() ? "fiber-arena" : "win32-fibers"; }

#endif /* _WIN32 */

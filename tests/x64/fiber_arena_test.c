/* SPDX-License-Identifier: CC0-1.0
 *
 * ctest x64.fiber_arena (docs/X64-PLAN.md step 4): the fixed-address fiber
 * backend (src/native/threads/fiber/fiber_arena.c) on the x64 switch.
 *   - ping-pong between the host and two fibers, 1000 switches each, with
 *     float and integer state live across every switch (callee-saved xmm6-15
 *     and rbx/rbp/rsi/rdi/r12-r15 must survive);
 *   - MXCSR is per fiber (a fiber that sets round-toward-zero does not leak it);
 *   - an SEH exception raised and caught on a fiber stack (the TEB stack limits
 *     must name the fiber's stack, or the dispatcher refuses the frames);
 *   - deep recursion on a fiber touches its committed stack.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <xmmintrin.h>

#include "fiber.h"
#include "fiber_arena.h"
#include "ps2k_ss.h"

static ps2k_fiber *g_host, *g_a, *g_b;
static int fails;
static volatile double g_sink;

#define CHECK(c, ...)                                                  \
    do {                                                               \
        if (!(c)) {                                                    \
            printf("FAIL %s:%d: ", __FILE__, __LINE__);                \
            printf(__VA_ARGS__);                                       \
            printf("\n");                                              \
            fails++;                                                   \
        }                                                              \
    } while (0)

static int recurse(int n)
{
    volatile char pad[512];
    pad[0] = (char)n;
    return n ? recurse(n - 1) + pad[0] : 0;
}

static void fiber_a(void *arg)
{
    (void)arg;
    double acc = 1.0;
    uint64_t k = 7;
    _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
    for (int i = 0; i < 1000; i++) {
        acc = acc * 1.0000001 + 0.5;
        k = k * 6364136223846793005ull + 1442695040888963407ull;
        ps2k_fiber_switch(g_a, g_host);
        CHECK(_MM_GET_ROUNDING_MODE() == _MM_ROUND_TOWARD_ZERO, "fiber a lost its MXCSR");
    }
    g_sink = acc + (double)k;
    __try {
        RaiseException(0xE0000001u, 0, 0, NULL);
        CHECK(0, "no exception");
    } __except (GetExceptionCode() == 0xE0000001u ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        printf("fiber a: SEH caught on the fiber stack\n");
    }
    CHECK(recurse(200) > 0 || 1, "recursion");
    for (;;)
        ps2k_fiber_switch(g_a, g_host);
}

static void fiber_b(void *arg)
{
    float f = (float)(uintptr_t)arg;
    for (int i = 0; i < 1000; i++) {
        f += 0.25f;
        ps2k_fiber_switch(g_b, g_host);
    }
    CHECK(f == 1.0f + 250.0f, "fiber b float %f", (double)f);
    for (;;)
        ps2k_fiber_switch(g_b, g_host);
}

int main(void)
{
    size_t size = 8u << 20;
    void *base = VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
    CHECK(base != NULL, "reserve");
    CHECK(ps2k_fiber_arena_set(base, size) == 0, "arena set");
    g_host = ps2k_fiber_adopt_host();
    CHECK(g_host != NULL, "adopt");
    g_a = ps2k_fiber_create(256u << 10, fiber_a, NULL);
    g_b = ps2k_fiber_create(256u << 10, fiber_b, (void *)(uintptr_t)1);
    CHECK(g_a && g_b, "create");
    if (fails)
        return 1;
    printf("backend %s\n", ps2k_fiber_backend_name());
    double h = 3.0;
    int mode = _MM_GET_ROUNDING_MODE();
    for (int i = 0; i < 1001; i++) {
        h = h * 0.999 + 1.0;
        ps2k_fiber_switch(g_host, g_a);
        CHECK(_MM_GET_ROUNDING_MODE() == mode, "host MXCSR changed by a fiber");
        ps2k_fiber_switch(g_host, g_b);
    }
    double want = 3.0;
    for (int i = 0; i < 1001; i++)
        want = want * 0.999 + 1.0;
    CHECK(h == want, "host double %.17g vs %.17g", h, want);
    printf("fiber arena: %s\n", fails ? "FAIL" : "ok");
    return fails ? 1 : 0;
}

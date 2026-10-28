/* SPDX-License-Identifier: CC0-1.0
 * The ps2k API in a default build (docs/NATIVE-THREADS.md "Native kernel table"): two
 * implementations, chosen by ps2k_init's cfg.native:
 *   0  the EE kernel HLE (this directory, ps2k_hle_*): RG_THREADS=hle|service|frame, the
 *      oracle and the tests' kernel;
 *   1  the native kernel table (src/native/threads/rg_nk*.c, rg_nk_*): RG_THREADS=native.
 * Every ps2k_* function forwards to the one in use (generated rows: kapi/ps2k_api.inc,
 * tools/native/thread_api.py).  Host-side registrations made before any init (the frame
 * driver's hooks from constructors, the census tap, the violation hook) go to both.
 * RG_NATIVE_ONLY builds do not link this library: the native table defines ps2k_* itself
 * (cmake/native_only.cmake, rg_ps2_kernel=rg_native_kernel_ps2k). */
#include "ps2k.h"
#include "ps2k_ss.h"

#define PS2K_API(ret, name, params, args) ret ps2k_hle_##name params; ret rg_nk_##name params;
#define PS2K_APIV(name, params, args) void ps2k_hle_##name params; void rg_nk_##name params;
#include "ps2k_api.inc"
#undef PS2K_API
#undef PS2K_APIV

static int g_native; /* the kernel was initialised frame-driven (model state: a state carries it) */

/* registrations that are host state in both implementations: set both */
#define BOTH(name, params, args)                                                                                \
    void ps2k_##name params                                                                                     \
    {                                                                                                           \
        ps2k_hle_##name args;                                                                                   \
        rg_nk_##name args;                                                                                      \
    }
BOTH(set_start_hook, (ps2k_start_hook_fn fn), (fn))
BOTH(set_signal_hook, (ps2k_signal_hook_fn fn), (fn))
BOTH(set_phase_hook, (ps2k_phase_hook_fn fn), (fn))
BOTH(set_parked_hook, (ps2k_parked_hook_fn fn), (fn))
BOTH(set_block_hook, (ps2k_block_hook_fn fn), (fn))
BOTH(set_census_tap, (ps2k_tap_fn fn), (fn))
BOTH(set_violation_hook, (ps2k_violation_fn fn), (fn))
#undef BOTH

int ps2k_init(const ps2k_config *cfg)
{
    int native = cfg && cfg->native;
    if (native ? ps2k_hle_running() : rg_nk_running())
        return -1; /* the other kernel is still running */
    if (native) {
        ps2k_hle_shutdown();
        g_native = 1;
        return rg_nk_init(cfg);
    }
    rg_nk_shutdown();
    g_native = 0;
    return ps2k_hle_init(cfg);
}

/* everything else: the implementation in use */
#define PS2K_API(ret, name, params, args) \
    ret ps2k_##name params { return g_native ? rg_nk_##name args : ps2k_hle_##name args; }
#define PS2K_APIV(name, params, args)                                                                           \
    void ps2k_##name params                                                                                     \
    {                                                                                                           \
        if (g_native)                                                                                           \
            rg_nk_##name args;                                                                                  \
        else                                                                                                    \
            ps2k_hle_##name args;                                                                               \
    }
/* the rows defined above are compiled out of the list by name */
#define ps2k_init               ps2k_dispatch_unused_init
#define ps2k_set_start_hook     ps2k_dispatch_unused_set_start_hook
#define ps2k_set_signal_hook    ps2k_dispatch_unused_set_signal_hook
#define ps2k_set_phase_hook     ps2k_dispatch_unused_set_phase_hook
#define ps2k_set_parked_hook    ps2k_dispatch_unused_set_parked_hook
#define ps2k_set_block_hook     ps2k_dispatch_unused_set_block_hook
#define ps2k_set_census_tap     ps2k_dispatch_unused_set_census_tap
#define ps2k_set_violation_hook ps2k_dispatch_unused_set_violation_hook
#include "ps2k_api.inc"

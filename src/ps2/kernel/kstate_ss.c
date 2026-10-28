/* SPDX-License-Identifier: CC0-1.0
 * Kernel state for port save states (ps2k_ss.h, docs/TEST-FIXTURES.md).
 *
 * The whole kstate K is saved.  On load, everything the GAME built (threads,
 * semaphores, handlers, alarms, timers, the clock, the event queue, the
 * trace hash) comes from the state; what the loading PROCESS registered in
 * its own init stays: the scheduler fiber, VBlank observers, devices, the
 * pacing / trace / violation hooks and the run-control part of the config
 * (stop / stall limits).  The game-visible config (VBlank line and enable,
 * kernel-call cost, EIE model) must be equal, else the load
 * is refused. */
#include <stddef.h>
#include <string.h>

#include "internal.h"
#include "ps2k_ss.h"

#define KSS_MAGIC 0x3153534Bu /* "KSS1" */

typedef struct kss_hdr {
    uint32_t magic;
    uint32_t bytes;   /* sizeof(kstate) */
    uint32_t fiber_arena;
    uint32_t pad;
} kss_hdr;

size_t ps2k_ss_size(void) { return sizeof(kss_hdr) + sizeof(kstate); }

int ps2k_ss_save(void *buf, size_t cap)
{
    if (cap < ps2k_ss_size() || K.cur || K.in_handler)
        return -1;
    kss_hdr h = {KSS_MAGIC, (uint32_t)sizeof(kstate), (uint32_t)ps2k_fiber_arena_on(), 0};
    memcpy(buf, &h, sizeof h);
    memcpy((uint8_t *)buf + sizeof h, &K, sizeof K);
    return (int)ps2k_ss_size();
}

int ps2k_ss_load(const void *buf, size_t n)
{
    kss_hdr h;
    if (n != ps2k_ss_size() || K.cur || K.in_handler || !K.inited)
        return -1;
    memcpy(&h, buf, sizeof h);
    if (h.magic != KSS_MAGIC || h.bytes != sizeof(kstate) || !h.fiber_arena || !ps2k_fiber_arena_on())
        return -1;
    const kstate *s = (const kstate *)((const uint8_t *)buf + sizeof h);
    if (s->cfg.vblank_enable != K.cfg.vblank_enable ||
        s->cfg.vblank_start_line != K.cfg.vblank_start_line ||
        s->cfg.kcall_cycles != K.cfg.kcall_cycles || s->cfg.eie_per_thread != K.cfg.eie_per_thread ||
        s->cfg.host_stack_size != K.cfg.host_stack_size || s->cfg.native != K.cfg.native)
        return -1; /* native: a frame-driven state holds flows only (docs/NATIVE-THREADS.md) */

    /* this process's own bindings */
    ps2k_config cfg = K.cfg;
    ps2k_fiber *sched = K.sched;
    ps2k_pacing_fn pacing = K.pacing;
    void *pacing_user = K.pacing_user;
    kobserver obs[PS2K_MAX_OBSERVERS];
    kdevice dev[PS2K_MAX_DEVICES];
    int nobs = K.nobs, ndev = K.ndev, next_glue_id = K.next_glue_id;
    memcpy(obs, K.obs, sizeof obs);
    memcpy(dev, K.dev, sizeof dev);
    ps2k_trace_fn trace_hook = K.trace_hook;
    void *trace_user = K.trace_user;
    ps2k_violation_fn violation = K.violation;

    memcpy(&K, s, sizeof K);

    K.cfg = cfg;
    if (!sched)
        sched = ps2k_fiber_adopt_host(); /* this process never called ps2k_start */
    K.sched = sched;
    K.pacing = pacing;
    K.pacing_user = pacing_user;
    memcpy(K.obs, obs, sizeof obs);
    memcpy(K.dev, dev, sizeof dev);
    K.nobs = nobs;
    K.ndev = ndev;
    K.next_glue_id = next_glue_id;
    K.trace_hook = trace_hook;
    K.trace_user = trace_user;
    K.violation = violation;
    K.cur = NULL;
    K.in_handler = 0;
    K.in_device_poll = 0;
    return sched ? 0 : -1;
}

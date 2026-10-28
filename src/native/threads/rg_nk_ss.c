/* SPDX-License-Identifier: CC0-1.0
 * The native kernel table in port save states (kapi/ps2k_ss.h, docs/TEST-FIXTURES.md).
 *
 * The whole table NK is saved (thread objects, semaphores, handler chains, the event
 * list, the logic clock, the flows' fiber pointers: their stacks are in the fixed-address
 * arena, saved by src/savestate).  On load, what the loading PROCESS registered keeps its
 * value: the driver's host fiber, VBlank observers, devices, the pacing / trace /
 * violation hooks and the run-control part of the config.  The game-visible config
 * (VBlank line and enable, EIE model) must be equal, else the load is refused. */
#include <stddef.h>
#include <string.h>

#include "rg_nk_internal.h"
#include "ps2k_ss.h"

#define NKSS_MAGIC 0x314B4E4Eu /* "NNK1": not loadable into the HLE ("KSS1") or back */

typedef struct nkss_hdr {
    uint32_t magic;
    uint32_t bytes;
    uint32_t fiber_arena;
    uint32_t pad;
} nkss_hdr;

size_t ps2k_ss_size(void) { return sizeof(nkss_hdr) + sizeof(nkstate); }

int ps2k_ss_save(void *buf, size_t cap)
{
    if (cap < ps2k_ss_size() || NK.cur || NK.in_handler)
        return -1;
    nkss_hdr h = {NKSS_MAGIC, (uint32_t)sizeof(nkstate), (uint32_t)ps2k_fiber_arena_on(), 0};
    memcpy(buf, &h, sizeof h);
    memcpy((uint8_t *)buf + sizeof h, &NK, sizeof NK);
    return (int)ps2k_ss_size();
}

int ps2k_ss_load(const void *buf, size_t n)
{
    nkss_hdr h;
    if (n != ps2k_ss_size() || NK.cur || NK.in_handler || !NK.inited)
        return -1;
    memcpy(&h, buf, sizeof h);
    if (h.magic != NKSS_MAGIC || h.bytes != sizeof(nkstate) || !h.fiber_arena || !ps2k_fiber_arena_on())
        return -1;
    const nkstate *s = (const nkstate *)((const uint8_t *)buf + sizeof h);
    if (s->cfg.vblank_enable != NK.cfg.vblank_enable || s->cfg.vblank_start_line != NK.cfg.vblank_start_line ||
        s->cfg.eie_per_thread != NK.cfg.eie_per_thread || s->cfg.host_stack_size != NK.cfg.host_stack_size)
        return -1;

    ps2k_config cfg = NK.cfg;
    ps2k_fiber *sched = NK.sched;
    ps2k_pacing_fn pacing = NK.pacing;
    void *pacing_user = NK.pacing_user;
    nkobserver obs[PS2K_MAX_OBSERVERS];
    nkdevice dev[PS2K_MAX_DEVICES];
    int nobs = NK.nobs, ndev = NK.ndev, next_glue_id = NK.next_glue_id;
    memcpy(obs, NK.obs, sizeof obs);
    memcpy(dev, NK.dev, sizeof dev);
    ps2k_trace_fn trace_hook = NK.trace_hook;
    void *trace_user = NK.trace_user;
    ps2k_violation_fn violation = NK.violation;

    memcpy(&NK, s, sizeof NK);

    NK.cfg = cfg;
    if (!sched)
        sched = ps2k_fiber_adopt_host(); /* this process never called ps2k_start */
    NK.sched = sched;
    NK.pacing = pacing;
    NK.pacing_user = pacing_user;
    memcpy(NK.obs, obs, sizeof obs);
    memcpy(NK.dev, dev, sizeof dev);
    NK.nobs = nobs;
    NK.ndev = ndev;
    NK.next_glue_id = next_glue_id;
    NK.trace_hook = trace_hook;
    NK.trace_user = trace_user;
    NK.violation = violation;
    NK.cur = NULL;
    NK.in_handler = 0;
    NK.in_device_poll = 0;
    NK.in_step = 0;
    return sched ? 0 : -1;
}

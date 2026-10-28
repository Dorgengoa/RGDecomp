/* SPDX-License-Identifier: CC0-1.0 */
/* Card time model of the native save service (mccard.h, docs/NATIVE-IOP.md): the
 * virtual time a memory-card operation takes.  Placeholder values until a PCSX2 trace
 * measures the game's load/save steps (docs/PADMC.md "Open questions" 8). */
#include "mccard.h"

#include <string.h>

#define BUSCLK 147456000ull

static struct {
    mc_time_config cfg;
    int set;
} T;

void mc_time_default_config(mc_time_config *c)
{
    c->op_cycles = BUSCLK / 1000;                /* 1 ms */
    c->read_cycles_per_kb = BUSCLK * 25 / 10000; /* 2.5 ms */
    c->write_cycles_per_kb = BUSCLK * 6 / 1000;  /* 6 ms */
    c->format_cycles = BUSCLK * 2;               /* 2 s */
}

void mc_time_configure(const mc_time_config *c)
{
    if (c)
        T.cfg = *c;
    else
        mc_time_default_config(&T.cfg);
    T.set = 1;
}

const mc_time_config *mc_time_get_config(void)
{
    if (!T.set)
        mc_time_configure(NULL);
    return &T.cfg;
}

static uint64_t kb_cost(int bytes, uint64_t per_kb)
{
    if (bytes <= 0)
        return 0;
    return ((uint64_t)bytes * per_kb + 1023u) / 1024u;
}

uint64_t mc_time_cost(int op, int result)
{
    const mc_time_config *c = mc_time_get_config();
    uint64_t f = c->format_cycles > 0xFFFFFFFFull ? 0xFFFFFFFFull : c->format_cycles;
    switch (op) {
    case MC_OP_INIT:
    case MC_OP_SLOTMAX:
        return 0;
    case MC_OP_READ:
        return (uint32_t)c->op_cycles + (uint32_t)kb_cost(result, c->read_cycles_per_kb);
    case MC_OP_WRITE:
        return (uint32_t)c->op_cycles + (uint32_t)kb_cost(result, c->write_cycles_per_kb);
    case MC_OP_FORMAT:
    case MC_OP_UNFORMAT:
        return f;
    case MC_OP_GETINFO: case MC_OP_OPEN: case MC_OP_CLOSE: case MC_OP_SEEK: case MC_OP_FLUSH:
    case MC_OP_CHDIR: case MC_OP_GETDIR: case MC_OP_SETINFO: case MC_OP_DELETE: case MC_OP_ENTSPACE:
        return (uint32_t)c->op_cycles;
    default:
        return 0;
    }
}

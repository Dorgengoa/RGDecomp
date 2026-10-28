/* SPDX-License-Identifier: CC0-1.0 */
/* RG_OVL_DATA backing: MAIN code that reads/writes overlay memory by literal
 * address (docs/HWBUS.md "Overlay data").  The overlay manager installs a
 * resolver; until it does, or while the overlay is not resident, accesses go
 * to a zeroed scratch slot and are reported once per symbol. */
#include "hwbus.h"

#include <stdio.h>
#include <string.h>

#define OVL_SCRATCH 0x10000u
#define OVL_MAX_REPORTED 64

static struct {
    hwbus_ovl_resolver_fn fn;
    void *user;
    uint64_t unresolved;
    const char *reported[OVL_MAX_REPORTED];
    int nreported;
} O;

static uint8_t g_scratch[OVL_SCRATCH] __attribute__((aligned(16)));

void hwbus_set_ovl_resolver(hwbus_ovl_resolver_fn fn, void *user)
{
    O.fn = fn;
    O.user = user;
}

uint64_t hwbus_ovl_unresolved(void) { return O.unresolved; }

void *rg_ovl_data_ptr(const char *ovl, const char *sym, uint32_t sym_addr, uint32_t off)
{
    int i;
    if (O.fn) {
        uint8_t *p = (uint8_t *)O.fn(O.user, ovl, sym, sym_addr);
        if (p) return p + off;
    }
    O.unresolved++;
    for (i = 0; i < O.nreported; i++)
        if (strcmp(O.reported[i], sym) == 0) break;
    if (i == O.nreported && O.nreported < OVL_MAX_REPORTED) {
        O.reported[O.nreported++] = sym;
        fprintf(stderr,
                "hwbus: overlay data %s:%s+0x%X (retail 0x%08X) unresolved (%s) -- "
                "scratch slot; reported once\n",
                ovl, sym, off, sym_addr + off, O.fn ? "overlay not resident" : "no resolver");
    }
    return g_scratch + ((sym_addr + off) & (OVL_SCRATCH - 1u));
}

/* SPDX-License-Identifier: CC0-1.0
 *
 * Game-facing bindings of the overlay manager (docs/OVERLAY.md "Bindings").
 *
 * OverlayLoadFile_100410 is an asm-bodied unit (EXCLUDED.tsv, band
 * crt0+MSL-runtime), so it is BOUND here, not overridden: ingest cuts the
 * game file and this definition takes the symbol.  Retail body:
 *
 *     n = FileReadAll_1004b0(path, load)       sceOpen/Lseek/Read/Close over FILEIO,
 *     if (n <= 0) return 0;                    whole file (header+text+data) -> load
 *     OverlayLoadNotifyStubMaybe_100400(load); empty
 *     FlushCache(0); FlushCache(2);
 *     if (hdr->bss) memset(load + n, 0, hdr->bss);
 *     RunStaticCtors_100df0(hdr->ctors, hdr->dtors, 0, 0);   then EhRegisterFragment stub
 *     return 1;
 *
 * Its caller OverlayLoad_1c3210 (C, unchanged) retries `while (!...)`, then
 * stores the loader index in D_0047E254 (GetLoadedOverlayId_1c3200).
 *
 * The port does not read the .BIN: the overlay is linked in and its pristine
 * .data comes from the registry.  FileReadAll_1004b0 (only caller: this
 * function) therefore needs no binding of its own.
 */
#include "ovl.h"
#include "hwbus.h"

#include <stdio.h>
#include <stdlib.h>

/* s32 OverlayLoadFile_100410(s32 path, s32 load) -- OverlayLoad_1c3210.cpp's
 * declaration; `path` is a host char * (D_0044AF90 row), `load` is
 * D_0047D134[0] = &data2c_overlay_load_base (the arena). */
/* D_0044AF90[3][7] holds RAW .rodata addresses of the 21 path strings (both at
 * naming 2efa6b43 and in data2c d784320c: .rodata pointers were not
 * symbolized): 0x0045AD30 + 0x20 * (row * 7 + loader index), rows cdrom0:,
 * cdrom1:, host0:.  Until MAIN's .rodata is relocated, OverlayLoad_1c3210
 * hands us such a number; decode it instead of dereferencing it. */
#define RG_OVL_PATHS_PS2 0x0045AD30u
#define RG_OVL_PATH_STRIDE 0x20u

int OverlayLoadFile_100410(int path, int load)
{
    const char *p = (const char *)(intptr_t)path;
    const rg_ovl_registry *r = rg_ovl_bound();
    uint32_t u = (uint32_t)path;
    int ovl;
    if (u >= RG_OVL_PATHS_PS2 && u < RG_OVL_PATHS_PS2 + 21 * RG_OVL_PATH_STRIDE &&
        (u - RG_OVL_PATHS_PS2) % RG_OVL_PATH_STRIDE == 0) {
        ovl = rg_ovl_find_index((int)((u - RG_OVL_PATHS_PS2) / RG_OVL_PATH_STRIDE) % 7);
        p = "(retail D_0044AF90 entry)";
    } else {
        ovl = rg_ovl_find_file(p);
    }
    if (ovl < 0) {
        fprintf(stderr, "ovl: OverlayLoadFile(\"%s\"): no such overlay in the registry\n",
                p ? p : "(null)");
        abort();        /* retail would spin in OverlayLoad_1c3210's retry loop forever */
    }
    if (r && r->arena && (unsigned char *)(intptr_t)load != r->arena)
        fprintf(stderr, "ovl: OverlayLoadFile: load address %p is not the arena %p (ignored)\n",
                (void *)(intptr_t)load, (void *)r->arena);
    rg_ovl_load(ovl);
    return 1;
}

/* Runtime service hook (rg_runtime_set_service_hook): bind the registry
 * passed as `user` and install the RG_OVL_DATA resolver into hwbus. */
void rg_ovl_service_init(void *user)
{
    const rg_ovl_registry *reg = (const rg_ovl_registry *)user;
    if (reg && rg_ovl_bind(reg) != 0) {
        fprintf(stderr, "ovl: registry rejected\n");
        abort();
    }
    hwbus_set_ovl_resolver(rg_ovl_hwbus_resolve, NULL);
}

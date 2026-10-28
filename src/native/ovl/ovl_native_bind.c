/* SPDX-License-Identifier: CC0-1.0
 *
 * Game-facing bindings of the native module table (docs/OVERLAY.md section 8).
 *
 * OverlayLoadFile_100410 is an asm-bodied unit (EXCLUDED.tsv, crt0+MSL band), so
 * it is BOUND here: retail reads the .BIN over the arena, zeroes the bss after it
 * and runs the .ctors range.  The modules are linked in, so the binding names the
 * module by the file name in `path` (a host string: datareloc relocated
 * D_0044AF90's path pointers) and loads it.  `load` (D_0047D134[0] =
 * &data2c_overlay_load_base, retail's 0x004E9E80) names no memory any more: each
 * module has its own segment; it is ignored.  Its caller OverlayLoad_1c3210 (C,
 * unchanged) retries `while (!...)` and stores the loader index in D_0047E254.
 */
#include "ovl.h"

#include <stdio.h>
#include <stdlib.h>

int OverlayLoadFile_100410(int path, int load)
{
    const char *p = (const char *)(intptr_t)path;
    int ovl = rg_ovl_find_file(p);
    (void)load;
    if (ovl < 0) {
        fprintf(stderr, "ovl: OverlayLoadFile(\"%s\"): no such module in the table\n",
                p ? p : "(null)");
        abort();        /* retail would spin in OverlayLoad_1c3210's retry loop forever */
    }
    rg_ovl_load(ovl);
    return 1;
}

/* Runtime service hook (rg_runtime_set_service_hook): bind the module table
 * passed as `user`. */
void rg_ovl_service_init(void *user)
{
    const rg_ovl_registry *reg = (const rg_ovl_registry *)user;
    if (reg && rg_ovl_bind(reg) != 0) {
        fprintf(stderr, "ovl: module table rejected\n");
        abort();
    }
}

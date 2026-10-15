#include "types.h"

/* factory.bin overlay, 0x004EC3F0 -- the module's per-tick poll: do nothing at
 * all unless the module is live, and inside that, only run the refresh when the
 * panel exists AND the "dirty" byte is set.
 * 64 bytes, 16 instructions, 3 conditional branches, 1 call.
 *
 * * The first test is the EARLY RETURN -- retail's `beql` carries the epilogue's
 * `ld $31` in its likely slot, which is what distinguishes it from the two
 * inner tests, whose plain `beqz`/`nop` pairs are the `&&` short circuit into
 * the shared tail at 0x004EC424.
 *
 * * `lw $4` -- the panel handle is TESTED AND THEN PASSED, exactly the shape
 * `factory_FactoryMenuTexRelease_4ec090` documents: retail leaves it in $4 across the second
 * test and the `jal`'s delay slot is a bare `nop`.
 */

extern u8    D_00484A68;                        /* _gp - 0x708  */
extern void *D_00484A60;                        /* _gp - 0x710  */
extern u8    D_00480800;                        /* _gp - 0x4970 */

extern void factory_FactoryMarkerDrawAll_4f6ba0(void *p);

void factory_FactoryMenuDraw2_4ec3f0(void)
{
    if (D_00484A68 == 0) {
        return;
    }
    if (D_00484A60 != 0 && D_00480800 != 0) {
        factory_FactoryMarkerDrawAll_4f6ba0(D_00484A60);
    }
}

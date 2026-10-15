#include "types.h"

/* insmenu.bin overlay, 0x004F32E0 -- store the argument into a gp byte flag.
 *
 *     jr $31
 *      sb $4, -0xE6C($28)          <- gp 0x00485170 - 0xE6C = 0x00484304
 *
 * D_00484304 is INSIDE the gp window (0x47D170..0x48D170), so the extern is
 * deliberately NOT `const` -- `const` would switch it to %hi/%lo and cost a
 * second instruction.  That is the overlay-data rule read the other way round.
 *
 * ⚠ The parameter width is unconstrained by the two call sites in
 * insmenu_InsectVsTeamCommitCb_4f3860: both pass `addiu $4, $0, 1`, which is what a `u8` and
 * an `s32` argument both materialise.  `u8` is written because the store is a
 * byte and the flag is set to 0/1; nothing measures it.
 */

extern u8 D_00484304;

void insmenu_InsectVsSetBusyFlagMaybe_4f32e0(u8 v)
{
    D_00484304 = v;
}

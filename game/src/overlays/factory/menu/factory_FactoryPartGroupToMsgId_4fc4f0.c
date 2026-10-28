/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupToMsgId_4fc4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FC4F0 -- map a slot index to its message id.
 *
 * A compiled `switch` with a real jump table (factory_jtbl_0050CD80, 6 entries);
 * scripts/f_jtbl.py points it at the overlay's own table instead of letting
 * mwcc emit a second copy into the object's .rodata.
 *
 * ★ The CASE ORDER is read off the table, not off the block order: entry N of
 * factory_jtbl_0050CD80 is the address of case N's body, and the bodies run 4, 5, 0,
 * 3, 1, 2 in ASCENDING address order -- which is source order for a jump
 * table (the reversed-chain rule is about compare CHAINS and does not apply).
 *
 * ★ Cases 4 and 5 both return 0x4E20 and retail gives each its own block, so
 * they are two separate `case` labels with their own `return`, not a shared
 * fall-through pair.
 *
 * ★ `beql $1, $0, .L004FC54C` carrying `addiu $2, $0, -0x1` is the ordinary
 * likely-branch duplication of the merge's first instruction -- the default
 * block at 0x004FC548 is that same instruction.  There is no second `return`.
 *
 * $4 is marshalled by the caller (`daddu $4, $19, $0`) and never read here.
 */

s32 factory_FactoryPartGroupToMsgId_4fc4f0(void *o, s32 slot)
{
    switch (slot) {
    case 4:
        return 0x4E20;
    case 5:
        return 0x4E20;
    case 0:
        return 0x4E21;
    case 3:
        return 0x4E22;
    case 1:
        return 0x4E23;
    case 2:
        return 0x4E24;
    }
    return -1;
}

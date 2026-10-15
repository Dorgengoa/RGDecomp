#include "types.h"

/* factory.bin overlay, 0x004FC560 -- slot index -> message id.  the same index -> id
 * map as `factory_FactoryPartGroupToItemId_4f4070`, for the second parts list.
 *
 * A compiled `switch` over indices 0..0x12, so mwcc emits a real jump table;
 * scripts/f_jtbl.py points it at the overlay's own jtbl_0050CDA0.
 *
 * ★★ THE CASE ORDER IS READ OFF THE TABLE, NOT OFF THE CONSTANTS.  Entry N of
 * jtbl_0050CDA0 is case N's body address, and the bodies run in ASCENDING
 * address order carrying ASCENDING ids -- so source order is 13, 14, 18, 15,
 * 16, 17, 4, 5, 6, 0, 3, 1, 2, 10, 11, 12, which is nothing like the numeric
 * order of the labels.  Writing them 0..18 is the right length and the wrong
 * table.
 *
 * ★ Entries 7, 8 and 9 all hold the DEFAULT block's address, so those three
 * cases are simply absent from the source -- mwcc fills the hole itself.  The
 * bound is `sltiu 0x13` because the highest case is 18.
 *
 * $4 is marshalled at the call site and never read here.
 */

s32 factory_FactoryPartGroupToItemId_4fc560(void *o, s32 slot)
{
    switch (slot) {
    case 13:
        return 0x4183;
    case 14:
        return 0x4184;
    case 18:
        return 0x4185;
    case 15:
        return 0x4186;
    case 16:
        return 0x4187;
    case 17:
        return 0x4188;
    case 4:
        return 0x4189;
    case 5:
        return 0x418A;
    case 6:
        return 0x418B;
    case 0:
        return 0x418C;
    case 3:
        return 0x418D;
    case 1:
        return 0x418E;
    case 2:
        return 0x418F;
    case 10:
        return 0x4190;
    case 11:
        return 0x4191;
    case 12:
        return 0x4192;
    }
    return -1;
}

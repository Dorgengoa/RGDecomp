/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsItemToGroup_4efb80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EFB80 -- message id -> slot index.
 *
 * A compiled `switch` over 16 contiguous ids 0x4183..0x4192, so mwcc emits a
 * real jump table; scripts/f_jtbl.py points it at the overlay's own
 * factory_jtbl_0050CAE0 instead of letting the object carry a second copy.
 *
 * ★ factory_jtbl_0050CAE0 is in ASCENDING address order, so the source case order is
 * ascending too -- read the ORDER off the table, never off the constants.
 * (`factory_FactoryPartGroupToItemId_4f4070` is the inverse map and its table is NOT ascending.)
 *
 * ★ `beql $1, $0, .L004EFC30` carrying `addiu $2, $0, -0x1` is the ordinary
 * likely-branch duplication of the merge's first instruction; the default
 * block at 0x004EFC2C is that same instruction and there is only one
 * `return -1` in the source.
 *
 * ★ `daddu $2, $0, $0` is `return 0` -- a case body, not a cleared register.
 *
 * $4 is marshalled at every call site and never read here.
 */

s32 factory_FactoryPartsItemToGroup_4efb80(void *o, s32 id)
{
    switch (id) {
    case 0x4183:
        return 0xD;
    case 0x4184:
        return 0xE;
    case 0x4185:
        return 0x12;
    case 0x4186:
        return 0xF;
    case 0x4187:
        return 0x10;
    case 0x4188:
        return 0x11;
    case 0x4189:
        return 4;
    case 0x418A:
        return 5;
    case 0x418B:
        return 6;
    case 0x418C:
        return 0;
    case 0x418D:
        return 3;
    case 0x418E:
        return 1;
    case 0x418F:
        return 2;
    case 0x4190:
        return 0xA;
    case 0x4191:
        return 0xB;
    case 0x4192:
        return 0xC;
    }
    return -1;
}

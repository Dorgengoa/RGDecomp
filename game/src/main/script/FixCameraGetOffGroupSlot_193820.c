/* rgp:protos */
#define RGP_SELF_FixCameraGetOffGroupSlot_193820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair returning the ADDRESS of an 8-byte record: count at
   +0xA4, table at +0xA8. */

typedef struct OwnerA4 {
    u8 pad000[0xA4];
    s32 count;         /* +0xA4 */
    u8 rec[1];         /* +0xA8, 8 bytes each */
} OwnerA4;

void *FixCameraGetOffGroupSlot_193820(OwnerA4 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 8];
}

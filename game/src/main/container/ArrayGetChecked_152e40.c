/* rgp:protos */
#define RGP_SELF_ArrayGetChecked_152e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of ArrayGetChecked_152fd0 (byte-identical, in cunits):
   guard pair over an indirect table, count at +0x0 and the array POINTER at
   +0x4; the pointer load fills the bounds guard's delay slot. */

typedef struct OwnerFUN_00152e40 {
    s32 count;         /* +0x00 */
    s32 *list;         /* +0x04 */
} OwnerFUN_00152e40;

s32 ArrayGetChecked_152e40(OwnerFUN_00152e40 *o, s32 index)
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
    return o->list[index];
}

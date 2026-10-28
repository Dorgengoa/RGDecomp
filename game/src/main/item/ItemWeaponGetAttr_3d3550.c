/* rgp:protos */
#define RGP_SELF_ItemWeaponGetAttr_3d3550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The asymmetric guard pair over a 5-entry byte table at +0x17.

   Reached only through the two function-pointer tables at 0x00475D70 and
   0x00475E90, which is why splat named it func_ rather than FUN_. */

typedef struct Owner17 {
    u8 pad000[0x17];
    s8 slot[1];        /* +0x17, 5 of them */
} Owner17;

s32 ItemWeaponGetAttr_3d3550(Owner17 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 5;
    if (ok != 0) {
        goto found;
    }
none:
    return (s8)(0);
found:
    return (s8)(o->slot[index]);
}

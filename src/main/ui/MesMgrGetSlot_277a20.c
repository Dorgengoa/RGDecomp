#include "types.h"

/* The asymmetric guard pair again -- fifth site, same three-line shape as
   ObjRecTableGet_1c3f60, and the bound is a CONSTANT 8 rather than a field. See that
   file for why the shared label has to sit physically before the compute
   block. */

typedef struct Owner00277a20 {
    u8 pad0000[0x1E00];
    void *slot[8];     /* +0x1E00 */
} Owner00277a20;

void *MesMgrGetSlot_277a20(Owner00277a20 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 8;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return o->slot[index];
}

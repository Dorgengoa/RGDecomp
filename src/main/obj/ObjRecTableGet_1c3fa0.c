#include "types.h"

/* The middle entry of the dispatcher ObjRecLookup_1c3ef0 fans out to, and the sixth
   member of the asymmetric-guard-pair class: count at +0x3C58, 0x28-byte
   records at +0x3C5C. See src/world/ObjRecTableGet_1c3f60.c for the recipe. */

typedef struct Owner3C58 {
    u8 pad0000[0x3C58];
    s32 count;         /* +0x3C58 */
    u8 rec[1];         /* +0x3C5C, 0x28 bytes each */
} Owner3C58;

void *ObjRecTableGet_1c3fa0(Owner3C58 *o, s32 index)
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
    return &o->rec[index * 0x28];
}

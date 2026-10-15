#include "types.h"

/* Read the s16 at +0x14. */

typedef struct Obj_FUN_003237b0 {
    u8 pad000[0x14];
    s16 field;         /* +0x14 */
} Obj_FUN_003237b0;

s16 EntryListGetTileSize_3237b0(Obj_FUN_003237b0 *o)
{
    return o->field;
}

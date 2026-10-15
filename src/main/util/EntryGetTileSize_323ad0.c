#include "types.h"

/* Read the s32 at +0x28. */

typedef struct Obj_FUN_00323ad0 {
    u8 pad000[0x28];
    s32 field;         /* +0x28 */
} Obj_FUN_00323ad0;

s32 EntryGetTileSize_323ad0(Obj_FUN_00323ad0 *o)
{
    return o->field;
}

#include "types.h"

/* Write the s32 at +0x28. */

typedef struct Obj_FUN_00323ae0 {
    u8 pad000[0x28];
    s32 field;         /* +0x28 */
} Obj_FUN_00323ae0;

void EntrySetTileSize_323ae0(Obj_FUN_00323ae0 *o, s32 value)
{
    o->field = value;
}

#include "types.h"

/* Write the f32 at +0x4C. */

typedef struct Obj_FUN_001e73d0 {
    u8 pad000[0x4C];
    f32 field;         /* +0x4C */
} Obj_FUN_001e73d0;

void MapDataSetOffsetRotY_1e73d0(Obj_FUN_001e73d0 *o, f32 value)
{
    o->field = value;
}

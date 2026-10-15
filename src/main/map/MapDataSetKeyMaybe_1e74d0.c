#include "types.h"

/* Write the s16 at +0x1A. */

typedef struct Obj_FUN_001e74d0 {
    u8 pad000[0x1A];
    s16 field;         /* +0x1A */
} Obj_FUN_001e74d0;

void MapDataSetKeyMaybe_1e74d0(Obj_FUN_001e74d0 *o, s16 value)
{
    o->field = value;
}

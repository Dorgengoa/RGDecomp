#include "types.h"

/* Write the s16 at +0x1E. */

typedef struct Obj_FUN_001e74a0 {
    u8 pad000[0x1E];
    s16 field;         /* +0x1E */
} Obj_FUN_001e74a0;

void MapDataSetLightRef_1e74a0(Obj_FUN_001e74a0 *o, s16 value)
{
    o->field = value;
}

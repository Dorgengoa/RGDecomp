#include "types.h"

/* Read the s16 at +0x1C. */

typedef struct Obj_FUN_001e7bb0 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_001e7bb0;

s16 MapDataGetParentId_1e7bb0(Obj_FUN_001e7bb0 *o)
{
    return o->field;
}

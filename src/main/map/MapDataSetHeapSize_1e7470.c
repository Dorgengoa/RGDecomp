#include "types.h"

/* Write the s32 at +0x14. */

typedef struct Obj_FUN_001e7470 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_001e7470;

void MapDataSetHeapSize_1e7470(Obj_FUN_001e7470 *o, s32 value)
{
    o->field = value;
}

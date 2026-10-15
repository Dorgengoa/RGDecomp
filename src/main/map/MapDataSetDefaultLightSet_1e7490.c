#include "types.h"

/* Write the u8 at +0x20. */

typedef struct Obj_FUN_001e7490 {
    u8 pad000[0x20];
    u8 field;         /* +0x20 */
} Obj_FUN_001e7490;

void MapDataSetDefaultLightSet_1e7490(Obj_FUN_001e7490 *o, u8 value)
{
    o->field = value;
}

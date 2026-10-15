#include "types.h"

/* Write the u8 at +0x22. */

typedef struct Obj_FUN_001e72c0 {
    u8 pad000[0x22];
    u8 field;         /* +0x22 */
} Obj_FUN_001e72c0;

void MapDataSetState_1e72c0(Obj_FUN_001e72c0 *o, u8 value)
{
    o->field = value;
}

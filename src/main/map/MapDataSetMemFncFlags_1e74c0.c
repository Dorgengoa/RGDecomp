#include "types.h"

/* Write the u8 at +0x25. */

typedef struct Obj_FUN_001e74c0 {
    u8 pad000[0x25];
    u8 field;         /* +0x25 */
} Obj_FUN_001e74c0;

void MapDataSetMemFncFlags_1e74c0(Obj_FUN_001e74c0 *o, u8 value)
{
    o->field = value;
}

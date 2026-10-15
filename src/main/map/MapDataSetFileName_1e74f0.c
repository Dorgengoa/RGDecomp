#include "types.h"

/* Write the s32 at +0x10. */

typedef struct Obj_FUN_001e74f0 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_001e74f0;

void MapDataSetFileName_1e74f0(Obj_FUN_001e74f0 *o, s32 value)
{
    o->field = value;
}

#include "types.h"

/* Write the s32 at +0x4. */

typedef struct Obj_FUN_00311650 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_00311650;

void NavEdgeSetFlags_311650(Obj_FUN_00311650 *o, s32 value)
{
    o->field = value;
}

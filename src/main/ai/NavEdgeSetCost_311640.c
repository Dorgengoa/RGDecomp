#include "types.h"

/* Write the f32 at +0x8. */

typedef struct Obj_FUN_00311640 {
    u8 pad000[0x8];
    f32 field;         /* +0x8 */
} Obj_FUN_00311640;

void NavEdgeSetCost_311640(Obj_FUN_00311640 *o, f32 value)
{
    o->field = value;
}

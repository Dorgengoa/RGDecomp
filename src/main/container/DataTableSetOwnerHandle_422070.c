#include "types.h"

/* Write the s32 at +0x94. */

typedef struct Obj_FUN_00422070 {
    u8 pad000[0x94];
    s32 field;         /* +0x94 */
} Obj_FUN_00422070;

void DataTableSetOwnerHandle_422070(Obj_FUN_00422070 *o, s32 value)
{
    o->field = value;
}

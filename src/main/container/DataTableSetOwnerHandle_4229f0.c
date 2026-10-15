#include "types.h"

/* Write the s32 at +0x94. */

typedef struct Obj_FUN_004229f0 {
    u8 pad000[0x94];
    s32 field;         /* +0x94 */
} Obj_FUN_004229f0;

void DataTableSetOwnerHandle_4229f0(Obj_FUN_004229f0 *o, s32 value)
{
    o->field = value;
}

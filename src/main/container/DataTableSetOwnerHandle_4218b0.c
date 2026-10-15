#include "types.h"

/* Write the s32 at +0x94. */

typedef struct Obj_FUN_004218b0 {
    u8 pad000[0x94];
    s32 field;         /* +0x94 */
} Obj_FUN_004218b0;

void DataTableSetOwnerHandle_4218b0(Obj_FUN_004218b0 *o, s32 value)
{
    o->field = value;
}

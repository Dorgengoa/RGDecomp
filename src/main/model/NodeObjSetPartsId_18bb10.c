#include "types.h"

/* Write the s32 at +0x90. */

typedef struct Obj_FUN_0018bb10 {
    u8 pad000[0x90];
    s32 field;         /* +0x90 */
} Obj_FUN_0018bb10;

void NodeObjSetPartsId_18bb10(Obj_FUN_0018bb10 *o, s32 value)
{
    o->field = value;
}

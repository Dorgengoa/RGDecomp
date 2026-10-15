#include "types.h"

/* Write the s32 at +0x8C. */

typedef struct Obj_FUN_00195140 {
    u8 pad000[0x8C];
    s32 field;         /* +0x8C */
} Obj_FUN_00195140;

void NodeObjSetNameStr_195140(Obj_FUN_00195140 *o, s32 value)
{
    o->field = value;
}

#include "types.h"

/* Write the s32 at +0xEC. */

typedef struct Obj_FUN_00351fa0 {
    u8 pad000[0xEC];
    s32 field;         /* +0xEC */
} Obj_FUN_00351fa0;

void EvObjSubSetTargetCount_351fa0(Obj_FUN_00351fa0 *o, s32 value)
{
    o->field = value;
}

#include "types.h"

/* Read the s16 at +0xEA. */

typedef struct Obj_FUN_00336020 {
    u8 pad000[0xEA];
    s16 field;         /* +0xEA */
} Obj_FUN_00336020;

s16 EvObjLiftGetTargetSetCount_336020(Obj_FUN_00336020 *o)
{
    return o->field;
}

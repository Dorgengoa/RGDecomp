#include "types.h"

/* Read the s16 at +0x18A. */

typedef struct Obj_FUN_00303fb0 {
    u8 pad000[0x18A];
    s16 field;         /* +0x18A */
} Obj_FUN_00303fb0;

s16 EvDoorObjGetRefIndexCount_303fb0(Obj_FUN_00303fb0 *o)
{
    return o->field;
}

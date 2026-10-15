#include "types.h"

/* Write the s16 at +0x18A. */

typedef struct Obj_FUN_00303fa0 {
    u8 pad000[0x18A];
    s16 field;         /* +0x18A */
} Obj_FUN_00303fa0;

void EvDoorObjSetRefIndexCount_303fa0(Obj_FUN_00303fa0 *o, s16 value)
{
    o->field = value;
}

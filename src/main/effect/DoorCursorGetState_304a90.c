#include "types.h"

/* Read the s16 at +0x1E. */

typedef struct Obj_FUN_00304a90 {
    u8 pad000[0x1E];
    s16 field;         /* +0x1E */
} Obj_FUN_00304a90;

s16 DoorCursorGetState_304a90(Obj_FUN_00304a90 *o)
{
    return o->field;
}

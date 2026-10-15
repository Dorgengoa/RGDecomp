#include "types.h"

/* Read the f32 at +0x3FC. */

typedef struct Obj_FUN_00238570 {
    u8 pad000[0x3FC];
    f32 field;         /* +0x3FC */
} Obj_FUN_00238570;

f32 CharaGetMotionFrame_238570(Obj_FUN_00238570 *o)
{
    return o->field;
}

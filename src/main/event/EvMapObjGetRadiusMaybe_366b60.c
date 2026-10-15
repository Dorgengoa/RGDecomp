#include "types.h"

/* Read the f32 at +0x324. */

typedef struct Obj_FUN_00366b60 {
    u8 pad000[0x324];
    f32 field;         /* +0x324 */
} Obj_FUN_00366b60;

f32 EvMapObjGetRadiusMaybe_366b60(Obj_FUN_00366b60 *o)
{
    return o->field;
}

#include "types.h"

/* Read the f32 at +0x328. */

typedef struct Obj_FUN_00366b50 {
    u8 pad000[0x328];
    f32 field;         /* +0x328 */
} Obj_FUN_00366b50;

f32 EvMapObjGetScatterSpeedMaybe_366b50(Obj_FUN_00366b50 *o)
{
    return o->field;
}

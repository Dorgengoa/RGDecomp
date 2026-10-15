#include "types.h"

/* Read the f32 at +0x3E8. */

typedef struct Obj_FUN_00238360 {
    u8 pad000[0x3E8];
    f32 field;         /* +0x3E8 */
} Obj_FUN_00238360;

f32 CharaGetHeadHeightMaybe_238360(Obj_FUN_00238360 *o)
{
    return o->field;
}

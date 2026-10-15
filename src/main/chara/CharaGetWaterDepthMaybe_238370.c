#include "types.h"

/* Read the f32 at +0x3E4. */

typedef struct Obj_FUN_00238370 {
    u8 pad000[0x3E4];
    f32 field;         /* +0x3E4 */
} Obj_FUN_00238370;

f32 CharaGetWaterDepthMaybe_238370(Obj_FUN_00238370 *o)
{
    return o->field;
}

#include "types.h"

/* Write the s32 at +0x214. */

typedef struct Obj_FUN_00161d40 {
    u8 pad000[0x214];
    s32 field;         /* +0x214 */
} Obj_FUN_00161d40;

void CameraSetControlFlagsMaybe_161d40(Obj_FUN_00161d40 *o, s32 value)
{
    o->field = value;
}

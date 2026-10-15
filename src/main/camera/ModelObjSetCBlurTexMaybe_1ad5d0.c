#include "types.h"

/* Write the s32 at +0x454. */

typedef struct Obj_FUN_001ad5d0 {
    u8 pad000[0x454];
    s32 field;         /* +0x454 */
} Obj_FUN_001ad5d0;

void ModelObjSetCBlurTexMaybe_1ad5d0(Obj_FUN_001ad5d0 *o, s32 value)
{
    o->field = value;
}

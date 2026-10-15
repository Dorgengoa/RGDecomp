#include "types.h"

/* Write the f32 at +0x414. */

typedef struct Obj_FUN_00238230 {
    u8 pad000[0x414];
    f32 field;         /* +0x414 */
} Obj_FUN_00238230;

void CharaSetSpeedScale_238230(Obj_FUN_00238230 *o, f32 value)
{
    o->field = value;
}

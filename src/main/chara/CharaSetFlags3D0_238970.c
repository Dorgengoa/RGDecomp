#include "types.h"

/* Write the s64 at +0x3D0. */

typedef struct Obj_FUN_00238970 {
    u8 pad000[0x3D0];
    s64 field;         /* +0x3D0 */
} Obj_FUN_00238970;

void CharaSetFlags3D0_238970(Obj_FUN_00238970 *o, s64 value)
{
    o->field = value;
}

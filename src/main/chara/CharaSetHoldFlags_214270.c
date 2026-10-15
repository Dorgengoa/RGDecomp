#include "types.h"

/* Write the s64 at +0x578. */

typedef struct Obj_FUN_00214270 {
    u8 pad000[0x578];
    s64 field;         /* +0x578 */
} Obj_FUN_00214270;

void CharaSetHoldFlags_214270(Obj_FUN_00214270 *o, s64 value)
{
    o->field = value;
}

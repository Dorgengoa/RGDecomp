#include "types.h"

/* Read the f32 at +0x24. */

typedef struct Obj_FUN_003f8c80 {
    u8 pad000[0x24];
    f32 field;         /* +0x24 */
} Obj_FUN_003f8c80;

f32 AtkPrmGetKnockbackSpeed_3f8c80(Obj_FUN_003f8c80 *o)
{
    return o->field;
}

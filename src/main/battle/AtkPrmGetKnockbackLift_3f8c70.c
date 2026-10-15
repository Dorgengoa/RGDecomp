#include "types.h"

/* Read the f32 at +0x28. */

typedef struct Obj_FUN_003f8c70 {
    u8 pad000[0x28];
    f32 field;         /* +0x28 */
} Obj_FUN_003f8c70;

f32 AtkPrmGetKnockbackLift_3f8c70(Obj_FUN_003f8c70 *o)
{
    return o->field;
}

#include "types.h"

/* Read the f32 at +0x8. */

typedef struct Obj_FUN_002e7100 {
    u8 pad000[0x8];
    f32 field;         /* +0x8 */
} Obj_FUN_002e7100;

f32 TargetRefGetRadius_2e7100(Obj_FUN_002e7100 *o)
{
    return o->field;
}

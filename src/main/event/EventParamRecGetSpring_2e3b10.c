#include "types.h"

/* Read the f32 at +0x10. */

typedef struct Obj_FUN_002e3b10 {
    u8 pad000[0x10];
    f32 field;         /* +0x10 */
} Obj_FUN_002e3b10;

f32 EventParamRecGetSpring_2e3b10(Obj_FUN_002e3b10 *o)
{
    return o->field;
}

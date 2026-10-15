#include "types.h"

/* Write the s16 at +0x8. */

typedef struct Obj_FUN_0022f1b0 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_0022f1b0;

void ActInfoEvntSetCount_22f1b0(Obj_FUN_0022f1b0 *o, s16 value)
{
    o->field = value;
}

#include "types.h"

/* Write the s16 at +0x8. */

typedef struct Obj_FUN_0022eee0 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_0022eee0;

void ActInfoWepActSetCount_22eee0(Obj_FUN_0022eee0 *o, s16 value)
{
    o->field = value;
}

#include "types.h"

/* Write the s16 at +0x8. */

typedef struct Obj_FUN_0022ec30 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_0022ec30;

void ActInfoAbltSetCount_22ec30(Obj_FUN_0022ec30 *o, s16 value)
{
    o->field = value;
}

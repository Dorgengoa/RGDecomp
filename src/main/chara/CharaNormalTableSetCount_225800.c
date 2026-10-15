#include "types.h"

/* Write the s16 at +0x2C. */

typedef struct Obj_FUN_00225800 {
    u8 pad000[0x2C];
    s16 field;         /* +0x2C */
} Obj_FUN_00225800;

void CharaNormalTableSetCount_225800(Obj_FUN_00225800 *o, s16 value)
{
    o->field = value;
}

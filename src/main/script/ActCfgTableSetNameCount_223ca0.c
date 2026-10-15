#include "types.h"

/* Write the s16 at +0x5C. */

typedef struct Obj_FUN_00223ca0 {
    u8 pad000[0x5C];
    s16 field;         /* +0x5C */
} Obj_FUN_00223ca0;

void ActCfgTableSetNameCount_223ca0(Obj_FUN_00223ca0 *o, s16 value)
{
    o->field = value;
}

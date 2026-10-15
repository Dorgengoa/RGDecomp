#include "types.h"

/* Write the s16 at +0x6C. */

typedef struct Obj_FUN_00223c20 {
    u8 pad000[0x6C];
    s16 field;         /* +0x6C */
} Obj_FUN_00223c20;

void ActCfgTableSetEfctCount_223c20(Obj_FUN_00223c20 *o, s16 value)
{
    o->field = value;
}

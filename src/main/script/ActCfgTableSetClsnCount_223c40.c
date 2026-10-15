#include "types.h"

/* Write the s16 at +0x68. */

typedef struct Obj_FUN_00223c40 {
    u8 pad000[0x68];
    s16 field;         /* +0x68 */
} Obj_FUN_00223c40;

void ActCfgTableSetClsnCount_223c40(Obj_FUN_00223c40 *o, s16 value)
{
    o->field = value;
}

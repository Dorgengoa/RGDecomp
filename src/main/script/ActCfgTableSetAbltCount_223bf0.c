#include "types.h"

/* Write the s16 at +0x72. */

typedef struct Obj_FUN_00223bf0 {
    u8 pad000[0x72];
    s16 field;         /* +0x72 */
} Obj_FUN_00223bf0;

void ActCfgTableSetAbltCount_223bf0(Obj_FUN_00223bf0 *o, s16 value)
{
    o->field = value;
}

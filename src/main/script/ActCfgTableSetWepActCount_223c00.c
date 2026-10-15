#include "types.h"

/* Write the s16 at +0x70. */

typedef struct Obj_FUN_00223c00 {
    u8 pad000[0x70];
    s16 field;         /* +0x70 */
} Obj_FUN_00223c00;

void ActCfgTableSetWepActCount_223c00(Obj_FUN_00223c00 *o, s16 value)
{
    o->field = value;
}

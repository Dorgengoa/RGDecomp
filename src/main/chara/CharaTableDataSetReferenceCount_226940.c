#include "types.h"

/* Write the s16 at +0x24. */

typedef struct Obj_FUN_00226940 {
    u8 pad000[0x24];
    s16 field;         /* +0x24 */
} Obj_FUN_00226940;

void CharaTableDataSetReferenceCount_226940(Obj_FUN_00226940 *o, s16 value)
{
    o->field = value;
}

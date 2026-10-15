#include "types.h"

/* Write the s16 at +0x30. */

typedef struct Obj_FUN_002268e0 {
    u8 pad000[0x30];
    s16 field;         /* +0x30 */
} Obj_FUN_002268e0;

void CharaTableDataSetTimePrmtCount_2268e0(Obj_FUN_002268e0 *o, s16 value)
{
    o->field = value;
}

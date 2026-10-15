#include "types.h"

/* Write the s16 at +0x32. */

typedef struct Obj_FUN_002268d0 {
    u8 pad000[0x32];
    s16 field;         /* +0x32 */
} Obj_FUN_002268d0;

void CharaTableDataSetTimeCnctCount_2268d0(Obj_FUN_002268d0 *o, s16 value)
{
    o->field = value;
}

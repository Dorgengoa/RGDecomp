#include "types.h"

/* Write the s16 at +0x2A. */

typedef struct Obj_FUN_00226910 {
    u8 pad000[0x2A];
    s16 field;         /* +0x2A */
} Obj_FUN_00226910;

void CharaTableDataSetTimeAcclCount_226910(Obj_FUN_00226910 *o, s16 value)
{
    o->field = value;
}

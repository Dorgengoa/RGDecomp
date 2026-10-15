#include "types.h"

/* Read the s32 at +0x1C. */

typedef struct Obj_FUN_00226970 {
    u8 pad000[0x1C];
    s32 field;         /* +0x1C */
} Obj_FUN_00226970;

s32 CharaTableDataGetTimePrmtList_226970(Obj_FUN_00226970 *o)
{
    return o->field;
}

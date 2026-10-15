#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_002269e0 {
    s32 field;         /* +0x00 */
} Obj_FUN_002269e0;

s32 CharaTableDataGetMotionName_2269e0(Obj_FUN_002269e0 *o)
{
    return o->field;
}

#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_003f29d0 {
    s32 field;         /* +0x00 */
} Obj_FUN_003f29d0;

void WorldDataMgrSetGameData_3f29d0(Obj_FUN_003f29d0 *o, s32 value)
{
    o->field = value;
}

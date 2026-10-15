#include "types.h"

/* Read the s32 at +0x34. */

typedef struct Obj_FUN_00234850 {
    u8 pad000[0x34];
    s32 field;         /* +0x34 */
} Obj_FUN_00234850;

s32 ActionMgrGetGlobalTable_234850(Obj_FUN_00234850 *o)
{
    return o->field;
}

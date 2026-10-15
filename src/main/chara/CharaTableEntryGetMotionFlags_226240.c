#include "types.h"

/* Read the s32 at +0x34. */

typedef struct Obj_FUN_00226240 {
    u8 pad000[0x34];
    s32 field;         /* +0x34 */
} Obj_FUN_00226240;

s32 CharaTableEntryGetMotionFlags_226240(Obj_FUN_00226240 *o)
{
    return o->field;
}

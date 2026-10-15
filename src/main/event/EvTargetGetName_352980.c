#include "types.h"

/* Read the s32 at +0x30. */

typedef struct Obj_FUN_00352980 {
    u8 pad000[0x30];
    s32 field;         /* +0x30 */
} Obj_FUN_00352980;

s32 EvTargetGetName_352980(Obj_FUN_00352980 *o)
{
    return o->field;
}

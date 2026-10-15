#include "types.h"

/* Read the s32 at +0x130. */

typedef struct Obj_FUN_00352950 {
    u8 pad000[0x130];
    s32 field;         /* +0x130 */
} Obj_FUN_00352950;

s32 EvTargetGetPointCount_352950(Obj_FUN_00352950 *o)
{
    return o->field;
}

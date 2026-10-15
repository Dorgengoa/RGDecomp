#include "types.h"

/* Read the s32 at +0x224. */

typedef struct Obj_FUN_00366ba0 {
    u8 pad000[0x224];
    s32 field;         /* +0x224 */
} Obj_FUN_00366ba0;

s32 EvMapObjGetModelName_366ba0(Obj_FUN_00366ba0 *o)
{
    return o->field;
}

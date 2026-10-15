#include "types.h"

/* Read the s32 at +0x228. */

typedef struct Obj_FUN_00366b90 {
    u8 pad000[0x228];
    s32 field;         /* +0x228 */
} Obj_FUN_00366b90;

s32 EvMapObjGetName_366b90(Obj_FUN_00366b90 *o)
{
    return o->field;
}

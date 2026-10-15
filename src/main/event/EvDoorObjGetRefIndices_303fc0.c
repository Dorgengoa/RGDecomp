#include "types.h"

/* Read the s32 at +0x184. */

typedef struct Obj_FUN_00303fc0 {
    u8 pad000[0x184];
    s32 field;         /* +0x184 */
} Obj_FUN_00303fc0;

s32 EvDoorObjGetRefIndices_303fc0(Obj_FUN_00303fc0 *o)
{
    return o->field;
}

#include "types.h"

/* Read the s32 at +0x12C. */

typedef struct Obj_FUN_00353320 {
    u8 pad000[0x12C];
    s32 field;         /* +0x12C */
} Obj_FUN_00353320;

s32 EvNodeAttachObjGetModelName_353320(Obj_FUN_00353320 *o)
{
    return o->field;
}

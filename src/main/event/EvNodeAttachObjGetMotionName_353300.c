#include "types.h"

/* Read the s32 at +0x134. */

typedef struct Obj_FUN_00353300 {
    u8 pad000[0x134];
    s32 field;         /* +0x134 */
} Obj_FUN_00353300;

s32 EvNodeAttachObjGetMotionName_353300(Obj_FUN_00353300 *o)
{
    return o->field;
}

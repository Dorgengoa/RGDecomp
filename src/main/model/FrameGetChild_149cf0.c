#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_00149cf0 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00149cf0;

s32 FrameGetChild_149cf0(Obj_FUN_00149cf0 *o)
{
    return o->field;
}

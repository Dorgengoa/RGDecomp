#include "types.h"

/* Read the s32 at +0x118. */

typedef struct Obj_FUN_002f80a0 {
    u8 pad000[0x118];
    s32 field;         /* +0x118 */
} Obj_FUN_002f80a0;

s32 EvFollowObjGetParamRec_2f80a0(Obj_FUN_002f80a0 *o)
{
    return o->field;
}

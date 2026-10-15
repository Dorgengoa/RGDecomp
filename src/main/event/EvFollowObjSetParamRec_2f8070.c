#include "types.h"

/* Write the s32 at +0x118. */

typedef struct Obj_FUN_002f8070 {
    u8 pad000[0x118];
    s32 field;         /* +0x118 */
} Obj_FUN_002f8070;

void EvFollowObjSetParamRec_2f8070(Obj_FUN_002f8070 *o, s32 value)
{
    o->field = value;
}

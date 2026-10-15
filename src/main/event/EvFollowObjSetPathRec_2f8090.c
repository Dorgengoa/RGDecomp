#include "types.h"

/* Write the s32 at +0x110. */

typedef struct Obj_FUN_002f8090 {
    u8 pad000[0x110];
    s32 field;         /* +0x110 */
} Obj_FUN_002f8090;

void EvFollowObjSetPathRec_2f8090(Obj_FUN_002f8090 *o, s32 value)
{
    o->field = value;
}

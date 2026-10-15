#include "types.h"

/* Write the s32 at +0x114. */

typedef struct Obj_FUN_002f8080 {
    u8 pad000[0x114];
    s32 field;         /* +0x114 */
} Obj_FUN_002f8080;

void EvFollowObjSetVolumeRec_2f8080(Obj_FUN_002f8080 *o, s32 value)
{
    o->field = value;
}

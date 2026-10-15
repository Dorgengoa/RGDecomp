#include "types.h"

/* Read the s32 at +0x60. */

typedef struct Obj_FUN_00336fd0 {
    u8 pad000[0x60];
    s32 field;         /* +0x60 */
} Obj_FUN_00336fd0;

s32 TargetRefPairGetRec_336fd0(Obj_FUN_00336fd0 *o)
{
    return o->field;
}

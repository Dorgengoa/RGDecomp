#include "types.h"

/* Read the s32 at +0x60. */

typedef struct Obj_FUN_00338680 {
    u8 pad000[0x60];
    s32 field;         /* +0x60 */
} Obj_FUN_00338680;

s32 TargetRefPairGetRec_338680(Obj_FUN_00338680 *o)
{
    return o->field;
}

#include "types.h"

/* Address of the sub-object at +0xE0. */

typedef struct Obj_FUN_002f80d0 {
    u8 pad000[0xE0];
    u8 sub[1];         /* +0xE0 */
} Obj_FUN_002f80d0;

void *EvFollowObjGetTargetRef_2f80d0(Obj_FUN_002f80d0 *o)
{
    return o->sub;
}

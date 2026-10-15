#include "types.h"

/* Address of the sub-object at +0x1F0. */

typedef struct Obj_FUN_0018c530 {
    u8 pad000[0x1F0];
    u8 sub[1];         /* +0x1F0 */
} Obj_FUN_0018c530;

void *ModelObjGetMotionList_18c530(Obj_FUN_0018c530 *o)
{
    return o->sub;
}

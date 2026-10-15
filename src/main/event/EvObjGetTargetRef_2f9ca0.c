#include "types.h"

/* Address of the sub-object at +0xA0. */

typedef struct Obj_FUN_002f9ca0 {
    u8 pad000[0xA0];
    u8 sub[1];         /* +0xA0 */
} Obj_FUN_002f9ca0;

void *EvObjGetTargetRef_2f9ca0(Obj_FUN_002f9ca0 *o)
{
    return o->sub;
}

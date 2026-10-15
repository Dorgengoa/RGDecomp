#include "types.h"

/* Address of the sub-object at +0xF4. */

typedef struct Obj_FUN_00353330 {
    u8 pad000[0xF4];
    u8 sub[1];         /* +0xF4 */
} Obj_FUN_00353330;

void *EvNodeAttachObjGetNodeTargetRef_353330(Obj_FUN_00353330 *o)
{
    return o->sub;
}

#include "types.h"

/* Address of the sub-object at +0x4. */

typedef struct Obj_FUN_002e70e0 {
    u8 pad000[0x4];
    u8 sub[1];         /* +0x4 */
} Obj_FUN_002e70e0;

void *TargetRefGetObjSlot_2e70e0(Obj_FUN_002e70e0 *o)
{
    return o->sub;
}

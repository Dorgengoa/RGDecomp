#include "types.h"

/* Address of the sub-object at +0x10. */

typedef struct Obj_FUN_002e70f0 {
    u8 pad000[0x10];
    u8 sub[1];         /* +0x10 */
} Obj_FUN_002e70f0;

void *TargetRefGetName_2e70f0(Obj_FUN_002e70f0 *o)
{
    return o->sub;
}

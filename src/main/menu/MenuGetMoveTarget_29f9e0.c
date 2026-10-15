#include "types.h"

/* Address of the sub-object at +0xEC. */

typedef struct Obj_FUN_0029f9e0 {
    u8 pad000[0xEC];
    u8 sub[1];         /* +0xEC */
} Obj_FUN_0029f9e0;

void *MenuGetMoveTarget_29f9e0(Obj_FUN_0029f9e0 *o)
{
    return o->sub;
}

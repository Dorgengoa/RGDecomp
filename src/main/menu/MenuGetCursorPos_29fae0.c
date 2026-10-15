#include "types.h"

/* Address of the sub-object at +0x5C. */

typedef struct Obj_FUN_0029fae0 {
    u8 pad000[0x5C];
    u8 sub[1];         /* +0x5C */
} Obj_FUN_0029fae0;

void *MenuGetCursorPos_29fae0(Obj_FUN_0029fae0 *o)
{
    return o->sub;
}

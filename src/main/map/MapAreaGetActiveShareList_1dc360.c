#include "types.h"

/* Address of the sub-object at +0x128. */

typedef struct Obj_FUN_001dc360 {
    u8 pad000[0x128];
    u8 sub[1];         /* +0x128 */
} Obj_FUN_001dc360;

void *MapAreaGetActiveShareList_1dc360(Obj_FUN_001dc360 *o)
{
    return o->sub;
}

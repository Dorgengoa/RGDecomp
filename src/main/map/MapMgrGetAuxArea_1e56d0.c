#include "types.h"

/* Address of the sub-object at +0x2058. */

typedef struct Obj_FUN_001e56d0 {
    u8 pad000[0x2058];
    u8 sub[1];         /* +0x2058 */
} Obj_FUN_001e56d0;

void *MapMgrGetAuxArea_1e56d0(Obj_FUN_001e56d0 *o)
{
    return o->sub;
}

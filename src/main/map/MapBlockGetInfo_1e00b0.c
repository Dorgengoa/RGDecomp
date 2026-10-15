#include "types.h"

/* Address of the sub-object at +0x54. */

typedef struct Obj_FUN_001e00b0 {
    u8 pad000[0x54];
    u8 sub[1];         /* +0x54 */
} Obj_FUN_001e00b0;

void *MapBlockGetInfo_1e00b0(Obj_FUN_001e00b0 *o)
{
    return o->sub;
}

#include "types.h"

/* Address of the sub-object at +0x10. */

typedef struct Obj_FUN_002243a0 {
    u8 pad000[0x10];
    u8 sub[1];         /* +0x10 */
} Obj_FUN_002243a0;

void *CharaNormalTableObjGetBody_2243a0(Obj_FUN_002243a0 *o)
{
    return o->sub;
}

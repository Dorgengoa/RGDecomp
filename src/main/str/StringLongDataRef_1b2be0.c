#include "types.h"

/* Address of the sub-object at +0x8. */

typedef struct Obj_FUN_001b2be0 {
    u8 pad000[0x8];
    u8 sub[1];         /* +0x8 */
} Obj_FUN_001b2be0;

void *StringLongDataRef_1b2be0(Obj_FUN_001b2be0 *o)
{
    return o->sub;
}

#include "types.h"

/* Address of the sub-object at +0x4. */

typedef struct Obj_FUN_001a2fc0 {
    u8 pad000[0x4];
    u8 sub[1];         /* +0x4 */
} Obj_FUN_001a2fc0;

void *StrMapGetNodeAlloc_1a2fc0(Obj_FUN_001a2fc0 *o)
{
    return o->sub;
}

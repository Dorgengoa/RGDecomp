#include "types.h"

/* Address of the sub-object at +0x1A0. */

typedef struct Obj_FUN_002db7f0 {
    u8 pad000[0x1A0];
    u8 sub[1];         /* +0x1A0 */
} Obj_FUN_002db7f0;

void *EffModelObjGetModel_2db7f0(Obj_FUN_002db7f0 *o)
{
    return o->sub;
}

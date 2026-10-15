#include "types.h"

/* Address of the sub-object at +0x3C. */

typedef struct Obj_FUN_0018bc20 {
    u8 pad000[0x3C];
    u8 sub[1];         /* +0x3C */
} Obj_FUN_0018bc20;

void *NodeGetFarClip_18bc20(Obj_FUN_0018bc20 *o)
{
    return o->sub;
}

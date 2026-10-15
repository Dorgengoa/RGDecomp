#include "types.h"

/* Address of the sub-object at +0xA8C. */

typedef struct Obj_FUN_00212500 {
    u8 pad000[0xA8C];
    u8 sub[1];         /* +0xA8C */
} Obj_FUN_00212500;

void *CharaGetPlayedMotionName_212500(Obj_FUN_00212500 *o)
{
    return o->sub;
}

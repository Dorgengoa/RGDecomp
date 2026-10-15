#include "types.h"

/* Address of the sub-object at +0x15C. */

typedef struct Obj_FUN_001601a0 {
    u8 pad000[0x15C];
    u8 sub[1];         /* +0x15C */
} Obj_FUN_001601a0;

void *CameraGetParamBlock_1601a0(Obj_FUN_001601a0 *o)
{
    return o->sub;
}

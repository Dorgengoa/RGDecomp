#include "types.h"

/* Read the s32 at +0x17BC. */

typedef struct Obj_FUN_001e6330 {
    u8 pad000[0x17BC];
    s32 field;         /* +0x17BC */
} Obj_FUN_001e6330;

s32 MapSkyGetHeap_1e6330(Obj_FUN_001e6330 *o)
{
    return o->field;
}

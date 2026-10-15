#include "types.h"

/* Read the s16 at +0x2. */

typedef struct Obj_FUN_003116f0 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_003116f0;

s16 NavEdgeGetNodeB_3116f0(Obj_FUN_003116f0 *o)
{
    return o->field;
}

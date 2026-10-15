#include "types.h"

/* Address of the sub-object at +0x30. */

typedef struct Obj_FUN_00336fe0 {
    u8 pad000[0x30];
    u8 sub[1];         /* +0x30 */
} Obj_FUN_00336fe0;

void *TargetRefPairGetSecond_336fe0(Obj_FUN_00336fe0 *o)
{
    return o->sub;
}

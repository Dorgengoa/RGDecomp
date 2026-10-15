#include "types.h"

/* Address of the sub-object at +0x870. */

typedef struct Obj_FUN_00214a00 {
    u8 pad000[0x870];
    u8 sub[1];         /* +0x870 */
} Obj_FUN_00214a00;

void *CharaGetHitInfo_214a00(Obj_FUN_00214a00 *o)
{
    return o->sub;
}

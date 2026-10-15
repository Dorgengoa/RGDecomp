#include "types.h"

/* Address of the sub-object at +0x950. */

typedef struct Obj_FUN_002149d0 {
    u8 pad000[0x950];
    u8 sub[1];         /* +0x950 */
} Obj_FUN_002149d0;

void *CharaGetSquash_2149d0(Obj_FUN_002149d0 *o)
{
    return o->sub;
}

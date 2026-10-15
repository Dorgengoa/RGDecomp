#include "types.h"

/* Address of the sub-object at +0x20. */

typedef struct Obj_FUN_00233b40 {
    u8 pad000[0x20];
    u8 sub[1];         /* +0x20 */
} Obj_FUN_00233b40;

void *ActionMgrGetCharaList_233b40(Obj_FUN_00233b40 *o)
{
    return o->sub;
}

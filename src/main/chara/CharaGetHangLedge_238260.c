#include "types.h"

/* Address of the sub-object at +0x350. */

typedef struct Obj_FUN_00238260 {
    u8 pad000[0x350];
    u8 sub[1];         /* +0x350 */
} Obj_FUN_00238260;

void *CharaGetHangLedge_238260(Obj_FUN_00238260 *o)
{
    return o->sub;
}

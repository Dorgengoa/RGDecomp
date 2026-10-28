/* rgp:protos */
#define RGP_SELF_ObjRecDefaultTexGroupMaybe_250440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x1C9. */

typedef struct Obj_FUN_00250440 {
    u8 pad000[0x1C9];
    u8 sub[1];         /* +0x1C9 */
} Obj_FUN_00250440;

void *ObjRecDefaultTexGroupMaybe_250440(Obj_FUN_00250440 *o)
{
    return o->sub;
}

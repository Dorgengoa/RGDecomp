/* rgp:protos */
#define RGP_SELF_MapNodeMoverGetNodeName_2fa790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x28. */

typedef struct Obj_FUN_002fa790 {
    u8 pad000[0x28];
    u8 sub[1];         /* +0x28 */
} Obj_FUN_002fa790;

void *MapNodeMoverGetNodeName_2fa790(Obj_FUN_002fa790 *o)
{
    return o->sub;
}

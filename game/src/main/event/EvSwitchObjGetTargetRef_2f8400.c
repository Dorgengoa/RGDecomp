/* rgp:protos */
#define RGP_SELF_EvSwitchObjGetTargetRef_2f8400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0xE0. */

typedef struct Obj_FUN_002f8400 {
    u8 pad000[0xE0];
    u8 sub[1];         /* +0xE0 */
} Obj_FUN_002f8400;

void *EvSwitchObjGetTargetRef_2f8400(Obj_FUN_002f8400 *o)
{
    return o->sub;
}

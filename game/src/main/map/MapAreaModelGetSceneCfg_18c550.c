/* rgp:protos */
#define RGP_SELF_MapAreaModelGetSceneCfg_18c550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x70. */

typedef struct Obj_FUN_0018c550 {
    u8 pad000[0x70];
    u8 sub[1];         /* +0x70 */
} Obj_FUN_0018c550;

void *MapAreaModelGetSceneCfg_18c550(Obj_FUN_0018c550 *o)
{
    return o->sub;
}

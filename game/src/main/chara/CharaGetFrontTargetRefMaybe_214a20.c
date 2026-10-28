/* rgp:protos */
#define RGP_SELF_CharaGetFrontTargetRefMaybe_214a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x9AC. */

typedef struct Obj_FUN_00214a20 {
    u8 pad000[0x9AC];
    u8 sub[1];         /* +0x9AC */
} Obj_FUN_00214a20;

void *CharaGetFrontTargetRefMaybe_214a20(Obj_FUN_00214a20 *o)
{
    return o->sub;
}

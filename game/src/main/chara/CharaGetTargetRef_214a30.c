/* rgp:protos */
#define RGP_SELF_CharaGetTargetRef_214a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x97C. */

typedef struct Obj_FUN_00214a30 {
    u8 pad000[0x97C];
    u8 sub[1];         /* +0x97C */
} Obj_FUN_00214a30;

void *CharaGetTargetRef_214a30(Obj_FUN_00214a30 *o)
{
    return o->sub;
}

/* rgp:protos */
#define RGP_SELF_CharaGetActInfo_214cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x580. */

typedef struct Obj_FUN_00214cb0 {
    u8 pad000[0x580];
    u8 sub[1];         /* +0x580 */
} Obj_FUN_00214cb0;

void *CharaGetActInfo_214cb0(Obj_FUN_00214cb0 *o)
{
    return o->sub;
}

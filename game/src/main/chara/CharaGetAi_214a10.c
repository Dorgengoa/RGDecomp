/* rgp:protos */
#define RGP_SELF_CharaGetAi_214a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x590. */

typedef struct Obj_FUN_00214a10 {
    u8 pad000[0x590];
    u8 sub[1];         /* +0x590 */
} Obj_FUN_00214a10;

void *CharaGetAi_214a10(Obj_FUN_00214a10 *o)
{
    return o->sub;
}

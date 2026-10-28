/* rgp:protos */
#define RGP_SELF_EvObjSwitchGetState_2f89e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0xE0. */

typedef struct Obj_FUN_002f89e0 {
    u8 pad000[0xE0];
    u8 field;         /* +0xE0 */
} Obj_FUN_002f89e0;

u8 EvObjSwitchGetState_2f89e0(Obj_FUN_002f89e0 *o)
{
    return o->field;
}

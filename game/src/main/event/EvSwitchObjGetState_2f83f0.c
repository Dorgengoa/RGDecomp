/* rgp:protos */
#define RGP_SELF_EvSwitchObjGetState_2f83f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x158. */

typedef struct Obj_FUN_002f83f0 {
    u8 pad000[0x158];
    u8 field;         /* +0x158 */
} Obj_FUN_002f83f0;

u8 EvSwitchObjGetState_2f83f0(Obj_FUN_002f83f0 *o)
{
    return o->field;
}

/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleGetTargetPairs_338040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x110. */

typedef struct Obj_FUN_00338040 {
    u8 pad000[0x110];
    s32 field;         /* +0x110 */
} Obj_FUN_00338040;

s32 ObjTypeVehicleGetTargetPairs_338040(Obj_FUN_00338040 *o)
{
    return o->field;
}

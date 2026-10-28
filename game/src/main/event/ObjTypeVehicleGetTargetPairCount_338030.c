/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleGetTargetPairCount_338030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x114. */

typedef struct Obj_FUN_00338030 {
    u8 pad000[0x114];
    s16 field;         /* +0x114 */
} Obj_FUN_00338030;

s16 ObjTypeVehicleGetTargetPairCount_338030(Obj_FUN_00338030 *o)
{
    return o->field;
}

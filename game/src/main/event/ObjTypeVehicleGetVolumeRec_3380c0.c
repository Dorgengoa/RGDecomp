/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleGetVolumeRec_3380c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x118. */

typedef struct Obj_FUN_003380c0 {
    u8 pad000[0x118];
    s32 field;         /* +0x118 */
} Obj_FUN_003380c0;

s32 ObjTypeVehicleGetVolumeRec_3380c0(Obj_FUN_003380c0 *o)
{
    return o->field;
}

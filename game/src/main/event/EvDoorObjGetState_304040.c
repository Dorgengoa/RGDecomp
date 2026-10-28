/* rgp:protos */
#define RGP_SELF_EvDoorObjGetState_304040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x19C. */

typedef struct Obj_FUN_00304040 {
    u8 pad000[0x19C];
    s16 field;         /* +0x19C */
} Obj_FUN_00304040;

s16 EvDoorObjGetState_304040(Obj_FUN_00304040 *o)
{
    return o->field;
}

/* rgp:protos */
#define RGP_SELF_EvDoorObjSetRefListCount_303fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x188. */

typedef struct Obj_FUN_00303fd0 {
    u8 pad000[0x188];
    s16 field;         /* +0x188 */
} Obj_FUN_00303fd0;

void EvDoorObjSetRefListCount_303fd0(Obj_FUN_00303fd0 *o, s16 value)
{
    o->field = value;
}

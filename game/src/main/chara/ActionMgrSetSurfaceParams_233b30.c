/* rgp:protos */
#define RGP_SELF_ActionMgrSetSurfaceParams_233b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x30. */

typedef struct Obj_FUN_00233b30 {
    u8 pad000[0x30];
    s32 field;         /* +0x30 */
} Obj_FUN_00233b30;

void ActionMgrSetSurfaceParams_233b30(Obj_FUN_00233b30 *o, s32 value)
{
    o->field = value;
}

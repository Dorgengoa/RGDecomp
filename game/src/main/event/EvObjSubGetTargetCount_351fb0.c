/* rgp:protos */
#define RGP_SELF_EvObjSubGetTargetCount_351fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xEC. */

typedef struct Obj_FUN_00351fb0 {
    u8 pad000[0xEC];
    s32 field;         /* +0xEC */
} Obj_FUN_00351fb0;

s32 EvObjSubGetTargetCount_351fb0(Obj_FUN_00351fb0 *o)
{
    return o->field;
}

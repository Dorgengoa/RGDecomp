/* rgp:protos */
#define RGP_SELF_AiGetTargetCharaId_2c0fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x26C. */

typedef struct Obj_FUN_002c0fd0 {
    u8 pad000[0x26C];
    s32 field;         /* +0x26C */
} Obj_FUN_002c0fd0;

s32 AiGetTargetCharaId_2c0fd0(Obj_FUN_002c0fd0 *o)
{
    return o->field;
}

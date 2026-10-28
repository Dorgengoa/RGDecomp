/* rgp:protos */
#define RGP_SELF_AiSetTargetCharaId_2c0f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x26C. */

typedef struct Obj_FUN_002c0f10 {
    u8 pad000[0x26C];
    s32 field;         /* +0x26C */
} Obj_FUN_002c0f10;

void AiSetTargetCharaId_2c0f10(Obj_FUN_002c0f10 *o, s32 value)
{
    o->field = value;
}

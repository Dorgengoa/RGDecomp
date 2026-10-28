/* rgp:protos */
#define RGP_SELF_CharaSetAreaId_213c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xA4C. */

typedef struct Obj_FUN_00213c80 {
    u8 pad000[0xA4C];
    s32 field;         /* +0xA4C */
} Obj_FUN_00213c80;

void CharaSetAreaId_213c80(Obj_FUN_00213c80 *o, s32 value)
{
    o->field = value;
}

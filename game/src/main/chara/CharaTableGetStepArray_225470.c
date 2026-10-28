/* rgp:protos */
#define RGP_SELF_CharaTableGetStepArray_225470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x2C. */

typedef struct Obj_FUN_00225470 {
    u8 pad000[0x2C];
    s32 field;         /* +0x2C */
} Obj_FUN_00225470;

s32 CharaTableGetStepArray_225470(Obj_FUN_00225470 *o)
{
    return o->field;
}

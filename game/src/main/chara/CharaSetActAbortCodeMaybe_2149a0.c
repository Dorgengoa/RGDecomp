/* rgp:protos */
#define RGP_SELF_CharaSetActAbortCodeMaybe_2149a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xA1C. */

typedef struct Obj_FUN_002149a0 {
    u8 pad000[0xA1C];
    s32 field;         /* +0xA1C */
} Obj_FUN_002149a0;

void CharaSetActAbortCodeMaybe_2149a0(Obj_FUN_002149a0 *o, s32 value)
{
    o->field = value;
}

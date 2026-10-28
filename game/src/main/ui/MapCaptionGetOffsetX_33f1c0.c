/* rgp:protos */
#define RGP_SELF_MapCaptionGetOffsetX_33f1c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x2C. */

typedef struct Obj_FUN_0033f1c0 {
    u8 pad000[0x2C];
    s32 field;         /* +0x2C */
} Obj_FUN_0033f1c0;

s32 MapCaptionGetOffsetX_33f1c0(Obj_FUN_0033f1c0 *o)
{
    return o->field;
}

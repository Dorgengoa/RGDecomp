/* rgp:protos */
#define RGP_SELF_MapCaptionSetOffsetX_33f1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x2C. */

typedef struct Obj_FUN_0033f1d0 {
    u8 pad000[0x2C];
    s32 field;         /* +0x2C */
} Obj_FUN_0033f1d0;

void MapCaptionSetOffsetX_33f1d0(Obj_FUN_0033f1d0 *o, s32 value)
{
    o->field = value;
}

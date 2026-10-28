/* rgp:protos */
#define RGP_SELF_MapCaptionGetGlyphSpacing_33f130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x3C. */

typedef struct Obj_FUN_0033f130 {
    u8 pad000[0x3C];
    s32 field;         /* +0x3C */
} Obj_FUN_0033f130;

s32 MapCaptionGetGlyphSpacing_33f130(Obj_FUN_0033f130 *o)
{
    return o->field;
}

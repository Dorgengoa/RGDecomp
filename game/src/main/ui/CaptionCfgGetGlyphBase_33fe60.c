/* rgp:protos */
#define RGP_SELF_CaptionCfgGetGlyphBase_33fe60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x4C. */

typedef struct Obj_FUN_0033fe60 {
    u8 pad000[0x4C];
    s8 field;         /* +0x4C */
} Obj_FUN_0033fe60;

s8 CaptionCfgGetGlyphBase_33fe60(Obj_FUN_0033fe60 *o)
{
    return o->field;
}

/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeGetKey_340390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00340390 {
    s32 field;         /* +0x00 */
} Obj_FUN_00340390;

s32 CaptionGlyphNodeGetKey_340390(Obj_FUN_00340390 *o)
{
    return o->field;
}

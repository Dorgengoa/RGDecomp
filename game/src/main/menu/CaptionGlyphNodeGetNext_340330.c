/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeGetNext_340330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_00340330 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00340330;

s32 CaptionGlyphNodeGetNext_340330(Obj_FUN_00340330 *o)
{
    return o->field;
}

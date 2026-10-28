/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeGetAdvance_340310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x7. */

typedef struct Obj_FUN_00340310 {
    u8 pad000[0x7];
    s8 field;         /* +0x7 */
} Obj_FUN_00340310;

s8 CaptionGlyphNodeGetAdvance_340310(Obj_FUN_00340310 *o)
{
    return o->field;
}

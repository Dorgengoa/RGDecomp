/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeGetCode_340350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x4. */

typedef struct Obj_FUN_00340350 {
    u8 pad000[0x4];
    s16 field;         /* +0x4 */
} Obj_FUN_00340350;

s16 CaptionGlyphNodeGetCode_340350(Obj_FUN_00340350 *o)
{
    return o->field;
}

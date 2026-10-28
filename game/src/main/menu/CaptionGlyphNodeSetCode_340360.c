/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeSetCode_340360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x4. */

typedef struct Obj_FUN_00340360 {
    u8 pad000[0x4];
    s16 field;         /* +0x4 */
} Obj_FUN_00340360;

void CaptionGlyphNodeSetCode_340360(Obj_FUN_00340360 *o, s16 value)
{
    o->field = value;
}

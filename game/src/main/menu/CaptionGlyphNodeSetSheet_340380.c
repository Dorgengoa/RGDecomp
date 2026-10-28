/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeSetSheet_340380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x6. */

typedef struct Obj_FUN_00340380 {
    u8 pad000[0x6];
    u8 field;         /* +0x6 */
} Obj_FUN_00340380;

void CaptionGlyphNodeSetSheet_340380(Obj_FUN_00340380 *o, u8 value)
{
    o->field = value;
}

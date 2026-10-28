/* rgp:protos */
#define RGP_SELF_CaptionGlyphNodeSetNext_340340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x8. */

typedef struct Obj_FUN_00340340 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00340340;

void CaptionGlyphNodeSetNext_340340(Obj_FUN_00340340 *o, s32 value)
{
    o->field = value;
}

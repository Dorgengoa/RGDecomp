/* rgp:protos */
#define RGP_SELF_CaptionPanelSetOffsetX_33df40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x54. */

typedef struct Obj_FUN_0033df40 {
    u8 pad000[0x54];
    s32 field;         /* +0x54 */
} Obj_FUN_0033df40;

void CaptionPanelSetOffsetX_33df40(Obj_FUN_0033df40 *o, s32 value)
{
    o->field = value;
}

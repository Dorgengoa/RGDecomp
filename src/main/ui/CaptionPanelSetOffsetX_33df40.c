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

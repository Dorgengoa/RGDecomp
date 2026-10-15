#include "types.h"

/* Write the u8 at +0x7. */

typedef struct Obj_FUN_00340320 {
    u8 pad000[0x7];
    u8 field;         /* +0x7 */
} Obj_FUN_00340320;

void CaptionGlyphNodeSetAdvance_340320(Obj_FUN_00340320 *o, u8 value)
{
    o->field = value;
}

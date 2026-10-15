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

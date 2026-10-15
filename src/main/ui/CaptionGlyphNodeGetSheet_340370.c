#include "types.h"

/* Read the s8 at +0x6. */

typedef struct Obj_FUN_00340370 {
    u8 pad000[0x6];
    s8 field;         /* +0x6 */
} Obj_FUN_00340370;

s8 CaptionGlyphNodeGetSheet_340370(Obj_FUN_00340370 *o)
{
    return o->field;
}

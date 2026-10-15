#include "types.h"

/* Write the s16 at +0x6. */

typedef struct Obj_FUN_0026dd40 {
    u8 pad000[0x6];
    s16 field;         /* +0x6 */
} Obj_FUN_0026dd40;

void TextStyleSetAlpha_26dd40(Obj_FUN_0026dd40 *o, s16 value)
{
    o->field = value;
}

#include "types.h"

/* Write the u8 at +0x1. */

typedef struct Obj_FUN_0026edf0 {
    u8 pad000[0x1];
    u8 field;         /* +0x1 */
} Obj_FUN_0026edf0;

void TextStyleSetFontType_26edf0(Obj_FUN_0026edf0 *o, u8 value)
{
    o->field = value;
}

#include "types.h"

/* Write the s16 at +0x34. */

typedef struct Obj_FUN_0026e330 {
    u8 pad000[0x34];
    s16 field;         /* +0x34 */
} Obj_FUN_0026e330;

void TextStyleSetGradientMode_26e330(Obj_FUN_0026e330 *o, s16 value)
{
    o->field = value;
}

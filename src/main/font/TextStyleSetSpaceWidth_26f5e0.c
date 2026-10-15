#include "types.h"

/* Write the u8 at +0x5. */

typedef struct Obj_FUN_0026f5e0 {
    u8 pad000[0x5];
    u8 field;         /* +0x5 */
} Obj_FUN_0026f5e0;

void TextStyleSetSpaceWidth_26f5e0(Obj_FUN_0026f5e0 *o, u8 value)
{
    o->field = value;
}

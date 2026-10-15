#include "types.h"

/* Read the s8 at +0x1. */

typedef struct Obj_FUN_0026ede0 {
    u8 pad000[0x1];
    s8 field;         /* +0x1 */
} Obj_FUN_0026ede0;

s8 TextStyleGetFontType_26ede0(Obj_FUN_0026ede0 *o)
{
    return o->field;
}

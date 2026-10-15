#include "types.h"

/* Read the s16 at +0x36. */

typedef struct Obj_FUN_0026e410 {
    u8 pad000[0x36];
    s16 field;         /* +0x36 */
} Obj_FUN_0026e410;

s16 TextStyleGetZEnable_26e410(Obj_FUN_0026e410 *o)
{
    return o->field;
}

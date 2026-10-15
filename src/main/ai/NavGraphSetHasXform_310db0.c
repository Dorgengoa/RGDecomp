#include "types.h"

/* Write the u8 at +0x113. */

typedef struct Obj_FUN_00310db0 {
    u8 pad000[0x113];
    u8 field;         /* +0x113 */
} Obj_FUN_00310db0;

void NavGraphSetHasXform_310db0(Obj_FUN_00310db0 *o, u8 value)
{
    o->field = value;
}

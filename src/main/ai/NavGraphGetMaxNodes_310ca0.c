#include "types.h"

/* Read the u16 at +0xAA. */

typedef struct Obj_FUN_00310ca0 {
    u8 pad000[0xAA];
    u16 field;         /* +0xAA */
} Obj_FUN_00310ca0;

u16 NavGraphGetMaxNodes_310ca0(Obj_FUN_00310ca0 *o)
{
    return o->field;
}

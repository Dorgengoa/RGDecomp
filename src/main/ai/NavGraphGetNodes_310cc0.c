#include "types.h"

/* Read the s32 at +0xA0. */

typedef struct Obj_FUN_00310cc0 {
    u8 pad000[0xA0];
    s32 field;         /* +0xA0 */
} Obj_FUN_00310cc0;

s32 NavGraphGetNodes_310cc0(Obj_FUN_00310cc0 *o)
{
    return o->field;
}

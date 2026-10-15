#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_00178110 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_00178110;

s32 ScreenFadeBlockIsDone_178110(Obj_FUN_00178110 *o)
{
    return o->field;
}

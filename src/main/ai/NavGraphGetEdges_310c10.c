#include "types.h"

/* Read the s32 at +0xB0. */

typedef struct Obj_FUN_00310c10 {
    u8 pad000[0xB0];
    s32 field;         /* +0xB0 */
} Obj_FUN_00310c10;

s32 NavGraphGetEdges_310c10(Obj_FUN_00310c10 *o)
{
    return o->field;
}
